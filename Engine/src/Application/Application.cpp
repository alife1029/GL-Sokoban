#include "Engine/Application/Application.hpp"
#include "Engine/Application/Window.hpp"
#include "Engine/Exception.hpp"
#include "Engine/Graphics/Renderer2D.hpp"

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
        Renderer2D::Init();
        StaticRenderer2D::Initialize();

        Start();

        while(mWnd->IsOpen())
        {
            glClear(GL_COLOR_BUFFER_BIT);

            Update();
            int glerr = glGetError();
            if (glerr)
                THROW_OPENGL_EXCEPTION(glerr);

            glfwSwapBuffers(mWnd->GlfwWindow());
            glfwPollEvents();

            Renderer2D::ResetStats();

            // Check OpenGL errors
            /*int */glerr = glGetError();
            if (glerr)
                THROW_OPENGL_EXCEPTION(glerr);
        }

        Dispose();

        Renderer2D::Shutdown();
        StaticRenderer2D::Shutdown();
    }

    void Application::Start() { }
    void Application::Update() { }
    void Application::Dispose() { }
}
