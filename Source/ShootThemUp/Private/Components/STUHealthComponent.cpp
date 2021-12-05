// Shoot Them Up Game, All Rights Reserved


#include "Components/STUHealthComponent.h"
#include <GameFramework/Actor.h>
#include <STUDamageFireType.h>
#include <STUDamageIceType.h>

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)

USTUHealthComponent::USTUHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}



void USTUHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamage);
	}
}


void USTUHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	Health -= Damage;
	UE_LOG(LogHealthComponent, Display, TEXT("Damage: %f"), Damage);

	if (DamageType)
	{
		if (DamageType->IsA<USTUDamageFireType>())
		{
			UE_LOG(LogHealthComponent, Display, TEXT("Soooooo hoooot !!!"));
		}
		else if (DamageType->IsA<USTUDamageIceType>())
		{
			UE_LOG(LogHealthComponent, Display, TEXT("Soooooo coooold !!!"));
		}
	}
}