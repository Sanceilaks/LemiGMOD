#pragma once
#pragma once
#include "IBaseClientDll.h"
#include "math.h"

namespace MyHooks
{
	void __fastcall MyClientViewRender(IBaseClientDll* client, void* edx, vrect_t* rect);
}