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

	ImGui::CreateContext();

	this->GameDevice = GameDevice;
	auto game_hwnd = FindWindowW(L"Valve001", nullptr);
	if (game_hwnd != NULL)
	{
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

	DXRender::Get().Init(GameDevice);
}


void Render::NewFrame(IDirect3DDevice9* device)
{
	DXRender::Get().Render();


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
	Visual::Get().DrawFovCricle();
	Visual::Get().Test();

	//if (GetAsyncKeyState(G::Get().GetOthervars()->isAiming))		TODO: FIX
	//	AimBot::Get().DrawTarget();
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
#pragma warning( pop )

void DXRender::RenderFilledRect(int x, int y, int w, int h, const CColor& color)
{
	D3DRECT rect = { x, y, x + w, y + h };
	this->pDevice->Clear(1, &rect, D3DCLEAR_TARGET, GetDrawColor(color), 0, 0);
}

void DXRender::RenderBorderBox(int x, int y, int w, int h, int border_w, const CColor& color)
{
	RenderFilledRect(x, y, w, border_w, color);
	RenderFilledRect(x, y, border_w, h, color);
	RenderFilledRect(x + w, y, border_w, h, color);
	RenderFilledRect(x, y + h, w + border_w, border_w, color);
}

void DXRender::RenderLine(int x1, int y1, int x2, int y2, int line_w, const CColor& color)
{
	ID3DXLine* DLine;
	D3DXCreateLine(this->pDevice, &DLine);

	D3DXVECTOR2 Line[2];
	Line[0] = D3DXVECTOR2(x1, y1);
	Line[1] = D3DXVECTOR2(x2, y2);
	DLine->SetWidth(line_w);
	DLine->Draw(Line, 2, GetDrawColor(color));
	DLine->Release();
}

void DXRender::RenderText(int x, int y, const std::string& str, const CColor& color, LPD3DXFONT font)
{
	RECT rect = { x, y, x + 120, y + 15 };

	if (font == NULL)
		font = DefaultFont[16];

	font->DrawTextA(NULL, str.c_str(), -1, &rect, DT_NOCLIP, GetDrawColor(color));
}

void DXRender::Begin()
{
	this->drawCalls.clear();
}

void DXRender::End()
{
	std::unique_lock<std::shared_mutex> lock(mutex);
	drawCalls.swap(safeCalls);
}

void DXRender::Init(IDirect3DDevice9* pDev)
{
	this->pDevice = pDev;

	CreateDrawFont(100, "Arial", this->DefaultFont);
}

DWORD DXRender::GetDrawColor(CColor color) const
{
	return D3DCOLOR_ARGB(color.a(), color.r(), color.g(), color.b());
}

void DXRender::DrawFilledRect(int x, int y, int w, int h, CColor color)
{
	DrawCall call;
	call.type = filledbox;

	call.drawCallFilledBox.x = x;
	call.drawCallFilledBox.y = y;
	call.drawCallFilledBox.w = w;
	call.drawCallFilledBox.h = h;
	call.drawCallFilledBox.color = color;
	drawCalls.push_back(call);
}

void DXRender::DrawBorderBox(int x, int y, int w, int h, int border_w, CColor color)
{
	DrawCall call;
	call.type = borderedbox;

	call.drawCallBorderedBox.x = x;
	call.drawCallBorderedBox.y = y;
	call.drawCallBorderedBox.w = w;
	call.drawCallBorderedBox.h = h;
	call.drawCallBorderedBox.color = color;
	call.drawCallBorderedBox.border_w = border_w;
	drawCalls.push_back(call);
}

void DXRender::DrawLine(int x1, int y1, int x2, int y2, int line_w, CColor color)
{
	DrawCall call;
	call.type = line;

	call.drawCallLine.x1 = x1;
	call.drawCallLine.x2 = x2;
	call.drawCallLine.y1 = y1;
	call.drawCallLine.y2 = y2;
	call.drawCallLine.line_w = line_w;
	call.drawCallLine.color = color;
	drawCalls.push_back(call);
}

void DXRender::DrawString(int x, int y, const std::string& str, const CColor& color, LPD3DXFONT font)
{
	DrawCall call;
	call.type = text;

	call.drawCallText.x = x;
	call.drawCallText.y = y;
	call.drawCallText.str = str;
	call.drawCallText.color = color;
	call.drawCallText.font = font;
	drawCalls.push_back(call);
}


void DXRender::Render()
{
	std::unique_lock<std::shared_mutex> lock(mutex);

	for (DrawCall& call : safeCalls)
	{
		switch (call.type)
		{
		case none:
			break;
		case filledbox:
			RenderFilledRect(call.drawCallFilledBox.x, call.drawCallFilledBox.y, call.drawCallFilledBox.w, call.drawCallFilledBox.h, call.drawCallFilledBox.color);
			break;
		case borderedbox:
			RenderBorderBox(call.drawCallBorderedBox.x, call.drawCallBorderedBox.y, call.drawCallBorderedBox.w, call.drawCallBorderedBox.h, call.drawCallBorderedBox.border_w, call.drawCallBorderedBox.color);
			break;
		case line:
			RenderLine(call.drawCallLine.x1, call.drawCallLine.y1, call.drawCallLine.x2, call.drawCallLine.y2, call.drawCallLine.line_w, call.drawCallLine.color);
			break;
		case text:
			RenderText(call.drawCallText.x, call.drawCallText.y, call.drawCallText.str, call.drawCallText.color, call.drawCallText.font);
			break;
		default:
			break;
		}
	}
}

void DXRender::CreateDrawFont(int max_size, const char* font, std::vector<LPD3DXFONT>& out)
{
	std::vector<LPD3DXFONT> ret;

	for (int i = 1; i <= max_size; ++i)
	{
		LPD3DXFONT tmpFont;
		D3DXCreateFontA(this->pDevice, i, 0, FW_NORMAL, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, font, &tmpFont);
		ret.push_back(tmpFont);
	}

	out = ret;
}
