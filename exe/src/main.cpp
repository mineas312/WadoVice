#include <MouseHandler.hpp>
#include <MessageWindow.hpp>
#include <URLOpener.hpp>
#include <MP3Player.hpp>
#include <iostream>

int main()
{
    MP3Player Player;
    Player.LoadRes("JEBAU");
    Player.Play("JEBAU", true);

    MouseHandler::move_mouse(40, 40);
    MouseHandler::click_mouse(MOUSE_CLICK::LEFT);

    URLOpener::open_url("https://www.youtube.com/watch?v=khpq8uenSPw");
    MessageWindow::show_message("Cyka blyat", "Hello", MSG_WINDOW_TYPES::OK);

    system("pause");
    return 0;
}
