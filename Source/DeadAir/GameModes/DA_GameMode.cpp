// CopyRight © Dead Air Game. All Rights Reserved.


#include "GameModes/DA_GameMode.h"

#include "Character/DA_Character.h"
#include "Player/DA_PlayerController.h"

ADA_GameMode::ADA_GameMode()
{
	DefaultPawnClass = ADA_Character::StaticClass();
	PlayerControllerClass = ADA_PlayerController::StaticClass();
}

