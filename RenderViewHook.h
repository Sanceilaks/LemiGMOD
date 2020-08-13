#pragma once
#include "CViewSetup.h"

namespace MyHooks
{
	void __fastcall RenderView(CViewSetup& view, int nClearFlags, int whatToDraw);
}