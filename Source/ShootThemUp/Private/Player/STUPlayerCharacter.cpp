// Shoot Them Up Game, All Rights Reserved


#include "Player/STUPlayerCharacter.h"
#include <Camera/CameraComponent.h>
#include <Components/InputComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <Components/STUWeaponComponent.h>
#include <Components/SphereComponent.h>
#include <Components/CapsuleComponent.h>

ASTUPlayerCharacter::ASTUPlayerCharacter(const FObjectInitializer& InitObj): Super(InitObj)
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SocketOffset = FVector(0.0f, 100.0f, 80.0f);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	CameraCollisionComponent = CreateDefaultSubobject<USphereComponent>("CameraCollisionComponent");
	CameraCollisionComponent->SetupAttachment(CameraComponent);
	CameraCollisionComponent->SetSphereRadius(10.0f);
	CameraCollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

}

void ASTUPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(CameraCollisionComponent);

	CameraCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ASTUPlayerCharacter::OnComponentBeginOverlap);
	CameraCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ASTUPlayerCharacter::OnComponentEndOverlap);
}

void ASTUPlayerCharacter::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
												  int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckCameraOverlap();
}

void ASTUPlayerCharacter::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
												int32 OtherBodyIndex)
{
	CheckCameraOverlap();
}

void ASTUPlayerCharacter::CheckCameraOverlap()
{
	const auto HideMesh = CameraCollisionComponent->IsOverlappingComponent(GetCapsuleComponent());
	GetMesh()->SetOwnerNoSee(HideMesh);

	TArray<USceneComponent*> MeshChildren;
	GetMesh()->GetChildrenComponents(true, MeshChildren);

	for (auto MeshChild : MeshChildren)
	{
		const auto MeshChildGeometry = Cast<UPrimitiveComponent>(MeshChild);
		if (MeshChildGeometry)
		{
			MeshChildGeometry->SetOwnerNoSee(HideMesh);
		}
	}
}

void ASTUPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	check(WeaponComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASTUPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASTUPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ASTUPlayerCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &ASTUPlayerCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASTUPlayerCharacter::Jump);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASTUPlayerCharacter::OnStartRunning);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ASTUPlayerCharacter::OnStopRuning);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &USTUWeaponComponent::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &USTUWeaponComponent::StopFire);
	PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &USTUWeaponComponent::NextWeapon);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &USTUWeaponComponent::Reload);
	
	DECLARE_DELEGATE_OneParam(FZoomInputSignaure, bool);
	
	PlayerInputComponent->BindAction<FZoomInputSignaure>("Zoom", IE_Pressed, WeaponComponent, &USTUWeaponComponent::Zoom, true);
	PlayerInputComponent->BindAction<FZoomInputSignaure>("Zoom", IE_Released, WeaponComponent, &USTUWeaponComponent::Zoom, false);
}

void ASTUPlayerCharacter::MoveForward(float Amount)
{
	IsMovingForward = Amount > 0.0f;

	if (Amount == 0.0f) return;
	AddMovementInput(GetActorForwardVector(), Amount);
}

void ASTUPlayerCharacter::MoveRight(float Amount)
{
	if (Amount == 0.0f) return;
	AddMovementInput(GetActorRightVector(), Amount);
}

void ASTUPlayerCharacter::OnStartRunning()
{
	WhantsToRun = true;
}

void ASTUPlayerCharacter::OnStopRuning()
{
	WhantsToRun = false;
}

bool ASTUPlayerCharacter::IsRunning() const
{
	return WhantsToRun && IsMovingForward && !GetVelocity().IsZero();
}

void ASTUPlayerCharacter::OnDeath()
{
	Super::OnDeath();

	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
}