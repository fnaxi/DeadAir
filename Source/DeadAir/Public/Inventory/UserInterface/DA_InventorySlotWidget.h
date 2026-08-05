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
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UDA_InventoryDraggedSlotWidget> DraggedSlotWidgetClass;
	
	UPROPERTY(Transient, BlueprintReadOnly)
	FDA_InventorySlot SlotData;

	UPROPERTY(Transient, BlueprintReadOnly)
	UDA_InventoryGridWidget* ParentWidget;

	UFUNCTION(BlueprintCallable)
	void SetData(const FDA_InventorySlot& NewData, UDA_InventoryGridWidget* NewParentWidget);

	UFUNCTION(BlueprintCallable)
	void SetSlotSize(float Size);

	UFUNCTION(BlueprintImplementableEvent)
	void SetSlotColor(const FSlateBrush& Brush);

protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UCanvasPanel> SlotCanvas;
	
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	
};
