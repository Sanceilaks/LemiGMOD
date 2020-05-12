#pragma once
//#define IMGUI_DISABLE_OBSOLETE_FUNCTIONS
#include "imgui/imgui.h"
#define IMGUI_DEFINE_MATH_OPERATORS
//#define IMGUI_DEFINE_PLACEMENT_NEW
#include "imgui/imgui_internal.h"
//#include "imgui/directx9/imgui_impl_dx9.h"
#include <Windows.h>
#include <string>
#include <functional>
#include "GLOBALS.h"
#include <iostream>
#include <vector>
#include "Interfaces.h"


namespace Menu
{
	namespace CustomUI
	{
		static void DrawCursorToggle()
		{
			if (Interfaces::Get().Engine->isInGame())
				ImGui::GetIO().MouseDrawCursor = !ImGui::GetIO().MouseDrawCursor;
		}

		//static bool Items_ArrayGetter(void* data, int idx, const char** out_text)
		//{
		//	const char* const* items = (const char* const*)data;
		//	if (out_text)
		//		*out_text = items[idx];
		//	return true;
		//}

		//static auto vector_getter = [](void* vec, int idx, const char** out_text) {
		//	auto& vector = *static_cast<std::vector<std::string>*>(vec);
		//	if (idx < 0 || idx >= static_cast<int>(vector.size())) { return false; }
		//	*out_text = vector.at(idx).c_str();
		//	return true;
		//};

		//bool ImGui::VectorCombo(const char* label, int* currIndex, std::vector<std::string>& values) {
		//	if (values.empty()) { return false; }
		//	return ImGui::Combo(label, currIndex, vector_getter,
		//		static_cast<void*>(&values), values.size());
		//}


	}
	namespace CustomWindows
	{
		static void DrawEntityEspWindow()
		{
			if (!G::Get().GetMenuVars()->EntEspIsOpen)
				return;
			ImGui::Begin("Entity Esp Settings", (bool*)0, ImGuiWindowFlags_NoResize);
			ImGui::BeginChild("###drawlist");
			


			ImGui::EndChild();



			ImGui::End();
		}
	};
}

namespace ImGui 
{
	bool ToggleButton(const char* label, bool* v, const ImVec2& size_arg = ImVec2(0, 0));
	// Combo box helper allowing to pass an array of strings.
	bool Combo(const char* label, int* currIndex, std::vector<std::string>& values);
	bool BeginGroupBox(const char* name, const ImVec2& size_arg = ImVec2(0, 0));
	void EndGroupBox();
	bool Hotkey(const char* label, int* k, const ImVec2& size_arg = ImVec2(0, 0));
	bool ListBox(const char* label, int* current_item, std::string items[], int items_count, int height_items);
	bool ListBox(const char* label, int* current_item, std::function<const char* (int)> lambda, int items_count, int height_in_items);
	bool Combo(const char* label, int* current_item, std::function<const char* (int)> lambda, int items_count, int height_in_items);
	bool ItemHoverable(const ImRect& bb, ImGuiID id);
}
