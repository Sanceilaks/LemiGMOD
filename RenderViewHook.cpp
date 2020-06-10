#include "RenderViewHook.h"
#include "Settings.h"
#include "GLOBALS.h"


namespace MyHooks
{
	CViewSetup __stdcall RenderView(CViewSetup& view, int nClearFlags, int whatToDraw)
	{
		if (CoreSettings::Get().GetHackSettings()->VISUAL->bCustomFov)
			view.fovViewmodel = CoreSettings::Get().GetHackSettings()->VISUAL->iCustomFov;

		G::Get().GetOthervars()->GameFOV = view.fov;

		return view;
	}
}