// CopyRight Dead Air Game. All Rights Reserved.


#include "DA_DebugTool.h"

#include "imgui.h"
#include "ImGuiModule.h"
#include "DA_DebugToolMacros.h"
#include "Tab/DA_DebugTabCharacter.h"
#include "Tab/DA_DebugTabRender.h"
#include "Tab/DA_DebugTabSettings.h"
#include "Tab/DA_DebugTabShow.h"

static TAutoConsoleVariable<bool> CVarShowDebugTool(
	TEXT("XShowDebugTool"),
	true,
	TEXT("Show or hide the debug tool ImGui window"));

// Sets default values
ADA_DebugTool::ADA_DebugTool()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADA_DebugTool::BeginPlay()
{
	Super::BeginPlay();

	FImGuiModule::Get().SetInputMode(false);
	SetupImGuiStyle();

	NewDebugTab<UDA_DebugTabRender>();
	NewDebugTab<UDA_DebugTabShow>();
	NewDebugTab<UDA_DebugTabCharacter>();
	NewDebugTab<UDA_DebugTabSettings>();

	for (TObjectPtr<UDA_DebugTabBase> Tab : Tabs)
	{
		Tab->OnInitialize();
	}
}

// Called every frame
void ADA_DebugTool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	const bool bInputMode = FImGuiModule::Get().IsInputMode();
	DrawToolWindow(bInputMode);
	DrawOverlayWindow(bInputMode);

	for (TObjectPtr<UDA_DebugTabBase> Tab : Tabs)
	{
		if (Tab)
		{
			Tab->OnGameLogic();
		}
	}
}

void ADA_DebugTool::DrawToolWindow(const bool bInputMode)
{
	if (!CVarShowDebugTool.GetValueOnGameThread()) return;

	ImGui::Begin("DA Debug Tool (Shift+X)", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings);
	
	ImGui::SetWindowCollapsed(!bInputMode);
	ImGui::SetWindowPos(ImVec2(25, 45));
	ImGui::SetWindowSize(ImVec2(890, 390));

	ImGui::BeginTabBar("Main");
	for (TObjectPtr<UDA_DebugTabBase> Tab : Tabs)
	{
		if (Tab && ImGui::BeginTabItem(DA_IMTEXT(Tab->GetTabName())))
		{
			Tab->OnDrawToolUI();
			ImGui::EndTabItem();
		}
	}
	ImGui::EndTabBar();
	
	ImGui::End();
}

void ADA_DebugTool::DrawOverlayWindow(const bool bInputMode)
{
	if (!CVarShowDebugTool.GetValueOnGameThread()) return;
	
	bool bEnabledAnyDebugOverlay = false;
	for (TObjectPtr<UDA_DebugTabBase> Tab : Tabs)
	{
		if (Tab && Tab->IsOverlayEnabled())
		{
			bEnabledAnyDebugOverlay = true;
			break;
		}
	}
	
	if (!bInputMode && bEnabledAnyDebugOverlay)
	{
		ImGui::SetNextWindowBgAlpha(0.35f);
	
		ImGui::Begin("DA Overlay", nullptr, ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoFocusOnAppearing |
				ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar);
		ImGui::SetWindowPos(ImVec2(25.0f, 65.0f));
		ImGui::SetWindowCollapsed(!bInputMode);
		for (TObjectPtr<UDA_DebugTabBase> Tab : Tabs)
		{
			if (Tab && Tab->IsOverlayEnabled())
			{
				Tab->OnDrawOverlay();
			}
		}
		ImGui::End();
	}
}

void ADA_DebugTool::SetupImGuiStyle()
{
	ImGuiIO* IO = &ImGui::GetIO();
	IO->IniFilename = nullptr; // Window positions are hardcoded so we don't want to save them to .ini file

	ImGuiStyle* Style = &ImGui::GetStyle();
	Style->WindowRounding = 4.5f;
}

