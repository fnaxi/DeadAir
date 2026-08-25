// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Inventory/DA_InventoryTypes.h"
#include "DA_InventorySlotWidgetBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DEADAIR_API UDA_InventorySlotWidgetBase : public UCommonUserWidget
{
	GENERATED_BODY()

public:
	virtual void InitializeSlot(const FDA_InventorySlot& InSlotData, const float InSize);

	FORCEINLINE	FDA_InventorySlot GetSlotData() const { return SlotData; }
	
protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class USizeBox> Box;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UImage> Icon;
	
	UPROPERTY()
	FDA_InventorySlot SlotData;

	void SetSlotSize(float Size) const;
	void ChangeIcon(const FIntPoint& Coordinates, const FIntPoint& Size);
};
