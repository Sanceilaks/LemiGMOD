#pragma once
#include "BasePlayer.h"
#include "CUserCmd.h"
#include "Singleton.h"

class AimBot : public Singleton<AimBot>
{
public:
	CBasePlayer* TargetPly = nullptr;


	CBasePlayer* GetClosestEnemy(CUserCmd* UCMD);
	bool DoAim(CUserCmd* UCMD);
	void DrawTarget();
};

