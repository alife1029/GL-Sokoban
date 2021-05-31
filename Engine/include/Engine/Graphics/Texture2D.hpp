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
        static Texture2D WhiteTexture();
    private:
        static std::map<std::string, Texture2D> sTextureMap;
        static Texture2D sWhiteTexture;

    public:
        unsigned int Id() const;
        int Width() const;
        int Height() const;
        int NrChannels() const;
    private:
        unsigned int id = 0;
        int width = 0, height = 0, nrChannels = 0;
    };
}

#endif
