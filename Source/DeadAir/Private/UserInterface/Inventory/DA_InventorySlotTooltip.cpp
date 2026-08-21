// CopyRight © Dead Air Game. All Rights Reserved.


#include "UserInterface/Inventory/DA_InventorySlotTooltip.h"

#include "CommonTextBlock.h"
#include "Inventory/DA_InventoryItem.h"
#include "Inventory/DA_InventoryTypes.h"

void UDA_InventorySlotTooltip::SetData(const FDA_InventorySlot& InSlot)
{
	NameText->SetText(InSlot.Item->GetItemName());
	DescriptionText->SetText(InSlot.Item->GetItemDescription());

	// todo: change to LOCTEXT()
	WeightText->SetText(FText::FromString(FString::Printf(TEXT("%.2f kg"), InSlot.Item->GetWeight())));
}

