// CopyRight Dead Air Game. All Rights Reserved.


#include "DA_GameModeBase.h"

#include "DA_PlayerCharacter.h"
#include "DA_PlayerController.h"
#include "UserInterface/DA_GameHUD.h"

// Sets default values
ADA_GameModeBase::ADA_GameModeBase()
{
	DefaultPawnClass = ADA_PlayerCharacter::StaticClass();
	PlayerControllerClass = ADA_PlayerController::StaticClass();
	HUDClass = ADA_GameHUD::StaticClass();
}

void ADA_GameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnDebugTool();
}

void ADA_GameModeBase::SpawnDebugTool()
{
#if DA_WITH_DEBUG_TOOL
	K2_SpawnDebugTool();
#endif
}

