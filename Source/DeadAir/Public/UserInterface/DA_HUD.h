// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DA_HUD.generated.h"

/**
 * 
 */
UCLASS()
class DEADAIR_API ADA_HUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UDA_LayoutWidget> LayoutWidgetClass;
	
private:
	UPROPERTY()
	TObjectPtr<UDA_LayoutWidget> LayoutWidget;
};
