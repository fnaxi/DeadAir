// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

#include "CommonActivatableWidget.h"
#include "DA_ActivatableWidget.generated.h"

struct FUIInputConfig;

UENUM(BlueprintType)
enum class EDA_WidgetInputMode : uint8
{
	Default,
	GameAndMenu,
	Game,
	Menu
};

// An activatable widget that automatically drives the desired input config when activated
UCLASS(Abstract, Blueprintable)
class UDA_ActivatableWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	UDA_ActivatableWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) { }

	//~UCommonActivatableWidget interface
	virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override;
	//~End of UCommonActivatableWidget interface

protected:
	/** The desired input mode to use while this UI is activated, for example do you want key presses to still reach the game/player controller? */
	UPROPERTY(EditDefaultsOnly, Category = Input)
	EDA_WidgetInputMode InputConfig = EDA_WidgetInputMode::Default;

	/** The desired mouse behavior when the game gets input. */
	UPROPERTY(EditDefaultsOnly, Category = Input)
	EMouseCaptureMode GameMouseCaptureMode = EMouseCaptureMode::CapturePermanently;
};
