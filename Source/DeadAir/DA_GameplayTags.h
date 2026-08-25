// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

#include "NativeGameplayTags.h"

namespace DeadAirGameplayTags
{
	DEADAIR_API		FGameplayTag FindTagByString(const FString& TagString, bool bMatchPartialString = false);
	
	DEADAIR_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Layer_Game);
	DEADAIR_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Layer_GameMenu);
	DEADAIR_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Layer_Menu);
	DEADAIR_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Layer_Modal);
};
