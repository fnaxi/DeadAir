// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DA_InventoryItemTooltip.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DEADAIR_API UDA_InventoryItemTooltip : public UUserWidget
{
	GENERATED_BODY()

public:
	void InitializeTooltip(const class UDA_InventoryItem* InItem);
	
protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UCommonTextBlock> NameText;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> DescriptionText;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> WeightText;
};
