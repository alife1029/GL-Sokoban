#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Engine/API.hpp"
#include "Engine/Application/AppConfig.hpp"

namespace engine
{
    class Window;

    class ENGINE_API Application
    {
    public:
        Application(const AppConfig& cfg);
        ~Application();
        
        virtual void Start();
        virtual void Update();
        virtual void Dispose();

        void Run();
    private:
        Window* mWnd;

        friend class EventSystem;
    };
}

#endif
