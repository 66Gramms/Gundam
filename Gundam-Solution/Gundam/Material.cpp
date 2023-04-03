#include "Material.h"
#include <string>
#include <d3dcompiler.h>

namespace wrl = Microsoft::WRL;

void Material::CreatePixelShader(std::string path, ID3D11Device* pDevice)
{
	std::wstring stemp = std::wstring(path.begin(), path.end());
	LPCWSTR sw = stemp.c_str();

	wrl::ComPtr<ID3D11PixelShader> pPixelShader;
	wrl::ComPtr<ID3DBlob> pBlob;
	D3DReadFileToBlob(sw, &pBlob);
	pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader);
	this->pPixelShader = pPixelShader;
}

void Material::CreateVertexShader(std::string path, ID3D11Device* pDevice)
{
	std::wstring stemp = std::wstring(path.begin(), path.end());
	LPCWSTR sw = stemp.c_str();

	wrl::ComPtr<ID3D11VertexShader> pVertexShader;
	wrl::ComPtr<ID3DBlob> pBlob;
	D3DReadFileToBlob(sw, &pBlob);
	pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader);
	this->pVertexShader = pVertexShader;

	CreateInputLayout(pBlob, pDevice);
}

void Material::CreateInputLayout(wrl::ComPtr<ID3DBlob> pBlob, ID3D11Device* pDevice)
{
	wrl::ComPtr<ID3D11InputLayout> pInputLayout;
	const D3D11_INPUT_ELEMENT_DESC inputElementDescriptor[] =
	{
		{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	pDevice->CreateInputLayout(inputElementDescriptor, (UINT)std::size(inputElementDescriptor), pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &pInputLayout);
	this->pInputLayout = pInputLayout;
}

void Material::SetShaders(ID3D11Device* pDevice)
{
	CreatePixelShader("shaders\\PixelShader.cso", pDevice);
	CreateVertexShader("shaders\\VertexShader.cso", pDevice);
}