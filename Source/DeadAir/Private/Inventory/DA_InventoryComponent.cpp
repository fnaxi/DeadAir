// CopyRight Dead Air Game. All Rights Reserved.


#include "Inventory/DA_InventoryComponent.h"

// Sets default values for this component's properties
UDA_InventoryComponent::UDA_InventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UDA_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

// Called every frame
void UDA_InventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

