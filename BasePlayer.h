#pragma once
#include "CBaseEntity.h"
#include "Interfaces.h"
#include "CBaseWeapon.h"

class CBasePlayer : public CBaseEntity
{
public:
	static CBasePlayer* GetLocalPlayer()
	{
		return (CBasePlayer*)Interfaces::Get().EntityList->GetEntityByIndex(Interfaces::Get().Engine->GetLocalPlayerIndex());
	}

	NETVAR("DT_BasePlayer", "m_fFlags", GetFlags, int);
	NETVAR("DT_BasePlayer", "m_vecViewOffset[0]", GetViewOffset, Math::CVector);
	NETVAR("DT_BaseCombatCharacter", "m_hActiveWeapon", ActiveWeaponHandle, uintptr_t);


	CBaseWeapon* GetActiveWeapon()
	{
		return (CBaseWeapon*)Interfaces::Get().EntityList->GetEntityByHandle(this->ActiveWeaponHandle());
	}

	Math::CVector GetEyePosition()
	{
		return GetOrigin() + GetViewOffset();
	}
};