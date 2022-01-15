// Shoot Them Up Game, All Rights Reserved


#include "Menu/STUMenuGameModeBase.h"
#include <Menu/STUMenuPlayerController.h>
#include <Menu/UI/STUMenuHUD.h>

ASTUMenuGameModeBase::ASTUMenuGameModeBase()
{
	HUDClass = ASTUMenuHUD::StaticClass();
	PlayerControllerClass = ASTUMenuPlayerController::StaticClass();
}