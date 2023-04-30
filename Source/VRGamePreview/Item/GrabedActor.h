#pragma once

#include "CoreMinimal.h"
#include "MainTypes.h"
#include "VRGamePreview/Game/GrabInterface.h"
#include "GameFramework/Actor.h"
#include "MotionControllerComponent.h"
#include "GrabedActor.generated.h"




UCLASS()
class VRGAMEPREVIEW_API AGrabedActor : public AActor, public IGrabInterface
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	class USceneComponent* SceneComponent = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	class UStaticMeshComponent* StaticMesh = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	class USkeletalMeshComponent* SkeletalMesh = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	class UBoxComponent* InteractBox = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	EAttachState AttachState = EAttachState::Free;

protected:
	AGrabedActor();
	
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

	void MeshInit();

public:
	
	/*UFUNCTION(BlueprintCallable)
	void Fire();
	*/

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "GrabInterface")
	void Grab(class UMotionControllerComponent* MotionController);

	virtual void Grab_Implementation(class UMotionControllerComponent* MotionController) override;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "GrabInterface")
	void Drop(class UMotionControllerComponent* MotionController);

	virtual void Drop_Implementation(class UMotionControllerComponent* MotionController) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "GrabInterface")
	void TriggerPressed (class UMotionControllerComponent* MotionController);

	virtual void TriggerPressed_Implementation(class UMotionControllerComponent* MotionController) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "GrabInterface")
	void TriggerReleased(class UMotionControllerComponent* MotionController);

	virtual void TriggerReleased_Implementation(class UMotionControllerComponent* MotionController) override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grab")
	bool bUsing = false;

	bool bSimulatePhysics;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Grab")
	class UMotionControllerComponent* CurrentMotionController;

};

