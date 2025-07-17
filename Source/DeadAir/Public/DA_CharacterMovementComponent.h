// CopyRight Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DA_CharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class DEADAIR_API UDA_CharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
public:
	// Sets default values
	UDA_CharacterMovementComponent();
	
	/** A modifier to apply when a character is sprinting. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DA|Movement", meta = (ClampMin = "1.25", ClampMax = "10.0"))
	float SprintModifier = 1.5f;
	
	//BEGIN UMovementComponent Interface
	virtual float GetMaxSpeed() const override;
	//END UMovementComponent Interface
	
};
