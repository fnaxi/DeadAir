// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DA_InventorySlotWidgetBase.h"
#include "DA_InventorySlotWidget.generated.h"

class UDA_InventoryGridWidget;

/**
 * 
 */
UCLASS()
class DEADAIR_API UDA_InventorySlotWidget : public UDA_InventorySlotWidgetBase
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TWeakObjectPtr<class UDA_InventoryGridWidget> Grid;

	virtual void SetData(const FDA_InventorySlot& InSlotData, const float InSize) override;
	
protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UDA_InventorySlotTooltip> TooltipClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UDA_InventoryDraggedSlotWidget> DraggedSlotWidgetClass;

	virtual void NativeConstruct() override;
	
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

private:
	void DropItem() const;
};
