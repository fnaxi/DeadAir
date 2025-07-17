// CopyRight Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DA_GameHUD.generated.h"

/**
 * 
 */
UCLASS()
class DEADAIR_API ADA_GameHUD : public AHUD
{
	GENERATED_BODY()

public:
	// Sets default values
	ADA_GameHUD();
	
	virtual void DrawHUD() override;

protected:
	// Calls when game starts or when spawned
	virtual void BeginPlay() override;

	/** Player HUD widget class. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DA|UserInterface")
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass;
	
private:
	/** Draw the crosshair. */
	void DrawCrosshair();
	
};
