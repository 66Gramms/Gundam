#pragma once
#include <wrl.h>
#include <d3d11.h>
#include <string>

namespace wrl = Microsoft::WRL;

class Material
{
public:
	wrl::ComPtr<ID3D11PixelShader> GetPixelShader() { return pPixelShader; };
	wrl::ComPtr<ID3D11VertexShader> GetVertexShader() { return pVertexShader; };
	wrl::ComPtr<ID3D11InputLayout> GetInputLayout() { return pInputLayout; };

	void CreatePixelShader(std::string path, ID3D11Device* pDevice);
	void CreateVertexShader(std::string path, ID3D11Device* pDevice);
	void SetShaders(ID3D11Device* pDevice);

private:
	wrl::ComPtr<ID3D11PixelShader> pPixelShader;
	wrl::ComPtr<ID3D11VertexShader> pVertexShader;
	wrl::ComPtr<ID3D11InputLayout> pInputLayout;

	void CreateInputLayout(Microsoft::WRL::ComPtr<ID3DBlob> pBlob, ID3D11Device* pDevice);
};