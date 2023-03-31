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

	Mesh CreateCube(ID3D11Device* pDevice)
	{
		Mesh mesh = {};

		const Model::Vertex vertices[] =
		{
			{-1.0f, -1.0f, -1.0f},
			{ 1.0f, -1.0f, -1.0f},
			{-1.0f,  1.0f, -1.0f},
			{ 1.0f,  1.0f, -1.0f},
			{-1.0f, -1.0f,  1.0f},
			{ 1.0f, -1.0f,  1.0f},
			{-1.0f,  1.0f,  1.0f},
			{ 1.0f,  1.0f,  1.0f},
		};

		const unsigned short indices[] =
		{
			0, 2, 1,  2, 3, 1,
			1, 3, 5,  3, 7, 5,
			2, 6, 3,  3, 6, 7,
			4, 5, 7,  4, 7, 6,
			0, 4, 2,  2, 4, 6,
			0, 1, 4,  1, 5, 4
		};
		mesh.IndexCount = std::size(indices);

		D3D11_BUFFER_DESC bd = {};
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;
		bd.ByteWidth = sizeof(vertices);
		bd.StructureByteStride = sizeof(Vertex);
		D3D11_SUBRESOURCE_DATA sd = {};
		sd.pSysMem = vertices;
		pDevice->CreateBuffer(&bd, &sd, &mesh.pVertexBuffer);

		D3D11_BUFFER_DESC ibd = {};
		ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibd.Usage = D3D11_USAGE_DEFAULT;
		ibd.CPUAccessFlags = 0;
		ibd.MiscFlags = 0;
		ibd.ByteWidth = sizeof(indices);
		ibd.StructureByteStride = sizeof(unsigned short);
		D3D11_SUBRESOURCE_DATA isd = {};
		isd.pSysMem = indices;
		pDevice->CreateBuffer(&ibd, &isd, &mesh.pIndexBuffer);

		return mesh;
	}
};