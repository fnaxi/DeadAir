// CopyRight © Dead Air Game. All Rights Reserved.


#include "UserInterface/Inventory/DA_InventoryDraggedSlotWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/SizeBox.h"
#include "Inventory/DA_InventoryComponent.h"
#include "Inventory/DA_InventoryItem.h"

/*void UDA_InventoryDraggedSlotWidget::SetData(const FDA_InventorySlot& InData, const float InCellSize)
{
	// todo: Fix crash here or remove. we don't need rotation anyway
	/*if (!SlotData.Item->OnItemRotated.IsBoundToObject(this))
	{
		SlotData.Item->OnItemRotated.AddUObject(this, &ThisClass::OnItemRotated);
	}#1#
}*/

void UDA_InventoryDraggedSlotWidget::OnItemRotated()
{
	/*if (SlotData.Item->CanRotate())
	{
		SlotData.Item->Rotate();

		const FVector2D OldSize = FVector2D(Box->GetWidthOverride(), Box->GetHeightOverride());
		
		Box->SetWidthOverride(OldSize.Y);
		Box->SetHeightOverride(OldSize.X);
	}*/
}

