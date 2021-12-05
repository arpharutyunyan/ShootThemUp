// Shoot Them Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUDevDamageActor.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUDevDamageActor : public AActor
{
	GENERATED_BODY()

public:

	ASTUDevDamageActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
		USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Radius = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Damage = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool DoFullDamage = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FColor SphereColor = FColor::Red;

protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;


};
