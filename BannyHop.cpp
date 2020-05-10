#include "BannyHop.h"
#include "Settings.h"
#include "BasePlayer.h"

#define	FL_ONGROUND				(1<<0)


void BannyHop::DoBhop(CUserCmd* UCMD)
{
	if (!CoreSettings::Get().GetHackSettings()->BHOP->isActive)
		return;

	CBasePlayer* LocalPlayer = CBasePlayer::GetLocalPlayer();

	if (!LocalPlayer) return;
	if (LocalPlayer->GetHealth() <= 0) return;

	if (LocalPlayer->GetFlags() & FL_ONGROUND && UCMD->Buttons & IN_JUMP)
		UCMD->Buttons &= IN_JUMP;

	//if (UCMD->Buttons & IN_JUMP && !(LocalPlayer->GetFlags() & FL_ONGROUND))
	//	UCMD->Buttons &= ~IN_JUMP;
}