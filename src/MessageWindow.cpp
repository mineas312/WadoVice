#include "MessageWindow.hpp"

DWORD WINAPI CreateMessageBox(LPVOID lpParam)
{
    MsgParams params = *((MsgParams *)lpParam);
    MessageBoxA(NULL, params.message.c_str(), params.title.c_str(), (UINT)params.mwt);
    return 0;
}

MsgParams *createMsgParams(std::string title, std::string message, MSG_WINDOW_TYPES mwt)
{
    MsgParams *params = new MsgParams();
    params->message = message;
    params->title = title;
    params->mwt = mwt;
    return params;
}

MessageWindow::MessageWindow()
{}

void MessageWindow::show_message(std::string title, std::string message, MSG_WINDOW_TYPES mwt)
{
    MessageBoxA(NULL, message.c_str(), title.c_str(), (UINT)mwt);
}

void MessageWindow::show_async_message(MsgParams *params)
{
    CreateThread(NULL, 0, &CreateMessageBox, params, 0, NULL);
}
