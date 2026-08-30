// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "DA_CheatManager.generated.h"

/**
 * 
 */
UCLASS()
class DEADAIR_API UDA_CheatManager : public UCheatManager
{
	GENERATED_BODY()

public:
	UFUNCTION(Exec, BlueprintCallable, Category = "Cheat Manager")
	void XAddInventoryItem(const FString& ItemName);
};
