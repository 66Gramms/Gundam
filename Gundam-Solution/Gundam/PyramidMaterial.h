#pragma once

#include "Material.h"

class PyramidMaterial : public Material
{
public:
	PyramidMaterial(std::string pixelShaderPath, std::string vertexShaderPath, ID3D11Device* pDevice);

private:
	wrl::ComPtr<ID3D11PixelShader> CreatePixelShader(std::string path, ID3D11Device* pDevice);
	wrl::ComPtr<ID3D11VertexShader> CreateVertexShader(std::string path, ID3D11Device* pDevice);
	wrl::ComPtr<ID3D11Buffer> CreateColorCB(ID3D11Device* pDevice);

	void CreateInputLayout(wrl::ComPtr<ID3DBlob> pBlob, ID3D11Device* pDevice);
};