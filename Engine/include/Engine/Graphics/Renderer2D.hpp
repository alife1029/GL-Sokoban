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
        size_t StaticQuads;
        size_t StaticBatches;

        size_t Batches() const { return DynamicBatches + StaticBatches; }
        size_t Quads() const { return DynamicQuads + StaticQuads; }
        size_t Tris() const { return Quads() * 2; }
        size_t Verts() const { return Quads() * 4; }
        size_t Indices() const { return Quads() * 6; }
        size_t StaticTris() const { return StaticQuads * 2; }
        size_t StaticVerts() const { return StaticQuads * 4; }
        size_t DynamicTris() const { return DynamicQuads * 2; }
        size_t DynamicVerts() const { return DynamicQuads * 4; }
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

    // Static batching
    class ENGINE_API StaticRenderer2D
    {
    public:
        static void Initialize();
        static void Shutdown();

        static void BeginScene();
        static void EndScene();

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

        static void RenderScene(const glm::mat4& viewProj);

        static void ResetStats();
    private:
        static void RegisterBatch();
    };

    ENGINE_API RenderStat& RenderStats();
}

#endif
