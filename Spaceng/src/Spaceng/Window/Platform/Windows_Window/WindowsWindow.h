#pragma once
#include "Spaceng/Window/Window.h"
#include "glfw/glfw3.h"

namespace Spaceng {


	class WindowsWindow : public Window
	{
	public :
		WindowsWindow(const WindowSettings& Settings);
		virtual ~WindowsWindow();

	
		virtual void OnUpdate() override;

		virtual std::pair<uint32_t, uint32_t> GetSize() const override;
		inline std::pair<float, float> GetPos() const override { return { m_Data.Height , m_Data.Width }; }
		inline  uint32_t GetWidth()  const override { return m_Data.Width; }
		inline  uint32_t GetHeight() const override { return m_Data.Height; }


		virtual void SetVsync(bool Enabled) override;
		virtual bool IsVsync() const override;


		inline const std::string GetTitle() const override { return m_Data.Tittle; }
		virtual void UpdateTittle(const std::string tittle)  override;
		inline void* GetWindow() const override { return m_Window; }

	private:
		GLFWwindow* m_Window;
	};
	

	struct WindowData
	{
		std::string Tittle;
		uint32_t Width, Height;
		bool Vsync;
	};
	WindowData m_Data;




}