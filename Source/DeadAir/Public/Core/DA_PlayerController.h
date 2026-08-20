// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DA_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DEADAIR_API ADA_PlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<class UInputMappingContext> MappingContext;
	
	virtual void BeginPlay() override;
	
private:
	void SetUIMode(bool bUIMode);
};
