// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DA_InventoryCellWidget.generated.h"

class UDA_InventoryGridWidget;

/**
 * 
 */
UCLASS(Config = Game)
class DEADAIR_API UDA_InventoryCellWidget : public UUserWidget
{
	GENERATED_BODY()
		
public:	
	void InitializeCell(const FIntPoint& InCoordinates, UDA_InventoryGridWidget* InGrid, const float InSize);
	
	void SetCellColor(const FSlateBrush& Brush) const;
	
	FORCEINLINE FSlateBrush GetDefaultCellColor() const { return DefaultCellColor; }
	FORCEINLINE FIntPoint GetCoordinates() const { return Coordinates; }
	
protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UTextBlock> CoordinatesText;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class USizeBox> Box;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UImage> Background;

	UPROPERTY(EditDefaultsOnly)
	FSlateBrush DefaultCellColor;

	UPROPERTY(EditDefaultsOnly)
	FSlateBrush ValidCellPlacementColor;

	UPROPERTY(EditDefaultsOnly)
	FSlateBrush InvalidCellPlacementColor;

	virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

private:
	UPROPERTY()
	TWeakObjectPtr<UDA_InventoryGridWidget> Grid;
	
	UPROPERTY(Config)
	bool bUseDebugCoordinates;
	
	/** Current cell coordinates in the grid. */
	FIntPoint Coordinates;

	void SetCellSize(float Size) const;
};
