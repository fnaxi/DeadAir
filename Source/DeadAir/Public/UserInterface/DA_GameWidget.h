// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "DA_GameWidget.generated.h"

/**
 * 
 */
UCLASS()
class DEADAIR_API UDA_GameWidget : public UCommonUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UDA_InventoryWidget> InventoryWidget;
};
