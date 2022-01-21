// Shoot Them Up Game, All Rights Reserved


#include "Player/STUCharacter.h"

#include <Components/STUCharacterMovementComponent.h>
#include <Components/STUHealthComponent.h>
#include <Components/TextRenderComponent.h>
#include <Components/STUWeaponComponent.h>
#include <Components/CapsuleComponent.h>
#include <GameFramework/Controller.h>
#include <Sound/SoundCue.h>
#include <Kismet/GameplayStatics.h>

DEFINE_LOG_CATEGORY_STATIC(CharacterLog, All, All)

ASTUCharacter::ASTUCharacter(const FObjectInitializer& InitObj)
	: Super(InitObj.SetDefaultSubobjectClass<USTUCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<USTUHealthComponent>("HealthComponent");
	
	WeaponComponent = CreateDefaultSubobject<USTUWeaponComponent>("WeaponComponent");
}

void ASTUCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(HealthComponent);
	check(GetCharacterMovement());
	check(GetMesh());

	OnHealthChanged(HealthComponent->GetHealth(), 0.0f);
	HealthComponent->OnDeath.AddUObject(this, &ASTUCharacter::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &ASTUCharacter::OnHealthChanged);

	LandedDelegate.AddDynamic(this, &ASTUCharacter::OnGroundLanded);

}

void ASTUCharacter::OnHealthChanged(float Health, float HealthDelta)
{
	
}

void ASTUCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ASTUCharacter::IsRunning() const
{
	return false;
}

float ASTUCharacter::GetMovementDiraction() const
{
	if (GetVelocity().IsZero()) return 0.0f;

	const auto VelocityNorm = GetVelocity().GetSafeNormal();
	const auto AngleBetween = FMath::Acos(FVector::DotProduct(VelocityNorm, GetActorForwardVector()));
	const auto CrossProduct = FVector::CrossProduct(VelocityNorm, GetActorForwardVector());
	const auto Degrees = FMath::RadiansToDegrees(AngleBetween);

	return CrossProduct.IsZero() ? Degrees : FMath::Sign(CrossProduct.Z);
}

void ASTUCharacter::OnDeath()
{
	UE_LOG(CharacterLog, Display, TEXT("Actor %s is dead."), *GetName());
	// PlayAnimMontage(DeathAnimMontage);

	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(5.0f);

	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	WeaponComponent->StopFire();

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), DeathSound, GetActorLocation());
}


void ASTUCharacter::OnGroundLanded(const FHitResult& Hit)
{
	const auto FallVelocityZ = -GetVelocity().Z;
	UE_LOG(CharacterLog, Display, TEXT("On Landed %f "), FallVelocityZ);

	if (FallVelocityZ < LandedDamageVelocity.X) return;

	const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);
	UE_LOG(CharacterLog, Display, TEXT("FinalDamage %f "), FinalDamage);
	TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);
}

void ASTUCharacter::SetPlayerColor(const FLinearColor& Color)
{
	const auto MaterialInst = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);
	if (!MaterialInst) return;

	MaterialInst->SetVectorParameterValue(MaterialColorName, Color);
}

