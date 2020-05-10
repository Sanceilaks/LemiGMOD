#pragma once
#include "color.h"
#include "Singleton.h"

//struct UISettings
//{
//
//};
//
//struct HackSettings
//{
//public:
//	struct EspBox
//	{
//	public:
//		bool IsActive = true;
//		Color BoxColor = Color(10, 10, 10);
//		Color NameColor = Color(255, 0, 0);
//	};
//	struct BannyHop
//	{
//	public:
//		bool isActive = true;
//	};
//}HackSet;


struct BannyHopSet
{
public:
	bool isActive = true;
};
struct EspSettings
{
public:
	bool IsActive = true;
	float BoxColor[3] = { 10, 10, 10};
	float NameColor[3] = { 255, 0, 0};
};
struct AimSettings
{
public:
	bool isActive = true;
	bool isSilent = true;
};
struct HackSettings
{
public:
	AimSettings* AIM = new AimSettings();
	EspSettings* ESP = new EspSettings();
	BannyHopSet* BHOP = new BannyHopSet();
};

class CoreSettings : public Singleton<CoreSettings>
{
	HackSettings* HSettings = new HackSettings();
public:
	HackSettings* GetHackSettings()
	{
		return this->HSettings;
	}
};