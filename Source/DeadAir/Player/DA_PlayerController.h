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
	ADA_PlayerController();
	
	UFUNCTION(BlueprintCallable, Category = PlayerController)
	class UDA_AbilitySystemComponent* GetDeadAirAbilitySystemComponent() const;
	
	//~APlayerController interface
	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused) override;
	//~End of APlayerController interface
	
protected:
	virtual void BeginPlay() override;
};
