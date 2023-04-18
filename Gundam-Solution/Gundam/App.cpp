#include "App.h"
#include "Model.h"
#include "CubeMaterial.h"
#include "PyramidMaterial.h"
#include "Camera.h"

App::App() : window(800, 600, "Title") {}

int App::Start()
{
	pDevice = window.GetGfx().GetPDevice().Get();

	Camera* camera = new Camera();
	camera->Initialize(window.GetWidth(), window.GetHeight(), &window);
	this->camera = camera;

	CubeMaterial* defaultMaterial = new CubeMaterial("shaders\\PixelShader.cso", "shaders\\VertexShader.cso", pDevice);
	PyramidMaterial* pyramidMaterial = new PyramidMaterial("shaders\\PSDefault.cso", "shaders\\VSDefault.cso", pDevice);

	Model* cube = new Model();
	cube->mesh = Model::CreateCube(pDevice);
	cube->material = defaultMaterial;
	cube->CreateConstantBuffer(pDevice);
	models.push_back(cube);

	Model* pyramid = new Model();
	pyramid->mesh = Model::CreatePyramid(pDevice);
	pyramid->material = pyramidMaterial;
	pyramid->CreateConstantBuffer(pDevice);
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
	camera->OnUpdate(timer.DeltaTime());

	window.GetGfx().DrawModel(models[0], camera, timer.Peek(), sin(timer.Peek()) * 5, 0.0f);
	window.GetGfx().DrawModel(models[1], camera, -timer.Peek(), 0.0f, cos(timer.Peek()) * 5);
	window.GetGfx().EndFrame();
}