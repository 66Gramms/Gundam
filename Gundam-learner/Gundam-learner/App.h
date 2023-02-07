#pragma once
#include "Window.h"
#include "GundamTimer.h"

class App
{
public:
	App();
	int Start();
private:
	void Update();

	Window window;
	GundamTimer timer;
};
