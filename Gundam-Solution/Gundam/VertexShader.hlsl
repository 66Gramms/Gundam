cbuffer CBuf : register(b0)
{
	matrix transform;
};

struct VertexOut
{
	float4 position : SV_Position;
	float2 uv : TexCoord;
};

VertexOut main(float3 pos : POSITION, float2 uv : TEXCOORD) 
{
	VertexOut output;
	output.position = mul(float4(pos, 1.0f), transform);
	output.uv = uv;
	return output;
}