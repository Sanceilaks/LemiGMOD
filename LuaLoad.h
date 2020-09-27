#pragma once
#include "Singleton.h"
#include <stdio.h>
#include <iostream>


typedef int(__cdecl* _luaL_loadfile)(void* state, const char* filename);
typedef int(__cdecl* _lua_pcall)(void* state, int nargs, int nresults, int errfunc);

class LuaLoad : public Singleton<LuaLoad>
{
	_luaL_loadfile lua_load_file = nullptr;
	_lua_pcall lua_pcall = nullptr;
public:
	void Init();

	void LoadFile(const std::string& file);
};