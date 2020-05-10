#include "HooksManager.h"
#include "minhook/MinHook.h"
#include "Interfaces.h"
#include "ConsoleColor.h"
#include "hi.h"

unsigned int get_virtual(void* class_, unsigned int index) { return (unsigned int)(*(int**)class_)[index]; }

bool HookManager::Init()
{
	auto CreateMoveTarget = reinterpret_cast<void*>(get_virtual(Interfaces::Get().ClientMode, 21));			        //https://github.com/danielga/sourcesdk-minimal/blob/403f18104139472451a2b3518973fadeaf9691cf/game/client/iclientmode.h#L89
	auto EndScaneTarget	  = reinterpret_cast<void*>(get_virtual(Interfaces::Get().DirectX, 42));				    //In dx9 always 42
	auto ResetTarget      = reinterpret_cast<void*>(get_virtual(Interfaces::Get().DirectX, 16));					//In dx9 always 16
	auto LockCursorTarget = reinterpret_cast<void*>(get_virtual(Interfaces::Get().Surface, 62));					

	if (MH_Initialize() != MH_OK)
	{
		printf("failed to initialize MH_Initialize.\n");
		throw std::runtime_error("failed to initialize MH_Initialize.");
		return false;
	}

	if (MH_CreateHook(CreateMoveTarget, &Hooks::CreateMove::hook, reinterpret_cast<void**>(&this->CreateMoveOriginal)) != MH_OK) {
		printf("failed to initialize CreateMove (outdated index?)\n");
		throw std::runtime_error("failed to initialize create_move. (outdated index?)");
		return false;
	}

	if (MH_CreateHook(EndScaneTarget, &Hooks::EndScane::hook, reinterpret_cast<void**>(&this->EndScaneOriginal)) != MH_OK) {
		printf("failed to initialize EndScane (outdated index?)\n");
		throw std::runtime_error("failed to initialize EndScane (outdated index?)");
		return false;
	}

	if (MH_CreateHook(ResetTarget, &Hooks::Reset::hook, reinterpret_cast<void**>(&this->ResetOriginal)) != MH_OK) {
		printf("failed to initialize Reset (outdated index?)\n");
		throw std::runtime_error("failed to initialize Reset (outdated index?)");
		return false;
	}

	if (MH_CreateHook(LockCursorTarget, &Hooks::LockCursor::hook, reinterpret_cast<void**>(&this->LockCursorOriginal)) != MH_OK) {
		printf("failed to initialize LockCursor (outdated index?)\n");
		throw std::runtime_error("failed to initialize Reset (outdated index?)");
		return false;
	}

	if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK) {
		throw std::runtime_error("failed to enable hooks.");
		return false;
	}

	std::cout << ColorConsole::red << "{CORE} " << ColorConsole::white << "Hooks initialized!\n";

	return true;
}

void HookManager::UnhookAll()
{
	MH_Uninitialize();
	MH_DisableHook(MH_ALL_HOOKS);
}

bool __fastcall Hooks::CreateMove::hook(void* ecx, void* edx, int FrameTime, CUserCmd* UCMD)
{
	HookManager::Get().CreateMoveOriginal(FrameTime, UCMD);
	return MyHooks::MyCreateMoveHook(ecx, edx, FrameTime, UCMD);
}

long __stdcall Hooks::EndScane::hook(IDirect3DDevice9* device)
{
	MyHooks::EndScane(device);
	return HookManager::Get().EndScaneOriginal(device);
}
long __stdcall Hooks::Reset::hook(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	long hr = HookManager::Get().ResetOriginal(device, pPresentationParameters);
	MyHooks::Reset(device, pPresentationParameters, hr);
	return hr;
}

void __stdcall Hooks::LockCursor::hook()
{
	if (!MyHooks::MyLockCursor())
		HookManager::Get().LockCursorOriginal(Interfaces::Get().Surface);
}