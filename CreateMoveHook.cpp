#include "CreateMoveHook.h"
#include "BasePlayer.h"
#include "BannyHop.h"
#include "GLOBALS.h"
#include <Windows.h>
#include "AimBot.h"
#include "Settings.h"
#define	FL_ONGROUND				(1<<0)

bool __fastcall MyHooks::MyCreateMoveHook(void* ecx, void* edx, int FrameTime, CUserCmd* UCMD)
{
	Math::QAngle oldView = UCMD->ViewAngles;
	float oldSlideMove = UCMD->SideMove;
	float oldForwardMove = UCMD->ForwardMove;

	//BannyHop::Get().DoBhop(UCMD);

	if (CoreSettings::Get().GetHackSettings()->BHOP->isActive)
	{
		CBasePlayer* LocalPlayer = CBasePlayer::GetLocalPlayer();
		if (LocalPlayer)
		{
			if (LocalPlayer->GetHealth() <= 0)
			{
				if (UCMD->Buttons & IN_JUMP && !(LocalPlayer->GetFlags() & FL_ONGROUND))
				{
					std::cout << "JUMP   " << UCMD->Buttons << "\n";
					UCMD->Buttons &= ~IN_JUMP;
				}
			}
		}
	}


	if (GetAsyncKeyState(VK_MENU))  //if ALT				TODO:	ADD CUSTOM AIM BUTTON  (and use it in InputSystem. Without Windows.h)
		AimBot::Get().DoAim(UCMD);




	if (G::Get().GetMenuVars()->MenuIsOpen)
		UCMD->Buttons &= ~IN_ATTACK;
	return false;
}