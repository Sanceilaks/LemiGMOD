#pragma once
#include "Singleton.h"


class HackCore : public Singleton<HackCore>
{
public:
	bool Init();
	bool Unload(void* dll);
};