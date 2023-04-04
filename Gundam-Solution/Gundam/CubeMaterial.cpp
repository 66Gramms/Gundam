#include "CubeMaterial.h"
#include "DirectXTex.h"
#include <d3dcompiler.h>
#include <vector>

CubeMaterial::CubeMaterial(std::string pixelShaderPath, std::string vertexShaderPath, ID3D11Device* pDevice)
{
	this->pPixelShader = CreatePixelShader(pixelShaderPath, pDevice);
	this->pVertexShader = CreateVertexShader(vertexShaderPath, pDevice);
	this->pColorCB = CreateColorCB(pDevice);

	DirectX::TexMetadata metadata;
	DirectX::ScratchImage scratchImage;
	DirectX::LoadFromWICFile(L"textures/grass.jpg", DirectX::WIC_FLAGS_NONE, &metadata, scratchImage);

	wrl::ComPtr<ID3D11Resource> texture = nullptr;
	DirectX::CreateTexture(pDevice, scratchImage.GetImages(), scratchImage.GetImageCount(), metadata, &texture);

	pDevice->CreateShaderResourceView(texture.Get(), nullptr, &CubesTexture);

	D3D11_SAMPLER_DESC sampDesc = {};
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

	pDevice->CreateSamplerState(&sampDesc, &CubesTexSamplerState);
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
		{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TexCoord", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	pDevice->CreateInputLayout(inputElementDescriptor, (UINT)std::size(inputElementDescriptor), pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &pInputLayout);
	this->pInputLayout = pInputLayout;
}

wrl::ComPtr<ID3D11Buffer> CubeMaterial::CreateColorCB(ID3D11Device* pDevice)
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
			{1.0f, 0.0f, 1.0f},
			{1.0f, 0.0f, 0.0f},
			{1.0f, 0.0f, 0.0f},
			{0.0f, 1.0f, 0.0f},
			{0.0f, 1.0f, 0.0f},
			{0.0f, 0.0f, 1.0f},
			{0.0f, 0.0f, 1.0f},
			{1.0f, 1.0f, 0.0f},
			{1.0f, 1.0f, 0.0f},
			{0.0f, 1.0f, 1.0f},
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