// CopyRight Dead Air Game. All Rights Reserved.


#include "UserInterface/DA_GameHUD.h"

#include "Blueprint/UserWidget.h"
#include "Engine/Canvas.h"

// Sets default values
ADA_GameHUD::ADA_GameHUD()
{
}

void ADA_GameHUD::DrawHUD()
{
	Super::DrawHUD();

	DrawCrosshair();
}

void ADA_GameHUD::BeginPlay()
{
	Super::BeginPlay();

	if (UUserWidget* PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass))
	{
		PlayerHUDWidget->AddToViewport();
	}
}

void ADA_GameHUD::DrawCrosshair()
{
	const TInterval<float> Center(Canvas->SizeX * 0.5, Canvas->SizeY * 0.5);
	
	constexpr float HalfLineSize = 10.0f;
	constexpr float LineThickness = 2.0f;
	const FLinearColor LineColor = FLinearColor(105, 105, 105);

	DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, LineColor, LineThickness);
	DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, LineColor, LineThickness);
}

