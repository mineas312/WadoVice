#pragma once
#include <filesystem>
#include <string>

struct ResourceMem
{
    char *start;
    unsigned long size;
};

class ResourceUtil
{
  public:
    ResourceUtil();
    static std::filesystem::path GetResourcePath(std::string res_name, std::string res_ext);
    static ResourceMem GetResourceMemory(std::string res_name);
};
