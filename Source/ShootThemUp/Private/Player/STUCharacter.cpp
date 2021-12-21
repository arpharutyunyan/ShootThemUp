// Shoot Them Up Game, All Rights Reserved


#include "Player/STUCharacter.h"
#include <Camera/CameraComponent.h>
#include <Components/InputComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <Components/STUCharacterMovementComponent.h>
#include <Components/STUHealthComponent.h>
#include <Components/TextRenderComponent.h>
#include <Components/STUWeaponComponent.h>
#include <Components/CapsuleComponent.h>
#include <GameFramework/Controller.h>


DEFINE_LOG_CATEGORY_STATIC(CharacterLog, All, All)

ASTUCharacter::ASTUCharacter(const FObjectInitializer& InitObj)
	: Super(InitObj.SetDefaultSubobjectClass<USTUCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SocketOffset = FVector(0.0f, 100.0f, 80.0f);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	HealthComponent = CreateDefaultSubobject<USTUHealthComponent>("HealthComponent");
	HelthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HelthTextComponent");
	HelthTextComponent->SetupAttachment(GetRootComponent());
	HelthTextComponent->SetOwnerNoSee(true);

	WeaponComponent = CreateDefaultSubobject<USTUWeaponComponent>("WeaponComponent");
}

void ASTUCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(HealthComponent);
	check(HelthTextComponent);
	check(GetCharacterMovement());
	check(GetMesh());

	OnHealthChanged(HealthComponent->GetHealth());
	HealthComponent->OnDeath.AddUObject(this, &ASTUCharacter::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &ASTUCharacter::OnHealthChanged);

	LandedDelegate.AddDynamic(this, &ASTUCharacter::OnGroundLanded);

}

void ASTUCharacter::OnHealthChanged(float Health)
{
	HelthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}

void ASTUCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASTUCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	check(WeaponComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASTUCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASTUCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ASTUCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &ASTUCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASTUCharacter::Jump);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASTUCharacter::OnStartRunning);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ASTUCharacter::OnStopRuning);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &USTUWeaponComponent::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &USTUWeaponComponent::StopFire);
	PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &USTUWeaponComponent::NextWeapon);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &USTUWeaponComponent::Reload);
}

void ASTUCharacter::MoveForward(float Amount)
{
	IsMovingForward = Amount > 0.0f;

	if (Amount == 0.0f) return;
	AddMovementInput(GetActorForwardVector(), Amount);
}

void ASTUCharacter::MoveRight(float Amount)
{
	if (Amount == 0.0f) return;
	AddMovementInput(GetActorRightVector(), Amount);
}

void ASTUCharacter::OnStartRunning()
{
	WhantsToRun = true;
}

void ASTUCharacter::OnStopRuning()
{
	WhantsToRun = false;
}

bool ASTUCharacter::IsRunning() const
{
	return WhantsToRun && IsMovingForward && !GetVelocity().IsZero();
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
	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}

	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	WeaponComponent->StopFire();

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);
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

