#ifndef EVENT_SYSTEM_HPP
#define EVENT_SYSTEM_HPP

#include "Engine/API.hpp"
#include "Application.hpp"

namespace engine
{
    class ENGINE_API EventSystem
    {
    public:
        void SetEventListener(Application* listener);

        // Callbacks
        virtual void Resize(int width, int height);
		virtual void Keydown(int keycode);
		virtual void Keyup(int keycode);
    };
}

#endif
