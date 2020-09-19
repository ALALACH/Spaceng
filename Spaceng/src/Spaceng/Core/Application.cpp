#include "PCH.h"
#include "Application.h"

namespace Spaceng {


	Application* Application::s_Instance = nullptr;

	Application::Application(const ApplicationSettings& Settings)
	{
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create(WindowSettings(Settings.Name, Settings.WindowWidth, Settings.WindowHeight)));
		m_Window->SetVsync(true);
	}
	Application::~Application()
	{

	}
	void Application::Run()
	{
		while (m_Running)
		{
			if (!m_Minimized)
			{ 
				Application* app = this;
			}
				m_Window->OnUpdate();
		}
	}
}