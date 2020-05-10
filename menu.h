#pragma once
#include "imgui/imgui.h"
#include "HackCore.h"
#include "CustomUIModules.h"
#include "Settings.h"
#include "GLOBALS.h"
#include "Interfaces.h"


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
				ImGui::BeginGroup();
				ImGui::Checkbox("ESPBox active", &CoreSettings::Get().GetHackSettings()->ESP->IsActive); ImGui::SameLine();
				ImGui::ColorEdit3("ESPBox color", CoreSettings::Get().GetHackSettings()->ESP->BoxColor, ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_RGB | ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_NoInputs);
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
				ImGui::EndGroup();
			};
		}
		namespace Skins
		{
			static void Draw()
			{
				ImGui::BeginGroup();
				//ImGui::Checkbox("ESPBox active", &CoreSettings::Get().GetHackSettings()->ESP->IsActive);
				ImGui::EndGroup();
			};
		}
		namespace Misc
		{
			static void Draw()
			{
				ImGui::BeginGroup();
				ImGui::Checkbox("BHOP active", &CoreSettings::Get().GetHackSettings()->BHOP->isActive);
				ImGui::EndGroup();
			};
		}
		namespace Config
		{
			static void Draw()
			{
				ImGui::BeginGroup();
				//ImGui::Checkbox("ESPBox active", &CoreSettings::Get().GetHackSettings()->ESP->IsActive);
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
		ImGui::Begin("Hello", (bool*)0, ImVec2(700, 340), 0.9f, ImGuiWindowFlags_NoResize);
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