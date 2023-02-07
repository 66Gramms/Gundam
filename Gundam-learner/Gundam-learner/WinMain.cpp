#include "App.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	try
	{
		return App().Start();
	}
	catch (const GundamException& e)
	{
		MessageBox(nullptr, e.what(), nullptr, MB_OK | MB_ICONEXCLAMATION);
	}
	catch (const std::exception& e)
	{
		MessageBox(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBox(nullptr, "No deteails available", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	return -1;
}