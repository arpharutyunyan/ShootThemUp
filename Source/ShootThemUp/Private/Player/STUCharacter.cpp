// Shoot Them Up Game, All Rights Reserved


#include "Player/STUCharacter.h"
#include <Camera/CameraComponent.h>
#include <Components/InputComponent.h>
#include <GameFramework/SpringArmComponent.h>

ASTUCharacter::ASTUCharacter()
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
	}


}

void ASTUCharacter::MoveForward(float Amount)
{
	AddMovementInput(GetActorForwardVector(), Amount);
}

void ASTUCharacter::MoveRight(float Amount)
{
	AddMovementInput(GetActorRightVector(), Amount);
}


