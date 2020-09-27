#include "OtherVisual.h"
#include "Settings.h"
#include "Interfaces.h"
#include "ImGuiBaseDraw.h"
#include "math.h"
#include "GLOBALS.h"


void Visual::DrawFovCricle()
{
	if (!CoreSettings::Get().GetHackSettings()->AIM->DrawFov) return;
	if (!Interfaces::Get().Engine->isInGame()) return;
	if (G::Get().GetMenuVars()->MenuIsOpen) return;

	int fov = CoreSettings::Get().GetHackSettings()->AIM->AimFov;
	Math::CVector2D screen = Interfaces::Get().Engine->GetScreenSize();
	if (fov > 180)
		fov = 180; 


	IMDraw::RenderOutlinedCricle(screen.x / 2, screen.y / 2, tan(DEG2RAD(fov) / 2) / tan(DEG2RAD(G::Get().GetOthervars()->GameFOV) / 2) * screen.x, CColor(0, 0, 0), 124);
}

void Visual::Test()
{
	//DXRender::Get().DrawFilledRect(0, 0, 100, 100, CColor(255, 255, 255));
}