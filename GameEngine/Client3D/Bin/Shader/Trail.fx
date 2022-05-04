#include "Share.fx"


Texture2D	g_GBuffer2	: register(t50);

cbuffer	TrailCBuffer	: register(b13)
{
	float3	g_TrailCurrentPos;
	float	g_TrailScale;
	float4	g_TrailVelocity[30];
	float4	g_TrailVelocity2[30];
}

struct VS_INPUT_POS
{
	float3	Pos : POSITION;
};

struct VS_OUTPUT_TEX
{
	float4	Pos	: SV_POSITION;
	float2	UV		: TEXCOORD0;
	float4	ProjPos	: POSITION;
};

VS_INPUT_POS TrailVS(VS_INPUT_POS input)
{
	VS_INPUT_POS	output = (VS_INPUT_POS)0;

	output.Pos = mul(float4(input.Pos, 1.0f), g_matWorld);

	return output;
}

[maxvertexcount(60)]
void TrailGS(point VS_INPUT_POS input[1],
	inout TriangleStream<VS_OUTPUT_TEX> stream)
{
	float3	Pos[60];

	for (int i = 0; i < 30; ++i)
	{
		Pos[i * 2] = g_TrailVelocity[i];
		Pos[i * 2 + 1] = g_TrailVelocity2[i];
	}

	float2	UV[60];

	float	UVPos = 0.f;


	for (int i = 0; i < 30; ++i)
	{
		UV[i * 2] = float2(UVPos, 0.f);
		UV[i * 2 + 1] = float2(UVPos, 1.f);
		UVPos += 1.f / 30;
	}

	VS_OUTPUT_TEX	output = (VS_OUTPUT_TEX)0;
	for (int i = 0; i < 60; ++i)
	{
		output.Pos = mul(float4(Pos[i], 1.f), g_matVP);
		output.ProjPos = output.Pos;
		output.UV = UV[i];

		stream.Append(output);
	}
	stream.RestartStrip();
}

float4 TrailPS(VS_OUTPUT_TEX input) : SV_Target
{
	float4  BaseColor = 0;
	float2	ScreenUV;
	ScreenUV.x = input.ProjPos.x / input.ProjPos.w * 0.5f + 0.5f;
	ScreenUV.y = input.ProjPos.y / input.ProjPos.w * -0.5f + 0.5f;

	float4  GBuffer2 = g_GBuffer2.Sample(g_AnisotropicSmp, ScreenUV);
	float4	result = (float4)0.f;

	float	Alpha = 1.f;

	if (GBuffer2.w > 0.f)
		Alpha = (GBuffer2.y - input.ProjPos.w) / 2.5f;
	if (g_MtrlDistortionEnable == 1)
	{
		float2 DUV = DistortionUV(input.UV);
		BaseColor = g_BaseTexture.Sample(g_AnisotropicSmp, DUV);

	}
	else
	{
		BaseColor = g_BaseTexture.Sample(g_AnisotropicSmp, input.UV);
	}
	
	result.rgb = BaseColor.rgb;
	result.a = BaseColor.a * g_MtrlOpacity;

	return result;
}