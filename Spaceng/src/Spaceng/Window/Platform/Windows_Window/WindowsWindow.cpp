#include "PCH.h"
#include "WindowsWindow.h"

namespace Spaceng {

	
	Window* Window::Create(const WindowSettings& Settings)
	{
		return new WindowsWindow(Settings);
	}
	
	WindowsWindow::WindowsWindow(const WindowSettings& Settings)
	{
		Init(Settings);
	}

	void WindowsWindow::Init(const WindowSettings& Settings)
	{
		m_Data.Tittle = Settings.Tittle;
		m_Data.Width = Settings.Width;
		m_Data.Height = Settings.Height;

		if(!GLFWInit)
		{ 
		glfwInit();
		GLFWInit = true;
		LOG_INFO("GLFW Initiated : {} ", GLFWInit);
		}

		m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Tittle.c_str(), nullptr, nullptr);
		LOG_INFO("Window Created ");

		glfwMakeContextCurrent(m_Window);
		glfwMaximizeWindow(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);

	}


	WindowsWindow::~WindowsWindow()
	{
	}

	void WindowsWindow::OnUpdate()
	{
		glfwSwapBuffers(m_Window);
	}

	std::pair<float, float> WindowsWindow::GetPos() const
	{
		int xPos, yPos;
		glfwGetWindowPos(m_Window, &xPos, &yPos);
		return { (float)xPos, (float)yPos };
	}

	void WindowsWindow::SetVsync(bool Enabled)
	{
		if (Enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
		m_Data.Vsync = Enabled;	
	}

	bool WindowsWindow::IsVsync() const
	{
		return m_Data.Vsync;
	}

	void WindowsWindow::UpdateTittle(const std::string tittle)
	{
		m_Data.Tittle = tittle;
		glfwSetWindowTitle(m_Window, m_Data.Tittle.c_str());
	}











}