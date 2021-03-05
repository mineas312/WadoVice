#include <MouseHandler.hpp>
#include <MessageWindow.hpp>
#include <URLOpener.hpp>
#include <MP3Player.hpp>
#include <Kremuwka.hpp>
#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    MP3Player Player;
    Player.LoadRes("JEBAU");
    Player.Play("JEBAU", true);

    MouseHandler::move_mouse(40, 40);
    MouseHandler::click_mouse(MOUSE_CLICK::LEFT);

    URLOpener::open_url("https://www.youtube.com/watch?v=khpq8uenSPw");
    MessageWindow::show_async_message(createMsgParams("JAN PAWEL DRUGI", "JEBAL MALE DZIECI", MSG_WINDOW_TYPES::OK));

    Kremuwka kremuwka = Kremuwka(hInstance);
    kremuwka.Kremuwkuj(15);
    while (1)
        Sleep(1);
    return 0;
}
