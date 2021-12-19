// Shoot Them Up Game, All Rights Reserved


#include "Pickups/STUBasePickup.h"
#include <Components/SphereComponent.h>

DEFINE_LOG_CATEGORY_STATIC(LogBasePickup, All, All);

ASTUBasePickup::ASTUBasePickup()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	CollosionComponent = CreateDefaultSubobject<USphereComponent>("CollosionComponent");
	CollosionComponent->InitSphereRadius(50.0f);
	CollosionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollosionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetRootComponent(CollosionComponent);
}


void ASTUBasePickup::BeginPlay()
{
	Super::BeginPlay();
	
	check(CollosionComponent);
}

void ASTUBasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASTUBasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	const auto Pawn = Cast<APawn>(OtherActor);
	if (GivePickupTo(Pawn))
	{
		PickupWasTaken();
	}
	
}

void ASTUBasePickup::PickupWasTaken()
{
	CollosionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	if (GetRootComponent())
	{
		GetRootComponent()->SetVisibility(false, true);
	}

	FTimerHandle RespawnTimerHandle;
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ASTUBasePickup::Respawn, RespawnTime);

}

void ASTUBasePickup::Respawn()
{
	CollosionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	if (GetRootComponent())
	{
		GetRootComponent()->SetVisibility(true, true);
	}
}

bool ASTUBasePickup::GivePickupTo(APawn* PlayerPawn)
{
	return false;
}

