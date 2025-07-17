// CopyRight Dead Air Game. All Rights Reserved.


#include "DA_CharacterMovementComponent.h"

#include "DA_PlayerCharacter.h"

// Sets default values
UDA_CharacterMovementComponent::UDA_CharacterMovementComponent()
{
	bCanWalkOffLedgesWhenCrouching = true;
}

float UDA_CharacterMovementComponent::GetMaxSpeed() const
{
	const float MaxSpeed = Super::GetMaxSpeed();
	
	const ADA_PlayerCharacter* Character = Cast<ADA_PlayerCharacter>(GetPawnOwner());
	return Character && Character->IsSprinting() ? MaxSpeed * SprintModifier : MaxSpeed;
}

