#include "ResetHook.h"
#include "Imgui/imgui.h"
#include "imgui/imgui_impl_dx9.h"
#include <iostream>

long __stdcall MyHooks::Reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* pPresentationParameters, long hr)
{
	ImGui_ImplDX9_InvalidateDeviceObjects();

	if (hr >= 0)
	{
		ImGui_ImplDX9_CreateDeviceObjects();
	}

	return hr;
}