#pragma once
#include "CClientClass.h"


class IBaseClientDll
{
public:
	ClientClass* GetAllClasses()
	{
		using orig_fn = ClientClass * (__thiscall*)(IBaseClientDll*); //8
		return(*(orig_fn**)this)[8](this);
	}
};