#include "App.h"

App::App() : window(800, 600, "Title") {}

int App::Start()
{
	while (true)
	{
		if (const auto ecode = Window::ProcessMessages())
		{
			return *ecode;
		}
		
		Update();
	}
}

void App::Update()
{
	if (window.keyboard.KeyIsPressed(VK_ESCAPE))
	{
		PostQuitMessage(0);
	}
}