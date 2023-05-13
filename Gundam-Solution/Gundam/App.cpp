#include "App.h"
#include "Model.h"
#include "CubeMaterial.h"
#include "PyramidMaterial.h"
#include "Camera.h"

#if FULLSCREEN
App::App() : window(GetSystemMetrics(SM_CXVIRTUALSCREEN), GetSystemMetrics(SM_CYVIRTUALSCREEN), "Gundam-engine") {}
#else
App::App() : window(800, 600, "Gundam-engine") {}
#endif

int NuberOfPyramids = 9;

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

    Model* pyramid = new Model();
    pyramid->mesh = Model::CreatePyramid(pDevice);
    pyramid->material = pyramidMaterial;
    pyramid->CreateConstantBuffer(pDevice);

    models.push_back(cube);
    for (int i = 0; i < NuberOfPyramids; i++)
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
    window.GetGfx().ClearBuffer(0.1f, c * 0.65f, 0.1f);
    camera->OnUpdate(timer.DeltaTime(), sin(timer.Peek()) * 15.f, sin(timer.Peek()) * 11.5f, cos(timer.Peek()) * 20.f);
    window.GetGfx().DrawModel(models[0], camera, sin(timer.Peek() / 2.0f) * -1.2f, sin(timer.Peek() / 2.0f) * 1.2f, 0, 0, 0);

    for (int i = 1; i < NuberOfPyramids + 1; i++)
        window.GetGfx().DrawModel(models[i], camera, i % 2 == 1 ? timer.Peek() + i : -timer.Peek() + i, i % 2 == 1 ? timer.Peek() : -timer.Peek(), i * ((1 / (float)NuberOfPyramids) * 40) - 20.6666, 0, abs(sin(3.1415926535 / (float)NuberOfPyramids * i)) * 15.0f);
    for (int i = 1; i < NuberOfPyramids + 1; i++)
        window.GetGfx().DrawModel(models[i], camera, i % 2 == 1 ? timer.Peek() + i : -timer.Peek() + i, i % 2 == 1 ? timer.Peek() : -timer.Peek(), i * ((1 / (float)NuberOfPyramids) * 40) - 20.6666, 0, abs(sin(3.1415926535 / (float)NuberOfPyramids * i)) * -15.0f);

    for (int i = 1; i < NuberOfPyramids + 1; i++)
        window.GetGfx().DrawModel(models[i], camera, i % 2 == 1 ? timer.Peek() + i : -timer.Peek() + i, i % 2 == 1 ? timer.Peek() : -timer.Peek(), 0, i * ((1 / (float)NuberOfPyramids) * 40) - 20.6666, abs(sin(3.1415926535 / (float)NuberOfPyramids * i)) * 15.0f);
    for (int i = 1; i < NuberOfPyramids + 1; i++)
        window.GetGfx().DrawModel(models[i], camera, i % 2 == 1 ? timer.Peek() + i : -timer.Peek() + i, i % 2 == 1 ? timer.Peek() : -timer.Peek(), 0, i * ((1 / (float)NuberOfPyramids) * 40) - 20.6666, abs(sin(3.1415926535 / (float)NuberOfPyramids * i)) * -15.0f);

    window.GetGfx().EndFrame();
}