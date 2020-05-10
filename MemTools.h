#pragma once

#pragma region includes

#include <Windows.h>
#include <iostream>
#include <vector>

#pragma endregion

#pragma region protos

typedef void* (*Interface)(const char* _Name, int Return);
typedef void* (*InstantiateInterface)();

#pragma endregion



class CMemTools
{
public:
	static void* GetInterface(const char* _Module, const char* _Interface);
	static std::uint8_t* PatternScaner(const char* module_name, const char* signature) noexcept;
	template< typename Function > static Function EmulateVirtual(void* _VMT, int Index);
};