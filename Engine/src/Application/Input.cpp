#include "Engine/Application/Input.hpp"

#include <GLFW/glfw3.h>

namespace engine
{
    GLFWwindow* Input::mWindow = nullptr;

	bool Input::GetKey(int keycode) noexcept
	{
		int state = glfwGetKey(mWindow, keycode);
		if (state == GLFW_PRESS)
			return true;
		return false;
	}   
}

