// Shoot Them Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ASTUProjectile();

	void SetShotDiraction(const FVector& Diraction) { ShotDiraction = Diraction; }

protected:

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		USphereComponent* CollisionComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		UProjectileMovementComponent* MovementComponent;
	
	virtual void BeginPlay() override;

private:
	FVector ShotDiraction;
};
