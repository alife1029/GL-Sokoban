#include "Engine/Graphics/Renderer2D.hpp"
#include "Engine/Graphics/ShaderProgram.hpp"
#include "Engine/Graphics/Texture2D.hpp"
#include "Engine/Exception.hpp"

#include <array>
#include <vector>
#include <cstdint>

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

namespace engine
{
    static const uint32_t MaxQuads = 1000;
    static const uint32_t MaxVertices = MaxQuads * 4;
    static const uint32_t MaxIndices = MaxQuads * 6;
    static const uint32_t MaxTextures = 32;

    struct Vertex2D
    {
        glm::vec2 Pos;
        glm::vec4 Color;
        glm::vec2 TexCoord;
        float TexIndex;
    };

    struct DRenderer2DData
    {
        GLuint QuadVA = 0;
        GLuint QuadVB = 0;
        GLuint QuadIB = 0;
        uint32_t WhiteTextureSlot = 0;

        uint32_t IndexCount = 0;

        Vertex2D* QuadBuffer = nullptr;
        Vertex2D* QuadBufferPtr = nullptr;

        std::array<uint32_t, MaxTextures> TextureSlots;
        uint32_t TextureSlotIndex = 1;

        ShaderProgram* Shader;
        glm::mat4 ViewProj;
    };

    static DRenderer2DData dRendererData;
    static RenderStat renderStats;

    void Renderer2D::Init()
    {
        dRendererData.Shader = new ShaderProgram("GLShaders/v_2d.glsl", "GLShaders/f_2d.glsl");
        dRendererData.Shader->Use();
        dRendererData.Shader->AddUniform("u_ViewProj");
        dRendererData.Shader->AddUniform("u_Textures");

        dRendererData.QuadBuffer = new Vertex2D[MaxVertices];

        glGenVertexArrays(1, &dRendererData.QuadVA);
        glBindVertexArray(dRendererData.QuadVA);

        glGenBuffers(1, &dRendererData.QuadVB);
        glBindBuffer(GL_ARRAY_BUFFER, dRendererData.QuadVB);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex2D) * MaxVertices, nullptr, GL_DYNAMIC_DRAW);

        // Vertex Attribs
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (const void*)offsetof(Vertex2D, Pos));
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (const void*)offsetof(Vertex2D, Color));
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (const void*)offsetof(Vertex2D, TexCoord));
        glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (const void*)offsetof(Vertex2D, TexIndex));
    
        // Indices
        uint32_t indices[MaxIndices];
        uint32_t offset = 0;
        for (size_t i = 0; i < MaxIndices; i+=6)
        {
            indices[i] = offset;
            indices[i + 1] = offset + 1;
            indices[i + 2] = offset + 2;
            
            indices[i + 3] = offset;
            indices[i + 4] = offset + 2;
            indices[i + 5] = offset + 3;

            offset += 4;
        }

        glGenBuffers(1, &dRendererData.QuadIB);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, dRendererData.QuadIB);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // Texture slots
        dRendererData.TextureSlots[0] = Texture2D::WhiteTexture().Id();
        for (size_t i = 0; i < MaxTextures; i++)
            dRendererData.TextureSlots[i] = 0;
    }

    void Renderer2D::Shutdown()
    {
        glDeleteVertexArrays(1, &dRendererData.QuadVA);
        glDeleteBuffers(1, &dRendererData.QuadVB);
        glDeleteBuffers(1, &dRendererData.QuadIB);

        delete[] dRendererData.QuadBuffer;
        delete dRendererData.Shader;
    }

    void Renderer2D::Begin(const glm::mat4& viewProj)
    {
        dRendererData.QuadBufferPtr = dRendererData.QuadBuffer;
        dRendererData.ViewProj = viewProj;
    }

    void Renderer2D::End()
    {
        GLsizeiptr size = (uint8_t*)dRendererData.QuadBufferPtr - (uint8_t*)dRendererData.QuadBuffer;
        glBindBuffer(GL_ARRAY_BUFFER, dRendererData.QuadVB);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, dRendererData.QuadBuffer);
    }

    void Renderer2D::Flush()
    {
        dRendererData.Shader->Use();

        int* samplers = (int*)alloca(dRendererData.TextureSlotIndex * sizeof(int));
        for (int i = 0; i < dRendererData.TextureSlotIndex; i++)
        {
            samplers[i] = i;
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, dRendererData.TextureSlots[i]);
        }

        dRendererData.Shader->SetUniformIntArr("u_Textures", dRendererData.TextureSlotIndex, samplers);
        dRendererData.Shader->SetUniformMat4("u_ViewProj", dRendererData.ViewProj);

        glBindVertexArray(dRendererData.QuadVA);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, dRendererData.QuadIB);
        glDrawElements(GL_TRIANGLES, dRendererData.IndexCount, GL_UNSIGNED_INT, nullptr);

        dRendererData.IndexCount = 0;
        dRendererData.TextureSlotIndex = 1;
        ++renderStats.DynamicBatches;
    }

    void Renderer2D::DrawQuad(const glm::vec2& position)
    {
        DrawQuad(Texture2D::WhiteTexture(), position, { 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f });
    }
    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec4& color)
    {
        DrawQuad(Texture2D::WhiteTexture(), position, { 1.0f, 1.0f }, 0.0f, color);
    }
    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
    {
        DrawQuad(Texture2D::WhiteTexture(), position, size, 0.0f, color);
    }
    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
    {
        DrawQuad(Texture2D::WhiteTexture(), position, size, rotation, color);
    }
    void Renderer2D::DrawQuad(const Texture2D& tex, const glm::vec2& position)
    {
        DrawQuad(tex, position, { 1.0f, 1.0f }, 0.0f, { 1.0f, 1.0f, 1.0f, 1.0f });
    }
    void Renderer2D::DrawQuad(const Texture2D& tex, const glm::vec2& position, const glm::vec2& size)
    {
        DrawQuad(tex, position, size, 0.0f, { 1.0f, 1.0f, 1.0f, 1.0f });
    }
    void Renderer2D::DrawQuad(const Texture2D& tex, const glm::vec2& position, const glm::vec2& size, float rotation)
    {
        DrawQuad(tex, position, size, rotation, { 1.0f, 1.0f, 1.0f, 1.0f });
    }
    void Renderer2D::DrawQuad(const Texture2D& tex, const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
    {
        DrawQuad(tex, position, size, 0.0f, color);
    }
    void Renderer2D::DrawQuad(const Texture2D& tex, const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x, position.y, 0.0f })
            * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
            * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        
        DrawQuad(tex, transform, color);
    }
    void Renderer2D::DrawQuad(const Texture2D& tex, const glm::mat4& modelMat)
    {
        DrawQuad(tex, modelMat, { 1.0f, 1.0f, 1.0f, 1.0f });
    }
    void Renderer2D::DrawQuad(const glm::mat4& modelMat, const glm::vec4& color)
    {
        DrawQuad(Texture2D::WhiteTexture(), modelMat, { 1.0f, 1.0f, 1.0f, 1.0f });
    }
    void Renderer2D::DrawQuad(const Texture2D& tex, const glm::mat4& modelMat, const glm::vec4& color)
    {
        if (dRendererData.IndexCount >= MaxIndices || dRendererData.TextureSlotIndex > MaxTextures - 1)
        {
            End();
            Flush();
            Begin(dRendererData.ViewProj);
        }

        float textureIndex = -1.0f;
        for (uint32_t i = 0; i < dRendererData.TextureSlotIndex; i++)
        {
            if (dRendererData.TextureSlots[i] == tex.Id())
            {
                textureIndex = (float)i;
                break;
            }
        }

        if (textureIndex == -1.0f)
        {
            textureIndex = (float)dRendererData.TextureSlotIndex;
            dRendererData.TextureSlots[dRendererData.TextureSlotIndex] = tex.Id();
            ++dRendererData.TextureSlotIndex;
        }

        glm::vec4 vertexPoses[] = {
            { -0.5f, -0.5f, 0.0f, 1.0f },
            {  0.5f, -0.5f, 0.0f, 1.0f },
            {  0.5f,  0.5f, 0.0f, 1.0f },
            { -0.5f,  0.5f, 0.0f, 1.0f }
        };
        glm::vec2 texCoords[] = {
            { 0.0f, 0.0f },
            { 1.0f, 0.0f },
            { 1.0f, 1.0f },
            { 0.0f, 1.0f } 
        };

        for (int i = 0; i < 4; i++)
        {
            glm::vec3 transformed = modelMat * vertexPoses[i];
            dRendererData.QuadBufferPtr->Pos = { transformed.x, transformed.y };
            dRendererData.QuadBufferPtr->Color = color;
            dRendererData.QuadBufferPtr->TexCoord = texCoords[i];
            dRendererData.QuadBufferPtr->TexIndex = textureIndex;
            ++dRendererData.QuadBufferPtr;
        }

        dRendererData.IndexCount += 6;
        ++renderStats.DynamicQuads;
    }

    void Renderer2D::ResetStats()
    {
        renderStats.DynamicBatches = 0;
        renderStats.DynamicQuads = 0;
    }












    // Static Renderer
    struct Batch
    {
        unsigned int VAO;
        unsigned int VBO;
        unsigned int IndexCount;

        std::array<uint32_t, MaxTextures> TextureSlots;
        uint32_t TextureSlotIndex = 1;

        void Dispose()
        {
            if (VAO) glDeleteVertexArrays(1, &VAO);
            if (VBO) glDeleteBuffers(1, &VBO);
        }
    };

    struct SRenderData
    {
        std::vector<Batch> Batches;
        std::vector<Vertex2D> Vertices;
        std::array<uint32_t, MaxTextures> TextureSlots;
        uint32_t TextureSlotIndex = 1;

        ShaderProgram* Shader;
        unsigned int IBO;

        size_t QuadCount = 0;
        bool SceneInitialized = false;
    };

    static SRenderData sData;

    void StaticRenderer2D::Initialize()
    {
        sData.Shader = new ShaderProgram("GLShaders/v_2d.glsl", "GLShaders/f_2d.glsl");
        sData.Shader->Use();
        sData.Shader->AddUniform("u_ViewProj");
        sData.Shader->AddUniform("u_Textures");

        uint32_t indices[MaxIndices];
        uint32_t offset = 0;

        // Calculate indices
        for (size_t i = 0; i < MaxIndices; i += 6)
        {
            indices[i] = offset;
            indices[i + 1] = offset + 1;
            indices[i + 2] = offset + 2;

            indices[i + 3] = offset;
            indices[i + 4] = offset + 2;
            indices[i + 5] = offset + 3;

            offset += 4;
        }

        // Generate index buffer
        glGenBuffers(1, &sData.IBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sData.IBO),
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // Texture slots
        sData.TextureSlots[0] = Texture2D::WhiteTexture().Id();
        for (size_t i = 1; i < MaxTextures; i++)
            sData.TextureSlots[i] = 0;

        int glerr = glGetError();
            if (glerr)
                THROW_OPENGL_EXCEPTION(glerr);
    }

    void StaticRenderer2D::BeginScene()
    {
        sData.SceneInitialized = false;
    }

    void StaticRenderer2D::EndScene()
    {
        RegisterBatch();
        sData.SceneInitialized = true;
    }

    void StaticRenderer2D::RenderScene(const glm::mat4& viewProj)
    {
        if (sData.SceneInitialized)
        {
            sData.Shader->Use();
            int i = 0;

            for (auto batch : sData.Batches)
            {
                // Activate texture units
                int* samplers = (int*)alloca(batch.TextureSlotIndex * sizeof(int));
                for (int i = 0; i < batch.TextureSlotIndex; i++)
                {
                    samplers[i] = i;
                    glActiveTexture(GL_TEXTURE0 + i);
                    glBindTexture(GL_TEXTURE_2D, batch.TextureSlots[i]);
                }

                sData.Shader->SetUniformIntArr("u_Textures", batch.TextureSlotIndex, samplers);
                sData.Shader->SetUniformMat4("u_ViewProj", viewProj);

                // Bind buffers
                glBindVertexArray(batch.VAO);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sData.IBO);

                // OpenGL draw call
                glDrawElements(GL_TRIANGLES, batch.IndexCount, GL_UNSIGNED_INT, (const void*)0);
            }
        }
    }

    void StaticRenderer2D::DrawQuad(const glm::vec2& position)
    {
        DrawQuad(Texture2D::WhiteTexture(), position, { 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f });
    }
    void StaticRenderer2D::DrawQuad(const glm::vec2& position, const glm::vec4& color)
    {
        DrawQuad(Texture2D::WhiteTexture(), position, { 1.0f, 1.0f }, 0.0f, color);
    }
    void StaticRenderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
    {
        DrawQuad(Texture2D::WhiteTexture(), position, size, 0.0f, color);
    }
    void StaticRenderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
    {
        DrawQuad(Texture2D::WhiteTexture(), position, size, rotation, color);
    }
    void StaticRenderer2D::DrawQuad(const Texture2D& tex, const glm::vec2& position)
    {
        DrawQuad(tex, position, { 1.0f, 1.0f }, 0.0f, { 1.0f, 1.0f, 1.0f, 1.0f });
    }
    void StaticRenderer2D::DrawQuad(const Texture2D& tex, const glm::vec2& position, const glm::vec2& size)
    {
        DrawQuad(tex, position, size, 0.0f, { 1.0f, 1.0f, 1.0f, 1.0f });
    }
    void StaticRenderer2D::DrawQuad(const Texture2D& tex, const glm::vec2& position, const glm::vec2& size, float rotation)
    {
        DrawQuad(tex, position, size, rotation, { 1.0f, 1.0f, 1.0f, 1.0f });
    }
    void StaticRenderer2D::DrawQuad(const Texture2D& tex, const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
    {
        DrawQuad(tex, position, size, 0.0f, color);
    }
    void StaticRenderer2D::DrawQuad(const Texture2D& tex, const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x, position.y, 0.0f })
            * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
            * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        
        DrawQuad(tex, transform, color);
    }
    void StaticRenderer2D::DrawQuad(const Texture2D& tex, const glm::mat4& modelMat)
    {
        DrawQuad(tex, modelMat, { 1.0f, 1.0f, 1.0f, 1.0f });
    }
    void StaticRenderer2D::DrawQuad(const glm::mat4& modelMat, const glm::vec4& color)
    {
        DrawQuad(Texture2D::WhiteTexture(), modelMat, { 1.0f, 1.0f, 1.0f, 1.0f });
    }
    void StaticRenderer2D::DrawQuad(const Texture2D& tex, const glm::mat4& modelMat, const glm::vec4& color)
    {
        if (sData.QuadCount >= MaxQuads || sData.TextureSlotIndex > MaxTextures - 1)
            RegisterBatch();

        float textureIndex = -1.0f;
        for (size_t i = 0; i < sData.TextureSlotIndex; i++)
        {
            if (sData.TextureSlots[i] == tex.Id())
            {
                textureIndex = (float)i;
                break;
            }
        }

        if (textureIndex == -1.0f)
        {
            textureIndex = (float)sData.TextureSlotIndex;
            sData.TextureSlots[sData.TextureSlotIndex] = tex.Id();
            ++sData.TextureSlotIndex;
        }

        glm::vec4 vertexPoses[] = {
            { -0.5f, -0.5f, 0.0f, 1.0f },
            {  0.5f, -0.5f, 0.0f, 1.0f },
            {  0.5f,  0.5f, 0.0f, 1.0f },
            { -0.5f,  0.5f, 0.0f, 1.0f }
        };

        glm::vec2 texCoords[] = {
            { 0.0f, 0.0f },
            { 1.0f, 0.0f },
            { 1.0f, 1.0f },
            { 0.0f, 1.0f }
        };

        for (int i = 0; i < 4; i++)
        {
            sData.Vertices.push_back({
                modelMat * vertexPoses[i],
                color,
                texCoords[i],
                textureIndex
            });
        }

        ++sData.QuadCount;
        ++renderStats.StaticQuads;
    }

    void StaticRenderer2D::RegisterBatch()
    {
        Batch batch;
        batch.IndexCount = sData.QuadCount * 6;

        // Load data to VRAM
        glGenVertexArrays(1, &batch.VAO);
        glGenBuffers(1, &batch.VBO);
        glBindVertexArray(batch.VAO);
        glBindBuffer(GL_ARRAY_BUFFER, batch.VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex2D) * sData.Vertices.size(), &sData.Vertices[0], GL_STATIC_DRAW);

        // Vertex Attribs
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (const void*)offsetof(Vertex2D, Pos));
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (const void*)offsetof(Vertex2D, Color));
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (const void*)offsetof(Vertex2D, TexCoord));
        glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (const void*)offsetof(Vertex2D, TexIndex));
    
        // Unbind
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        batch.TextureSlotIndex = sData.TextureSlotIndex;
        batch.TextureSlots = sData.TextureSlots;

        sData.Vertices.clear();
        sData.QuadCount = 0;
        sData.TextureSlotIndex = 1;
        sData.TextureSlots[0] = Texture2D::WhiteTexture().Id();
        for (size_t i = 1; i < MaxTextures; i++)
            sData.TextureSlots[i] = 0;

        sData.Batches.push_back(batch);

        ++renderStats.StaticBatches;
    }

    void StaticRenderer2D::Shutdown()
    {
        // Dispose all buffers
        for (auto batch : sData.Batches)
            batch.Dispose();
        glDeleteBuffers(1, &sData.IBO);

        // Clear vectors
        sData.Vertices.clear();
        sData.Batches.clear();
        sData.SceneInitialized = false;

        renderStats.StaticBatches = 0;
        renderStats.StaticQuads = 0;

        delete sData.Shader;
    }


    // Render stats
    RenderStat& RenderStats()
    {
        return renderStats;
    }
}
