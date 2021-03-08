#include <MouseHandler.hpp>
#include <MessageWindow.hpp>
#include <URLOpener.hpp>
#include <MP3Player.hpp>
#include <BorderlessTransparentWindow.hpp>
#include <windows.h>
#include <Drawing/Anims/Kremuwka.hpp>
#include <SystemInfo.hpp>
#include <vector>
#include <random>
#include <iostream>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    //MP3Player Player;
    //Player.LoadRes("JEBAU");
    //Player.Play("JEBAU", true);

    //MouseHandler::move_mouse(40, 40);
    //MouseHandler::click_mouse(MOUSE_CLICK::LEFT);

    //URLOpener::open_url("https://www.youtube.com/watch?v=khpq8uenSPw");
    //MessageWindow::show_async_message(createMsgParams("JAN PAWEL DRUGI", "JEBAL MALE DZIECI", MSG_WINDOW_TYPES::OK));

    int screen_width = SystemInfo::get_screen_width(ScreenType::VIRTUAL);
    int screen_height = SystemInfo::get_screen_height(ScreenType::VIRTUAL);
    std::vector<Animation *> animations;
    BorderlessTransparentWindow *anims_window = new BorderlessTransparentWindow();
    for (int i = 1; i < 50; i++)
    {
        animations.push_back(new Kremuwka(anims_window->dx, screen_width, screen_height, 0, 0, i));
    }
    anims_window->create_window(hInstance, animations, "KREMUWKUJ", screen_width, screen_height);

    SystemInfo::write_reg("hehe", "asd");
    std::cout << SystemInfo::read_reg("hehe") << std::endl;

    while (1)
        Sleep(1);
    return 0;
}
