// CopyRight © Dead Air Game. All Rights Reserved.


#include "Core/DA_Character.h"

#include "Inventory/DA_InventoryComponent.h"

// Sets default values
ADA_Character::ADA_Character()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	InventoryComponent = CreateDefaultSubobject<UDA_InventoryComponent>(TEXT("InventoryComponent"));
}

// Called when the game starts or when spawned
void ADA_Character::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADA_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ADA_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

