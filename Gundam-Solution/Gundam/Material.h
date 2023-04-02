#pragma once
#include <wrl.h>
#include <d3d11.h>
#include <string>

class Material
{
public:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;

	void CreatePixelShader(std::string path, ID3D11Device* pDevice);
	void CreateVertexShader(std::string path, ID3D11Device* pDevice);

private:
	void CreateInputLayout(Microsoft::WRL::ComPtr<ID3DBlob> pBlob, ID3D11Device* pDevice);
};