// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inventory/DA_InventoryTypes.h"
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
	/** Current cell coordinates in the grid. */
	UPROPERTY(BlueprintReadOnly)
	FDA_Point2D Coordinates;

	UPROPERTY(BlueprintReadOnly)
	float CellSize;	

	UPROPERTY(BlueprintReadOnly)
	UDA_InventoryGridWidget* ParentWidget;

	UPROPERTY(EditDefaultsOnly)
	FSlateBrush DefaultCellColor;
	
	void SetData(const FDA_Point2D& NewCoordinates, const float NewSize, UDA_InventoryGridWidget* NewParentWidget);

	void SetCellSize(float Size);
	void SetCellColor(const FSlateBrush& Brush);

protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UTextBlock> CoordinatesText;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UCanvasPanel> CellCanvas; // TODO(DA): replace with UVerticalBox
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UImage> Background;

	UPROPERTY(EditDefaultsOnly)
	FSlateBrush ValidCellPlacementColor;

	UPROPERTY(EditDefaultsOnly)
	FSlateBrush InvalidCellPlacementColor;

	virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	
private:
	void OnDataReceived();
};
