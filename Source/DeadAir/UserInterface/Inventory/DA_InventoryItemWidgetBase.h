// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "DA_InventoryItemWidgetBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DEADAIR_API UDA_InventoryItemWidgetBase : public UCommonUserWidget
{
	GENERATED_BODY()

public:
	virtual void InitializeSlot(class UDA_InventoryItem* InItem, const float InSize);

	FORCEINLINE	UDA_InventoryItem* GetItem() const { return Item; }
	
protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class USizeBox> Box;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UImage> Icon;
	
	UPROPERTY()
	TObjectPtr<UDA_InventoryItem> Item;

	void SetSlotSize(float Size) const;
	void ChangeIcon(const FIntPoint& Coordinates, const FIntPoint& Size);
};
