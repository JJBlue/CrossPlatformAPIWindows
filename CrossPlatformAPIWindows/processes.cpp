#include "pch.h"

#include "processes.h"

#include <Psapi.h>
#include <vector>
#include <string>
#include <TlHelp32.h>

#include <iostream>

//Not used. Supported in Java 9

long long processToLong() {
	//TODO
}

HANDLE longToProcess() {
	//TODO
}

DWORD getCurrentProcessID() {
	return GetCurrentProcessId();
}

void listAllProcesses(std::vector<void*> list) {
	//DWORD processes[1], cbNeeded;

	//bool succes = EnumProcesses(processes, sizeof(processes), &cbNeeded);
	//if (succes == 0)
	//	return;

	//int size = cbNeeded / sizeof(DWORD);

	SetConsoleOutputCP(CP_UTF8);

	HANDLE processSnap;
	processSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (processSnap == INVALID_HANDLE_VALUE) return;

	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);

	if (!Process32First(processSnap, &pe32)) {
		CloseHandle(processSnap);
		return;
	}

	do {
		std::wstring str(pe32.szExeFile);

        if (str == L"javaw.exe") {
            std::wcout << str << std::endl;
            ListProcessModules(pe32.th32ProcessID);
        }

		
	} while (Process32Next(processSnap, &pe32));

	CloseHandle(processSnap);

}

BOOL TerminateMyProcess(DWORD dwProcessId, UINT uExitCode) {
	DWORD dwDesiredAccess = PROCESS_TERMINATE;
	HANDLE hProcess = OpenProcess(dwDesiredAccess, FALSE, dwProcessId);
	if (hProcess == NULL) return FALSE;

	BOOL result = TerminateProcess(hProcess, uExitCode);
	CloseHandle(hProcess);

	return result;
}

BOOL ListProcessModules(DWORD dwPID) {
    HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
    MODULEENTRY32 me32;

    hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);
    if (hModuleSnap == INVALID_HANDLE_VALUE) {
        return(FALSE);
    }

    me32.dwSize = sizeof(MODULEENTRY32);

    if (!Module32First(hModuleSnap, &me32)) {
        CloseHandle(hModuleSnap);
        return(FALSE);
    }
    
    do {
        std::wcout << "\n\n     MODULE NAME:     " << std::wstring(me32.szModule) << std::endl;
        std::wcout << "\n     Executable     = " << std::wstring(me32.szExePath) << std::endl;
        std::cout << "\n     Process ID     = " << me32.th32ProcessID << std::endl;
        std::cout << "\n     Ref count (g)  = " << me32.GlblcntUsage << std::endl;
        std::cout << "\n     Ref count (p)  = " << me32.ProccntUsage << std::endl;
        std::cout << "\n     Base address   = " << (DWORD)me32.modBaseAddr << std::endl;
        std::cout << "\n     Base size      = " << me32.modBaseSize << std::endl;
    } while (Module32Next(hModuleSnap, &me32));

    CloseHandle(hModuleSnap);
    return(TRUE);
}

BOOL ListProcessThreads(DWORD dwOwnerPID) {
    HANDLE hThreadSnap = INVALID_HANDLE_VALUE;
    THREADENTRY32 te32;

    hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if (hThreadSnap == INVALID_HANDLE_VALUE)
        return(FALSE);

    te32.dwSize = sizeof(THREADENTRY32);

    if (!Thread32First(hThreadSnap, &te32)) {
        CloseHandle(hThreadSnap);
        return(FALSE);
    }

    do {
        if (te32.th32OwnerProcessID == dwOwnerPID) {
           
        }
    } while (Thread32Next(hThreadSnap, &te32));

    CloseHandle(hThreadSnap);
    return(TRUE);
}