#pragma once 
#include "Spaceng/EventSystem/Event.h"
#include <string>

namespace Spaceng {

	class Layer {
	public:
		Layer(const std::string Name);
		~Layer();
		
		virtual void OnAttach();
		virtual void OnDetach();
		virtual void OnUpdate();
		virtual void OnEvent(Event& Event);

		inline const std::string& GetName() const { return m_DebugName;}

	protected:
		std::string m_DebugName;
	};
}