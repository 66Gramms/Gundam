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
    models.push_back(cube);
    models.push_back(cube);
    models.push_back(cube);

    models.push_back(pyramid);
    models.push_back(pyramid);
    models.push_back(pyramid);
    models.push_back(pyramid);

    models.push_back(cube);
    models.push_back(cube);
    models.push_back(cube);
    models.push_back(cube);

    models.push_back(pyramid);
    models.push_back(pyramid);
    models.push_back(pyramid);
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
    int mod = 0;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            window.GetGfx().DrawModel(models[mod], camera, ((i + j) % 2) ? timer.Peek() : -timer.Peek(), j * 5, i * 5);
            mod += 1;
        }
    }

    window.GetGfx().EndFrame();
}