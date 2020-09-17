#pragma once
#include "Spaceng.h"
#include <iostream>

#ifdef SE_PLATFORM_WIN

extern Spaceng::Application* Spaceng::CreateApplication();

int main(int argc, char** argv)
{
	Spaceng::log::init();
	LOG_WARN("SPACENG ENGINE {}",SE_BUILD_ID);
	Spaceng::Application* app = Spaceng::CreateApplication();
	app->Run();
	delete app;
	std::cin.get();
}

#endif