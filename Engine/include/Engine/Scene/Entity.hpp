#ifndef ENGINE_ENTITY_HPP
#define ENGINE_ENTITY_HPP

#include "Engine/API.hpp"
#include "Scene.hpp"
#include "Components.hpp"

#include <string>
#include <cstdint>

#include <entt.hpp>
#include <glm/glm.hpp>

namespace engine
{
    class ENGINE_API Entity
    {
    public:
        Entity() = default;
        Entity(entt::entity handle, Scene* scene);
        Entity(const Entity& other) = default;

        TagComponent& AddComponent(const std::string& tag);
        TransformComponent& AddComponent(   const glm::vec2& pos, 
                                            const glm::vec2& size = glm::vec2(1.0f, 1.0f),
                                            const float rotation = 0.0f);
        SpriteRendererComponent& AddComponent(const glm::vec4& color = glm::vec4(1.0f));

        void RemoveComponent(Components component);

        TagComponent& GetTagComponent();
        TransformComponent& GetTransformComponent();
        SpriteRendererComponent& GetSpriteRendererComponent();

        bool HasTagComponent();
        bool HasTransformComponent();
        bool HasSpriteRendererComponent();

        operator bool() const;
        operator entt::entity() const;
        operator uint32_t() const;

        bool operator==(const Entity& other) const;
		bool operator!=(const Entity& other) const;

    private:
        entt::entity mEntityHandle { entt::null };
        Scene* mScene = nullptr;
    };
}

#endif
