#include "PCH.h"
#include "Application.h"

namespace Spaceng {


	Application* Application::s_Instance = nullptr;

	Application::Application(const ApplicationSettings& Settings)
	{
		s_Instance = this;
		
		m_Window = std::unique_ptr<Window>
			(Window::Create(WindowSettings(Settings.Name, Settings.WindowWidth, Settings.WindowHeight)));

		SE_LOG_DEBUG("Window {} Created",m_Window->GetTitle())

		m_Window->SetEventCallback(SE_BIND_EVENT(Application::OnEvent));

		SE_LOG_DEBUG("Window {} EventCallback Set", m_Window->GetTitle())

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
				m_Window->OnUpdate();
			}
		}
	}
	
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(SE_BIND_EVENT(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(SE_BIND_EVENT(Application::OnWindowResize));
		
	}

	void Application::OnUpdate()
	{

	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		//uint32_t Height = e.GetHeight(), Width = e.GetWidth();
		//todo : Resize viewport & ImGui Pannels
		return true;
	}
}