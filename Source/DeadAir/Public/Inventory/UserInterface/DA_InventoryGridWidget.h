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
	UFUNCTION(BlueprintCallable, Category = "Grid")
	void SetData(UDA_InventoryComponent* NewInventory);

	UFUNCTION(BlueprintImplementableEvent, Category = "Grid")
	void OnDataReceived();

	UFUNCTION(BlueprintImplementableEvent, Category = "Grid")
	void OnPrePopulateData();

	UFUNCTION(BlueprintImplementableEvent, Category = "Grid")
	void OnCellCreated(UDA_InventoryCellWidget* Widget);

	UFUNCTION(BlueprintImplementableEvent, Category = "Grid")
	void OnSlotCreated(UDA_InventorySlotWidget* Widget);

	UFUNCTION(BlueprintImplementableEvent, Category = "Grid")
	void OnSlotRemoved(UDA_InventorySlotWidget* Widget);

	UFUNCTION(BlueprintImplementableEvent, Category = "Grid")
	void OnInventoryUpdated();
	
	void NativeOnDataReceived();
	void NativeOnInventoryUpdated();

	/** Returns index of cell widget in cells widgets array from the specified cell coordinates. -1 if none found. */
	int32 GetCellIndex(const FDA_Point2D& InCoordinates);
	
	UPROPERTY(BlueprintReadOnly, Category = "Grid")
	UDA_InventoryComponent* Inventory;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Grid")
	TSubclassOf<UDA_InventoryCellWidget> CellWidgetClass;

	UPROPERTY(BlueprintReadOnly, Category = "Grid")
	TArray<UDA_InventoryCellWidget*> CellsWidgets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Grid")
	TSubclassOf<UDA_InventorySlotWidget> SlotWidgetClass;

	UPROPERTY(BlueprintReadOnly, Category = "Grid")
	TArray<UDA_InventorySlotWidget*> SlotsWidgets;
};
