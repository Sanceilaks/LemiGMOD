#pragma once
#include "Singleton.h"
#include <d3d9.h>
#include "imgui/imgui.h"
#include "imgui/impl/imgui_impl_dx9.h"
#include "imgui/impl/imgui_impl_win32.h"
#include <mutex>
#include <shared_mutex>
#include <vector>
#include <string>
#include "color.h"
#include <d3dx9.h>

#pragma warning( push )
#pragma warning( disable : 4244) //4244

class Render : public Singleton<Render>
{
	void* GameHWND;
	IDirect3DDevice9* GameDevice;
	ImDrawList* DrawList;
	ImDrawList* DrawListActualy;
	ImDrawList* DrawListRender;

public:
	WNDPROC wnd_proc = nullptr;

	void ClearDrawList();
	void BeginScene();
	ImDrawList* RenderScene();
	ImDrawList* GetDrawList() { return ImGui::GetOverlayDrawList(); }

	void NewFrame(IDirect3DDevice9* device);
	void* GetGameHWND() { return this->GameHWND; }
	IDirect3DDevice9* GetDevice() { return this->GameDevice; }
	void Init(IDirect3DDevice9* GameDevice);
};

enum DrawCallType 
{ 
	none, 
	filledbox, 
	borderedbox,
	line,
	text
};

class DrawCallFilledBox
{
public:
	int x, y;
	int w = 0;
	int h = 0;
	CColor color;
};

class DrawCallBorderedBox
{
public:
	int x, y;
	int w = 0;
	int h = 0;
	CColor color;
	int border_w = 0;
};

class DrawCallLine
{
public:
	int x1, y1, x2, y2, line_w;
	CColor color;
};

class DrawCallText
{
public:
	int x, y;
	std::string str;
	CColor color;
	LPD3DXFONT font = NULL;
};

class DrawCall
{
public:
	DrawCall() {}
	DrawCallType type = none;
	DrawCallFilledBox drawCallFilledBox;
	DrawCallBorderedBox drawCallBorderedBox;
	DrawCallLine drawCallLine;
	DrawCallText drawCallText;
};

class DXRender : public Singleton<DXRender>
{
private:
	IDirect3DDevice9* pDevice = nullptr;
	DWORD Color;
	

	void RenderFilledRect(int x, int y, int w, int h, const CColor& color);
	void RenderBorderBox(int x, int y, int w, int h, int border_w, const CColor& color);
	void RenderLine(int x1, int y1, int x2, int y2, int line_w, const CColor& color);
	void RenderText(int x, int y, const std::string& str, const CColor& color, LPD3DXFONT font = NULL);

public:
	void Begin();
	void End();

	void Init(IDirect3DDevice9* pDev);
	DWORD GetDrawColor(CColor color) const;
	void Render();
	void CreateDrawFont(int max_size, const char* font, std::vector<LPD3DXFONT>& out);


	void DrawFilledRect(int x, int y, int w, int h, CColor color);
	void DrawBorderBox(int x, int y, int w, int h, int border_w, CColor color);
	void DrawLine(int x1, int y1, int x2, int y2, int line_w, CColor color);
	void DrawString(int x, int y, const std::string& str, const CColor& color, LPD3DXFONT font = NULL);

	std::vector<DrawCall> drawCalls;
	std::vector<DrawCall> safeCalls;

	std::vector<LPD3DXFONT> DefaultFont;

	mutable std::shared_mutex mutex;
};
#pragma warning( pop )