// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DA_InventoryItemWidgetBase.h"
#include "DA_InventoryItemWidget.generated.h"

DECLARE_DELEGATE(FDA_OnSlotDragSignature)

/**
 * 
 */
UCLASS(Abstract)
class DEADAIR_API UDA_InventoryItemWidget : public UDA_InventoryItemWidgetBase
{
	GENERATED_BODY()

public:
	FDA_OnSlotDragSignature OnBeginDrag;
	FDA_OnSlotDragSignature OnEndDrag;
	
	virtual void InitializeSlot(UDA_InventoryItem* InItem, const float InSize) override;
	
protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UDA_InventoryItemTooltip> TooltipClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UDA_InventoryDraggedItemWidget> DraggedItemWidgetClass;
	
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
};
