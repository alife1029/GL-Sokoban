#include "Engine/Scene/Scene.hpp"
#include "Engine/Scene/Entity.hpp"
#include "Engine/Scene/Components.hpp"
#include "Engine/Graphics/Renderer2D.hpp"

#include <algorithm>

#include <glm/glm.hpp>

namespace engine
{   
    Scene::Scene()
    {

    }

    Scene::~Scene()
    {
        mRegistry.clear();
    }

    Entity Scene::CreateEntity(const std::string& name)
    {
        Entity entity = { mRegistry.create(), this };
        entity.AddComponent(glm::vec2{0.0f, 0.0f}); // Transform component
        entity.AddComponent(name.empty() ? "Entity" : name); // Tag component
        return entity;
    }

    void Scene::DestroyEntity(Entity entity)
    {
        mRegistry.destroy(entity);
    }

    void Scene::OnUpdate()
    {
        auto group = mRegistry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
        for (auto entity : group)
        {
            auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
            transform.OnUpdate();
            Renderer2D::DrawQuad(transform, sprite.Color);
        }
    }
}
