#include "DllFunctions.hpp"
#include <MouseHandler.hpp>
#include <MessageWindow.hpp>
#include <URLOpener.hpp>
#include <MP3Player.hpp>
#include <BorderlessTransparentWindow.hpp>
#include <Drawing/Anims/Kremuwka.hpp>
#include <SystemInfo.hpp>
#include <vector>
#include <random>
#include <iostream>

DllFunctions::DllFunctions()
{
}

void DllFunctions::test()
{

}

DWORD WINAPI ThreadFunction(LPVOID lpParam)
{
    int screen_width = SystemInfo::get_screen_width(ScreenType::VIRTUAL);
    int screen_height = SystemInfo::get_screen_height(ScreenType::VIRTUAL);
    std::vector<Animation *> animations;
    BorderlessTransparentWindow *anims_window = new BorderlessTransparentWindow();
    for (int i = 1; i < 50; i++)
    {
        animations.push_back(new Kremuwka(anims_window->dx, screen_width, screen_height, 0, 0, i));
    }
    anims_window->create_window(NULL, animations, "KREMUWKUJ", screen_width, screen_height);

    SystemInfo::write_reg("hehe", "asd");
    std::cout << SystemInfo::read_reg("hehe") << std::endl;

    while (1)
        Sleep(1);
    return 0;
}
