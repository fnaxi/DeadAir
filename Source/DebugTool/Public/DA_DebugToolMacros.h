// CopyRight Dead Air Game. All Rights Reserved.

#pragma once

#define DA_IMTEXT(InText) (StringCast<ANSICHAR>(*(InText)).Get())
#define DA_FTEXT(InText) FString(TEXT(InText))

#define DA_IMGUI_TEXTBOX(InText) ImGui::Text(DA_IMTEXT(InText));
#define DA_IMGUI_BUTTON(InText, Size) ImGui::Button(DA_IMTEXT(InText), Size)
#define DA_IMGUI_CHECKBOX(InText, Var) ImGui::Checkbox(DA_IMTEXT(InText), Var)
