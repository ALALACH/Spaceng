#pragma once
#include "Core.h"

namespace Spaceng {


	
	class Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	};

	//client
	Application* CreateApplication();

}