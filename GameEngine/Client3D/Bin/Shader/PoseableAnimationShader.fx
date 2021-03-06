
#include "Share.fx"

struct VS_INPUT_3D
{
	float3	Pos	: POSITION;
	float3	Normal : NORMAL;
	float2	UV	: TEXCOORD;
	float3	Tangent : TANGENT;
	float3	Binormal : BINORMAL;
	float4	BlendWeight : BLENDWEIGHT;
	float4	BlendIndex : BLENDINDICES;
};

struct VS_OUTPUT_3D
{
	float4	Pos	: SV_POSITION;
	float4	ProjPos : POSITION;
	float3	ViewPos : POSITION1;
	float3	Normal : NORMAL;
	float2	UV	: TEXCOORD;
	float3	Tangent : TANGENT;
	float3	Binormal : BINORMAL;
};

VS_OUTPUT_3D PoseableAnimationVS(VS_INPUT_3D input)
{
	VS_OUTPUT_3D	output = (VS_OUTPUT_3D)0;

	SkinningInfo	Info = Skinning(input.Pos, input.Normal, input.Tangent, input.Binormal,
		input.BlendWeight, input.BlendIndex);

	float3  Pos = Info.Pos - g_vPivot * g_vMeshSize;

	// output.Pos 의 x, y, z 에는 input.Pos의 x, y, z 가 들어가고 w에는 1.f 이 들어가게 된다.
	output.ProjPos = mul(float4(Info.Pos, 1.f), g_matWVP);
	output.Pos = output.ProjPos;

	output.ViewPos = mul(float4(Info.Pos, 1.f), g_matWV).xyz;

	// Bump 처리를 할때 
	// Z축
	output.Normal = normalize(mul(float4(Info.Normal, 0.f), g_matWV).xyz);

	// X축
	output.Tangent = normalize(mul(float4(Info.Tangent, 0.f), g_matWV).xyz);

	// Y축
	output.Binormal = normalize(mul(float4(Info.Binormal, 0.f), g_matWV).xyz);

	output.UV = input.UV;
	return output;
}

//cbuffer LightCBuffer : register(b7)
//{
//	float4	g_LightDiffuse;
//	float4	g_LightAmbient;
//	float4	g_LightSpecular;
//	int		g_LightLightType;
//	float3	g_LightPos;
//	float3	g_LightDir;
//	float	g_LightDistance;
//	float	g_LightAngleIn;
//	float	g_LightAngleOut;
//	float	g_LightAtt1;
//	float	g_LightAtt2;
//	float	g_LightAtt3;
//	float3	g_LightEmpty;
//};



float4 PoseableAnimationPS(VS_OUTPUT_3D input) : SV_Target
{

	float4 BaseColor = g_vMtrlBaseColor;
	BaseColor.w = g_MtrlOpacity;

	return BaseColor;
}

