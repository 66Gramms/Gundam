#include "Model.h"

Model::Mesh Model::CreatePyramid(ID3D11Device* pDevice)
{
	Model::Mesh mesh = {};

	const Model::Vertex vertices[] =
	{
		{ -1.0f, 0.0f, 1.0f},
		{ 1.0f, 0.0f, 1.0f},
		{ -1.0f, 0.0f, -1.0f},
		{ 1.0f, 0.0f, -1.0f},
		{ 0.0f, 1.5f, 0.0f},
	};

	const unsigned short indices[] =
	{
		0, 2, 1,
		1, 2, 3,
		0, 1, 4,
		1, 3, 4,
		3, 2, 4,
		2, 0, 4,
	};
	mesh.IndexCount = std::size(indices);

	// Create vertex buffer
	D3D11_BUFFER_DESC bd = {};
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.ByteWidth = sizeof(vertices);
	bd.StructureByteStride = sizeof(Model::Vertex);
	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = vertices;
	pDevice->CreateBuffer(&bd, &sd, &mesh.pVertexBuffer);

	// Create index buffer
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

Model::Mesh Model::CreateCube(ID3D11Device* pDevice)
{
	Model::Mesh mesh = {};

	const Model::Vertex vertices[] =
	{
		//Front face
		{{-1.0f, -1.0f, -1.0f}, {0, 1}},
		{{-1.0f,  1.0f, -1.0f}, {0, 0}},
		{{ 1.0f,  1.0f, -1.0f}, {1, 0}},
		{{ 1.0f, -1.0f, -1.0f}, {1, 1}},

		// Back Face
		{{-1.0f, -1.0f, 1.0f}, {1, 1}},
		{{1.0f, -1.0f, 1.0f}, {0, 1}},
		{{1.0f,  1.0f, 1.0f}, {0, 0}},
		{{-1.0f,  1.0f, 1.0f}, {1, 0}},

		// Top Face
		{{-1.0f, 1.0f, -1.0f}, {0, 1}},
		{{-1.0f, 1.0f,  1.0f}, {0, 0}},
		{{1.0f, 1.0f,  1.0f}, {1, 0}},
		{{1.0f, 1.0f, -1.0f}, {1, 1}},

		// Bottom Face
		{{-1.0f, -1.0f, -1.0f}, {1, 1}},
		{{1.0f, -1.0f, -1.0f}, {0, 1}},
		{{1.0f, -1.0f,  1.0f}, {0, 0}},
		{{-1.0f, -1.0f,  1.0f}, {1, 0}},

		// Left Face
		{{-1.0f, -1.0f,  1.0f}, {0, 1}},
		{{-1.0f,  1.0f,  1.0f}, {0, 0}},
		{{-1.0f,  1.0f, -1.0f}, {1, 0}},
		{{-1.0f, -1.0f, -1.0f}, {1, 1}},

		// Right Face
		{{1.0f, -1.0f, -1.0f}, {0, 1}},
		{{1.0f,  1.0f, -1.0f}, {0, 0}},
		{{1.0f,  1.0f,  1.0f}, {1, 0}},
		{{1.0f, -1.0f,  1.0f}, {1, 1}},
	};

	const unsigned short indices[] =
	{
		// Front Face
		0,  1,  2,
		0,  2,  3,

		// Back Face
		4,  5,  6,
		4,  6,  7,

		// Top Face
		8,  9, 10,
		8, 10, 11,

		// Bottom Face
		12, 13, 14,
		12, 14, 15,

		// Left Face
		16, 17, 18,
		16, 18, 19,

		// Right Face
		20, 21, 22,
		20, 22, 23
	};

	mesh.IndexCount = std::size(indices);

	// Create vertex buffer
	D3D11_BUFFER_DESC bd = {};
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.ByteWidth = sizeof(vertices);
	bd.StructureByteStride = sizeof(Model::Vertex);
	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = vertices;
	pDevice->CreateBuffer(&bd, &sd, &mesh.pVertexBuffer);

	// Create index buffer
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