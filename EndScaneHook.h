#pragma once
#include <d3d9.h>

namespace MyHooks
{
	static bool isInit = false;
	void __stdcall EndScane(IDirect3DDevice9* device);
}