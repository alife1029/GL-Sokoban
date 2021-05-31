#ifndef RENDERER_2D_HPP
#define RENDERER_2D_HPP

#include "Engine/API.hpp"
#include "Texture2D.hpp"

#include <glm/glm.hpp>

namespace engine
{
    struct ENGINE_API RenderStat
    {
        size_t DynamicQuads;
        size_t DynamicBatches;

        size_t Tris() const { return DynamicQuads * 2; }
        size_t Verts() const { return DynamicQuads * 4; }
        size_t Indices() const { return DynamicQuads * 6; }
    };

    class ENGINE_API Renderer2D
    {
    public:
        static void Init();
        static void Shutdown();

        static void Begin(const glm::mat4& viewProj);
        static void End();
        static void Flush();

        static void DrawQuad(const glm::vec2& position);
        static void DrawQuad(const glm::vec2& position, const glm::vec4& color);
        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
        static void DrawQuad(const Texture2D& tex, const glm::vec2& position);
        static void DrawQuad(const Texture2D& tex, const glm::vec2& position, const glm::vec2& size);
        static void DrawQuad(const Texture2D& tex, const glm::vec2& position, const glm::vec2& size, float rotation);
        static void DrawQuad(const Texture2D& tex, const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
        static void DrawQuad(const Texture2D& tex, const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
        static void DrawQuad(const Texture2D& tex, const glm::mat4& modelMat);
        static void DrawQuad(const glm::mat4& modelMat, const glm::vec4& color);
        static void DrawQuad(const Texture2D& tex, const glm::mat4& modelMat, const glm::vec4& color);

        static void ResetStats();
    };

    RenderStat& RenderStats();
}

#endif
