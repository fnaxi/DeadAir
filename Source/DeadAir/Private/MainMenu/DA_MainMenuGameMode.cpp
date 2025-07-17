// CopyRight Dead Air Game. All Rights Reserved.


#include "MainMenu/DA_MainMenuGameMode.h"

#include "MainMenu/DA_MainMenuHUD.h"

// Sets default values
ADA_MainMenuGameMode::ADA_MainMenuGameMode()
{
	HUDClass = ADA_MainMenuHUD::StaticClass();
}

// Called when the game starts or when spawned
void ADA_MainMenuGameMode::BeginPlay()
{
	Super::BeginPlay();
}

