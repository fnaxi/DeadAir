// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inventory/DA_InventoryTypes.h"
#include "DA_InventoryDraggedSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class DEADAIR_API UDA_InventoryDraggedSlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	FDA_InventorySlot SlotData; // todo: Make private

	/*UPROPERTY()
	TWeakObjectPtr<UDA_InventoryItem> CopyItem;*/
	
	void SetData(const FDA_InventorySlot& InData, float InCellSize);

protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class USizeBox> Box;

private:
	float CellSize;
	
	void SetSlotSize(float Size) const;
	void OnItemRotated();
};
