#include "Engine/Application/Application.hpp"
#include "Engine/Application/Window.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace engine
{
    Application::Application(const AppConfig& cfg)
    {
        mWnd = new Window(cfg);
    }

    Application::~Application()
    {
        delete mWnd;
    }

    void Application::Run()
    {
        Start();

        while(mWnd->IsOpen())
        {
            glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            Update();

            glfwSwapBuffers(mWnd->GlfwWindow());
            glfwPollEvents();
        }

        Dispose();
    }

    void Application::Start() { }
    void Application::Update() { }
    void Application::Dispose() { }
}
