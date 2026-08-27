// CopyRight © Dead Air Game. All Rights Reserved.


#include "DA_AbilitySystemComponent.h"

// Sets default values for this component's properties
UDA_AbilitySystemComponent::UDA_AbilitySystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UDA_AbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UDA_AbilitySystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

