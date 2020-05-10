#pragma once
#include <cstdint>

class IVClientEntityList
{
public:
	void* GetEntityByIndex(int n)	//3
	{
		using orig_fn = void* (__thiscall*)(IVClientEntityList*, int);
		return(*(orig_fn**)this)[3](this, n);
	}
	void* GetEntityByHandle(uintptr_t handle)	//4
	{
		using orig_fn = void* (__thiscall*)(IVClientEntityList*, uintptr_t);
		return(*(orig_fn**)this)[4](this, handle);
	}
};