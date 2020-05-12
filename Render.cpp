#include "Render.h"
#include "menu.h"
#include "MenuThemes.h"
#include "GLOBALS.h"
#include "ESPBox.h"
#include "AimBot.h"
#include "Settings.h"
#include "OtherVisual.h"

ImDrawListSharedData _data;

std::mutex render_mutex;

static LRESULT STDMETHODCALLTYPE user_wndproc(HWND window, UINT message_type, WPARAM w_param, LPARAM l_param)
{
	if (GetAsyncKeyState(CoreSettings::Get().GetMenuSettings()->MainSettings->TriggerKey) & 0x1) {
		Menu::ToggleMenu();
	}
	if (ImGui_ImplWin32_WndProcHandler(window, message_type, w_param, l_param) && G::Get().GetMenuVars()->MenuIsOpen) {
		return true;
	}

	return CallWindowProc(Render::Get().wnd_proc, window, message_type, w_param, l_param);
}

void Render::Init(IDirect3DDevice9* GameDevice)
{
	//std::cout << "Render init...\n";

	ImGui::CreateContext();

	this->GameDevice = GameDevice;
	auto game_hwnd = FindWindowW(L"Valve001", nullptr);
	if (game_hwnd != NULL)
	{
		//std::cout << "WndProc hooking\n";
		this->GameHWND = game_hwnd;
		this->wnd_proc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(game_hwnd, GWLP_WNDPROC, (LONG_PTR)user_wndproc));

		ImGui_ImplWin32_Init(game_hwnd);
		ImGui_ImplDX9_Init(GameDevice);

		ImGui::GetIO().IniFilename = nullptr;

		Menu::Themes::MyStdTheme::Setup();
	}

	this->DrawList = new ImDrawList(ImGui::GetDrawListSharedData());
	this->DrawListActualy = new ImDrawList(ImGui::GetDrawListSharedData());
	this->DrawListRender = new ImDrawList(ImGui::GetDrawListSharedData());
	//std::cout << "Init True\n";
}


void Render::NewFrame()
{
	//std::cout << "New frame...\n";
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	this->BeginScene();

	if (G::Get().GetMenuVars()->MenuIsOpen)
		Menu::Draw();

	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}


void Render::ClearDrawList()
{
	render_mutex.lock();
	this->DrawListActualy->Clear();
	render_mutex.unlock();
}

void Render::BeginScene()
{
	ESPBox::Get().Render();
	Visual::Get().DrawFovCricle();

	if (GetAsyncKeyState(G::Get().GetOthervars()->isAiming))
		AimBot::Get().DrawTarget();
}

ImDrawList* Render::RenderScene()
{
	//if (render_mutex.try_lock())
	//{
	//	*this->DrawListRender = *this->DrawListActualy;
	//	render_mutex.unlock();
	//}
	return this->DrawList;
}