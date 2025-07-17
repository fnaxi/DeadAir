// CopyRight Dead Air Game. All Rights Reserved.

#pragma once

#if DA_WITH_DEBUG_TOOL

#define DA_DEBUG_ACCESS_VAR(VarType, VarName) \
public: \
FORCEINLINE VarType GetDebug##VarName() const \
{ \
return VarName(); \
} \
private:
#define DA_DEBUG_ACCESS_FUNCTION(VarType, VarName, FunctionName) \
public: \
VarType GetDebug##VarName() const \
{ \
return FunctionName(); \
} \
private:
#define DA_DEBUG_ALLOW_FULL_ACCESS() friend class ADA_DebugTool;

#else

#define DA_DEBUG_ACCESS_VAR(VarType, VarName)
#define DA_DEBUG_ACCESS_METHOD(VarType, VarName, FunctionName)
#define DA_DEBUG_ALLOW_FULL_ACCESS()

#endif
