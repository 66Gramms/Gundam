#pragma once
#include "Window.h"
#include "GundamTimer.h"

class App
{
public:
	App();
	int Start();
private:
	void Update(float seconds);

	Window window;
	GundamTimer timer;

	class ID3D11Device* pDevice;
	std::vector<class Model*> models;
	class Camera* camera;
	float prev_seconds = -1.f;
};
