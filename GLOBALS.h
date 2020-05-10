#pragma once
#include "Singleton.h"


struct MenuVars
{
public:
	bool MenuIsOpen = false;
};

class G : public Singleton<G>
{
	MenuVars* MenuV = new MenuVars();
public:
	MenuVars* GetMenuVars()
	{
		return this->MenuV;
	}
};