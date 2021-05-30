#include "Engine/Application/Application.hpp"
#include "Engine/Application/Window.hpp"
#include "Engine/Exception.hpp"

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
            glClear(GL_COLOR_BUFFER_BIT);

            Update();

            glfwSwapBuffers(mWnd->GlfwWindow());
            glfwPollEvents();

            // Check OpenGL errors
            int glerr = glGetError();
            if (glerr)
                THROW_OPENGL_EXCEPTION(glerr);
        }

        Dispose();
    }

    void Application::Start() { }
    void Application::Update() { }
    void Application::Dispose() { }
}
