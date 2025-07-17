// CopyRight Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DA_MainMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class DEADAIR_API ADA_MainMenuHUD : public AHUD
{
	GENERATED_BODY()

public:
	// Sets default values
	ADA_MainMenuHUD();
	
	virtual void DrawHUD() override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	/** Main widget class for the main menu. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DA|UserInterface")
	TSubclassOf<UUserWidget> MainWidgetClass;
	
};
