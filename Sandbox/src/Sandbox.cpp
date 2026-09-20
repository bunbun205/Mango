//
// Created by Beany on 9/20/26.
//

#include <Mango.hpp>

class Sandbox : public Mango::Application {
public:
	Sandbox() {

	}

	~Sandbox() {

	}
};

Mango::Application* Mango::CreateApplication() {
	return new Sandbox();
}