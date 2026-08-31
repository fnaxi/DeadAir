// CopyRight © Dead Air Game. All Rights Reserved.


#include "UserInterface/Inventory/DA_InventoryItemTooltip.h"

#include "CommonTextBlock.h"
#include "Inventory/DA_InventoryItem.h"

void UDA_InventoryItemTooltip::InitializeTooltip(const UDA_InventoryItem* InItem)
{
	NameText->SetText(InItem->GetItemName());
	DescriptionText->SetText(InItem->GetItemDescription());

	//@TODO: change to LOCTEXT()
	WeightText->SetText(FText::FromString(FString::Printf(TEXT("%.2f kg"), InItem->GetWeight())));
}

