#pragma once
#include "Material.h"
#include <wrl.h>
#include <d3d11.h>
#include <array>

namespace wrl = Microsoft::WRL;

class Model
{
public:
	struct Vertex
	{
		struct
		{
			float x;
			float y;
			float z;
		} pos;
	};

	struct Mesh
	{
		wrl::ComPtr<ID3D11Buffer> pVertexBuffer;
		wrl::ComPtr<ID3D11Buffer> pIndexBuffer;
		size_t IndexCount;
	} mesh;

	Material* material = new Material();

	wrl::ComPtr<ID3D11PixelShader> pPixelShader;
	wrl::ComPtr<ID3D11VertexShader> pVertexShader;
	wrl::ComPtr<ID3D11InputLayout> pInputLayout;

	static Mesh CreateCube(ID3D11Device* pDevice);
	static Mesh CreatePyramid(ID3D11Device* pDevice);

	void SetShaders(ID3D11Device* pDevice);
};