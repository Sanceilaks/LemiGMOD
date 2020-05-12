#include "RenderViewHook.h"
#include "Settings.h"
#include "GLOBALS.h"


namespace MyHooks
{
	CViewSetup __stdcall RenderView(CViewSetup& view, int nClearFlags, int whatToDraw)
	{
		if (CoreSettings::Get().GetHackSettings()->VISUAL->bCustomViewModelFov)
			view.fovViewmodel = CoreSettings::Get().GetHackSettings()->VISUAL->iCustomViewModelFov;

		G::Get().GetOthervars()->GameFOV = view.fov;

		return view;
	}
}