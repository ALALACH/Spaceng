#pragma once
#include "Codes.h"



namespace Spaceng {

	class Event
	{
	public:
		bool Handeled = false;
	};


	class EventDispatcher : public Event
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& e)
			:m_Event(e) {}

		template<class C>
		bool Dispatch(EventFn<C> func)
		{

			m_Event.Handeled = func(*(C*)&m_Event);
			return true;
		}
		
	private:
		Event& m_Event;
	};



	// Window Events

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}
	};


	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(uint32_t Width, uint32_t Height)
			:m_Width(Width), m_Height(Height) {}

		inline uint32_t GetHeight() const { return m_Height; }
		inline uint32_t GetWidth() const { return m_Width; }

	private:
		uint32_t m_Width, m_Height;
	};



	// Keyboard Events
	class KeyPressedEvent : public Event
	{
	public:
		KeyPressedEvent(Code keycode, int repeatCount)
			: m_KeyCode(keycode), m_RepeatCount(repeatCount) {}

		inline Code GetKeyCode() const { return m_KeyCode; }

	private:

		Code m_KeyCode;
		uint32_t m_RepeatCount;
	};



	class keyReleasedEvent : public Event
	{
	public:
		keyReleasedEvent(Code keycode)
			:m_KeyCode(keycode){}

		inline Code GetKeyCode() const { return m_KeyCode; }

	private:

		Code m_KeyCode;
	};





	// Mouse Events
	class MouseButtonPressedEvent : public Event
	{
	public:
		MouseButtonPressedEvent(Code mousebutton)
			:m_MouseButton(mousebutton){}

		inline Code GetMouseButton() const { return m_MouseButton; }

	private:
		Code m_MouseButton;
	};


	class MouseButtonReleasedEvent : public Event
	{
	public:
		MouseButtonReleasedEvent(Code mousebutton)
			:m_MouseButton(mousebutton) {}
	private:
		Code m_MouseButton;
	};


	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float XOffset , float YOffset)
			:m_XOffset(XOffset), m_YOffset(YOffset){}

		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }

	private:
		float m_XOffset, m_YOffset;
	};


	class MouseMovedEvent :public Event
	{
	public:
		MouseMovedEvent(float XPOS, float YPOS)
			:m_XPos(XPOS), m_YPos(YPOS) {}

		inline float GetXPosition() const { return m_XPos; }
		inline float GetYPosition() const { return m_YPos; }

	private:
		float m_XPos, m_YPos;

	};
}
