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
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UCanvasPanel> SlotCanvas;
	
	UPROPERTY(BlueprintReadOnly)
	FDA_InventorySlot SlotData;

	UPROPERTY(BlueprintReadOnly)
	float CellSize;

	UPROPERTY(Transient, BlueprintReadOnly)
	UDA_InventoryItem* CopyItem;
	
	UFUNCTION(BlueprintCallable)
	void SetData(const FDA_InventorySlot NewData, float InCellSize);

	void SetSlotSize(float Size);
	void OnItemRotated();
};
