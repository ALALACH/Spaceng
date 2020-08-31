#pragma once

#include <iostream>

#ifdef SE_PLATFORM_WIN

extern Spaceng::Application* Spaceng::CreateApplication();

int main(int argc, char** argv)
{
	std::cout << "SPACENG " << std::endl;
	Spaceng::Application* app = Spaceng::CreateApplication();
	app->Run();
	delete app;
	std::cin.get();
}

#endif