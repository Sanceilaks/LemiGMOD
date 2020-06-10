#pragma once
#include "Singleton.h"
#include "CUserCmd.h"
#include <d3d9.h>
#include "ISurface.h"
#include "RenderView.h"
#include "CViewSetup.h"
#include "IPanel.h"

namespace Hooks
{
	namespace CreateMove
	{
		using func = bool(_stdcall*)(float, CUserCmd*);
		static bool __fastcall hook(void* ecx, void* edx, int FrameTime, CUserCmd* UCMD);
	};
	namespace EndScane
	{
		using func = long(__stdcall*)(IDirect3DDevice9*);
		static long __stdcall hook(IDirect3DDevice9* device);
	};

	namespace Reset
	{
		using func = long(__stdcall*)(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);
		static long __stdcall hook(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* pPresentationParameters);
	}
	namespace LockCursor
	{
		using func = void(__thiscall*)(ISurface*);
		static void __stdcall hook();
	};

	namespace RenderViewFn
	{
		using func = void(__thiscall*)(IRenderView*, CViewSetup&, int, int);
		static void __stdcall hook(CViewSetup& view, int nClearFlags, int whatToDraw);
	};

	namespace PaintTreverseFn
	{
		using func = void(__thiscall*)(IPanel*, unsigned int, bool, bool);
		static void __fastcall hook(IPanel* p_panel, void*, unsigned int panel, bool force_repaint, bool allow_force);
	};
}




class HookManager : public Singleton<HookManager>
{
	bool isInit = false;
public:
	Hooks::CreateMove::func CreateMoveOriginal = nullptr;
	Hooks::EndScane::func EndScaneOriginal = nullptr;
	Hooks::Reset::func ResetOriginal = nullptr;
	Hooks::LockCursor::func LockCursorOriginal = nullptr;
	Hooks::RenderViewFn::func RenderViewOriginal = nullptr;
	Hooks::PaintTreverseFn::func PaintTreverseOriginal = nullptr;

	void UnhookAll();
	bool Init();
};