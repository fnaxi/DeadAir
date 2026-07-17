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
UCLASS(PrioritizeCategories="Slot")
class DEADAIR_API UDA_InventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(Transient, BlueprintReadOnly, Category = "Slot")
	FDA_InventorySlot SlotData;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "Slot")
	UDA_InventoryGridWidget* ParentWidget;

	UFUNCTION(BlueprintCallable, Category = "Slot")
	void SetData(const FDA_InventorySlot& NewData, UDA_InventoryGridWidget* NewParentWidget);

	UFUNCTION(BlueprintImplementableEvent, Category = "Slot")
	void OnDataReceived();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Slot")
	void SetSlotSize(float Size);

	UFUNCTION(BlueprintImplementableEvent, Category = "Slot")
	void SetSlotColor(const FSlateBrush& Brush);

	virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
};
