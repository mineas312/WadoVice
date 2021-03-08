#include "SystemInfo.hpp"
#include <Windows.h>
#include <iostream>

SystemInfo::SystemInfo()
{}

int SystemInfo::get_screen_width(ScreenType st)
{
    if(st == ScreenType::PHYSICAL)
        return GetSystemMetrics(SM_CXSCREEN);
    else if(st == ScreenType::VIRTUAL)
        return GetSystemMetrics(SM_CXVIRTUALSCREEN);
}

int SystemInfo::get_screen_height(ScreenType st)
{
    if(st == ScreenType::PHYSICAL)
        return GetSystemMetrics(SM_CYSCREEN);
    else if(st == ScreenType::VIRTUAL)
        return GetSystemMetrics(SM_CYVIRTUALSCREEN);
}

struct tm *SystemInfo::get_time()
{
    time_t t = time(0);
    struct tm *time_struct = localtime(&t);
    return time_struct;
}

void SystemInfo::write_reg(std::string name, std::string val)
{
    std::string path = "SOFTWARE\\WadoVice";
    LPCSTR str = path.c_str();
    LPCSTR str2 = name.c_str();

    HKEY hKeyFolder;

    RegCreateKeyEx(HKEY_LOCAL_MACHINE, str, 0L, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKeyFolder, NULL);

    RegSetValueEx(hKeyFolder, str2, 0, REG_SZ, (LPBYTE)val.c_str(), val.size());

    RegCloseKey(hKeyFolder);
}

std::string SystemInfo::read_reg(std::string name)
{
    std::string path = "SOFTWARE\\WadoVice";
    LPCSTR str = path.c_str();

    HKEY hKeyFolder;

    RegOpenKeyExA(HKEY_LOCAL_MACHINE, str, 0, KEY_READ, &hKeyFolder);
    
    CHAR szBuffer[512];
    DWORD dwBufferSize = sizeof(szBuffer);
    RegQueryValueEx(hKeyFolder, name.c_str(), 0, NULL, (LPBYTE)szBuffer, &dwBufferSize);

    std::string ret = "";

    for(int i = 0; i < 512; i++)
    {
        if(szBuffer[i] == '\0')
            break;
        else
            ret += szBuffer[i];
    }

    return ret;
}
