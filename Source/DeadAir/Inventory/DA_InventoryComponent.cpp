// CopyRight © Dead Air Game. All Rights Reserved.


#include "Inventory/DA_InventoryComponent.h"

#include "DA_InventoryItemDefinition.h"
#include "DA_LogChannels.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetRegistry/IAssetRegistry.h"
#include "Inventory/DA_InventoryItem.h"

// Sets default values
UDA_InventoryComponent::UDA_InventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UDA_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

bool UDA_InventoryComponent::IsWithinBoundaries(const FIntPoint& Coordinates) const
{
	if (Coordinates.X >= 0 && Coordinates.Y >= 0 && Coordinates.X < GridSize.X && Coordinates.Y < GridSize.Y)
	{
		return true;
	}

	return false;
}

void UDA_InventoryComponent::Initialize()
{
	Items.Empty();
	
	Cells.Empty();
	for (int32 Y = 0; Y < GridSize.Y; Y++)
	{
		for (int32 X = 0; X < GridSize.X; X++)
		{
			Cells.Add(FIntPoint(X, Y));
		}
	}

	UE_LOG(X_Inventory, Log, TEXT("%s: Initialized inventory"), *GetOwner()->GetName())
}

bool UDA_InventoryComponent::IsFree(const FIntPoint& Coordinates, const UDA_InventoryItem* ItemToIgnore) const
{
	if (!IsWithinBoundaries(Coordinates))
	{
		// The cell at these coordinates is outside the grid
		return false;
	}

	for (const UDA_InventoryItem* Item : GetItems())
	{
		if (ItemToIgnore && Item == ItemToIgnore) continue;
		
		for (const FIntPoint& Cell : Item->GetSizeInCells())
		{
			if (Item->GetStartCoordinates().X + Cell.X == Coordinates.X &&
				Item->GetStartCoordinates().Y + Cell.Y == Coordinates.Y)
			{
				// The cell at these coordinates is not empty.
				return false;
			}
		}
	}

	return true;
}

bool UDA_InventoryComponent::DoesItemFit(TArray<FIntPoint> const& SizeInCells, const FIntPoint& Coordinates, const UDA_InventoryItem* ItemToIgnore) const
{
	for (const FIntPoint& Cell : SizeInCells)
	{
		const FIntPoint TargetCell = Coordinates + Cell;
		if (!IsFree(TargetCell, ItemToIgnore)) 
		{
			// Item does not fit because the cell at these coordinates is occupied.
			return false;
		}
	}

	return true;
}

FIntPoint UDA_InventoryComponent::GetFreeCell()
{
	const FIntPoint* FoundCoordinates = Cells.FindByPredicate([this](const FIntPoint& Coordinates)
	{
		return IsFree(Coordinates);
	});

	return FoundCoordinates ? *FoundCoordinates : FIntPoint(-1);
}

FIntPoint UDA_InventoryComponent::GetFreeCellThatFitsItem(TArray<FIntPoint> const& SizeInCells)
{
	const FIntPoint* FoundCoordinates = Cells.FindByPredicate([this, SizeInCells](const FIntPoint& Coordinates)
	{
		return IsFree(Coordinates) && DoesItemFit(SizeInCells, Coordinates);
	});

	return FoundCoordinates ? *FoundCoordinates : FIntPoint(-1);
}

bool UDA_InventoryComponent::AddItem(UDA_InventoryItem* Item)
{
	if (AreCoordinatesValid(Item->GetStartCoordinates())) //@TODO: check that cell is free
	{
		Items.Add(Item);
		UE_LOG(X_Inventory, Verbose, TEXT("%s: Added \"%s\" item"), *GetOwner()->GetName(), *Item->GetItemName().ToString())
	
		NotifyInventoryUpdated();
		return true;
	}
	
	UE_LOG(X_Inventory, Log, TEXT("%s: Can't add \"%s\" item!"), *GetOwner()->GetName(), *Item->GetItemName().ToString())
	return false;
}

void UDA_InventoryComponent::AddNewItemByName(const FString& ItemName)
{
	const FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
	const IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

	FARFilter Filter;
	Filter.ClassPaths.Add(UDA_InventoryItemDefinition::StaticClass()->GetClassPathName());
	Filter.bRecursiveClasses = true;

	TArray<FAssetData> FoundAssets;
	AssetRegistry.GetAssets(Filter, FoundAssets);

	UDA_InventoryItemDefinition* ItemDefinition = nullptr;
	for (const FAssetData& AssetData : FoundAssets)
	{
		if (AssetData.AssetName.ToString() == ItemName)
		{
			ItemDefinition = Cast<UDA_InventoryItemDefinition>(AssetData.GetAsset());
			break;
		}
	}

	if (!IsValid(ItemDefinition))
	{
		UE_LOG(X_Inventory, Warning, TEXT("%s: Can't find item definition with name: %s!"), *GetName(), *ItemName);
		return;
	}

	AddNewItem(ItemDefinition);
}

bool UDA_InventoryComponent::AddNewItem(UDA_InventoryItemDefinition* Definition, const int32 Quantity)
{
	UDA_InventoryItem* Item = CreateItem(Definition); //@TODO: Use quantity
	if (Item == nullptr) return false;
	
	const FIntPoint Coordinates = GetFreeCellThatFitsItem(Item->GetSizeInCells());
	Item->SetStartCoordinates(Coordinates);

	return AddItem(Item);
}

bool UDA_InventoryComponent::RemoveItem(UDA_InventoryItem* Item)
{
	Items.Remove(Item);
	UE_LOG(X_Inventory, Verbose, TEXT("%s: Removed \"%s\" item"), *GetOwner()->GetName(), *Item->GetItemName().ToString())
	
	return true;
}

bool UDA_InventoryComponent::MoveItem(const UDA_InventoryItem* InItem, const FIntPoint& Destination)
{	
	for (UDA_InventoryItem* Item : Items)
	{
		if (Item != InItem) continue; //@TODO: Predicate?
		
		if (DoesItemFit(Item->GetSizeInCells(), Destination, Item))
		{
			Item->SetStartCoordinates(Destination);
			UE_LOG(X_Inventory, Log, TEXT("%s: Moved \"%s\" item to %s coordinates"), *GetOwner()->GetName(), *Item->GetItemName().ToString(), *Destination.ToString())
			
			NotifyInventoryUpdated();
			return true;
		}
	}

	UE_LOG(X_Inventory, Log, TEXT("%s: Item \"%s\" can't be moved to %s coordinates!"), *GetOwner()->GetName(), *InItem->GetItemName().ToString(), *Destination.ToString())
	return false;
}

UDA_InventoryItem* UDA_InventoryComponent::CreateItem(UDA_InventoryItemDefinition* Definition)
{
	if (!ensure(Definition && Definition->ItemClass)) return nullptr;
	
	UDA_InventoryItem* Item = NewObject<UDA_InventoryItem>(GetOwner(), Definition->ItemClass);
	if (Item != nullptr)
	{
		Item->SetOwningInventory(this);
		Item->SetDefinition(Definition);
	}
	
	return Item;
}

void UDA_InventoryComponent::NotifyInventoryUpdated()
{
	OnInventoryUpdated.Broadcast();
	UE_LOG(X_Inventory, Verbose, TEXT("%s: Inventory was updated"), *GetOwner()->GetName())
}

