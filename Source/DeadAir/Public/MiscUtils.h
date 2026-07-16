// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

#define DA_ENSURE_ASSET(AssetName) \
	if (ensureMsgf(AssetName, TEXT("The required asset was not set in %s: %s"), *GetName(), TEXT(#AssetName)))
