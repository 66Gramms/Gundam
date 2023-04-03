#pragma once
#include <wrl.h>
#include <d3d11.h>
#include <string>

namespace wrl = Microsoft::WRL;

class Material
{
public:
	wrl::ComPtr<ID3D11PixelShader> pPixelShader;
	wrl::ComPtr<ID3D11VertexShader> pVertexShader;
	wrl::ComPtr<ID3D11InputLayout> pInputLayout;
};