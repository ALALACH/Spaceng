#pragma once
#include "Spaceng/Window/Window.h"
#include "glfw/include/GLFW/glfw3.h"

namespace Spaceng {


	struct WindowData
	{
		std::string Tittle;
		uint32_t Width, Height;
		bool Vsync;
		EventCallbackFn EventCallback;
	};
	WindowData m_Data;


	class WindowsWindow : public Window
	{
	public :
		WindowsWindow(const WindowSettings& Settings);
		virtual ~WindowsWindow();

	
		virtual void OnUpdate() override;

		virtual std::pair<float, float> GetPos() const override;

		inline std::pair<uint32_t, uint32_t> GetSize() const  override { return { m_Data.Height , m_Data.Width }; }
		inline  uint32_t GetWidth()  const override { return m_Data.Width; }
		inline  uint32_t GetHeight() const override { return m_Data.Height; }

		virtual void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		virtual void SetVsync(bool Enabled) override;
		virtual bool IsVsync() const override;

		inline const std::string GetTitle() const override { return m_Data.Tittle; }
		virtual void UpdateTittle(const std::string tittle)  override;

		inline void* GetGlfwWindow() const  { return m_Window; }
	
	
	private:
		void Init(const WindowSettings& Settings);


	private:
		GLFWwindow* m_Window;
	};
	
	static bool s_GLFWInit = false;





}