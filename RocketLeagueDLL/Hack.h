#pragma once
#include "pch.h"
#include "Offsets.h"
#include "mem.h"
#include "proc.h"

void Run()
{
	static bool Worked = false;
	static uintptr_t moduleBaseAddr = (uintptr_t)GetModuleHandle(L"RocketLeague.exe") + 0x02525040;
	static std::vector<unsigned int> BoostOffsets = { 0x58, 0xAC0, 0x8, 0xB0, 0x340, 0x60, 0x98 };
	static std::vector<unsigned int> TurtlingOffsets = { 0x58, 0xAC0, 0x8, 0xB0, 0x340, 0x60, 0x9C };
	static int* BoostAmount = (int*)proc::FindDMAAddyInternal(moduleBaseAddr, BoostOffsets);
	static int* Turtling = (int*)proc::FindDMAAddyInternal(moduleBaseAddr, TurtlingOffsets);
	if (GetAsyncKeyState(VK_SPACE))
	{
		Worked = false;
		if (BoostAmount != NULL && *BoostAmount != NULL && *BoostAmount <= 100 && *BoostAmount >= 0)
		{
			std::cout << *BoostAmount << std::dec << std::endl;
		}
		else
		{
			std::cout << "Error when Reading Boost" << std::endl;
		}
		if (*Turtling == 3)
		{
			std::cout << "Turtling = True" << std::endl;
			Worked = true;
		}
		if (*Turtling == 2)
		{
			std::cout << "Turtling = False" << std::endl;
			Worked = true;
		}
		if (*Turtling == NULL || *Turtling != 2 && *Turtling != 3 && Worked == false)
		{
			std::cout << "Error when Reading Turtling." << std::endl;
		}
	}
}