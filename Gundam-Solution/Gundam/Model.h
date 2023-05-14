#pragma once
#include <wrl.h>
#include <d3d11.h>
#include <array>
#include <DirectXMath.h>

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

		struct
		{
			float u;
			float v;
		} texCord;
	};
	Microsoft::WRL::ComPtr<ID3D11Buffer> GetConstantBuffer() const noexcept;
	void CreateConstantBuffer(ID3D11Device* pDevice);

	struct Mesh
	{
		wrl::ComPtr<ID3D11Buffer> pVertexBuffer;
		wrl::ComPtr<ID3D11Buffer> pIndexBuffer;
		size_t IndexCount;
	} mesh;

	class Material* material;

	static Mesh CreateCube(ID3D11Device* pDevice);
	static Mesh CreatePyramid(ID3D11Device* pDevice);

	typedef struct ConstantBuffer
	{
		DirectX::XMMATRIX world;
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX projection;
		float			  time;
	}ConstantBuffer;
	ConstantBuffer cb = {};
	Microsoft::WRL::ComPtr<ID3D11Buffer> pConstantBuffer;
};