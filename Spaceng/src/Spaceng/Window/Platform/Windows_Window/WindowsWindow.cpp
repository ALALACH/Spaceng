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

		if(!s_GLFWInit)
		{ 
		glfwInit();
		s_GLFWInit = true;
		SE_ASSERT(s_GLFWInit, "GLFW could not be Initiated!")
		}

		m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Tittle.c_str(), nullptr, nullptr);
		LOG_DEBUG("{} Window Created ",m_Data.Tittle);

		glfwMakeContextCurrent(m_Window);
		//glfwMaximizeWindow(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);


		/* Setting glfw Callbacks */
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				auto& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent e;
				data.EventCallback(e);
				LOG_DEBUG("Window Closed EventCallback");
			});

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				auto& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowResizeEvent e((uint32_t)width,(uint32_t)height);
				data.EventCallback(e);
				data.Height = height;
				data.Width = width;
			});
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				auto& data = *(WindowData*)glfwGetWindowUserPointer(window);
				switch (action)
				{ 
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent e((Code)button);
						data.EventCallback(e);
							break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent e((Code)button);
							data.EventCallback(e);
							break;

					}
				}
			});
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				auto& data = *(WindowData*)glfwGetWindowUserPointer(window);
				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent e((Code)key, 0);
						data.EventCallback(e);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressedEvent e((Code)key, 1);
						data.EventCallback(e);
						break;
					}
					case GLFW_RELEASE:
					{
						keyReleasedEvent e((Code)key);
						data.EventCallback(e);
						break;
					}
					}
			});
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				auto& data = *((WindowData*)glfwGetWindowUserPointer(window));

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.EventCallback(event);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double XPOS, double YPOS)
			{
				auto& data = *((WindowData*)glfwGetWindowUserPointer(window));

				MouseMovedEvent event((float)XPOS, (float)YPOS);
				data.EventCallback(event);
			});

	}

	WindowsWindow::~WindowsWindow()
	{
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
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