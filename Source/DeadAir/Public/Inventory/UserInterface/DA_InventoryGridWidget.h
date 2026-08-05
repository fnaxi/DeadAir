// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DA_InventoryGridWidget.generated.h"

struct FDA_Point2D;
class UDA_InventoryComponent;
class UDA_InventoryCellWidget;
class UDA_InventorySlotWidget;

/**
 * 
 */
UCLASS()
class DEADAIR_API UDA_InventoryGridWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	TArray<UDA_InventoryCellWidget*> CellsWidgets; // TODO(DA): private?

	UPROPERTY(BlueprintReadOnly)
	TArray<UDA_InventorySlotWidget*> SlotsWidgets;
	
	void SetData(UDA_InventoryComponent* NewInventory);

	/** Returns index of cell widget in cells widgets array from the specified cell coordinates. -1 if none found. */
	int32 GetCellIndex(const FDA_Point2D& InCoordinates);
	
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UGridPanel> Grid;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UDA_InventoryCellWidget> CellWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UDA_InventorySlotWidget> SlotWidgetClass;

	UPROPERTY(BlueprintReadOnly)
	UDA_InventoryComponent* Inventory;

private:
	void OnDataReceived();
	void OnPrePopulateData();

	void OnCellCreated(UDA_InventoryCellWidget* Widget);
	
	void OnSlotCreated(UDA_InventorySlotWidget* Widget);
	void OnSlotRemoved(UDA_InventorySlotWidget* Widget);
	
	void OnInventoryUpdated();
};
