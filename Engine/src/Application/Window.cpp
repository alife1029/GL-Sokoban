#include "Engine/Application/Window.hpp"
#include "Engine/Application/AppConfig.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace engine
{
    Window::Window(const AppConfig& cfg)
    {
        if (!glfwInit())
            std::cout << "Failed to Initialize GLFW!" << std::endl;

        // Minimum OpenGL 3.3 Required
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        mWnd = glfwCreateWindow(cfg.Width, cfg.Height, cfg.Title.c_str(), cfg.FullScreen ? glfwGetPrimaryMonitor() : NULL, NULL);
        if (!mWnd)
        {
            glfwTerminate();
            std::cout << "Failed to create window! Check your OpenGL version. Minimum OpenGL 3.3 required!" << std::endl;
        }

        glfwMakeContextCurrent(mWnd);
        glfwSwapInterval(1); // vSync

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            glfwDestroyWindow(mWnd);
            glfwTerminate();
            std::cout << "Failed to load GL pointers!" << std::endl;
        }

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    Window::~Window()
    {
        glfwDestroyWindow(mWnd);
        glfwTerminate();
    }

    bool Window::IsOpen()
    {
        return glfwWindowShouldClose(mWnd) == 0;
    }

    GLFWwindow* Window::GlfwWindow()
    {
        return mWnd;
    }
}
