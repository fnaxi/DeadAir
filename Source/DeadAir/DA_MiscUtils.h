// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

/** Used to check that required asset is set in kismet. */
#define ENSURE_KISMET(AssetName, ...) \
	if (!ensureMsgf(AssetName, TEXT("%s: Missing asset: %s!"), *GetName(), TEXT(#AssetName))) \
	{ \
		DEBUG_MESSAGE(10.f, FColor::Red, FString::Printf(TEXT("%s: MISSING ASSET: %s!"), *GetName(), TEXT(#AssetName))); \
		return __VA_ARGS__; \
	}

#define DEBUG_MESSAGE(TimeToDisplay, Color, Message, ...) \
	if (GEngine) \
		GEngine->AddOnScreenDebugMessage(-1, TimeToDisplay, Color, Message, ##__VA_ARGS__);

#define DA_LOCTEXT(StringID) LOCTEXT(StringID, StringID)
