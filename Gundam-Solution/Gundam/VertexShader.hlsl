cbuffer CBuf : register(b0)
{
	matrix world;
	matrix view;
	matrix projection;
	float time;
};

struct VertexOut
{
	float4 position : SV_Position;
	float2 uv : TexCoord;
};

#define PI 3.1415926535

VertexOut main(float3 pos : POSITION, float2 uv : TEXCOORD) 
{
	float bpm = 160;
	float beat = time * 60 / bpm / 2;

	VertexOut output;
	pos *= 2;
	pos *= abs(sin(beat * PI * 16)) * 0.8f + 1;
	matrix WorldViewProj = mul(mul(world, view), projection);
	output.position = mul(float4(pos, 1), WorldViewProj);
	output.uv = uv;
	return output;
}