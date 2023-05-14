cbuffer CBuf : register(b0)
{
	matrix world;
	matrix view;
	matrix projection;
	float time;

};

float4 main(float3 pos : POSITION) :SV_Position
{
	matrix WorldViewProj = mul(mul(world, view), projection);
	return  mul(float4(pos, 1), WorldViewProj);
}