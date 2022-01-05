// Shoot Them Up Game, All Rights Reserved


#include "STUGameModeBase.h"
#include "Player/STUPlayerController.h"
#include "Player/STUCharacter.h"
#include "UI/STUGameHUD.h"
#include <AIController.h>

ASTUGameModeBase::ASTUGameModeBase() 
{
	DefaultPawnClass = ASTUCharacter::StaticClass();
	PlayerControllerClass = ASTUPlayerController::StaticClass();
	HUDClass = ASTUGameHUD::StaticClass();
}

void ASTUGameModeBase::StartPlay()
{
	Super::StartPlay();

	SpawnBots();
}

void ASTUGameModeBase::SpawnBots()
{
	if (!GetWorld()) return;

	for (int32 i = 0; i < GameData.PlayersNum - 1; ++i)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		const auto STUNewAIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
		RestartPlayer(STUNewAIController);
	}
}

UClass* ASTUGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (InController && InController->IsA<AAIController>())
	{
		return AIPawnClass;
	}

	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

