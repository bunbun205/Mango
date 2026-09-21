//
// Created by Beany on 9/20/26.
//

#pragma once

extern Mango::Application* Mango::CreateApplication();

int main(int argc, char** argv) {
	Mango::Application* app = Mango::CreateApplication();
	app->Run();
	delete app;
}
