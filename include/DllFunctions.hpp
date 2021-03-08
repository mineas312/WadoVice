#pragma once
#include <Windows.h>

class DllFunctions
{
public:
    DllFunctions();

    static void test();
};

DWORD WINAPI ThreadFunction(LPVOID lpParam);
