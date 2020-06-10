#include "EndScaneHook.h"
#include "Render.h"

void __stdcall MyHooks::EndScane(IDirect3DDevice9* device)
{
	if (!isInit)
	{
		Render::Get().Init(device);
		isInit = true;
	}
	else
		Render::Get().NewFrame(device);
}