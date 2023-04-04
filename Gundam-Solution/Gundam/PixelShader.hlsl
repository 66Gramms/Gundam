cbuffer CBuf : register(b0)
{
	float4 triangle_colors[12];
};

float4 main(uint tid : SV_PrimitiveID) : SV_TARGET
{
	return triangle_colors[tid];
}