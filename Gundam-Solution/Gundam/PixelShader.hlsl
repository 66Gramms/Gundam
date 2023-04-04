Texture2D simpleTexture : register(t0);

SamplerState MeshTextureSampler : register(s0);

struct PixelIn
{
	float4 position : SV_Position;
	float2 uv : TexCoord;
};

float4 main(PixelIn input) : SV_TARGET0
{
	return simpleTexture.Sample(MeshTextureSampler, input.uv);
}