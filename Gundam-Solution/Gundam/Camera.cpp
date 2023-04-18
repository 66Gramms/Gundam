#include "Camera.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Window.h"

#include <complex>

void Camera::Initialize(const uint32_t Width, const uint32_t Height, Window* window) noexcept
{
	using namespace DirectX;

	this->window = window;
	this->Width = Width;
	this->Height = Height;

	Position = DirectX::XMVectorSet(0.0f, 5.0f, -10.0f, 0.0f);
	Target = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	Up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	View = DirectX::XMMatrixLookAtLH(Position, Target, Up);
	const auto AspectRatio = static_cast<float>(Width) / static_cast<float>(Height);
	Projection = DirectX::XMMatrixPerspectiveFovLH(0.4f * 3.14f, AspectRatio, 0.1f, 1000.0f);

	OnUpdate(0.0f);

	RotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(Pitch, Yaw, 0);
	Target = DirectX::XMVector3TransformCoord(DefaultForward, RotationMatrix);
	Target = DirectX::XMVector3Normalize(Target);

	Right = DirectX::XMVector3TransformCoord(DefaultRight, RotationMatrix);
	Forward = DirectX::XMVector3TransformCoord(DefaultForward, RotationMatrix);
	Up = DirectX::XMVector3Cross(Forward, Right);

	Position += LeftRight * Right;
	Position += BackForward * Forward;

	LeftRight = 0.0f;
	BackForward = 0.0f;

	Target = Position + Target;

	View = DirectX::XMMatrixLookAtLH(Position, Target, Up);


}

void Camera::OnUpdate(const float deltaTime) noexcept
{
	using namespace DirectX;

#ifdef _DEBUG
	if (window->mouse.RightIsPressed())
	{
		Yaw += window->mouse.GetMouseDeltaX() * deltaTime;
		Pitch += window->mouse.GetMouseDeltaY() * deltaTime;
	}

	window->keyboard.EnableAutorepeat();
	unsigned char pressedKey = window->keyboard.ReadKey().GetCode();
	if (pressedKey == 'W')
	{
		BackForward += 15.0f * deltaTime * Speed;
	}
	if(pressedKey == 'S')
	{
		BackForward -= 15.0f * deltaTime * Speed;
	}
	if(pressedKey == 'A')
	{
		LeftRight -= 15.0f * deltaTime * Speed;
	}
	if(pressedKey == 'D')
	{
		LeftRight += 15.0f * deltaTime * Speed;
	}
#endif
	View = DirectX::XMMatrixLookAtLH(Position, Target, Up);
	RotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(Pitch, Yaw, 0);
	Target = DirectX::XMVector3TransformCoord(DefaultForward, RotationMatrix);
	Target = DirectX::XMVector3Normalize(Target);

	Right = DirectX::XMVector3TransformCoord(DefaultRight, RotationMatrix);
	Forward = DirectX::XMVector3TransformCoord(DefaultForward, RotationMatrix);
	Up = DirectX::XMVector3Cross(Forward, Right);

	Position += LeftRight * Right;
	Position += BackForward * Forward;

	LeftRight = 0.0f;
	BackForward = 0.0f;

	Target = Position + Target;
	const auto AspectRatio = static_cast<float>(Width) / static_cast<float>(Height);

}

DirectX::XMMATRIX Camera::GetViewMatrix() const noexcept
{
	return View;
}

DirectX::XMMATRIX Camera::GetProjectionMatrix() const noexcept
{
	return Projection;
}
