#pragma once
#include "Singleton.h"
#include "BasePlayer.h"

struct MenuVars
{
public:
	bool MenuIsOpen = false;
	bool EntEspIsOpen = false;
};

struct OtherVars
{
public:
	int GameFOV = 0;
	bool isAiming = false;
};

//struct AimVars
//{
//public:
//	//CBasePlayer* TargePly = nullptr;
//};

class G : public Singleton<G>
{
	OtherVars* OtherV = new OtherVars();
	MenuVars* MenuV = new MenuVars();
public:
	OtherVars* GetOthervars() { return this->OtherV; }
	MenuVars* GetMenuVars() { return this->MenuV; }
};