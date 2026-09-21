//
// Created by Beany on 9/20/26.
//

#pragma once

#include <Mango/Core/LayerStack.hpp>
#include <Mango/Core/Window.hpp>
#include <Mango/Events/ApplicationEvent.hpp>

namespace Mango {
	class Application {
	public:
		Application();
		virtual ~Application();

		// App life cycle
		void Start();
		void Run();
		void Close();

		// Event Handling
		void OnEvent(Event& e);

		// Layer Management
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		bool m_Running = false;
		LayerStack m_LayerStack;
		static Application* s_Instance;

		float m_Timestep = 0.f;
		float m_FrameTime = 0.f;
		float m_LastFrameTime = 0.f;
	};

	Application* CreateApplication();
} // Mango
