#pragma once
#include <d3d9.h>

namespace MyHooks
{
	long __stdcall Reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* pPresentationParameters, long hr);
}