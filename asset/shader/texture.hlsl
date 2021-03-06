
Texture2D<float4> texture0 : register(t0);
SamplerState      sampler0 : register(s0);

cbuffer ConstantBuffer : register(b1)
{
	float2 m_vertexScale : packoffset(c0.x);
	float2 m_uvScale     : packoffset(c0.z);
};

struct VSInput
{
	float3 position : POSITION;
	float2 uv       : TEXCOORD0;
};

struct PSInput
{
	float4 position : SV_POSITION;
	float2 uv       : TEXCOORD0;
};

struct PsOutput
{
	float4 color    : SV_TARGET;
};

PSInput VSMain(VSInput input)
{
	PSInput result;

	result.position = float4(float3(m_vertexScale, 1) * input.position.xyz, 1);
	result.uv       = m_uvScale * input.uv;

	return result;
}

PsOutput PSMain(PSInput input)
{
	PsOutput output;
	
	output.color = texture0.Sample(sampler0, input.uv);

	return output;
}
