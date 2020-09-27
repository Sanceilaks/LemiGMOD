#include "PaintTreverseHook.h"
#include "Interfaces.h"
#include "menu.h"
#include "GLOBALS.h"
#include "ESPBox.h"
#include "OtherVisual.h"

#include "fnv.h"

namespace MyHooks
{
	void __fastcall MyPaintTraverse(IPanel* p_panel, void*, unsigned int panel, bool force_repaint, bool allow_force)
	{
		//if (!OverlayPopupPanel)
		//{
		//	const char* szName = Interfaces::Get().Panel->GetName(panel);
		//	if (szName[0] == 'O' && szName[7] == 'P')
		//		OverlayPopupPanel = panel;
		//}
		
		const char* szName = Interfaces::Get().Panel->GetName(panel);
		auto pnh = fnv::hash(szName);
		
		switch (pnh)
		{
		case fnv::hash("MatSystemTopPanel"):
			//render_text(10, 10, G::get().font, "LemiCSGO", false, Color::White());
			//ESP::get().draw();

			ESPBox::Get().Render();

			break;
		case fnv::hash("FocusOverlayPanel"):
			break;
		}
	}
}