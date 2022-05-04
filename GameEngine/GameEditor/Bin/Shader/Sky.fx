
#include "Share.fx"

TextureCube	g_SkyTexture : register(t20);

struct VS_SKY_OUTPUT
{
	float4	Pos : SV_POSITION;
	float3	UV : TEXCOORD;
};
//cbuffer Transform : register(b0)
//{
//	matrix	g_matPos;
//	matrix  g_matRot;
//	matrix  g_matScale;
//	matrix  g_matWorld;
//	matrix  g_matView;
//	matrix  g_matProj;
//	matrix  g_matWV;
//	matrix	g_matVP;
//	matrix  g_matWVP;
//	matrix	g_matInvView;
//	matrix	g_matInvProj;
//	matrix	g_matInvVP;
//	matrix	g_matInvWVP;
//	float3  g_vPivot;
//	int		g_Animation2DEnable;
//	float3  g_vMeshSize;
//	float   g_fTrEmpty2;
//};
//g_DeltaTime
float3 g_CloudSpeed = { 0.04f, 0.0f,0.f };
VS_SKY_OUTPUT SkyVS(float3 Pos : POSITION)
{
	VS_SKY_OUTPUT	output = (VS_SKY_OUTPUT)0;

	output.Pos = mul(float4(Pos, 1.f), g_matWVP).xyww;
	output.UV = Pos;

	output.UV = Pos + g_CloudSpeed * g_DeltaTime;
	return output;
}

float4 SkyPS(VS_SKY_OUTPUT input) : SV_TARGET
{
	float4	Color = g_SkyTexture.Sample(g_AnisotropicSmp, input.UV);

	return Color;
}
