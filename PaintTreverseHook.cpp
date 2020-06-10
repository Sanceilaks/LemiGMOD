#include "PaintTreverseHook.h"
#include "Interfaces.h"
#include "menu.h"
#include "GLOBALS.h"
#include "ESPBox.h"
#include "OtherVisual.h"

namespace MyHooks
{
	void __fastcall MyPaintTraverse(IPanel* p_panel, void*, unsigned int panel, bool force_repaint, bool allow_force)
	{
		if (!OverlayPopupPanel)
		{
			const char* szName = Interfaces::Get().Panel->GetName(panel);
			if (szName[0] == 'O' && szName[7] == 'P')
				OverlayPopupPanel = panel;
		}
	}
}