#include "PyramidMaterial.h"
#include <d3dcompiler.h>
#include <vector>

PyramidMaterial::PyramidMaterial(std::string pixelShaderPath, std::string vertexShaderPath, ID3D11Device* pDevice)
{
	this->pPixelShader = CreatePixelShader(pixelShaderPath, pDevice);
	this->pVertexShader = CreateVertexShader(vertexShaderPath, pDevice);
	this->pColorCB = CreateColorCB(pDevice);
}

wrl::ComPtr<ID3D11PixelShader> PyramidMaterial::CreatePixelShader(std::string path, ID3D11Device* pDevice)
{
	std::wstring stemp = std::wstring(path.begin(), path.end());
	LPCWSTR sw = stemp.c_str();

	wrl::ComPtr<ID3D11PixelShader> pPixelShader;
	wrl::ComPtr<ID3DBlob> pBlob;
	D3DReadFileToBlob(sw, &pBlob);
	pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader);
	return pPixelShader;
}

wrl::ComPtr<ID3D11VertexShader> PyramidMaterial::CreateVertexShader(std::string path, ID3D11Device* pDevice)
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

void PyramidMaterial::CreateInputLayout(wrl::ComPtr<ID3DBlob> pBlob, ID3D11Device* pDevice)
{
	wrl::ComPtr<ID3D11InputLayout> pInputLayout;
	const D3D11_INPUT_ELEMENT_DESC inputElementDescriptor[] =
	{
		{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	pDevice->CreateInputLayout(inputElementDescriptor, (UINT)std::size(inputElementDescriptor), pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &pInputLayout);
	this->pInputLayout = pInputLayout;
}

wrl::ComPtr<ID3D11Buffer> PyramidMaterial::CreateColorCB(ID3D11Device* pDevice)
{
	struct ConstantBuffer
	{
		struct
		{
			float r;
			float g;
			float b;
			float a;
		} triangle_colors[12];
	};
	const ConstantBuffer cb =
	{
		{
			{1.0f, 0.0f, 1.0f},
			{1.0f, 0.0f, 0.0f},
			{0.0f, 1.0f, 0.0f},
			{0.0f, 0.0f, 1.0f},
			{1.0f, 1.0f, 0.0f},
			{0.0f, 1.0f, 1.0f},
		}
	};

	wrl::ComPtr<ID3D11Buffer> pConstantBuffer;
	D3D11_BUFFER_DESC cbd;
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.Usage = D3D11_USAGE_DEFAULT;
	cbd.CPUAccessFlags = 0;
	cbd.MiscFlags = 0;
	cbd.ByteWidth = sizeof(cb);
	cbd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA csd = {};
	csd.pSysMem = &cb;
	pDevice->CreateBuffer(&cbd, &csd, &pConstantBuffer);

	return pConstantBuffer;
}