#pragma once
#include <Windows.h>
#include <stdint.h>
#include "CClientClass.h"
#include "vector.h"
#include "Netvars.h"
#include "VMatrix.h"
#include "LUA.h"


class CBaseEntity
{
public:
	template<class Y>
	inline Y GetFiledValue(int offset)
	{
		return *(Y*)((DWORD)this + offset);
	}

	template<class Y>
	inline Y* GetFiledPointer(int offset)
	{
		return (Y*)((DWORD)this + offset);
	}

	void* Renderable()
	{
		return reinterpret_cast<void*>(uintptr_t(this) + 0x4);
	}

	void* Networkable() 
	{
		return reinterpret_cast<void*>(uintptr_t(this) + 0x8);
	}

	int index() 
	{
		using original_fn = int(__thiscall*)(void*);
		return (*(original_fn**)Networkable())[10](Networkable());
	}
	int isDormant() 
	{
		using original_fn = bool(__thiscall*)(void*);
		return (*(original_fn**)Networkable())[9](Networkable());
	}
	ClientClass* GetClientClass()
	{
		using original_fn = ClientClass * (__thiscall*)(void*);
		return (*(original_fn**)Networkable())[3](Networkable());
	}
	const char* GetClassName()
	{
		using orig_fn = const char* (__thiscall*)(void*);
		return (*(orig_fn**)Networkable())[2](Networkable());
	}
	bool isAlive()
	{
		using original_fn = bool(__thiscall*)(void*);
		return (*(original_fn**)this)[129](this);
	}
	bool isPlayer()
	{
		using original_fn = bool(__thiscall*)(void*);
		return (*(original_fn**)this)[130](this);
	}
	bool UsesLua()
	{
		using original_fn = bool(__thiscall*)(void*);
		return (*(original_fn**)this)[170](this);
	}
	int GetMaxHealth()
	{
		using orig_fn = int(__thiscall*)(void*);
		return(*(orig_fn**)this)[109](this);
	}
	int GetHealth()
	{
		using orig_fn = int(__thiscall*)(void*);
		return(*(orig_fn**)this)[108](this);
	}

	bool SetupBones(Math::matrix3x4_t* out, int max_bones, int mask, float time) {
		if (!this)
			return false;

		using original_fn = bool(__thiscall*)(void*, Math::matrix3x4_t*, int, int, float);
		return (*(original_fn**)Renderable())[16](Renderable(), out, max_bones, mask, time);
	}

	NETVAR("DT_BasePlayer", "m_vecOrigin", GetOrigin, Math::CVector);

	float GetDistance(CBaseEntity* to)
	{
		return this->GetOrigin().DistTo(to->GetOrigin());
	}

	inline bool isNPC()
	{
		return std::memcmp(this->GetClassNameA(), "npc", 3);
	}

	void DrawModel(int flags)
	{
		if (!this)
			return;

		using original_fn = void(__thiscall*)(void*, int);
		return (*(original_fn**)Renderable())[10](Renderable(), flags);
	}

	inline void PushEntity()
	{
		using orig_fn = void(__thiscall*)(void*);
		return(*(orig_fn**)this)[172](this);
	}

	//inline void PushEntity(LUA::Interface* glua)
	//{

	//}
};