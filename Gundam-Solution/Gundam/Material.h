#pragma once
#include <wrl.h>
#include <d3d11.h>
#include <string>
#include <vector>

namespace wrl = Microsoft::WRL;

class Material
{
public:
	virtual void Nothing() {};

	wrl::ComPtr<ID3D11PixelShader> pPixelShader;
	wrl::ComPtr<ID3D11VertexShader> pVertexShader;
	wrl::ComPtr<ID3D11InputLayout> pInputLayout;

	wrl::ComPtr<ID3D11Buffer> pColorCB;
};