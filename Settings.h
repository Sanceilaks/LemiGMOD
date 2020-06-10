#pragma once
#include "color.h"
#include "Singleton.h"


#pragma warning( push )
#pragma warning( disable : 4244) //4244



enum AimType
{
	FOV = 0,
	DISTANCE = 1
};

enum HDrawType
{
	imgui,
	dx
};

const char* const HDrawTypeName[] = {
	"Stable",
	"Fast"
};

const char* const AimTypeName[] = {
	"Fov",
	"Distance"
};

struct BannyHopSet
{
public:
	bool isActive = true;
};


struct Visuals
{
public:
	int Dtype = imgui;
	bool bCustomFov = false;
	int iCustomFov = 90;
};

struct EspSettings
{
public:
	bool IsActive = true;
	bool DrawHealth = true;
	int MaxEspDistance = 1000;
	float BoxColor[3] = { 10, 10, 10};
	float NameColor[3] = { 255, 0, 0};
};
struct AimSettings
{
public:
	bool isActive = true;
	bool isSilent = true;
	bool AutoFire = true;
	bool OnlyVisible = true;
	bool DrawFov = false;
	int AimKey = 18;
	int MaxAimDistance = 750.0f;
	int AimFov = 30;
	int AimType = FOV;
};
struct HackSettings
{
public:
	Visuals* VISUAL = new Visuals();
	AimSettings* AIM = new AimSettings();
	EspSettings* ESP = new EspSettings();
	BannyHopSet* BHOP = new BannyHopSet();
};


struct MainMeniSettings
{
public:
	int TriggerKey = 45;
};

struct MenuSettings
{
public:
	MainMeniSettings* MainSettings = new MainMeniSettings();
};

class CoreSettings : public Singleton<CoreSettings>
{
	HackSettings* HSettings = new HackSettings();
	MenuSettings* MSetiings = new MenuSettings();
public:
	MenuSettings* GetMenuSettings() { return this->MSetiings; }
	HackSettings* GetHackSettings() { return this->HSettings; }
};


#pragma warning( pop )