#pragma once
#include "Core.h"
#include "Spaceng/Window/Window.h"
#include "Event.h"

namespace Spaceng {

	struct ApplicationSettings
	{
		std::string Name;
		uint32_t WindowWidth, WindowHeight;
	};
	
	class Application
	{
	public:
		Application(const ApplicationSettings& Settings = { "SpacEng",1280,720 });
		virtual ~Application();
		void Run();


		virtual void OnInit() {}
		virtual void OnShutdown() {}
		virtual void OnUpdate();

		virtual void OnEvent(Event& Event);

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		static inline Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		std::unique_ptr<Window> m_Window;

		static Application* s_Instance;
		bool m_Running = true;
		bool m_Minimized = false;

	};

	//client
	Application* CreateApplication();

}