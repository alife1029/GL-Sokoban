#ifndef APP_CONFIG
#define APP_CONFIG

#include "Engine/API.hpp"
#include <string>

namespace engine
{
    struct ENGINE_API AppConfig
    {
        int Width = 640;
        int Height = 480;
        bool FullScreen = false;
        std::string Title = "Game";
    };
}

#endif
