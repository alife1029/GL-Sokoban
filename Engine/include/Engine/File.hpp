#ifndef FILE_HPP
#define FILE_HPP

#include "Engine/API.hpp"
#include <string>

namespace engine
{
    class ENGINE_API File
    {
    public:
        static std::string ReadText(const char* file);
        static void WriteText(const char* file, const std::string& data);
    };
}

#endif
