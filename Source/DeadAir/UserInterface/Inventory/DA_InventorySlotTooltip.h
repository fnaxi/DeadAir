// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DA_InventorySlotTooltip.generated.h"

struct FDA_InventorySlot;

/**
 * 
 */
UCLASS(Abstract)
class DEADAIR_API UDA_InventorySlotTooltip : public UUserWidget
{
	GENERATED_BODY()

public:
	void InitializeTooltip(const FDA_InventorySlot& InSlot);
	
protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UCommonTextBlock> NameText;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> DescriptionText;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> WeightText;
};
