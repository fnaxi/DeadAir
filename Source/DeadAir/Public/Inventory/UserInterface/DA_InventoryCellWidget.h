// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Styling/SlateBrush.h"
#include "Inventory/DA_InventoryComponent.h"
#include "DA_InventoryCellWidget.generated.h"

class UDA_InventoryGridWidget;

/**
 * 
 */
UCLASS()
class DEADAIR_API UDA_InventoryCellWidget : public UUserWidget
{
	GENERATED_BODY()
		
public:
	UDA_InventoryCellWidget(const FObjectInitializer& ObjectInitializer);


	virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;


	UFUNCTION(BlueprintCallable, Category = "Cell")
	void SetData(const FDA_Point2D& NewCoordinates, const float NewSize, UDA_InventoryGridWidget* ParentWidget);

	UFUNCTION(BlueprintImplementableEvent, Category = "Cell")
	void OnDataReceived();

	UFUNCTION(BlueprintImplementableEvent, Category = "Cell")
	void SetCellSize(float Size);

	UFUNCTION(BlueprintImplementableEvent, Category = "Cell")
	void SetCellColor(const FSlateBrush& Brush);
	

	// Current cell coordinates in the grid.
	UPROPERTY(BlueprintReadOnly, Category = "Cell")
	FDA_Point2D Coordinates;

	UPROPERTY(BlueprintReadOnly, Category = "Cell")
	float CellSize;	

	UPROPERTY(BlueprintReadOnly, Category = "Cell")
	UDA_InventoryGridWidget* ParentWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cell")
	FSlateBrush DefaultCellColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cell")
	FSlateBrush ValidCellPlacementColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cell")
	FSlateBrush InvalidCellPlacementColor;
};
