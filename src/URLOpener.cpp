#include "URLOpener.hpp"
#include <windows.h>

URLOpener::URLOpener()
{}

void URLOpener::open_url(std::string url)
{
    ShellExecute(NULL, "open", ("microsoft-edge:" + url).c_str(), NULL, NULL, SW_SHOWNORMAL);
}
