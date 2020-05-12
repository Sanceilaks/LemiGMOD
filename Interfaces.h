#pragma once
#include "Singleton.h"
#include "iinclude.h"
#include <d3d9.h>


class Interfaces : public Singleton<Interfaces>
{
	bool isInit = false;
public:
	IVEngineClient* Engine = nullptr;
	IBaseClientDll* BaseClient = nullptr;
	IVClientEntityList* EntityList = nullptr;
	LUA::Shared* LuaShared = nullptr;
	ISurface* Surface = nullptr;
	IDirect3DDevice9* DirectX = nullptr;
	IInputSystem* InputSystem = nullptr;
	IClientMode* ClientMode = nullptr;
	IEngineTrace* EngineTrace = nullptr;
	IRenderView* RenderView = nullptr;

	void Parse();
	bool Init();
};

