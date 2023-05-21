#include "pch.h"
#include "proc.h"

DWORD proc::getProcId(const wchar_t* procName)
{
	DWORD procID = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		std::cout << "Sucess" << std::endl;
		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(procEntry);
		if (Process32First(hSnap, &procEntry))
		{
			do
			{
				if (!_wcsicmp(procEntry.szExeFile, procName))
				{
					procID = procEntry.th32ProcessID;
					break;
				}
			} while (Process32Next(hSnap, &procEntry));
		}
	}
	CloseHandle(hSnap);
	return procID;
}
uintptr_t proc::GetModuleBaseAdress(DWORD procID, const wchar_t* modName)
{
	uintptr_t modBaseAdress = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procID);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(hSnap, &modEntry))
		{
			do
			{
				if (!_wcsicmp(modEntry.szModule, modName))
				{
					modBaseAdress = (uintptr_t)modEntry.modBaseAddr;
					break;
				}
			} while (Module32Next(hSnap, &modEntry));
		}
	}
	else
	{
		std::cout << "Invalid Handle" << std::endl;
	}
	CloseHandle(hSnap);
	std::cout << std::hex << modBaseAdress << std::endl;
	return modBaseAdress;
}

uintptr_t proc::FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets)
{
	uintptr_t addr = ptr;
	for (unsigned int i = 0; i < offsets.size(); i++)
	{
		ReadProcessMemory(hProc, (BYTE*)addr, &addr, sizeof(addr), 0);
		addr += offsets[i];
		std::cout << std::hex << addr << std::endl;
	};
	return addr;
}

uintptr_t proc::FindDMAAddyInternal(uintptr_t ptr, std::vector<unsigned int> offsets)
{
	uintptr_t addr = ptr;
	for (unsigned int i = 0; i < offsets.size(); i++)
	{
		addr = *(uintptr_t*)addr;
		addr += offsets[i];
		std::cout << std::hex << addr << std::endl;
	};
	return addr;
}