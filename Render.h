#pragma once
#include "Singleton.h"
#include <d3d9.h>
#include "imgui/imgui.h"
#include "imgui/impl/imgui_impl_dx9.h"
#include "imgui/impl/imgui_impl_win32.h"
#include <mutex>


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

	void NewFrame();
	void* GetGameHWND() { return this->GameHWND; }
	IDirect3DDevice9* GetDevice() { return this->GameDevice; }
	void Init(IDirect3DDevice9* GameDevice);
};

