#pragma once
#include "Netvars.h"




class CBaseWeapon
{
public:
	bool UsesLua()
	{
		using orig_fn = bool(__thiscall*)(void*);
		return (*(orig_fn**)this)[170](this);
	}
	bool HasPrimaryAmmo()
	{
		using orig_fn = bool(__thiscall*)(void*);
		return (*(orig_fn**)this)[27](this);
	}

	float m_flNextPrimaryAttack()
	{
		if (this == nullptr)
			return 0.0f;
		return *reinterpret_cast<float*>((DWORD)this + 0x17CC);
	}

	bool CanFire()
	{
		if (!this)
			return false;

		if (/*this->m_flNextPrimaryAttack() <= Interfaces::GlobalVars->curtime &&*/ this->HasPrimaryAmmo())
			return true;

		return false;
	}
};