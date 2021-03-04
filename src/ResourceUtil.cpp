#include <windows.h>
#include <filesystem>
#include <string>
#include <fstream>
#include <libloaderapi.h>
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HMOD ((HMODULE)&__ImageBase)
std::filesystem::path GetResourcePath(std::string res_name, std::string res_ext)
{
    HMODULE h = HMOD;
    HRSRC res_info_handle = FindResource(h, res_name.c_str(), RT_RCDATA);
    DWORD res_size = SizeofResource(h, res_info_handle);
    HGLOBAL res_data_handle = LoadResource(h, res_info_handle);
    char* res_data_ptr = static_cast<char*>(LockResource(res_data_handle));
    char* res_data_endptr = res_data_ptr + res_size;
    std::filesystem::path temp_path = std::filesystem::temp_directory_path();
    std::filesystem::path file_path = temp_path / (res_name + res_ext);
    std::ofstream file(file_path, std::ofstream::binary | std::fstream::trunc);

    while (res_data_ptr < res_data_endptr)
    {
        file << *res_data_ptr;
        ++res_data_ptr;
    }
    
    file.close();
    return file_path;
}
