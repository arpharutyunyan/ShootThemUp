// Shoot Them Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Player/STUCharacter.h"
#include "STUAICharacter.generated.h"

class UBehaviorTree;

UCLASS()
class SHOOTTHEMUP_API ASTUAICharacter : public ASTUCharacter
{
	GENERATED_BODY()
	
public:
	ASTUAICharacter(const FObjectInitializer& InitObj);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
		UBehaviorTree* BehaviorTreeAsset;

protected:

	virtual void OnDeath() override;
};
