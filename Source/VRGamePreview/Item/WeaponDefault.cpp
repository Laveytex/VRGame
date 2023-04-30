// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponDefault.h"

#include "Clip.h"
#include "VRGamePreview/Game/MainGameInstance.h"
#include "NiagaraFunctionLibrary.h"
#include "ProjectileDefault.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/StaticMeshActor.h"
#include "Haptics/HapticFeedbackEffect_Base.h"
#include "XRMotionControllerBase.h"
#include "IXRTrackingSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AWeaponDefault::AWeaponDefault()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
	InteractBox->SetBoxExtent(FVector(10));
	InteractBox->SetSimulatePhysics(true);
	InteractBox->SetHiddenInGame(false);

	StaticMesh->SetCollisionProfileName(TEXT("NoCollision"));
	
	SkeletalMesh->SetCollisionProfileName(TEXT("NoCollision"));


	ShootLocation = CreateDefaultSubobject<UArrowComponent>(TEXT("ShootLocation"));
	ShootLocation->SetArrowColor(FColor::Red);
	ShootLocation->SetupAttachment(SkeletalMesh);

	ShellSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("SleevBullet point"));
	ShellSpawnPoint->SetArrowColor(FColor::Green);
	ShellSpawnPoint->SetupAttachment(SkeletalMesh);

	ClipSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("ClipPoint"));
	ClipSpawnPoint->SetArrowColor(FColor::Yellow);
	ClipSpawnPoint->SetupAttachment(SkeletalMesh);

	ClipSlot = CreateDefaultSubobject<UBoxComponent>(TEXT("ClipSlotComponent"));
	ClipSlot->SetCollisionProfileName(TEXT("OverlapAll"));
	ClipSlot->SetHiddenInGame(false);
	ClipSlot->SetBoxExtent(FVector(5));
	ClipSlot->SetupAttachment(ClipSpawnPoint);

	ClipSlot->OnComponentBeginOverlap.AddDynamic(this, &AWeaponDefault::ClipCollisionBoxHit);
}

// Called when the game starts or when spawned
void AWeaponDefault::BeginPlay()
{
	Super::BeginPlay();
	bSimulatePhysics = InteractBox->IsSimulatingPhysics();
	
	InitWeapon(InitWeaponName);	
}

void AWeaponDefault::ShellDrop()
{
	InitDropMesh(WeaponSetting.ShellDrop.DropMesh, ShellSpawnPoint, WeaponSetting.ShellDrop.DropMeshOffset,
		WeaponSetting.ShellDrop.DropMeshImpulseDirection, WeaponSetting.ShellDrop.ImpulseRandomDispersion,
		WeaponSetting.ShellDrop.PowerImpulse, WeaponSetting.ShellDrop.CustomMass);
}

void AWeaponDefault::ClipDrop()
{
	InitDropMesh(WeaponSetting.ClipDrop.DropMesh, ClipSpawnPoint, WeaponSetting.ClipDrop.DropMeshOffset,
		WeaponSetting.ClipDrop.DropMeshImpulseDirection, WeaponSetting.ClipDrop.ImpulseRandomDispersion,
		WeaponSetting.ClipDrop.PowerImpulse, WeaponSetting.ClipDrop.CustomMass);
}

void AWeaponDefault::InitDropMesh(UStaticMesh* DropMesh, UArrowComponent* ArrowComponent, FTransform Offset,
	FVector DropImpulsDirection,float ImpulsRandomDispersion, float PowerImpuls, float CustormMass)
{
	FTransform Transform;

	FVector locDirection = ArrowComponent->GetComponentLocation();
	Transform.SetLocation(locDirection);
	Transform.SetRotation(ArrowComponent->GetComponentRotation().Quaternion() + Offset.Rotator().Quaternion());

	AStaticMeshActor* NewActor = nullptr;
	
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	SpawnParameters.Owner = GetOwner();
	SpawnParameters.Instigator = GetInstigator();
	
	NewActor = (GetWorld()->SpawnActor<AStaticMeshActor>
		(AStaticMeshActor::StaticClass(), Transform.GetLocation(),
			Transform.GetRotation().Rotator(), SpawnParameters));

	if(NewActor && NewActor->GetStaticMeshComponent())
	{
		
		NewActor->GetStaticMeshComponent()->SetRelativeScale3D(Offset.GetScale3D());
		NewActor->GetStaticMeshComponent()->SetCollisionResponseToChannel
			(ECollisionChannel::ECC_Pawn, ECR_Ignore);
		NewActor->GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
		NewActor->GetStaticMeshComponent()->SetStaticMesh(DropMesh);
		NewActor->GetStaticMeshComponent()->SetSimulatePhysics(true);
		
		if (CustormMass > 0.0f)
		{
			NewActor->GetStaticMeshComponent()->SetMassOverrideInKg(NAME_None, CustormMass, true);
		}

		//**Repair impuls
		//***Add Direction
		
		FVector finDirection;
		finDirection = ArrowComponent->GetForwardVector();
		NewActor->GetStaticMeshComponent()->AddImpulse(finDirection * PowerImpuls);
		
		if (!FMath::IsNearlyZero(ImpulsRandomDispersion))
			{
				finDirection += UKismetMathLibrary::RandomUnitVectorInConeInDegrees
			(locDirection, ImpulsRandomDispersion);
					//UKismetMathLibrary::RandomUnitVectorInConeInDegrees
			
				//finDirection.GetSafeNormal(0.0001f);
				NewActor->GetStaticMeshComponent()->AddImpulse(finDirection * PowerImpuls);
			}
	}
}

void AWeaponDefault::ClipCollisionBoxHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResul)
{
	if (ClipEmpty == true)
	{
		if (OtherActor && OtherActor->IsA<AClip>())
		{
			ClipEmpty = false;
			ClipSpawn = false;
			SetWeaponRound(myWeaponInfo.MaxRound);
			OtherActor->Destroy();
		}
	}
}

// Called every frame
void AWeaponDefault::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FireTick(DeltaTime);
	ClipCheck();
}

void AWeaponDefault::FireTick(float DeltaTime)
{
	if (GetWeaponRound() > 0)
	{
		if (WeaponFiring)
			if (FireTimer < 0.f)
			{
				
				Fire();
				if(WeaponSetting.isSingleShoot)
				{
					SetWeaponStateFire(false);
				}
			}
			else
				FireTimer -=DeltaTime;
	}
	else
	{
		ClipEmpty = true;
	}
}

void AWeaponDefault::ClipCheck()
{
	if (ClipEmpty && ClipSpawn == false)
	{
		ClipDrop();
		ClipSpawn = true;
	}
}

void AWeaponDefault::TriggerPressed_Implementation(UMotionControllerComponent* MotionController)
{
	SetWeaponStateFire(true);
}

void AWeaponDefault::TriggerReleased_Implementation(UMotionControllerComponent* MotionController)
{
	SetWeaponStateFire(false);
}

void AWeaponDefault::SetWeaponStateFire(bool bIsFire)
{
		if (bIsFire)
		{
			WeaponFiring = bIsFire;
		}
		else
		{
			WeaponFiring = bIsFire;
			FireTimer = 0.01f;
		}		
}

void AWeaponDefault::InitWeapon(FName IDWeaponName)
{
	UMainGameInstance* myGI = Cast<UMainGameInstance>(GetGameInstance());
	
	if (myGI)
	{
		if(myGI->GetWeaponInfoByName(IDWeaponName, myWeaponInfo))
		{
			WeaponSetting = myWeaponInfo;
			SetWeaponRound(myWeaponInfo.MaxRound);
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("myGI not Find"));
	}
}


void AWeaponDefault::Fire()
{
	FireTimer = WeaponSetting.RateOfFire;
	if(ShootLocation)
	{
		FVector SpawnLocation = ShootLocation->GetComponentLocation();
		FRotator SpawnRotation = ShootLocation->GetComponentRotation();

		FProjectileInfo ProjectileInfo;
		ProjectileInfo = GetProjectile();
		
		WeaponInfo.Round--;
		
		if (ProjectileInfo.Projectile)
		{
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			SpawnParameters.Owner = GetOwner();
			SpawnParameters.Instigator = GetInstigator();

			AProjectileDefault* myProjectile = Cast<AProjectileDefault>
			(GetWorld()->SpawnActor(ProjectileInfo.Projectile, &SpawnLocation, &SpawnRotation, SpawnParameters));
			if(myProjectile)
			{
				myProjectile->InitProjectile(WeaponSetting.ProjectileSetting);
			}
		}
		
		ShellDrop();
		
		if(WeaponSetting.SoundFireWeapon)
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), WeaponSetting.SoundFireWeapon,
			ShootLocation->GetComponentLocation());
		
		if (WeaponSetting.EffectFireWeaponNi)
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), WeaponSetting.EffectFireWeaponNi,
				ShootLocation->GetComponentLocation(), ShootLocation->GetComponentRotation());
	}
}

FProjectileInfo AWeaponDefault::GetProjectile()
{
	return  WeaponSetting.ProjectileSetting;
}

int32 AWeaponDefault::GetWeaponRound()
{
	return WeaponInfo.Round;
}

int32 AWeaponDefault::SetWeaponRound(int RoundToSet)
{
	return WeaponInfo.Round = RoundToSet;
}

