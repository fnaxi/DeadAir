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

	DEADAIR_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);
	DEADAIR_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look_Mouse);
	DEADAIR_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look_Stick);
	DEADAIR_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Jump);
	DEADAIR_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Crouch);
	DEADAIR_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Inventory);
};
