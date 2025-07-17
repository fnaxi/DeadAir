// CopyRight Dead Air Game. All Rights Reserved.


#include "MainMenu/DA_MainMenuHUD.h"

#include "Blueprint/UserWidget.h"

// Sets default values
ADA_MainMenuHUD::ADA_MainMenuHUD()
{
}

// Called when the game starts or when spawned
void ADA_MainMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	if (UUserWidget* MainWidget = CreateWidget<UUserWidget>(GetWorld(), MainWidgetClass))
	{
		MainWidget->AddToViewport();
	}
}

void ADA_MainMenuHUD::DrawHUD()
{
	Super::DrawHUD();
}

