#pragma once
#include "BasePlayer.h"
#include "CUserCmd.h"
#include "Singleton.h"

class AimBot : public Singleton<AimBot>
{
public:
	CBasePlayer* GetClosestEnemy();
	void DoAim(CUserCmd* UCMD);
};

