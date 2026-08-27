// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PrimaryGameLayout.h"
#include "DA_LayoutWidget.generated.h"

/**
 *
 */
UCLASS(Abstract)
class DEADAIR_API UDA_LayoutWidget : public UPrimaryGameLayout
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonActivatableWidgetStack> Game_Stack;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonActivatableWidgetStack> GameMenu_Stack;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonActivatableWidgetStack> Menu_Stack;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonActivatableWidgetStack> Modal_Stack;
	
	virtual void NativeOnInitialized() override;
};
