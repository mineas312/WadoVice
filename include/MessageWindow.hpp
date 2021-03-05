#pragma once
#include <string>
#include <Windows.h>

enum class MSG_WINDOW_TYPES
{
    ABORT_RETRY_IGNORE = 0x00000002L,
    CANCEL_TRY_CONTINUE = 0x00000006L,
    HELP = 0x00004000L,
    OK = 0x00000000L,
    OK_CANCEL = 0x00000001L,
    RETRY_CANCEL = 0x00000005L,
    YES_NO = 0x00000004L,
    YES_NO_CANCEL = 0x00000003L
};

DWORD WINAPI CreateMessageBox(LPVOID lpParam);

struct MsgParams
{
    std::string title;
    std::string message;
    MSG_WINDOW_TYPES mwt;
};

MsgParams *createMsgParams(std::string title, std::string message, MSG_WINDOW_TYPES mwt);

class MessageWindow
{
  public:
    MessageWindow();

    // Wyświetla message boxa, zatrzymuje działanie programu do czasu kliknięcia
    static void show_message(std::string title, std::string message, MSG_WINDOW_TYPES mwt);

    static void show_async_message(MsgParams *params);
};
