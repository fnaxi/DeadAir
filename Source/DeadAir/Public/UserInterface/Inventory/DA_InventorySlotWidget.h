// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inventory/DA_InventoryTypes.h"
#include "DA_InventorySlotWidget.generated.h"

class UDA_InventoryGridWidget;

/**
 * 
 */
UCLASS()
class DEADAIR_API UDA_InventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TWeakObjectPtr<UDA_InventoryGridWidget> Grid;

	void SetData(const FDA_InventorySlot& InSlotData, UDA_InventoryGridWidget* InGrid, const float InSize);

	FORCEINLINE	FDA_InventorySlot GetSlotData() const { return SlotData; }

protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class USizeBox> Box;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UDA_InventoryDraggedSlotWidget> DraggedSlotWidgetClass;
	
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

private:
	FDA_InventorySlot SlotData;
	
	void DropItem() const;
	void SetSlotSize(float Size) const;
};
