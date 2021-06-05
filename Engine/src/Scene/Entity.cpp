#include "Engine/Scene/Entity.hpp"

namespace engine
{
    Entity::Entity(entt::entity handle, Scene* scene)
        : mEntityHandle(handle), mScene(scene) {}

    TagComponent& Entity::AddComponent(const std::string& tag)
    {
        if (HasTagComponent())
            printf("Entity already has this component!\n");
        TagComponent& component = mScene->mRegistry.emplace<TagComponent>(Entity::mEntityHandle, tag);
        return component;
    }

    TransformComponent& Entity::AddComponent(   const glm::vec2& pos, 
                                                const glm::vec2& size,
                                                const float rotation)
    {
        if (HasTransformComponent())
            printf("Entity already has this component!\n");
        TransformComponent& component = mScene->mRegistry.emplace<TransformComponent>(Entity::mEntityHandle, pos, size, rotation);
        return component;
    }

    SpriteRendererComponent& Entity::AddComponent(const glm::vec4& color)
    {
        if (HasSpriteRendererComponent())
            printf("Entity already has this component!\n");
        SpriteRendererComponent& component = mScene->mRegistry.emplace<SpriteRendererComponent>(Entity::mEntityHandle, color);
        return component;
    }


    void Entity::RemoveComponent(Components component)
    {
        switch(component)
        {
        case Components::TAG:
            if (!HasTagComponent()) printf("Entity does not have this component!\n");
            mScene->mRegistry.remove<TagComponent>(Entity::mEntityHandle);
            break;
        case Components::TRANSFORM:
            if (!HasTransformComponent()) printf("Entity does not have this component!\n");
            mScene->mRegistry.remove<TransformComponent>(Entity::mEntityHandle);
            break;
        case Components::SPRITE_RENDERER:
            if (!HasSpriteRendererComponent()) printf("Entity does not have this component!\n");
            mScene->mRegistry.remove<SpriteRendererComponent>(Entity::mEntityHandle);
            break;
        }
    }

    TagComponent& Entity::GetTagComponent()
    {
        if (!HasTagComponent())
            printf("Entity does not have this component!\n");
        return mScene->mRegistry.get<TagComponent>(Entity::mEntityHandle);
    }

    TransformComponent& Entity::GetTransformComponent()
    {
        if (!HasTransformComponent())
            printf("Entity does not have this component!\n");
        return mScene->mRegistry.get<TransformComponent>(Entity::mEntityHandle);
    }

    SpriteRendererComponent& Entity::GetSpriteRendererComponent()
    {
        if (!HasSpriteRendererComponent())
            printf("Entity does not have this component!\n");
        return mScene->mRegistry.get<SpriteRendererComponent>(Entity::mEntityHandle);
    }

    bool Entity::HasTagComponent()
    {
        return mScene->mRegistry.has<TagComponent>(Entity::mEntityHandle);
    }

    bool Entity::HasTransformComponent()
    {
        return mScene->mRegistry.has<TransformComponent>(Entity::mEntityHandle);
    }

    bool Entity::HasSpriteRendererComponent()
    {
        return mScene->mRegistry.has<SpriteRendererComponent>(Entity::mEntityHandle);
    }

    Entity::operator bool() const { return mEntityHandle != entt::null; }
    Entity::operator entt::entity() const { return mEntityHandle; }
    Entity::operator uint32_t() const { return (uint32_t)mEntityHandle; }
    
    bool Entity::operator==(const Entity& other) const
    {
        return mEntityHandle == other.mEntityHandle && mScene == other.mScene;
    }
    bool Entity::operator!=(const Entity& other) const
    {
        return !(*this == other);
    }
}
