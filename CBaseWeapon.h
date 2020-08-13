#pragma once
#include "Netvars.h"
#include "CBaseEntity.h"
#include "LUA.h"


class CBaseWeapon : public CBaseEntity
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

	const Math::CVector& orgGetBulletSpread()
	{
		using orig_fn = const Math::CVector & (__thiscall*)(void*);
		return (*(orig_fn**)this)[66](this);
	}

	bool CanFire()
	{
		if (!this)
			return false;

		if (/*this->m_flNextPrimaryAttack() <= Interfaces::GlobalVars->curtime &&*/ this->HasPrimaryAmmo())
			return true;

		return false;
	}


	Math::CVector GetBulletSpread()
	{
		if (this == nullptr)
			return Math::CVector(0, 0, 0);

		if (this->UsesLua())
		{
			float LUASpreadCone = this->LUASpread();
			if (!strcmp(this->GetWeaponBase(), "weapon_tttbase"))
				LUASpreadCone = this->TTTSpread();

			if (LUASpreadCone != -1.0f)
				return Math::CVector(LUASpreadCone, LUASpreadCone, LUASpreadCone);

			LUASpreadCone = this->LUASpread2();
			if (LUASpreadCone != -1.0f)
				return Math::CVector(LUASpreadCone, LUASpreadCone, LUASpreadCone);
		}

		return this->orgGetBulletSpread();
	}

	float LUASpread()
	{
		if (!this->UsesLua())
			return -1.0f;

		auto Lua = Interfaces::Get().LuaShared->CreateInterface(LUA::Type::client);
		this->PushEntity();
		Lua->GetField(-1, "Primary");
		if (!Lua->IsType(-1, 5))   //5 == table
		{
			Lua->Pop(2);
			return -1.0f;
		}
		Lua->GetField(-1, "Spread");
		if (!Lua->IsType(-1, 3))  //3 == num
		{
			std::cout << "Pop 3" << std::endl;
			Lua->Pop(3);
			return -1.0f;
		}
		double out = Lua->GetNumber(-1);
		Lua->Pop(3);
		return out;
	}

	float TTTSpread()
	{
		if (!this->UsesLua())
			return -1.0f;

		auto Lua = Interfaces::Get().LuaShared->CreateInterface(LUA::Type::client);
		Lua->PushSpecial((int)LUA::Special::glob);
		this->PushEntity();
		Lua->GetField(-1, "Primary");
		if (!Lua->IsType(-1, 5))
		{
			Lua->Pop(2);
			return -1.0f;
		}
		Lua->GetField(-1, "Cone");
		if (!Lua->IsType(-1, 3))
		{
			Lua->Pop(3);
			return -1.0f;
		}
		double out = Lua->GetNumber(-1);
		Lua->Pop(3);
		return out;
	}

	float LUASpread2()
	{
		if (!this->UsesLua())
			return -1.0f;

		auto Lua = Interfaces::Get().LuaShared->CreateInterface(LUA::Type::client);
		this->PushEntity();
		Lua->GetField(-1, "Spread");
		if (!Lua->IsType(-1, 3))
		{
			Lua->Pop(2);
			return -1.0f;
		}
		double out = Lua->GetNumber(-1);
		Lua->Pop(2);
		return out;
	}

	const char* GetWeaponBase()
	{
		auto Lua = Interfaces::Get().LuaShared->CreateInterface(LUA::Type::client);
		this->PushEntity();
		Lua->GetField(-1, "Base");
		if (!Lua->IsType(-1, (int)LUA::LuaType::TYPE_STRING))
		{
			Lua->Pop(2);
			return "";
		}
		const char* out = Lua->GetString(-1);
		Lua->Pop(2);
		return out;
	}
};