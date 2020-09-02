#include "Spaceng.h"
#include "EntryPoint.h"


class EditorApplication : public Spaceng::Application
{
public:
	EditorApplication()
	{

	}
};
Spaceng::Application* Spaceng::CreateApplication()
{
	return new EditorApplication();
}