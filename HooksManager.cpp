#include "HooksManager.h"
#include "minhook/MinHook.h"
#include "Interfaces.h"
#include "ConsoleColor.h"
#include "hi.h"

unsigned int get_virtual(void* class_, unsigned int index) { return (unsigned int)(*(int**)class_)[index]; }

bool HookManager::Init()
{
	auto CreateMoveTarget		= reinterpret_cast<void*>(get_virtual(Interfaces::Get().ClientMode, 21));			        //https://github.com/danielga/sourcesdk-minimal/blob/403f18104139472451a2b3518973fadeaf9691cf/game/client/iclientmode.h#L89
	auto EndScaneTarget			= reinterpret_cast<void*>(get_virtual(Interfaces::Get().DirectX, 42));				    //In dx9 always 42
	auto ResetTarget			= reinterpret_cast<void*>(get_virtual(Interfaces::Get().DirectX, 16));					//In dx9 always 16
	auto LockCursorTarget		= reinterpret_cast<void*>(get_virtual(Interfaces::Get().Surface, 62));					
	auto RenderViewTarget		= reinterpret_cast<void*>(get_virtual(Interfaces::Get().ViewRender, 6));
	auto PaintTreverseTarget	= reinterpret_cast<void*>(get_virtual(Interfaces::Get().Panel, 41));
	auto ReadPixelsTarget       = reinterpret_cast<void*>(get_virtual(Interfaces::Get().RenderContext, 11));
	auto ClientViewRenderTarget = reinterpret_cast<void*>(get_virtual(Interfaces::Get().BaseClient, 26));


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
		throw std::runtime_error("failed to initialize LockCursor (outdated index?)");
		return false;
	}

	if (MH_CreateHook(PaintTreverseTarget, &Hooks::PaintTreverseFn::hook, reinterpret_cast<void**>(&this->PaintTreverseOriginal)) != MH_OK) {
		printf("failed to initialize PaintTreverse (outdated index?)\n");
		throw std::runtime_error("failed to initialize PaintTreverse (outdated index?)");
		return false;
	}

	if (MH_CreateHook(RenderViewTarget, &Hooks::RenderViewFn::hook, reinterpret_cast<void**>(&this->RenderViewOriginal)) != MH_OK) {
		printf("failed to initialize RenderView (outdated index?)\n");
		throw std::runtime_error("failed to initialize Reset (outdated index?)");
		return false;
	}

	if (MH_CreateHook(ReadPixelsTarget, &Hooks::ReadPixelsFn::hook, reinterpret_cast<void**>(&this->ReadPixelsOriginal)) != MH_OK) {
		printf("failed to initialize ReadPixels (outdated index?)\n");
		throw std::runtime_error("failed to initialize Reset (outdated index?)");
		return false;
	}

	if (MH_CreateHook(ClientViewRenderTarget, &Hooks::ClientViewRenderFn::hook, reinterpret_cast<void**>(&this->ClientViewRenderOriginal)) != MH_OK) {
		printf("failed to initialize ClientViewRender (outdated index?)\n");
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

void __fastcall Hooks::RenderViewFn::hook(IViewRender* ViewRender, void* edx, CViewSetup& view, int nClearFlags, int whatToDraw)
{
	MyHooks::RenderView(view, nClearFlags, whatToDraw);
	HookManager::Get().RenderViewOriginal(ViewRender, view, nClearFlags, whatToDraw);
}

void __fastcall Hooks::PaintTreverseFn::hook(IPanel* p_panel, void* edx, unsigned int panel, bool force_repaint, bool allow_force)
{
	HookManager::Get().PaintTreverseOriginal(p_panel, panel, force_repaint, allow_force);
	MyHooks::MyPaintTraverse(p_panel, edx, panel, force_repaint, allow_force);
}

void __fastcall Hooks::ReadPixelsFn::hook(IMatRenderContext* self, uintptr_t edx, int x, int y, int w, int h, uint8_t* data, int dst)
{
	MyHooks::MyReadPixels(self, edx, x, y, w, h, data, dst);
	HookManager::Get().ReadPixelsOriginal(self, x, y, w, h, data, dst);
}

void __fastcall Hooks::ClientViewRenderFn::hook(IBaseClientDll* client, void* edx, vrect_t* rect)
{
	HookManager::Get().ClientViewRenderOriginal(client, rect);
	MyHooks::MyClientViewRender(client, edx, rect);
}