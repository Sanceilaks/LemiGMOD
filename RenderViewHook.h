#pragma once
#include "CViewSetup.h"

namespace MyHooks
{
	CViewSetup __stdcall RenderView(CViewSetup& view, int nClearFlags, int whatToDraw);
}