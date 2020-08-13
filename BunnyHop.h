#pragma once
#include "Singleton.h"
#include "CUserCmd.h"


class BunnyHop : public Singleton<BunnyHop>
{
public:
	void DoBhop(CUserCmd* UCMD);
};

