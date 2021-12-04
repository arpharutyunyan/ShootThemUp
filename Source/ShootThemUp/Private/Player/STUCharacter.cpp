// Shoot Them Up Game, All Rights Reserved


#include "Player/STUCharacter.h"
#include <Camera/CameraComponent.h>
#include <Components/InputComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <Components/STUCharacterMovementComponent.h>

ASTUCharacter::ASTUCharacter(const FObjectInitializer& InitObj) 
	: Super(InitObj.SetDefaultSubobjectClass<USTUCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void ASTUCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void ASTUCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASTUCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (PlayerInputComponent)
	{
		PlayerInputComponent->BindAxis("MoveForward", this, &ASTUCharacter::MoveForward);
		PlayerInputComponent->BindAxis("MoveRight", this, &ASTUCharacter::MoveRight);
		PlayerInputComponent->BindAxis("LookUp", this, &ASTUCharacter::AddControllerPitchInput);
		PlayerInputComponent->BindAxis("TurnAround", this, &ASTUCharacter::AddControllerYawInput);
		PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASTUCharacter::Jump);
		PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASTUCharacter::OnStartRunning);
		PlayerInputComponent->BindAction("Run", IE_Released, this, &ASTUCharacter::OnStopRuning);
	}


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

