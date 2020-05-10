#pragma once
#include "Singleton.h"


class ESPBox : public Singleton<ESPBox>
{
public:
	void Render();
};

