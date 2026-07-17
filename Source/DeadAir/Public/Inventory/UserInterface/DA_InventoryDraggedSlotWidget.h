// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inventory/DA_InventoryTypes.h"
#include "DA_InventoryDraggedSlotWidget.generated.h"

/**
 * 
 */
UCLASS(PrioritizeCategories="DraggedSlot")
class DEADAIR_API UDA_InventoryDraggedSlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "DraggedSlot")
	FDA_InventorySlot SlotData;

	UPROPERTY(BlueprintReadOnly, Category = "DraggedSlot")
	float CellSize;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "DraggedSlot")
	UDA_InventoryItem* CopyItem;
	
	UFUNCTION(BlueprintCallable, Category = "DraggedSlot")
	void SetData(const FDA_InventorySlot NewData, float InCellSize);

	UFUNCTION(BlueprintImplementableEvent, Category = "DraggedSlot")
	void OnDataReceived();

	UFUNCTION(BlueprintImplementableEvent, Category = "DraggedSlot")
	void SetSlotSize(float Size);

	UFUNCTION(BlueprintImplementableEvent, Category = "DraggedSlot")
	void OnItemRotated();
};
