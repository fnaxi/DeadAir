// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonPlayerController.h"
#include "DA_PlayerController.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DEADAIR_API ADA_PlayerController : public ACommonPlayerController
{
	GENERATED_BODY()

public:
	void OpenInventory();
	
protected:
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<class UInputMappingContext> MappingContext;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<class UInputAction> InventoryAction;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UDA_GameplayAbility_OpenInventory> ToggleInventoryAbilityClass;
	
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
};
