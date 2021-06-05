#ifndef ENGINE_SCENE_HPP
#define ENGINE_SCENE_HPP

#include "Engine/API.hpp"

#include <string>

#include <entt.hpp>

namespace engine
{
    class Entity;

    class ENGINE_API Scene
    {
    public:
        Scene();
        ~Scene();

        Entity CreateEntity(const std::string& name = std::string());
        void DestroyEntity(Entity entity);

        void OnUpdate();
    private:
        entt::registry mRegistry;

        friend class Entity;
    };
}

#endif
