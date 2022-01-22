// Shoot Them Up Game, All Rights Reserved


#include "Weapon/Components/STUWeaponVFXComponent.h"
#include <NiagaraFunctionLibrary.h>
#include <PhysicalMaterials/PhysicalMaterial.h>
#include <Kismet/GameplayStatics.h>
#include <Sound/SoundCue.h>
#include <Components/DecalComponent.h>

USTUWeaponVFXComponent::USTUWeaponVFXComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void USTUWeaponVFXComponent::PlayImpactFX(const FHitResult& Hit)
{
	auto ImpactData = DefaultImpactData;

	if (Hit.PhysMaterial.IsValid())
	{
		const auto PhysMat = Hit.PhysMaterial.Get();
		if (ImpactDataMap.Contains(PhysMat))
		{
			ImpactData = ImpactDataMap[PhysMat];
		}
	}


	// Niagara
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),						//
												   ImpactData.NiagaraEffect,		//
												   Hit.ImpactPoint,					//
												   Hit.ImpactNormal.Rotation());

	//Decal

	auto DecalComponent = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), //
										   ImpactData.DecalData.Material, //
										   ImpactData.DecalData.Size, //
										   Hit.ImpactPoint, //
										   Hit.ImpactNormal.Rotation());

	if (DecalComponent)
	{
		DecalComponent->SetFadeOut(ImpactData.DecalData.LifeTime, ImpactData.DecalData.FadeOutTime);
	}

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactData.Sound, Hit.ImpactPoint);
}

