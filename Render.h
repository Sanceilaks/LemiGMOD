#pragma once
#include "Singleton.h"
#include <d3d9.h>
#include "imgui/imgui.h"
#include "imgui/impl/imgui_impl_dx9.h"
#include "imgui/impl/imgui_impl_win32.h"
#include <mutex>
#include <shared_mutex>
#include <vector>
#include <d3d9.h>

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


enum DrawCallType { none, filledbox, borderedbox };
class Vec2 { public: Vec2(float x, float y) { this->x = x; this->y = y; }; float x, y; };

class DrawCallFilledBox
{
public:
	Vec2 origin;
	int w = 0;
	int h = 0;
	D3DCOLOR color;
};

class DrawCallBorderedBox
{
public:
	Vec2 origin;
	int w = 0;
	int h = 0;
	D3DCOLOR color;
	int thickness = 0;
};


class DrawCall
{
public:
	DrawCall() {}
	DrawCallType type = none;
	union
	{
		DrawCallFilledBox drawCallFilledBox;
		DrawCallBorderedBox drawCallBorderedBox;
	};
};

struct SD3DVertex
{
	float x = 0.f, y = 0.f, z = 0.f, rhw = 0.f;
	DWORD color = 0;
};

class DXRender : public Singleton<DXRender>
{
public:
	void RenderBorderedBox(Vec2 pos, int w, int h, int thickness, D3DCOLOR color);
	void RenderFilledBox(Vec2 pos, int w, int h, D3DCOLOR color);

	void Begin();
	void End();

	void Render(IDirect3DDevice9* device);

	std::vector<DrawCall> drawCalls;
	std::vector<DrawCall> safeCalls;

	mutable std::shared_mutex mutex;
};
#pragma warning( pop )