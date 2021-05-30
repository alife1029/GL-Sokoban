#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "AppConfig.hpp"

struct GLFWwindow;

namespace engine
{
    class Window
    {
    public:
        Window(const AppConfig& cfg);
        ~Window();
        bool IsOpen();
        GLFWwindow* GlfwWindow();
    private:
        GLFWwindow* mWnd;
    };
};

#endif
