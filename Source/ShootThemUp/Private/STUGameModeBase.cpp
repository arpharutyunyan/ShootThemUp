// Shoot Them Up Game, All Rights Reserved


#include "STUGameModeBase.h"
#include "Player/STUPlayerController.h"
#include "Player/STUCharacter.h"

ASTUGameModeBase::ASTUGameModeBase() 
{
	DefaultPawnClass = ASTUCharacter::StaticClass();
	PlayerControllerClass = ASTUPlayerController::StaticClass();
}

