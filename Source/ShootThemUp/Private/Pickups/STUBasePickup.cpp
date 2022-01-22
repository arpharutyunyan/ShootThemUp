// Shoot Them Up Game, All Rights Reserved


#include "Pickups/STUBasePickup.h"
#include <Components/SphereComponent.h>
#include <Kismet/GameplayStatics.h>
#include <Sound/SoundCue.h>

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

	GenerateRotationYaw();
}

void ASTUBasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalRotation(FRotator(0.0f, RotationYaw, 0.0f));

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

	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ASTUBasePickup::Respawn, RespawnTime);

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), PickupTakenSound, GetActorLocation());
}

void ASTUBasePickup::Respawn()
{
	GenerateRotationYaw();
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

void ASTUBasePickup::GenerateRotationYaw()
{
	const auto Diraction = FMath::RandBool() ? 1.0f : -1.0f;
	RotationYaw = FMath::RandRange(1.0f, 2.0f) * Diraction;
}

bool ASTUBasePickup::CouldBeTaken() const
{
	return GetWorldTimerManager().IsTimerActive(RespawnTimerHandle);

}
