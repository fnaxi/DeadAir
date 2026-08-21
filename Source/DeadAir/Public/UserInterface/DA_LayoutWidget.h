// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "DA_LayoutWidget.generated.h"

/**
 * The primary game UI layout of your game.
 * This widget class represents how to the layout, push and display all layers of the UI for a single player.
 */
UCLASS()
class DEADAIR_API UDA_LayoutWidget : public UCommonUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UCommonActivatableWidgetStack> GameLayer_Stack;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonActivatableWidgetStack> GameMenu_Stack;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonActivatableWidgetStack> Menu_Stack;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonActivatableWidgetStack> Modal_Stack;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UDA_InventoryWidget> InventoryWidgetClass;
	
protected:
	virtual void NativeOnInitialized() override;
};
