//
// Created by Beany on 9/20/26.
//

#pragma once

namespace Mango {
	class Application {
	public:
		Application();
		virtual ~Application();

		// App life cycle
		void Start();
		void Run();
		void Close();
	};

	Application* CreateApplication();
} // Mango
