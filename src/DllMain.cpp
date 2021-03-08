#include <Windows.h>
#include "DllFunctions.hpp"

extern "C" BOOL WINAPI DllMain(HINSTANCE const instance, DWORD const reason, LPVOID const reserved)
{
    DWORD dwThreadIdArray;
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(NULL, 0, ThreadFunction, "", 0, &dwThreadIdArray);
        break;
    
    default:
        break;
    }
}

