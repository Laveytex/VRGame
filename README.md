# VRGame

Комментарий по коду:

Переделаю!!!

GrabedActor, Clip, WeaponDefault - должды иметь общий родительский класс. Поторапился, разволновался, сделал глупость.

Нужно реализовать:

1. HealthComponent - компонент жизней. Применение урона к Овнеру, Событие смерти, Событие личения.
2. TraceShoot - стральба трейсами.


В превью мною реализовано:

1. Подбор объектов.
2. Таблица свойство.
3. Система оружия.
4. Перезарядка оружия.
5. Отображение кол-ва патронов.
6. Боты.
7. Респавно игрока.
8. Отображение попадания.
9. Снаряды.
10. Нанесение урона.

Краткое описание:

* Создана таблица Table (С++):
Таблица содержет в себе свойства объектов:
Свойства оружия, Свойства снарядов, Свойства поднимаемых предметов,
Своство выпадающих предметов, Факстические свойства оружия.

* Подбор объектов (все в c++):
Реализовано через интерфейс GrabInterface.
Из таблицы подстягивается состояние Подбора объекта. Можно взять предмет свободно или он приснапится к контроллеру.
Есть события: Взять, Отпустить, Контроль нажания курка, 
Контроль отжатия курка.

* Система снарядов (С++):
Projectile Default - основной класс оружия, в него подтягиваются свойства с Таблица -> Cостояния снаряда
 + свойства внутри объекта ProjectileDefault (стоит перенести в таблицу).
Настраиваемые свойства: Эффект следа снаряда, Максимальный урон, Минимальный урон, Скорость, Влияние гравитации, Меш снаряда.
Для реализации: Собздать BP объект класса ProjectileDefault, указать ссылку на него в строке оружия.

* Система оружия (С++ + отображение патронов BP):
WeaponDefault - основной класс оружия, в него подтягиваются свойства с Таблица -> Cостояния оружия.
Настраиваемые свойства: Скорость стрельбы, Максимальное количество патронов, Переключение темба стрельбы, 
Звук выстрела, Эффект выстрела, Объект магазина патронов, Объект гильз, Тип снаряда.
Отображение кол-ва патронов пока сделал в BP через TextRender для теста. 
Для перезарядки имеется коллизия с евентом оверлапа.
Для реализации: Создать BP объект класса WeaponDefault. В Его свойствах указать из таблицы Table имя оружия,
свойства которого мы хотим добавить текущему оружию. 

* Перезарядка оружия (С++):
Объект Clip - является условным магазином для оружия. Если в оружие нет патронов, 
нужно поднести одъект Clip к слоту ClipSlot на оружие, значение патронов выставится в максимальное у оружия.

* Боты (С++):
Сделан простенький класс Character и AIController.
При старте игры контроллер создает случайную точку в радиусе и бежит к ней. На определенном расстоянии до нее он создает новую.
Спавн ботов на уровне сделал через актора Кнопку и Точки спавка расположенные на карте.

* Отображение урона (С++ + BP):
При попадании снаряда по боту в пн прозванивается событие ApplyDamage. К нему привязан спавн актора с виджетом над головой бота. В Виджет передается урон. 

* Нанесение урона (С++)Ж
Реализовано через интерфейс DamageTakerInterface.

* Респавн игрока (BP):
Сделал Область удаления павна. Персонаж оправляет событие в GameMod для респавна Игрока. 
