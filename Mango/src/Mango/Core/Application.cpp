//
// Created by Beany on 9/20/26.
//

#include "Application.hpp"

#ifdef MANGO_PLATFORM_LINUX
#include <GLFW/glfw3.h>
#elif defined MANGO_PLATFORM_WINDOWS
#include <Windows.h>
#endif

#include <glm/ext/scalar_common.hpp>

#include <Mango/Core/Log.hpp>
#include <Mango/Core/Core.hpp>
#include <Mango/Core/Input.hpp>

namespace Mango {
	Application* Application::s_Instance = nullptr;

	static float GetTimeSeconds()
	{
#ifdef MANGO_PLATFORM_LINUX
		return (float) glfwGetTime();
#elif defined MANGO_PLATFORM_WINDOWS
		static LARGE_INTEGER s_Frequency = []
		{
			LARGE_INTEGER frequency;
			QueryPerformanceFrequency(&frequency);
			return frequency;
		}();

		LARGE_INTEGER now;
		QueryPerformanceCounter(&now);
		return (float)((double) now.QuadPart / (double)s_Frequency.QuadPart);
#endif
	}

	Application::Application() {}

	Application::~Application() {}

	void Application::Start() {
		MANGO_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		m_Running = true;
	}

	void Application::Close() {
		for (Layer* layer : m_LayerStack) {
			layer->OnDetach();
		}
	}

	void Application::OnEvent(Event &e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*--it)->OnEvent(e);
			if (e.Handled())
				break;
		}
	}

	void Application::PushLayer(Layer *layer) {
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer *overlay) {
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	bool Application::OnWindowClose(WindowCloseEvent &e) {
		m_Running = false;
		Close();
		return true;
	}

	void Application::Run() {
		while (m_Running) {
			float time = GetTimeSeconds();
			m_FrameTime = time - m_LastFrameTime;
			m_Timestep = glm::min<float>(m_FrameTime, 0.0333f);
			m_LastFrameTime = time;
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(m_Timestep);
			for (Layer* layer : m_LayerStack)
				layer->OnRender();

			m_Window->OnUpdate();
		}
	}
} // Mango