#pragma once
#include "HackCore.h"
#include <Windows.h>


bool HackCore::Unload(void* dll)
{
	FreeConsole();
}

bool HackCore::Init()
{
	AllocConsole();
}
