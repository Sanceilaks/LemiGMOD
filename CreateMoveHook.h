#pragma once
#include "HooksManager.h"

namespace MyHooks
{
	bool __fastcall MyCreateMoveHook(void* ecx, void* edx, int FrameTime, CUserCmd* UCMD);
}