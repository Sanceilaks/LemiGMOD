#pragma once
#include "Singleton.h"

class Visual : public Singleton<Visual>
{
public:
	void DrawFovCricle();
};