// CopyRight Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DA_PlayerHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class DEADAIR_API UDA_PlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;
	
};
