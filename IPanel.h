#pragma once


class IPanel
{
public:
	const char* GetName(int iIndex)
	{
		using orig_fn = const char*(__thiscall*)(IPanel*, int); //36
		return(*(orig_fn**)this)[36](this, iIndex);
	}
};