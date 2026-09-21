//
// Created by Beany on 9/20/26.
//

#pragma once

extern Mango::Application* Mango::CreateApplication();

int main(int argc, char** argv) {
	Mango::Log::Init();
	Mango::Application* app = Mango::CreateApplication();
	app->Start();
	app->Run();
	delete app;
}
