// CopyRight Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DA_GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class DEADAIR_API ADA_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	// Sets default values
	ADA_GameModeBase();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintImplementableEvent, Category = "DebugTool", DisplayName = "Spawn Debug Tool")
	void K2_SpawnDebugTool();

private:
	void SpawnDebugTool();
};
