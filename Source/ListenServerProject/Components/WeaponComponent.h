#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Misc/Enums.h"
#include "WeaponComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWeaponTypeChanged, EWeaponType, PrevType, EWeaponType, NewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LISTENSERVERPROJECT_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Settings")
	//TArray<TSubclassOf<class AWeapon>> WeaponClass;
	TArray<TSubclassOf<class AWeapon>> WeaponClass;

public:
	FORCEINLINE bool IsUnarmedMode() { return Type == EWeaponType::Max; }
	FORCEINLINE bool IsGunMode() { return Type == EWeaponType::Gun; }


public:	
	UWeaponComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


public:
	void Begin_Fire();
	void End_Fire();

public:
	void SetGunMode();

private:
	void SetMode(EWeaponType InType);
	void ChangeType(EWeaponType InType);

	void SetCurrentWeapon(AWeapon* NewWeapon);

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
		class AWeapon* GetCurrentWeapon();

public:
	EWeaponType Type = EWeaponType::Max;

public:
	FWeaponTypeChanged OnWeaponTypeChange;

private:
	ACharacter* Owner;
	AWeapon* Weapon;
	TArray<class AWeapon*> Weapons;

};
