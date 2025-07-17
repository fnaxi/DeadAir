// CopyRight Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DA_DebugTool.generated.h"

/**
 * 
 */
UCLASS()
class DEBUGTOOL_API ADA_DebugTool : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADA_DebugTool();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
private:
	void DrawToolWindow(bool bInputMode);
	void DrawOverlayWindow(bool bInputMode);
	
	/** Tabs the debug tool window has. */
	UPROPERTY()
	TArray<TObjectPtr<class UDA_DebugTabBase>> Tabs;
	
	template<typename TTabType>
	void NewDebugTab()
	{
		Tabs.Add(NewObject<TTabType>(this, TTabType::StaticClass()));
	}
	
	/** Setup style for the ImGui interface. */
	static void SetupImGuiStyle();
	
};
