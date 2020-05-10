#include "EndScaneHook.h"
#include <iostream>
#include <Windows.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx9.h"
#include "menu.h"
#include "MenuThemes.h"
#include "GLOBALS.h"
#include "ESPBox.h"

extern IMGUI_API LRESULT   ImGui_ImplDX9_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void CustomDraw()
{
	ESPBox::Get().Render();
}

namespace original
{
	static WNDPROC wnd_proc = nullptr;
}

LRESULT STDMETHODCALLTYPE user_wndproc(HWND window, UINT message_type, WPARAM w_param, LPARAM l_param) {
	if (GetAsyncKeyState(VK_INSERT) & 0x1) {
		//std::cout << "Insert down!\n";
		Menu::ToggleMenu();
	}
	if (ImGui_ImplDX9_WndProcHandler(window, message_type, w_param, l_param) && G::Get().GetMenuVars()->MenuIsOpen) {
		return 1l;
	}

	return CallWindowProc(original::wnd_proc, window, message_type, w_param, l_param);
};

void __stdcall MyHooks::EndScane(IDirect3DDevice9* device)
{
	if (!isInit) {
		auto game_hwnd = FindWindowW(L"Valve001", nullptr);
		if (game_hwnd != NULL) {
			original::wnd_proc = reinterpret_cast<WNDPROC>(
				SetWindowLongPtr(game_hwnd, GWLP_WNDPROC, LONG_PTR(user_wndproc))
				);

			ImGui_ImplDX9_Init(game_hwnd, device);

			ImGui::GetIO().IniFilename = nullptr;

			Menu::Themes::MyStdTheme::Setup();

			isInit = true;
		}
	}
	else
	{
		ImGui_ImplDX9_NewFrame();

		CustomDraw();

		if (G::Get().GetMenuVars()->MenuIsOpen)
			Menu::Draw();

		ImGui::Render();
	}
}