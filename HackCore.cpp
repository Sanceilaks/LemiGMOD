#pragma once
#include "HackCore.h"
#include <Windows.h>
#include <iostream>
#include "Interfaces.h"

bool HackCore::Unload(void* dll)
{
	FreeConsole();

	return true;
}

bool HackCore::Init()
{
	AllocConsole();
	freopen("CONOUT$", "wb", stdout);
	freopen("CONOUT$", "wb", stderr);
	freopen("CONIN$", "rb", stdin);

	if (!Interfaces::Get().Init())
		printf("Interfaces load error!\n");

	Interfaces::Get().Parse();

	return false;
}
