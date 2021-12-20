// Shoot Them Up Game, All Rights Reserved


#include "Weapon/Components/STUWeaponVFXComponent.h"
#include <NiagaraFunctionLibrary.h>

USTUWeaponVFXComponent::USTUWeaponVFXComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void USTUWeaponVFXComponent::PlayImpactFX(const FHitResult& Hit)
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Effect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
}

