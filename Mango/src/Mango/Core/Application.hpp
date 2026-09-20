//
// Created by Beany on 9/20/26.
//

#pragma once

namespace Mango {
	class Application {
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	Application* CreateApplication();
} // Mango
