#pragma once
#include <string>
#include <experimental/filesystem>

using namespace std::experimental;

class FileTools
{
public:
	static bool PathExist(std::string path)
	{
		return filesystem::exists(path);
	}

	static std::string GetScriptsFolder()
	{
		std::string ret = std::string(getenv("%APPDATA%")) + std::string("\\LemiGMOD\\LUA\\");
		return ret;
	}

	static void CreateScriptsFolder()
	{
		if (PathExist(GetScriptsFolder()))
			return;

		if (!PathExist(std::string(getenv("%APPDATA%")) + std::string("\\LemiGMOD")))
			filesystem::create_directory(std::string(getenv("%APPDATA%")) + std::string("\\LemiGMOD"));

		if (!PathExist(GetScriptsFolder()))
			filesystem::create_directory(GetScriptsFolder());
	}
};