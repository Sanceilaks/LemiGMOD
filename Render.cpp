#include "Render.h"
#include "menu.h"
#include "MenuThemes.h"
#include "GLOBALS.h"
#include "ESPBox.h"
#include "AimBot.h"
#include "Settings.h"
#include "OtherVisual.h"

#pragma warning( push )
#pragma warning( disable : 4244) //4244

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


void Render::NewFrame(IDirect3DDevice9* device)
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	this->BeginScene();

	if (G::Get().GetMenuVars()->MenuIsOpen)
		Menu::Draw();

	DXRender::Get().Render(device);
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

void DXRender::RenderBorderedBox(Vec2 pos, int w, int h, int thickness, D3DCOLOR color)
{
	DrawCall call;
	call.type = borderedbox;

	call.drawCallBorderedBox.w = w;
	call.drawCallBorderedBox.h = h;
	call.drawCallBorderedBox.color = color;
	call.drawCallBorderedBox.origin = pos;
	call.drawCallBorderedBox.thickness = thickness;

	drawCalls.push_back(call);
}

void DXRender::RenderFilledBox(Vec2 pos, int w, int h, D3DCOLOR color)
{
	DrawCall call;
	call.type = filledbox;


	call.drawCallFilledBox.w = w;
	call.drawCallFilledBox.h = h;
	call.drawCallFilledBox.color = color;
	call.drawCallFilledBox.origin = pos;

	drawCalls.push_back(call);
}

void DXRender::Begin()
{
	drawCalls.clear();
}

void DXRender::End()
{
	std::unique_lock<std::shared_mutex> lock(mutex);
	drawCalls.swap(safeCalls);
}

inline void FilledBox(IDirect3DDevice9* device, int x, int y, int w, int h, D3DCOLOR color)
{
	SD3DVertex pVertex[4] = { {x, y + h, 0.0f, 1.0f, color}, {x, y, 0.0f, 1.0f, color}, {x + w, y + h, 0.0f, 1.0f, color}, {x + w, y, 0.0f, 1.0f, color} };
	device->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, pVertex, sizeof(SD3DVertex));
}

inline void BorderedBox(IDirect3DDevice9* device, int x, int y, int w, int h, int thikness, D3DCOLOR color)
{
	FilledBox(device, x, y, w, thikness, color);
	FilledBox(device, x, y, thikness, h, color);
	FilledBox(device, x + w - thikness, y, thikness, h, color);
	FilledBox(device, x, y + h - thikness, w, thikness, color);
}

//inline void FilledBox(IDirect3DDevice9* device, int x1, int y1, int x2, int y2, D3DCOLOR color)
//{
//	int x = x1, y = y1, w = x2 - x1, h = y2 - y1;
//	SD3DVertex pVertex[4] = { {x, y + h, 0.0f, 1.0f, color}, {x, y, 0.0f, 1.0f, color}, {x + w, y + h, 0.0f, 1.0f, color}, {x + w, y, 0.0f, 1.0f, color} };
//	device->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
//	device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, pVertex, sizeof(SD3DVertex));
//}
//
//inline void BorderedBox(IDirect3DDevice9* device, int x1, int y1, int x2, int y2, int thikness, D3DCOLOR color)
//{
//	FilledBox(device, x1, y1, x2, y2, thikness, color);
//	FilledBox(device, x1, y1, x2 , y2 thikness, h, color);
//	FilledBox(device, x + w - thikness, y, thikness, h, color);
//	FilledBox(device, x, y + h - thikness, w, thikness, color);
//}


void DXRender::Render(IDirect3DDevice9* device)
{
	std::unique_lock<std::shared_mutex> lock(mutex);

	for (DrawCall & call : safeCalls)
	{
		switch (call.type)
		{
		case none:
			break;
		case filledbox:
			FilledBox(device, call.drawCallFilledBox.origin.x, call.drawCallFilledBox.origin.y, call.drawCallFilledBox.w, call.drawCallFilledBox.h, call.drawCallFilledBox.color);
			break;
		case borderedbox:
			BorderedBox(device, call.drawCallBorderedBox.origin.x, call.drawCallBorderedBox.origin.y, call.drawCallBorderedBox.w, call.drawCallBorderedBox.h, call.drawCallBorderedBox.thickness, call.drawCallBorderedBox.color);
			break;
		default:
			break;
		}
	}
}
#pragma warning( pop )