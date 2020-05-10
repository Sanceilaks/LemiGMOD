#pragma once
#include "Singleton.h"
#include "CUserCmd.h"


class BannyHop : public Singleton<BannyHop>
{
public:
	void DoBhop(CUserCmd* UCMD);
};

