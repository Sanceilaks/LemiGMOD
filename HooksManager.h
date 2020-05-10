#pragma once
#include "Singleton.h"

class HookManager : public Singleton<HookManager>
{
	bool isInit = false;
public:
	bool Init();
};