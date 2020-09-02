#pragma once
#include "Core.h"
#include "Spaceng/EventSystem/Event.h"

namespace Spaceng {


	
	class Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();


		virtual void OnInit() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& Event) {}
	};

	//client
	Application* CreateApplication();

}