#pragma once
#include "pch.h"
#include "mem.h"
#include "proc.h"

void Run()
{
	static uintptr_t moduleBaseAddr = (uintptr_t)GetModuleHandle(L"RocketLeague.exe") + 0x022E36F8;
	static std::vector<unsigned int> Offsets = { 0x930, 0x50, 0x20, 0x218, 0xF0, 0x480, 0x98};
	static int* BoostAmount = (int*)proc::FindDMAAddyInternal(moduleBaseAddr, Offsets);
	if (GetAsyncKeyState(VK_SPACE))
	{
		std::cout <<  *BoostAmount << std::dec << std::endl;
	}
}