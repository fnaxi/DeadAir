// CopyRight © Dead Air Game. All Rights Reserved.


#include "Core/DA_GameMode.h"

#include "Core/DA_Character.h"
#include "Core/DA_PlayerController.h"

ADA_GameMode::ADA_GameMode()
{
	DefaultPawnClass = ADA_Character::StaticClass();
	PlayerControllerClass = ADA_PlayerController::StaticClass();
}

