cbuffer CBuf : register(b0)
{
	matrix world;
	matrix view;
	matrix projection;
};

struct VertexOut
{
	float4 position : SV_Position;
	float2 uv : TexCoord;
};

VertexOut main(float3 pos : POSITION, float2 uv : TEXCOORD) 
{
	VertexOut output;
	matrix WorldViewProj = mul(mul(world, view), projection);
	output.position = mul(float4(pos, 1), WorldViewProj);
	output.uv = uv;
	return output;
}