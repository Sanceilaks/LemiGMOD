#include "LuaLoad.h"
#include <Windows.h>
#include <filesystem>
#include "Interfaces.h"
#include <future>

void LuaLoad::Init()
{
	HMODULE luaShared = GetModuleHandleA("lua_shared.dll");
	if (!luaShared)
	{
		std::cout << "luaShared null" << std::endl;
		return;
	}

	lua_load_file = (_luaL_loadfile)GetProcAddress(luaShared, "luaL_loadfile");
	if (!lua_load_file)
	{
		std::cout << "lua_load_file null" << std::endl;
		return;
	}

	lua_pcall = (_lua_pcall)GetProcAddress(luaShared, "lua_pcall");
	if (!lua_pcall)
	{
		std::cout << "lua_pcall null" << std::endl;
		return;
	}
}

void LuaLoad::LoadFile(const std::string& file)
{
	if (!std::filesystem::exists(file))
		return;

	auto lua = Interfaces::Get().LuaShared->CreateInterface(LUA::Type::client);
	if (!lua)
		return;

	std::async(std::launch::async, [&] 
	{
		std::ifstream File;

		File.open(file.c_str());

		if (File)
		{
			std::string lua_string((std::istreambuf_iterator<char>(File)), std::istreambuf_iterator<char>());
			lua->RunString("", "", lua_string.c_str());
		}
		File.close();

	});
}
