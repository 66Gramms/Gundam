#pragma once

#include "Material.h"

class CubeMaterial : public Material
{
public:
	CubeMaterial(std::string pixelShaderPath, std::string vertexShaderPath, ID3D11Device* pDevice);

	wrl::ComPtr<ID3D11ShaderResourceView> CubesTexture;
	wrl::ComPtr<ID3D11SamplerState> CubesTexSamplerState;

private:
	wrl::ComPtr<ID3D11PixelShader> CreatePixelShader(std::string path, ID3D11Device* pDevice);
	wrl::ComPtr<ID3D11VertexShader> CreateVertexShader(std::string path, ID3D11Device* pDevice);
	wrl::ComPtr<ID3D11Buffer> CreateColorCB(ID3D11Device* pDevice);

	void CreateInputLayout(wrl::ComPtr<ID3DBlob> pBlob, ID3D11Device* pDevice);
};