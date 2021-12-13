// Shoot Them Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUWeaponComponent.generated.h"

class ASTUBaseWeapon;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	USTUWeaponComponent();

	void StartFire();
	void StopFire();
	void NextWeapon();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		TArray<TSubclassOf<ASTUBaseWeapon>> WeaponClasses;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		FName WeaponEquipSocketName = "WeaponSocket";

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		FName WeaponArmorySocketName = "ArmorySocket";

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
		UAnimMontage* EquipAnimMontage;

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);


private:
	UPROPERTY()
		ASTUBaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
		TArray<ASTUBaseWeapon*> Weapons;

	void SpawnWeapons();
	void AttachWeaponToSocket(ASTUBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);
	void EquipWeapon(int32 WeaponIndex);
	void PlayeAnimMontage(UAnimMontage* Animation);
	void InitAnimations();
	void OnEquipFinished(USkeletalMeshComponent* MeshComp);
	bool CanFire() const;
	bool CanEquip() const;
	
	int32 CurrentWeaponIndex = 0;
	bool EquipAnimInProgress = false;
};
