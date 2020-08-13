#include "AimBot.h"
#include "QAngle.h"
#include "Interfaces.h"
#include "GameTools.h"
#include "Settings.h"
#include "ImGuiBaseDraw.h"
#include <cmath>
#include "GLOBALS.h"
#include "math.h"
#include "checksum_md5.h"



#pragma warning( push )
#pragma warning( disable : 4244) //4244


CBasePlayer* AimBot::GetClosestEnemy(CUserCmd* UCMD)
{
	CBasePlayer* LocalPlayer = CBasePlayer::GetLocalPlayer();

	if (!LocalPlayer || LocalPlayer->GetHealth() <= 0) return NULL;

	float maxdist = CoreSettings::Get().GetHackSettings()->AIM->MaxAimDistance;
	int MaxFov = CoreSettings::Get().GetHackSettings()->AIM->AimFov;
	int closestdistindex = -1;

	for (size_t i = 0; i <= Interfaces::Get().Engine->GetMaxClients(); i++)
	{
		CBasePlayer* ent = (CBasePlayer*)Interfaces::Get().EntityList->GetEntityByIndex(i);

		if (!ent) continue;
		if (ent->GetHealth() <= 0 || ent == CBasePlayer::GetLocalPlayer() || !ent->isDormant()) continue;

		if (CoreSettings::Get().GetHackSettings()->AIM->OnlyVisible)
			if (!GameTools::IsVisible(LocalPlayer->GetEyePosition(), ent->GetEyePosition(), ent))
				continue;

		float currentdist = LocalPlayer->GetDistance(ent);
		int currentfov = GameTools::GetFoV(UCMD->ViewAngles, LocalPlayer->GetEyePosition(), ent->GetEyePosition(), false);

		if (CoreSettings::Get().GetHackSettings()->AIM->AimType == AimType::DISTANCE)
		{
			if (!(currentdist < maxdist)) continue;
			if (!(currentfov < MaxFov)) continue;
		}
		else
		{
			if (!(currentfov < MaxFov)) continue;
			if (!(currentdist < maxdist)) continue;
		}

		maxdist = currentdist;
		MaxFov = currentfov;
		closestdistindex = i;
	}

	if (closestdistindex == -1) return NULL;

	return (CBasePlayer*)Interfaces::Get().EntityList->GetEntityByIndex(closestdistindex);
}

bool AimBot::DoAim(CUserCmd* UCMD)
{
	if (!CoreSettings::Get().GetHackSettings()->AIM->isActive) return false;
	if (!Interfaces::Get().Engine->isInGame()) return false;
	CBasePlayer* enemy = GetClosestEnemy(UCMD);
	if (!enemy) return false;

	CBasePlayer* LocalPlayer = CBasePlayer::GetLocalPlayer();
	if (!LocalPlayer || LocalPlayer->GetHealth() <= 0) return false;

	Math::QAngle ang = UCMD->ViewAngles;
	ang = GameTools::CalcAngle(LocalPlayer->GetEyePosition(), GameTools::GetEntityBone(enemy, ECSPlayerBones::head_0));

	ang = ang + SpreadAngle(UCMD);

	if (!CoreSettings::Get().GetHackSettings()->AIM->isSilent)
		Interfaces::Get().Engine->SetViewAngles(ang);
	else
		UCMD->ViewAngles = ang;

	if (CoreSettings::Get().GetHackSettings()->AIM->AutoFire)
		if (GameTools::IsVisible(LocalPlayer->GetEyePosition(), enemy->GetEyePosition(), enemy))
			if (LocalPlayer->GetActiveWeapon()->CanFire())
				UCMD->Buttons |= IN_ATTACK;

	G::Get().GetOthervars()->isAiming = true;
	this->TargetPly = enemy;
	return true;
}

void AimBot::DrawTarget()
{
	if (!CoreSettings::Get().GetHackSettings()->AIM->isActive) return;
	if (!Interfaces::Get().Engine->isInGame()) return;
	if (!this->TargetPly) return;

	if (this->TargetPly->GetHealth() <= 0 || this->TargetPly == CBasePlayer::GetLocalPlayer() || !this->TargetPly->isDormant()) return;

	Math::CVector vHead = this->TargetPly->GetEyePosition();

	Math::CVector vScreenHead;

	if (GameTools::WorldToScreen(vHead, vScreenHead))
			DXDraw::RenderOutlinedCricle(vScreenHead.x, vScreenHead.y, 10, CColor(50, 10, 60));
}

Math::QAngle AimBot::SpreadAngle(CUserCmd* UCMD)
{
	CBasePlayer* LocalPlayer = CBasePlayer::GetLocalPlayer();

	Math::CVector SpreadCone = LocalPlayer->GetActiveWeapon()->GetBulletSpread();
	float Spread = Math::FloatNegate((SpreadCone.x + SpreadCone.y + SpreadCone.z) / 3);

	float Random[2];
	unsigned int seed = MD5_PseudoRandom(UCMD->CommandNumber) & 0xFF;
	Interfaces::Get().Random->SetSeed(seed);

	Random[0] = Interfaces::Get().Random->RandomFloat(-0.5f, 0.5f) + Interfaces::Get().Random->RandomFloat(-0.5f, 0.5f);
	Random[1] = Interfaces::Get().Random->RandomFloat(-0.5f, 0.5f) + Interfaces::Get().Random->RandomFloat(-0.5f, 0.5f);

	Math::CVector ShootDirection = Math::CVector(1.0f, 0.0f, 0.0f) + (Math::CVector(0.0f, -1.0f, 0.0f) * Spread * Random[0]) + 
		(Math::CVector(0.0f, 0.0f, 1.0f) * Spread * Random[1]); // 0,0,0

	Math::QAngle out = GameTools::CalcAngle(Math::CVector(0, 0, 0), ShootDirection);
	out = GameTools::FixAngles(out);
	return out;
}

#pragma warning( pop )