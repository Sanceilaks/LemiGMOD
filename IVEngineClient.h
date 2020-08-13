#pragma once
#include <cstdint>
#include "QAngle.h"
#include "VMatrix.h"
#include "vector2d.h"

#pragma warning( push )
#pragma warning( disable : 4244) //4244

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

	bool GetPlayerInfo(int index, player_info_t* info)
	{
		using orig_fn = bool(__thiscall*)(IVEngineClient*, int, player_info_t*);
		return(*(orig_fn**)this)[8](this, index, info);
	}

	const Math::VMatrix& GetViewMatrix()
	{
		using orig_fn = const Math::VMatrix&(__thiscall*)(IVEngineClient*);
		return(*(orig_fn**)this)[36](this);
	}

	void GetScreenSize(int& width, int& height) {
		using original_fn = void(__thiscall*)(IVEngineClient*, int&, int&);
		return (*(original_fn**)this)[5](this, width, height);
	}
	
	Math::CVector2D GetScreenSize()
	{
		int w, h;
		this->GetScreenSize(w, h);
		return Math::CVector2D(w, h);
	}

	void SetViewAngles(Math::QAngle& Angle)
	{
		using original_fn = void(__thiscall*)(IVEngineClient*, Math::CVector&);
		return (*(original_fn**)this)[20](this, Angle);
	}
	int GetMaxClients()
	{
		using orig_fn = int(__thiscall*)(IVEngineClient*);
		return(*(orig_fn**)this)[21](this);
	}

	bool isTakingScreenshot()
	{
		using fn = bool(__thiscall*)(IVEngineClient*);
		return (*(fn**)this)[86](this); //86
	}
};
#pragma warning( pop )