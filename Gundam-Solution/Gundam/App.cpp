#include "App.h"
#include "Model.h"
#include "CubeMaterial.h"
#include "PyramidMaterial.h"
#include "Camera.h"

#include "../BassDll/c/bass.h"

#pragma comment(lib, "../BassDll/c/x64/bass.lib")

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

 
    auto res = BASS_Init(-1, 44100, 0, GetForegroundWindow(), nullptr);
    auto stream = BASS_StreamCreateFile(false, L"music.mp3", 0, 0, 0);
    
    res = BASS_ChannelStart(stream);
    while (true)
    {
        if (const auto ecode = Window::ProcessMessages())
        {
            return *ecode;
        }

        auto byte_pos = BASS_ChannelGetPosition(stream, BASS_POS_BYTE);
        auto seconds = BASS_ChannelBytes2Seconds(stream, byte_pos);
        Update((float)seconds);
    }
}

void App::Update(float seconds)
{
    if (prev_seconds < 0)
        prev_seconds = seconds;

    auto delta_seconds = seconds - prev_seconds;
    prev_seconds = seconds;

    if (window.keyboard.KeyIsPressed(VK_ESCAPE))
    {
        PostQuitMessage(0);
    }

    const float c = sin(seconds) / 2.0f + 0.5f;
    window.GetGfx().ClearBuffer(0.1f, c * 0.55f, 0.1f);
    camera->OnUpdate(delta_seconds, sin(seconds) * 15.f, sin(seconds) * 11.5f, cos(seconds) * 20.f);
    window.GetGfx().DrawModel(models[0], camera, sin(seconds / 2.0f) * -1.2f, sin(seconds / 2.0f) * 1.2f, 0, 0, 0, seconds);

    for (int i = 1; i < NuberOfPyramids + 1; i++)
        window.GetGfx().DrawModel(models[i], camera, i % 2 == 1 ? seconds + i : -seconds + i, i % 2 == 1 ? seconds : -seconds, i * ((1 / (float)NuberOfPyramids) * 40) - 20.6666, 0, abs(sin(3.1415926535 / (float)NuberOfPyramids * i)) * 15.0f, seconds);
    for (int i = 1; i < NuberOfPyramids + 1; i++)
        window.GetGfx().DrawModel(models[i], camera, i % 2 == 1 ? seconds + i : -seconds + i, i % 2 == 1 ? seconds : -seconds, i * ((1 / (float)NuberOfPyramids) * 40) - 20.6666, 0, abs(sin(3.1415926535 / (float)NuberOfPyramids * i)) * -15.0f, seconds);

    for (int i = 1; i < NuberOfPyramids + 1; i++)
        window.GetGfx().DrawModel(models[i], camera, i % 2 == 1 ? seconds + i : -seconds + i, i % 2 == 1 ? seconds : -seconds, 0, i * ((1 / (float)NuberOfPyramids) * 40) - 20.6666, abs(sin(3.1415926535 / (float)NuberOfPyramids * i)) * 15.0f, seconds);
    for (int i = 1; i < NuberOfPyramids + 1; i++)
        window.GetGfx().DrawModel(models[i], camera, i % 2 == 1 ? seconds + i : -seconds + i, i % 2 == 1 ? seconds : -seconds, 0, i * ((1 / (float)NuberOfPyramids) * 40) - 20.6666, abs(sin(3.1415926535 / (float)NuberOfPyramids * i)) * -15.0f, seconds);

    window.GetGfx().EndFrame();
}