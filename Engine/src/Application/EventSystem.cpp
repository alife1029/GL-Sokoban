#include "Engine/Application/EventSystem.hpp"
#include "Engine/Application/Window.hpp"

#include <GLFW/glfw3.h>

namespace engine
{
    // For GLFW events
    class GLFWevents
    {
    public:
        static void SetEventListener(EventSystem* eventSystem);
        
        // GLFW callbacks
        static void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void glfw_framebuffer_size_callback(GLFWwindow* window, int width, int height);
    private:
        static EventSystem* mEventSystem;        
    };

    // Implementation of GLFWevents
    EventSystem* GLFWevents::mEventSystem = nullptr;
	void GLFWevents::SetEventListener(EventSystem* eventSystem) { mEventSystem = eventSystem; }
	void GLFWevents::glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (action == GLFW_PRESS)
			mEventSystem->Keydown(key);
		else if (action == GLFW_RELEASE)
			mEventSystem->Keyup(key);
	}
	void GLFWevents::glfw_framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		mEventSystem->Resize(width, height);
	}




    // Implementation of Event System
	void EventSystem::SetEventListener(Application* listener)
	{
		GLFWevents::SetEventListener(this);

		// Set callbacks
		glfwSetKeyCallback(listener->mWnd->GlfwWindow(), GLFWevents::glfw_key_callback);
		glfwSetFramebufferSizeCallback(listener->mWnd->GlfwWindow(), GLFWevents::glfw_framebuffer_size_callback);
	}

	// Empty implementation of callbacks
	void EventSystem::Resize(int width, int height) { }
	void EventSystem::Keydown(int keycode) { }
	void EventSystem::Keyup(int keycode) { }
}
