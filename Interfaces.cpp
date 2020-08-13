#include "Interfaces.h"
#include "MemTools.h"
#include "ConsoleColor.h"

template<typename T>
void printInterface(T interface_)
{
	std::string text = std::string(typeid(interface_).name());
	text += std::string("            = ");
	std::cout << ColorConsole::red << "{CORE} " << ColorConsole::white << text << ColorConsole::yellow << reinterpret_cast<DWORD>(interface_) << ColorConsole::white << std::endl;
}

bool Interfaces::Init()
{
	this->Engine      = (IVEngineClient*)CMemTools::GetInterface("engine.dll", "VEngineClient015");
	this->BaseClient  = (IBaseClientDll*)CMemTools::GetInterface("client.dll", "VClient017");
	this->EntityList  = (IVClientEntityList*)CMemTools::GetInterface("client.dll", "VClientEntityList003");
	this->LuaShared   = (LUA::Shared*)CMemTools::GetInterface("lua_shared.dll", "LUASHARED003");
	this->Surface     = (ISurface*)CMemTools::GetInterface("vguimatsurface.dll", "VGUI_Surface030");
	this->InputSystem = (IInputSystem*)CMemTools::GetInterface("inputsystem.dll", "InputSystemVersion001");
	this->EngineTrace = (IEngineTrace*)CMemTools::GetInterface("engine.dll", "EngineTraceClient003");
	this->RenderView  = (IRenderView*)CMemTools::GetInterface("engine.dll", "VEngineRenderView014");
	this->Panel       = (IPanel*)CMemTools::GetInterface("vgui2.dll", "VGUI_Panel009");
	this->MaterialSystem = (IMaterialSystem*)CMemTools::GetInterface("materialsystem.dll", "VMaterialSystem080");
	this->RenderContext = MaterialSystem->GetRenderContext();
	this->ModelRender = (IVModelRender*)CMemTools::GetInterface("engine.dll", "VEngineModel016");


	do {
		this->ClientMode = **(IClientMode***)((*(uintptr_t**)this->BaseClient)[10] + 0x5);
	} while (!this->ClientMode);
	this->DirectX = **(IDirect3DDevice9***)(CMemTools::PatternScaner("shaderapidx9.dll", "A1 ? ? ? ? 50 8B 08 FF 51 0C") + 1);

	do {
		this->ViewRender = **(IViewRender***)((*(uintptr_t**)this->BaseClient)[27] + 0x5);
	} while (!this->ViewRender);

	void(*RandomSeed)(int);
	*(void**)&RandomSeed = GetProcAddress(GetModuleHandleA("vstdlib.dll"), "RandomSeed");
	if (RandomSeed)
		this->Random = **(CUniformRandomStream***)((uintptr_t)RandomSeed + 0x5);

	this->isInit = true;
	return this->isInit;
}
void Interfaces::Parse()
{
	printInterface(Engine);
	printInterface(BaseClient);
	printInterface(EntityList);
	printInterface(LuaShared);
	printInterface(Surface);
	printInterface(InputSystem);
	printInterface(ClientMode);
	printInterface(DirectX);
	printInterface(EngineTrace);
	printInterface(RenderView);
	printInterface(ViewRender);
	printInterface(Random);
	printInterface(MaterialSystem);
	printInterface(RenderContext);
	printInterface(ModelRender);
	/*std::cout << ColorConsole::red << "{CORE} " << ColorConsole::white << "Engine            = " << ColorConsole::yellow << reinterpret_cast<DWORD>(this->Engine) << ColorConsole::white << "\n";
	std::cout << ColorConsole::red << "{CORE} " << ColorConsole::white << "BaseClient        = " << ColorConsole::yellow << reinterpret_cast<DWORD>(this->BaseClient) << ColorConsole::white << "\n";
	std::cout << ColorConsole::red << "{CORE} " << ColorConsole::white << "EntityList        = " << ColorConsole::yellow << reinterpret_cast<DWORD>(this->EntityList) << ColorConsole::white << "\n";
	std::cout << ColorConsole::red << "{CORE} " << ColorConsole::white << "LuaShared         = " << ColorConsole::yellow << reinterpret_cast<DWORD>(this->LuaShared) << ColorConsole::white << "\n";
	std::cout << ColorConsole::red << "{CORE} " << ColorConsole::white << "Surface           = " << ColorConsole::yellow << reinterpret_cast<DWORD>(this->Surface) << ColorConsole::white << "\n";
	std::cout << ColorConsole::red << "{CORE} " << ColorConsole::white << "InputSystem       = " << ColorConsole::yellow << reinterpret_cast<DWORD>(this->InputSystem) << ColorConsole::white << "\n";
	std::cout << ColorConsole::red << "{CORE} " << ColorConsole::white << "ClientMode	   = " << ColorConsole::yellow << reinterpret_cast<DWORD>(this->ClientMode) << ColorConsole::white << "\n";
	std::cout << ColorConsole::red << "{CORE} " << ColorConsole::white << "DXAPI	         = " << ColorConsole::yellow << reinterpret_cast<DWORD>(this->DirectX) << ColorConsole::white << "\n";
	std::cout << ColorConsole::red << "{CORE} " << ColorConsole::white << "EngineTrace	   = " << ColorConsole::yellow << reinterpret_cast<DWORD>(this->EngineTrace) << ColorConsole::white << "\n";
	std::cout << ColorConsole::red << "{CORE} " << ColorConsole::white << "RenderView	   = " << ColorConsole::yellow << reinterpret_cast<DWORD>(this->RenderView) << ColorConsole::white << "\n";
	std::cout << ColorConsole::red << "{CORE} " << ColorConsole::white << "ViewRender	   = " << ColorConsole::yellow << reinterpret_cast<DWORD>(this->ViewRender) << ColorConsole::white << "\n";
	std::cout << ColorConsole::red << "{CORE} " << ColorConsole::white << "IRandom	   = " << ColorConsole::yellow << reinterpret_cast<DWORD>(this->Random) << ColorConsole::white << "\n";*/
}