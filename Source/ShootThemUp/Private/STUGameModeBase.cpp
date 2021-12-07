// Shoot Them Up Game, All Rights Reserved


#include "STUGameModeBase.h"
#include "Player/STUPlayerController.h"
#include "Player/STUCharacter.h"
#include "UI/STUGameHUD.h"

ASTUGameModeBase::ASTUGameModeBase() 
{
	DefaultPawnClass = ASTUCharacter::StaticClass();
	PlayerControllerClass = ASTUPlayerController::StaticClass();
	HUDClass = ASTUGameHUD::StaticClass();
}

