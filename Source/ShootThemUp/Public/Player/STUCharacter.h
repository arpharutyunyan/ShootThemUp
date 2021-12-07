// Shoot Them Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STUCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USTUHealthComponent;
class UTextRenderComponent;
class ASTUBaseWeapon;

UCLASS()
class SHOOTTHEMUP_API ASTUCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	ASTUCharacter(const FObjectInitializer& InitObj);

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		USTUHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UTextRenderComponent* HelthTextComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
		UAnimMontage* DeathAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		FVector2D LandedDamageVelocity = FVector2D(900.0f, 1200.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		FVector2D LandedDamage = FVector2D(10.0f, 100.0f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		TSubclassOf<ASTUBaseWeapon> WeaponClass;

	virtual void BeginPlay() override;


public:

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
		bool IsRunning() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
		float GetMovementDiraction() const;

private:
	UFUNCTION()
		void OnGroundLanded(const FHitResult& Hit);

	bool WhantsToRun = false;
	bool IsMovingForward = false;

	void MoveForward(float Amount);
	void MoveRight(float Amount);

	void OnStartRunning();
	void OnStopRuning();

	void OnDeath();

	void OnHealthChanged(float Health);

	void SpawnWeapon();

};
