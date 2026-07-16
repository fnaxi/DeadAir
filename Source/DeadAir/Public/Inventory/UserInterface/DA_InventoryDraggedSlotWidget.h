// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inventory/DA_InventoryComponent.h"
#include "DA_InventoryDraggedSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class DEADAIR_API UDA_InventoryDraggedSlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UDA_InventoryDraggedSlotWidget(const FObjectInitializer& ObjectInitializer);


	UFUNCTION(BlueprintCallable, Category = "DraggedSlot")
	void SetData(const FDA_InventorySlot NewData, float InCellSize);

	UFUNCTION(BlueprintImplementableEvent, Category = "DraggedSlot")
	void OnDataReceived();

	UFUNCTION(BlueprintImplementableEvent, Category = "DraggedSlot")
	void SetSlotSize(float Size);

	UFUNCTION(BlueprintImplementableEvent, Category = "DraggedSlot")
	void OnItemRotated();


	UPROPERTY(BlueprintReadOnly, Category = "DraggedSlot")
	FDA_InventorySlot SlotData;

	UPROPERTY(BlueprintReadOnly, Category = "DraggedSlot")
	float CellSize;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "DraggedSlot")
	UDA_InventoryItem* CopyItem;
};
