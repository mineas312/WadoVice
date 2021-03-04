#include "URLOpener.hpp"
#include <stdlib.h>

URLOpener::URLOpener()
{
}

void URLOpener::open_url(std::string url)
{
    std::string tmp = "start microsoft-edge:" + url;
    system(tmp.c_str());
}
