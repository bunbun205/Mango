//
// Created by beany on 2/8/25.
//

#include "LinuxInput.hpp"

#ifdef MANGO_PLATFORM_LINUX

#include <GLFW/glfw3.h>
#include "Mango/Core/Application.hpp"

namespace Mango {

	Input* Input::s_Instance = new LinuxInput();

	bool LinuxInput::IsKeyPressedImpl(KeyCode keycode) {
		auto window = (GLFWwindow*)Application::Get().GetWindow().GetNativeWindow();
		auto state = glfwGetKey(window, (int)keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool LinuxInput::IsMouseButtonPressedImpl(MouseButton button) {
		auto window = (GLFWwindow*)Application::Get().GetWindow().GetNativeWindow();
		auto state = glfwGetMouseButton(window, (int)button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> LinuxInput::GetMousePosImpl() {
		auto window = (GLFWwindow*)Application::Get().GetWindow().GetNativeWindow();
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);
		return { (float)xPos, (float)yPos };
	}

	float LinuxInput::GetMouseXImpl() {
		auto [x, y] = GetMousePosImpl();
		return x;
	}
	float LinuxInput::GetMouseYImpl() {
		auto [x, y] = GetMousePosImpl();
		return y;
	}

	void LinuxInput::SetCursorModeImpl(CursorMode mode) {
		auto window = (GLFWwindow*)Application::Get().GetWindow().GetNativeWindow();
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL + (int)mode);
	}

} // Mango
#endif
