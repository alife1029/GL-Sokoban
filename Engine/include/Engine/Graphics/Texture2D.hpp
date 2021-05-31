#ifndef TEXTURE_2D_HPP
#define TEXTURE_2D_HPP

#include "Engine/API.hpp"

#include <string>
#include <map>

namespace engine
{
    class ENGINE_API Texture2D
    {
    public:
        static Texture2D LoadTexture(const std::string& img);
    private:
        static std::map<std::string, Texture2D> sTextureMap;

    public:
        unsigned int Id();
        int Width();
        int Height();
        int NrChannels();
    private:
        unsigned int id;
        int width, height, nrChannels;
    };
}

#endif
