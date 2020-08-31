#include <Spaceng.h>
#include <Spaceng/EntryPoint.h>


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