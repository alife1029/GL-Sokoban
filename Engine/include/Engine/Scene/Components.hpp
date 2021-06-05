#ifndef ENGINE_COMPONENTS_HPP
#define ENGINE_COMPONENTS_HPP

#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace engine
{
    enum class Components
    {
        TAG,
        TRANSFORM,
        SPRITE_RENDERER
    };

    struct TagComponent
    {
        std::string Tag;

        TagComponent() = default;
        TagComponent(const TagComponent&) = default;
        TagComponent(const std::string& tag)
            : Tag(tag) {}
    };

    struct TransformComponent
    {
        glm::vec2 Position { 0.0f, 0.0f };
        glm::vec2 Scale { 1.0f, 1.0f };
        float Rotation { 0.0f };
        glm::mat4 TransformMatrix { 1.0f };

        TransformComponent() = default;
        TransformComponent(const TransformComponent&) = default;
        TransformComponent(const glm::vec2& position)
            :  Position(position) { CalculateTransformMatrix(); }
        TransformComponent(const glm::vec2& position, const glm::vec2& scale)
            : Position(position), Scale(scale) { CalculateTransformMatrix(); }
        TransformComponent(const glm::vec2& position, float rotation)
            : Position(position), Rotation(rotation) { CalculateTransformMatrix(); }
        TransformComponent(const glm::vec2& position, const glm::vec2& scale, float rotation)
            : Position(position), Scale(scale), Rotation(rotation) { CalculateTransformMatrix(); }

        void CalculateTransformMatrix()
        {
            TransformMatrix = glm::translate(glm::mat4(1.0f), { Position.x, Position.y, 0.0f })
                * glm::rotate(glm::mat4(1.0f), glm::radians(Rotation), { 0.0f, 0.0f, 1.0f })
                * glm::scale(glm::mat4(1.0f), { Scale.x, Scale.y, 1.0f });
        }

        void OnUpdate()
        {
            CalculateTransformMatrix();
        }

        operator glm::mat4&() { return TransformMatrix; }
        operator const glm::mat4&() const { return TransformMatrix; }
    };

    struct SpriteRendererComponent
    {
        glm::vec4 Color { 1.0f, 1.0f, 1.0f, 1.0f };

        SpriteRendererComponent() = default;
        SpriteRendererComponent(const SpriteRendererComponent&) = default;
        SpriteRendererComponent(const glm::vec4& color)
            : Color(color) {}
    };
}

#endif
