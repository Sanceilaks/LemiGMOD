#pragma once
#include "IPanel.h"

namespace MyHooks
{
	static unsigned int OverlayPopupPanel;
	void __fastcall MyPaintTraverse(IPanel* p_panel, void*, unsigned int panel, bool force_repaint, bool allow_force);
}