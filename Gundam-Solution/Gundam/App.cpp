#include "App.h"
#include "Model.h"

App::App() : window(800, 600, "Title") {}

int App::Start()
{
	pDevice = window.GetGfx().GetPDevice().Get();
	Model* cube = new Model();
	cube->mesh = cube->CreateCube(pDevice);
	models.push_back(cube);

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

	const float c = sin(timer.Peek()) / 2.0f + 0.5f;
	window.GetGfx().ClearBuffer(c, c, 1.0f);

	window.GetGfx().DrawModel(models[0], timer.Peek(), window.mouse.GetPosX() / 400.0f - 1, -window.mouse.GetPosY() / 300.0f + 1);
	window.GetGfx().DrawModel(models[0], -timer.Peek(), 0.0f, 0.0f);
	window.GetGfx().EndFrame();
}