#pragma once
#include "CViewSetup.h"
#include "IMatRenderContext.h"

namespace MyHooks
{
	void __fastcall MyReadPixels(IMatRenderContext* self, uintptr_t edx, int x, int y, int w, int h, uint8_t* data, int dst);
}