#include "Engine/Graphics/Texture2D.hpp"

#include <glad/glad.h>
#include <stb/stb_image.h>

namespace engine
{
    std::map<std::string, Texture2D> Texture2D::sTextureMap;
    Texture2D Texture2D::sWhiteTexture;

    Texture2D Texture2D::LoadTexture(const std::string& img)
    {
        // Load texture if not loaded before
        if (!sTextureMap.count(img))
        {
            Texture2D tex;
            
            unsigned char* pixels = stbi_load(img.c_str(), &tex.width, &tex.height, &tex.nrChannels, STBI_rgb_alpha);

            glGenTextures(1, &tex.id);
            glBindTexture(GL_TEXTURE_2D, tex.id);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex.width, tex.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
            // Texture Parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // Unbind
            glBindTexture(GL_TEXTURE_2D, 0);

            // Delete pixel data
            stbi_image_free(pixels);

            sTextureMap[img] = tex;
        }

        return sTextureMap[img];
    }

    Texture2D Texture2D::WhiteTexture()
    {
        if (!sWhiteTexture.id)
        {
            sWhiteTexture.width = 1;
            sWhiteTexture.height = 1;
            sWhiteTexture.nrChannels = 4;

            glGenTextures(1, &sWhiteTexture.id);
            glBindTexture(GL_TEXTURE_2D, sWhiteTexture.id);
            uint32_t color = 0xffffffff;
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, sWhiteTexture.width, sWhiteTexture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &color);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);            
        }

        return sWhiteTexture;
    }

    // Getters
    unsigned int Texture2D::Id() const { return id; }
    int Texture2D::Width() const { return width; }
    int Texture2D::Height() const { return height; }
    int Texture2D::NrChannels() const { return nrChannels; }
}
