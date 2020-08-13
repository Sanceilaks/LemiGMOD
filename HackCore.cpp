#pragma once
#include "HackCore.h"
#include <Windows.h>
#include <iostream>
#include "Interfaces.h"
#include "HooksManager.h"
#include "FileTools.h"

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

	//FileTools::CreateScriptsFolder();

	if (!Interfaces::Get().Init())
		printf("Interfaces load error!\n");
	Interfaces::Get().Parse();

	if (!HookManager::Get().Init())
		printf("POCHINI!!!!\n");

	return false;
}
