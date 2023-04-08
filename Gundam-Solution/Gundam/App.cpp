#include "App.h"
#include "Model.h"
#include "CubeMaterial.h"
#include "PyramidMaterial.h"

App::App() : window(800, 600, "Title") {}

int App::Start()
{
	pDevice = window.GetGfx().GetPDevice().Get();

	CubeMaterial* defaultMaterial = new CubeMaterial("shaders\\PixelShader.cso", "shaders\\VertexShader.cso", pDevice);
	PyramidMaterial* pyramidMaterial = new PyramidMaterial("shaders\\PSDefault.cso", "shaders\\VSDefault.cso", pDevice);

	Model* cube = new Model();
	cube->mesh = Model::CreateCube(pDevice);
	cube->material = defaultMaterial;
	models.push_back(cube);

	Model* pyramid = new Model();
	pyramid->mesh = Model::CreatePyramid(pDevice);
	pyramid->material = pyramidMaterial;
	models.push_back(pyramid);

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

	window.GetGfx().DrawModel(models[0], timer.Peek(), 1.5f, 0.0f);
	window.GetGfx().DrawModel(models[1], -timer.Peek(), -1.5f, 0.0f);
	window.GetGfx().EndFrame();
}