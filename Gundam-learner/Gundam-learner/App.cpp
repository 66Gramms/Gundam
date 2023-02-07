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
	const float time = timer.Peek();
	std::ostringstream oss;
	oss << "Time elapsed: " << std::setprecision(1) << std::fixed << time << "s";
	window.SetTitle(oss.str());
}