#include "CreateMoveHook.h"
#include "BasePlayer.h"
#include "BannyHop.h"
#include "GLOBALS.h"
#include <Windows.h>
#include "AimBot.h"
#include "Settings.h"
#include "GameTools.h"

#define	FL_ONGROUND				(1<<0)

bool __fastcall MyHooks::MyCreateMoveHook(void* ecx, void* edx, int FrameTime, CUserCmd* UCMD)
{
	Math::QAngle oldView = UCMD->ViewAngles;
	float oldSlideMove = UCMD->SideMove;
	float oldForwardMove = UCMD->ForwardMove;

	BannyHop::Get().DoBhop(UCMD);

	if (GetAsyncKeyState(CoreSettings::Get().GetHackSettings()->AIM->AimKey))
		if (!AimBot::Get().DoAim(UCMD))
			G::Get().GetOthervars()->isAiming = false;
	else
		G::Get().GetOthervars()->isAiming = false;

	if (G::Get().GetMenuVars()->MenuIsOpen)
		UCMD->Buttons &= ~IN_ATTACK;

	G::Get().GetOthervars()->GameFOV = GameTools::GetFov();

	//if (CoreSettings::Get().GetHackSettings()->VISUAL->bCustomFov)
	//	GameTools::SetFov(CoreSettings::Get().GetHackSettings()->VISUAL->iCustomFov);

	return false;
}