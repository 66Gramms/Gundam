#pragma once
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

	typedef struct Mesh
	{
		wrl::ComPtr<ID3D11Buffer> pVertexBuffer;
		wrl::ComPtr<ID3D11Buffer> pIndexBuffer;
		size_t IndexCount;
	};

	Mesh CreateCube(ID3D11Device* pDevice);
};