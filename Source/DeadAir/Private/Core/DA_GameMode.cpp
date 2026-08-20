// CopyRight © Dead Air Game. All Rights Reserved.


#include "Core/DA_GameMode.h"

#include "Core/DA_Character.h"
#include "Core/DA_PlayerController.h"
#include "UserInterface/DA_HUD.h"

ADA_GameMode::ADA_GameMode()
{
	DefaultPawnClass = ADA_Character::StaticClass();
	PlayerControllerClass = ADA_PlayerController::StaticClass();
	HUDClass = ADA_HUD::StaticClass();
}

