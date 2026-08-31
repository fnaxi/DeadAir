// CopyRight © Dead Air Game. All Rights Reserved.


#include "UserInterface/Inventory/DA_InventoryItemWidgetBase.h"

#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Inventory/DA_InventoryItem.h"

void UDA_InventoryItemWidgetBase::InitializeSlot(UDA_InventoryItem* InItem, const float InSize)
{
	Item = InItem;

	SetSlotSize(InSize);
	ChangeIcon(Item->GetAtlasCoordinates(), Item->GetSize());
}

void UDA_InventoryItemWidgetBase::SetSlotSize(const float Size) const
{
	const FVector2D NewSize = FVector2D(Item->GetSize().X * Size, Item->GetSize().Y * Size);

	Box->SetWidthOverride(NewSize.X);
	Box->SetHeightOverride(NewSize.Y);
}

void UDA_InventoryItemWidgetBase::ChangeIcon(const FIntPoint& Coordinates, const FIntPoint& Size)
{
	UMaterialInterface* BaseMaterial = Cast<UMaterialInterface>(Icon->GetBrush().GetResourceObject());
	if (!ensure(BaseMaterial)) return;
	
	UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(BaseMaterial, this);
	if (DynamicMaterial == nullptr) return;

	DynamicMaterial->SetScalarParameterValue(FName("Begin X"),	Coordinates.X);
	DynamicMaterial->SetScalarParameterValue(FName("Begin Y"),	Coordinates.Y);
	DynamicMaterial->SetScalarParameterValue(FName("Width"),	Size.X);
	DynamicMaterial->SetScalarParameterValue(FName("Height"),	Size.Y);
	
	Icon->SetBrushFromMaterial(DynamicMaterial);
}

