// CopyRight © Dead Air Game. All Rights Reserved.


#include "Player/DA_PlayerController.h"

#include "AbilitySystem/DA_AbilitySystemComponent.h"
#include "Player/DA_Character.h"

UDA_AbilitySystemComponent* ADA_PlayerController::GetDeadAirAbilitySystemComponent() const
{
	return Cast<ADA_Character>(GetPawn())->GetDeadAirAbilitySystemComponent();
}

void ADA_PlayerController::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
	if (UDA_AbilitySystemComponent* AbilitySystem = GetDeadAirAbilitySystemComponent())
	{
		AbilitySystem->ProcessAbilityInput(DeltaTime, bGamePaused);
	}
	
	Super::PostProcessInput(DeltaTime, bGamePaused);
}

void ADA_PlayerController::BeginPlay()
{
	Super::BeginPlay();
}

