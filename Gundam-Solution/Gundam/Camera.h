#pragma once

#include <DirectXMath.h>
#include <wrl.h>
#include <d3d11.h>

class Camera
{
public:
	void Initialize(const uint32_t Width, const uint32_t Height, class Window* window) noexcept;
	void OnUpdate(const float deltaTime) noexcept;

	DirectX::XMMATRIX GetViewMatrix() const noexcept;
	DirectX::XMMATRIX GetProjectionMatrix() const noexcept;

private:
	DirectX::XMVECTOR Position{};
	DirectX::XMVECTOR Target{};
	DirectX::XMVECTOR Up{};
	DirectX::XMVECTOR DefaultForward = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	DirectX::XMVECTOR DefaultRight = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	DirectX::XMVECTOR Forward = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	DirectX::XMVECTOR Right = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

	DirectX::XMMATRIX RotationMatrix{};

	DirectX::XMMATRIX View{};
	DirectX::XMMATRIX Projection{};


	float Speed = 1.0f;

	float LeftRight = 0.0f;
	float BackForward = 0.0f;
	float Yaw = 0.0f;
	float Pitch = 0.0f;
	uint32_t Width = 0;
	uint32_t Height = 0;

	float totalTime = 0;

	class Window* window;
};
