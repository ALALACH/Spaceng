#include "Spaceng.h"
#include "EntryPoint.h"
#include "EditorLayer.h"


class EditorApplication : public Spaceng::Application
{
public:
	EditorApplication()
	{

	}
	virtual void OnInit() override
	{

	}
	virtual void OnShutdown() override
	{

	}
};
Spaceng::Application* Spaceng::CreateApplication()
{
	return new EditorApplication();
}