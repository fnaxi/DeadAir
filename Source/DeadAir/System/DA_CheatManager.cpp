// CopyRight © Dead Air Game. All Rights Reserved.


#include "DA_CheatManager.h"

#include "Inventory/DA_InventoryComponent.h"
#include "Player/DA_Character.h"

void UDA_CheatManager::XAddInventoryItem(const FString& ItemName)
{
	if (const ADA_Character* Character = Cast<ADA_Character>(GetOuterAPlayerController()->GetPawn()))
	{
		if (UDA_InventoryComponent* InventoryComponent = Character->GetComponentByClass<UDA_InventoryComponent>())
		{
			InventoryComponent->AddNewItemByName(ItemName);
		}
	}
}
