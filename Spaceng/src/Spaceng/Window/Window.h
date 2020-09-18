#pragma once
#include <functional>
#include "Spaceng/EventSystem/Event.h"

namespace Spaceng {

	struct WindowSettings
	{
		std::string Tittle;
		unsigned int Width;
		unsigned int Height;

		WindowSettings(const std::string& tittle = "SpacEng"
			, unsigned int width = 1280 
			, unsigned int height=720)
			:Tittle(tittle), Width(width), Height(height) 
		{}
	};

	class Window
	{
	public:

		static Window* Create(const WindowSettings& Settings =  WindowSettings() );
		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual std::pair<uint32_t, uint32_t> GetSize() const = 0;
		virtual std::pair<float, float> GetPos() const = 0;
		virtual uint32_t GetWidth()  const =0 ;
		virtual uint32_t GetHeight() const = 0 ;


		virtual void SetVsync(bool Enabled) = 0;
		virtual bool IsVsync() const = 0;


		virtual const std::string GetTitle() const = 0;
		virtual void UpdateTittle(const std::string tittle) = 0;

		virtual void* GetWindow() const = 0;
	};
}