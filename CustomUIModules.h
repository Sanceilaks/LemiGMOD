#pragma once
#include "imgui/imgui.h"


namespace Menu
{
	namespace CustomUI
	{
		static void DrawCursorToggle()
		{
			ImGui::GetIO().MouseDrawCursor = !ImGui::GetIO().MouseDrawCursor;
		}
	}
}
