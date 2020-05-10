#include "AimBot.h"
#include "QAngle.h"
#include "Interfaces.h"
#include "GameTools.h"
#include "Settings.h"

Math::CVector CalcAngle(Math::CVector src, Math::CVector dst)
{
	auto ret = Math::CVector();
	Math::CVector delta = src - dst;
	double hyp = delta.Length2D();
	ret.y = (atan(delta.y / delta.x) * 57.295779513082f);
	ret.x = (atan(delta.z / hyp) * 57.295779513082f);
	ret.z = 0.f;

	if (delta.x >= 0.f)
		ret.y += 180.f;
	return ret;
}

CBasePlayer* AimBot::GetClosestEnemy()
{
	CBasePlayer* LocalPlayer = CBasePlayer::GetLocalPlayer();

	if (!LocalPlayer || LocalPlayer->GetHealth() <= 0) return NULL;

	float maxdist = 999999;
	int closestdistindex = -1;

	for (size_t i = 0; i <= Interfaces::Get().Engine->GetMaxClients(); i++)
	{
		CBasePlayer* ent = (CBasePlayer*)Interfaces::Get().EntityList->GetEntityByIndex(i);

		if (!ent) continue;
		if (ent->GetHealth() <= 0 || ent == CBasePlayer::GetLocalPlayer() || !ent->isDormant()) continue;

		float currentdist = LocalPlayer->GetDistance(ent);

		if (!(currentdist < maxdist)) continue;

		maxdist = currentdist;
		closestdistindex = i;
	}

	if (closestdistindex == -1) return NULL;

	return (CBasePlayer*)Interfaces::Get().EntityList->GetEntityByIndex(closestdistindex);
}


void AimBot::DoAim(CUserCmd* UCMD)
{
	if (!CoreSettings::Get().GetHackSettings()->AIM->isActive) return;
	if (!Interfaces::Get().Engine->isInGame()) return;
	CBasePlayer* enemy = GetClosestEnemy();
	if (!enemy) return;

	CBasePlayer* LocalPlayer = CBasePlayer::GetLocalPlayer();
	if (!LocalPlayer || LocalPlayer->GetHealth() <= 0) return;

	Math::QAngle VA = UCMD->ViewAngles;
	Math::QAngle ang = UCMD->ViewAngles;
	ang = CalcAngle(LocalPlayer->GetEyePosition(), GameTools::GetEntityBone(enemy, ECSPlayerBones::head_0));
	//Math::ClampAngles(ang);
	//ang = GameTools::FixAngles(ang);
	

	//std::cout << "X = " << ang.x << " Y = " << ang.y << " Z = " << ang.z << "\n";

	if (!CoreSettings::Get().GetHackSettings()->AIM->isSilent)
		Interfaces::Get().Engine->SetViewAngles(ang);
	else
	{
		UCMD->ViewAngles = ang;
		//UCMD->ViewAngles = ang;
	}
}