// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DA_InventoryGridWidget.generated.h"

class UDA_InventoryComponent;
class UDA_InventoryCellWidget;
class UDA_InventorySlotWidget;

/**
 * 
 */
UCLASS(Abstract)
class DEADAIR_API UDA_InventoryGridWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/** Returns index of cell widget in cells widgets array from the specified cell coordinates. -1 if none found. */
	int32 GetCellIndex(const FIntPoint& InCoordinates) const;

	/** Reset all grid cells to their default color. */
	void ResetCellsToDefaultColor();

	void ChangeSlotsLayer(int32 Layer);
	
	virtual void NativeOnInitialized() override;
	
	FORCEINLINE TArray<TObjectPtr<UDA_InventoryCellWidget>> GetCellWidgets() const { return CellWidgets; }
	FORCEINLINE TArray<TObjectPtr<UDA_InventorySlotWidget>> GetSlotWidgets() const { return SlotWidgets; }
	
protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UGridPanel> Grid;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDA_InventoryCellWidget> CellWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDA_InventorySlotWidget> SlotWidgetClass;

private:
	UPROPERTY()
	TArray<TObjectPtr<UDA_InventoryCellWidget>> CellWidgets;

	UPROPERTY()
	TArray<TObjectPtr<UDA_InventorySlotWidget>> SlotWidgets;
	
	UPROPERTY()
	TWeakObjectPtr<UDA_InventoryComponent> Inventory;
	
	void CreateCells();
	void CreateSlots();
	
	void OnCellCreated(UDA_InventoryCellWidget* Widget) const;
	
	void OnSlotCreated(UDA_InventorySlotWidget* Widget) const;
	void OnSlotRemoved(UDA_InventorySlotWidget* Widget) const;
	
	void OnInventoryUpdated();
};
