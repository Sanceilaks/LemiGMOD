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
	NETVAR("DT_BasePlayer", "m_vecMins", GetOBBMin, Math::CVector);
	NETVAR("DT_BasePlayer", "m_vecMaxs", GetOBBMax, Math::CVector);

	CBaseWeapon* GetActiveWeapon()
	{
		return (CBaseWeapon*)Interfaces::Get().EntityList->GetEntityByHandle(this->ActiveWeaponHandle());
	}

	Math::CVector GetEyePosition()
	{
		return GetOrigin() + GetViewOffset();
	}

	inline bool GetName(std::string& name_in)
	{
		player_info_t pi;
		if (!Interfaces::Get().Engine->GetPlayerInfo(this->index(), &pi))
			return false;
		name_in = std::string((const char*)pi.name);
		return true;
	}
};