#pragma once
#include "pch.h"
namespace proc
{
	DWORD getProcId(const wchar_t* procName);
	uintptr_t GetModuleBaseAdress(DWORD procId, const wchar_t* modName);
	uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets);


	uintptr_t FindDMAAddyInternal(uintptr_t ptr, std::vector<unsigned int> offsets);
}