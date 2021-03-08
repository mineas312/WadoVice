#pragma once
#include <ctime>
#include <string>

enum class ScreenType
{
    PHYSICAL,
    VIRTUAL
};

class SystemInfo
{
public:
    SystemInfo();

    static int get_screen_width(ScreenType st);
    static int get_screen_height(ScreenType st);

    static struct tm *get_time();

    static void write_reg(std::string name, std::string val);
    static std::string read_reg(std::string name);
};
