#pragma once
#include <string>

class URLOpener
{
public:
    URLOpener();

    // Otwiera stronę internetową w edge, umożliwia to autoplay youtube
    static void open_url(std::string url);
};
