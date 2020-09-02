#pragma once
#include"Layer.h"
#include <vector>

namespace Spaceng {

	class LayerStack {
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* Layer);
		void PushOverLay(Layer* Layer);
		void PopLayer(Layer* Layer);
		void PopOverLay(Layer* Layer);

	private:
		std::vector<Layer*> m_Layers;
		unsigned int m_LayerIndex = 0;
	};
}