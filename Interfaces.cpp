#include "Interfaces.h"
#include "MemTools.h"
#include "ConsoleColor.h"


bool Interfaces::Init()
{
	this->Engine     = (IVEngineClient*)CMemTools::GetInterface("engine.dll", "VEngineClient015");
	this->BaseClient = (IBaseClientDll*)CMemTools::GetInterface("client.dll", "VClient017");
	this->EntityList = (IVClientEntityList*)CMemTools::GetInterface("client.dll", "VClientEntityList003");
	this->LuaShared  = (LUA::Shared*)CMemTools::GetInterface("lua_shared.dll", "LUASHARED003");
	this->Surface    = (ISurface*)CMemTools::GetInterface("vguimatsurface.dll", "VGUI_Surface030");
	this->InputSystem = (IInputSystem*)CMemTools::GetInterface("inputsystem.dll", "InputSystemVersion001");
	

	do {
		this->ClientMode = **(IClientMode***)((*(uintptr_t**)this->BaseClient)[10] + 0x5);
	} while (!this->ClientMode);
	this->DirectX = **(IDirect3DDevice9***)(CMemTools::PatternScaner("shaderapidx9.dll", "A1 ? ? ? ? 50 8B 08 FF 51 0C"));



	this->isInit = true;
	return this->isInit;
}
void Interfaces::Parse()
{
	std::cout << ColorConsole::red << "{CORE} " << ColorConsole::white << "Engine      = " << ColorConsole::yellow << reinterpret_cast<DWORD>(this->Engine) << ColorConsole::white << "\n";
	std::cout << ColorConsole::red << "{CORE} " << ColorConsole::white << "BaseClient  = " << ColorConsole::yellow << reinterpret_cast<DWORD>(this->BaseClient) << ColorConsole::white << "\n";
	std::cout << ColorConsole::red << "{CORE} " << ColorConsole::white << "EntityList  = " << ColorConsole::yellow << reinterpret_cast<DWORD>(this->EntityList) << ColorConsole::white << "\n";
	std::cout << ColorConsole::red << "{CORE} " << ColorConsole::white << "LuaShared   = " << ColorConsole::yellow << reinterpret_cast<DWORD>(this->LuaShared) << ColorConsole::white << "\n";
	std::cout << ColorConsole::red << "{CORE} " << ColorConsole::white << "Surface     = " << ColorConsole::yellow << reinterpret_cast<DWORD>(this->Surface) << ColorConsole::white << "\n";
	std::cout << ColorConsole::red << "{CORE} " << ColorConsole::white << "InputSystem = " << ColorConsole::yellow << reinterpret_cast<DWORD>(this->InputSystem) << ColorConsole::white << "\n";
	std::cout << ColorConsole::red << "{CORE} " << ColorConsole::white << "ClientMode  = " << ColorConsole::yellow << reinterpret_cast<DWORD>(this->ClientMode) << ColorConsole::white << "\n";
	std::cout << ColorConsole::red << "{CORE} " << ColorConsole::white << "DXAPI	   = " << ColorConsole::yellow << reinterpret_cast<DWORD>(this->DirectX) << ColorConsole::white << "\n";
}