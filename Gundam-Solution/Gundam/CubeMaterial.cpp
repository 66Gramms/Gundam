#include "CubeMaterial.h"
#include <d3dcompiler.h>

CubeMaterial::CubeMaterial(std::string pixelShaderPath, std::string vertexShaderPath, ID3D11Device* pDevice)
{
	this->pPixelShader = CreatePixelShader(pixelShaderPath, pDevice);
	this->pVertexShader = CreateVertexShader(vertexShaderPath, pDevice);
}

wrl::ComPtr<ID3D11PixelShader> CubeMaterial::CreatePixelShader(std::string path, ID3D11Device* pDevice)
{
	std::wstring stemp = std::wstring(path.begin(), path.end());
	LPCWSTR sw = stemp.c_str();

	wrl::ComPtr<ID3D11PixelShader> pPixelShader;
	wrl::ComPtr<ID3DBlob> pBlob;
	D3DReadFileToBlob(sw, &pBlob);
	pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader);
	return pPixelShader;
}

wrl::ComPtr<ID3D11VertexShader> CubeMaterial::CreateVertexShader(std::string path, ID3D11Device* pDevice)
{
	std::wstring stemp = std::wstring(path.begin(), path.end());
	LPCWSTR sw = stemp.c_str();

	wrl::ComPtr<ID3D11VertexShader> pVertexShader;
	wrl::ComPtr<ID3DBlob> pBlob;
	D3DReadFileToBlob(sw, &pBlob);
	pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader);
	CreateInputLayout(pBlob, pDevice);

	return pVertexShader;
}

void CubeMaterial::CreateInputLayout(wrl::ComPtr<ID3DBlob> pBlob, ID3D11Device* pDevice)
{
	wrl::ComPtr<ID3D11InputLayout> pInputLayout;
	const D3D11_INPUT_ELEMENT_DESC inputElementDescriptor[] =
	{
		{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	pDevice->CreateInputLayout(inputElementDescriptor, (UINT)std::size(inputElementDescriptor), pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &pInputLayout);
	this->pInputLayout = pInputLayout;
}