#pragma once
#include "imgui/imgui.h"
#include "imgui/impl/imgui_impl_dx9.h"
#include "imgui/impl/imgui_impl_win32.h"
#include "HackCore.h"
#include "CustomUIModules.h"
#include "Settings.h"
#include "GLOBALS.h"
#include "Interfaces.h"

#include "LuaLoad.h"

#define ButtonSize ImVec2(80, 30)
namespace BindButtons
{
	struct BaseKey
	{
		BaseKey(int c, const char* n) { this->code = c; this->name = n; };
		int code;
		const char* name;
	};
	namespace AimKey
	{
		struct Keys
		{
			BaseKey LALT = BaseKey(81, "LALT");
		};
	};
};


namespace Menu
{
	enum WinButtons
	{
		AIM,
		VISUAL,
		SKIN,
		MISC,
		CONFIG
	};

	namespace mywin
	{
		namespace Visual
		{
			static void Draw()
			{
				ImGui::BeginGroup();		//espbox
				ImGui::Checkbox("ESPBox active", &CoreSettings::Get().GetHackSettings()->ESP->IsActive); ImGui::SameLine();
				ImGui::ColorEdit3("ESPBox visible color", CoreSettings::Get().GetHackSettings()->ESP->VBoxColor, ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_RGB | ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_NoInputs);
				ImGui::SameLine();
				ImGui::ColorEdit3("ESPBox invisible color", CoreSettings::Get().GetHackSettings()->ESP->IBoxColor, ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_RGB | ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_NoInputs);
				ImGui::Checkbox("Draw health", &CoreSettings::Get().GetHackSettings()->ESP->DrawHealth);
				ImGui::SliderInt("Max distance", &CoreSettings::Get().GetHackSettings()->ESP->MaxEspDistance, 0, 100000);
				ImGui::EndGroup();
				ImGui::BeginGroup();
				ImGui::Checkbox("Draw Fov", &CoreSettings::Get().GetHackSettings()->AIM->DrawFov);
				ImGui::Checkbox("Custom Fov", &CoreSettings::Get().GetHackSettings()->VISUAL->bCustomFov);
				ImGui::SameLine();
				ImGui::PushItemWidth(60);
				ImGui::SliderInt("Custom Fov Value", &CoreSettings::Get().GetHackSettings()->VISUAL->iCustomFov, 0, 250);
				ImGui::PopItemWidth();
				ImGui::SameLine();
				ImGui::Checkbox("Custom Viewmodel Fov", &CoreSettings::Get().GetHackSettings()->VISUAL->bCustomViewmodelFov);
				ImGui::SameLine();
				ImGui::PushItemWidth(60);
				ImGui::SliderInt("Custom Viewmodel Fov Value", &CoreSettings::Get().GetHackSettings()->VISUAL->iCustomViewmodelFov, 0, 250);
				ImGui::PopItemWidth();
				ImGui::EndGroup();
			};
		};
		namespace Aim
		{
			static void Draw()
			{
				ImGui::BeginGroup();
				ImGui::Checkbox("Aim active", &CoreSettings::Get().GetHackSettings()->AIM->isActive);
				ImGui::SameLine();
				ImGui::Checkbox("Silent", &CoreSettings::Get().GetHackSettings()->AIM->isSilent);
				ImGui::SameLine();
				ImGui::Checkbox("Only Visible", &CoreSettings::Get().GetHackSettings()->AIM->OnlyVisible);
				ImGui::SameLine();
				ImGui::Checkbox("AutoFire", &CoreSettings::Get().GetHackSettings()->AIM->AutoFire);
				ImGui::Spacing();
				ImGui::SliderInt("FOV", &CoreSettings::Get().GetHackSettings()->AIM->AimFov, 0, 360);
				ImGui::SliderInt("Max distance", &CoreSettings::Get().GetHackSettings()->AIM->MaxAimDistance, 0, 100000);
				ImGui::Checkbox("Legit", &CoreSettings::Get().GetHackSettings()->AIM->Legit);

				if (CoreSettings::Get().GetHackSettings()->AIM->Legit)
				{
					ImGui::SliderInt("Smooth", &CoreSettings::Get().GetHackSettings()->AIM->Smooth, 1, 200);
				}

				ImGui::Hotkey("AimKey", &CoreSettings::Get().GetHackSettings()->AIM->AimKey);
				ImGui::Spacing();
				ImGui::Combo("Aim Type", &CoreSettings::Get().GetHackSettings()->AIM->AimType, AimTypeName, 2);
				ImGui::EndGroup();
			};
		}
		namespace Skins
		{
			static void Draw()
			{
				ImGui::BeginGroup();

				if (ImGui::Button("Test"))
				{
					LuaLoad::Get().LoadFile("C:\\Test\\test.lua");
				}

				//ImGui::Checkbox("ESPBox active", &CoreSettings::Get().GetHackSettings()->ESP->IsActive);
				ImGui::EndGroup();
			};
		}
		namespace Misc
		{
			static void Draw()
			{
				ImGui::BeginGroup();
				ImGui::Checkbox("BunnyHop", &CoreSettings::Get().GetHackSettings()->BHOP->isActive);
				ImGui::EndGroup();
			};
		}
		namespace Config
		{
			static void Draw()
			{
				ImGui::BeginGroup();
				ImGui::Hotkey("Open Menu On", &CoreSettings::Get().GetMenuSettings()->MainSettings->TriggerKey);
				//ImGui::Combo("Draw Type", &CoreSettings::Get().GetHackSettings()->VISUAL->Dtype, HDrawTypeName, 2);
				ImGui::EndGroup();
			};
		}
	};
	static int currentwin = VISUAL;
	static bool is_open = false;

	static void DrawCurrent()
	{
		switch (currentwin)
		{
		case AIM:
			mywin::Aim::Draw();
			break;
		case VISUAL:
			mywin::Visual::Draw();
			break;
		case SKIN:
			mywin::Skins::Draw();
			break;
		case MISC:
			mywin::Misc::Draw();
			break;
		case CONFIG:
			mywin::Config::Draw();
			break;
		}
	}

	static void Draw()
	{
		ImGui::Begin("Hello", (bool*)0, ImVec2(700, 340), 0.9f, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
		ImGui::SameLine();

		ImGui::BeginChild("###tabs", ImVec2(600, 40));
		ImGui::SameLine();

		if (ImGui::Button("AIM", ButtonSize))		currentwin = AIM;
		ImGui::SameLine();

		if (ImGui::Button("VISUAL", ButtonSize))	currentwin = VISUAL;
		ImGui::SameLine();

		if (ImGui::Button("SKIN", ButtonSize))		currentwin = SKIN;
		ImGui::SameLine();

		if (ImGui::Button("MISC", ButtonSize))		currentwin = MISC;
		ImGui::SameLine();

		if (ImGui::Button("CONFIG", ButtonSize))	currentwin = CONFIG;
		ImGui::SameLine();

		ImGui::EndChild();

		ImGui::Spacing();
		
		ImGui::BeginChild("###content");
		
		DrawCurrent();

		ImGui::EndChild();

		ImGui::End();
	} 
	static void ToggleMenu()
	{
		G::Get().GetMenuVars()->MenuIsOpen = !G::Get().GetMenuVars()->MenuIsOpen;
		is_open = !is_open;
		switch (G::Get().GetMenuVars()->MenuIsOpen)
		{
		case true:
			CustomUI::DrawCursorToggle();
			Interfaces::Get().InputSystem->EnableInput(G::Get().GetMenuVars()->MenuIsOpen);
			break;
		case false:
			CustomUI::DrawCursorToggle();
			Interfaces::Get().InputSystem->EnableInput(G::Get().GetMenuVars()->MenuIsOpen);
			break;
		}
	}
}