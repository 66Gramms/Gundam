#pragma once
#include "GundamWin.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include <optional>
#include <memory>

class Window
{
public:
	Window(int width, int height, const char* name);
	~Window();
	Window(const Window&) = delete;
	Window& operator = (const Window&) = delete;

	int GetWidth() const noexcept { return windowWidth; };
	int GetHeight() const noexcept { return windowHeight; };
	void SetTitle(const std::string& title);
	static std::optional<int> ProcessMessages();
	
	Graphics& GetGfx();
	Keyboard keyboard;
	Mouse mouse;

private:
	class WindowClass
	{
	public:
		static const char* GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;
	private:
		WindowClass() noexcept;
		~WindowClass();
		WindowClass(const WindowClass&) = delete;
		WindowClass& operator = (const WindowClass&) = delete;
		static constexpr const char* wndClassName = "Gundam Direct3D Engine Window";
		static WindowClass wndClass;
		HINSTANCE hInst;
	};

	static LRESULT WINAPI HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT WINAPI HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

	int windowWidth;
	int windowHeight;
	HWND hWnd;
	std::unique_ptr<Graphics> pGfx;
};