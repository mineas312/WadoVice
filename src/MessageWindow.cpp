#include "MessageWindow.hpp"
#include <Windows.h>
#include <thread>

MessageWindow::MessageWindow()
{}

void MessageWindow::show_message(std::string title, std::string message, MSG_WINDOW_TYPES mwt)
{
    MessageBox(NULL, (LPCSTR)message.c_str(), (LPCSTR)title.c_str(), (UINT)mwt);
}
