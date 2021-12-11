// Shoot Them Up Game, All Rights Reserved


#include "Components/STUWeaponComponent.h"
#include <Weapon/STUBaseWeapon.h>
#include <GameFramework/Character.h>


USTUWeaponComponent::USTUWeaponComponent()
{
	
	PrimaryComponentTick.bCanEverTick = false;

}


void USTUWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();

}

void USTUWeaponComponent::SpawnWeapon()
{
	if (!GetWorld()) return;
	
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	CurrantWeapon = GetWorld()->SpawnActor<ASTUBaseWeapon>(WeaponClass);
	if (!CurrantWeapon) return;
	
	FAttachmentTransformRules AttachmentRule(EAttachmentRule::SnapToTarget, false);
	CurrantWeapon->AttachToComponent(Character->GetMesh(), AttachmentRule, WeaponAttachPointName);
	CurrantWeapon->SetOwner(Character);
}

void USTUWeaponComponent::StartFire()
{
	if (!CurrantWeapon) return;
	CurrantWeapon->StartFire();
}

void USTUWeaponComponent::StopFire()
{
	if (!CurrantWeapon) return;
	CurrantWeapon->StopFire();
}
