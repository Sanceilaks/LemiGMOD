#pragma once
#include <cstdint>
#include "QAngle.h"
#include "VMatrix.h"

struct player_info_t
{
	char name[32];
	int  id;
	char guid[33];
	struct
	{
		uint32_t id;
		char name[32];
	} buddy;
	bool bot;
	bool hltv;
	uint32_t files[4];
	uint8_t  downloaded;
};

class IVEngineClient
{
public:
	int GetLocalPlayerIndex()			//Get LocalPlayer INDEX. NOT OBJECT!
	{
		using orig_fn = int(__thiscall*)(IVEngineClient*);
		return (*(orig_fn**)this)[12](this);
	}

	float GetLastTimeStemp()
	{
		using orig_fn = float(__thiscall*)(IVEngineClient*);
		return(*(orig_fn**)this)[14](this);
	}

	const char* GetLevelName()
	{
		using orig_fn = const char* (__thiscall*)(IVEngineClient*);
		return(*(orig_fn**)this)[53](this);
	}
	bool isInGame()
	{
		using orig_fn = bool(__thiscall*)(IVEngineClient*);
		return(*(orig_fn**)this)[26](this);					//26
	}
};