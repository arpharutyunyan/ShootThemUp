// Shoot Them Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class USTUWeaponVFXComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUProjectile : public AActor
{
	GENERATED_BODY()

public:

	ASTUProjectile();

	void SetShotDiraction(const FVector& Diraction) { ShotDiraction = Diraction; }

protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UProjectileMovementComponent* MovementComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		float DamageRadius = 200.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		float DamageAmount = 50.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		bool DoFullDamage = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		float LifeSeconds = 5.0f;

	UPROPERTY(VisibleAnywhere, Category = "VFX")
		USTUWeaponVFXComponent* WeaponVFXComponent;

	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
						 const FHitResult& Hit );

	AController* GetController() const;


	FVector ShotDiraction;
};
