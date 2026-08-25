// Copyright Epic Games, Inc. All Rights Reserved.


#include "DA_GameplayTags.h"

#include "Engine/EngineTypes.h"
#include "GameplayTagsManager.h"

namespace DeadAirGameplayTags
{
	UE_DEFINE_GAMEPLAY_TAG(Layer_Game,			"UI.Layer.Game");
	UE_DEFINE_GAMEPLAY_TAG(Layer_GameMenu,		"UI.Layer.GameMenu");
	UE_DEFINE_GAMEPLAY_TAG(Layer_Menu,			"UI.Layer.Menu");
	UE_DEFINE_GAMEPLAY_TAG(Layer_Modal,			"UI.Layer.Modal");

	FGameplayTag FindTagByString(const FString& TagString, bool bMatchPartialString)
	{
		const UGameplayTagsManager& Manager = UGameplayTagsManager::Get();
		FGameplayTag Tag = Manager.RequestGameplayTag(FName(*TagString), false);

		if (!Tag.IsValid() && bMatchPartialString)
		{
			FGameplayTagContainer AllTags;
			Manager.RequestAllGameplayTags(AllTags, true);

			for (const FGameplayTag& TestTag : AllTags)
			{
				if (TestTag.ToString().Contains(TagString))
				{
					UE_LOG(LogTemp, Display, TEXT("Could not find exact match for tag [%s] but found partial match on tag [%s]."), *TagString, *TestTag.ToString());
					Tag = TestTag;
					break;
				}
			}
		}

		return Tag;
	}
}

