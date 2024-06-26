#include "EditorLayer.h"
#include "PCH.h"
#include "imgui/imgui_internal.h"
#include "imgui/imgui.h"



namespace Spaceng
{

	EditorLayer::EditorLayer(const std::string Name)
		:m_DebugName(Name)
	{

	}
	EditorLayer::~EditorLayer()
	{
		//free Dynamically all members
	}

	void EditorLayer::OnAttach()
	{
		LoadAsset("Screen", Video_PNG, true);
	}

	void EditorLayer::OnDetach()
	{

	}

	void EditorLayer::OnUpdate(float Timestep)
	{
		Application::Get().GetWindow().UpdateTittle("SpaceEngine : Network");
	}

	void EditorLayer::OnEvent(Event& Event)
	{
		EventDispatcher dispatcher(Event);
		dispatcher.Dispatch<KeyPressedEvent>(SE_BIND_EVENT(EditorLayer::OnKeyPressed));

	}
	bool EditorLayer::OnKeyPressed(KeyPressedEvent& e)
	{
		switch (e.GetKeyCode())
		{
			//Access Application memebers through methods implemented in Application.h
			case Key::X:
				Application::Get().GetClient().SendImgData(Application::Get().getProjectDirectory());
				
				break;
		}
		return false;
	}


	void EditorLayer::LoadAsset(std::string name,AssetType type , bool DepthStencil)
	{
		Application::Get().PrepareAsset(name , type , DepthStencil);
	}
}