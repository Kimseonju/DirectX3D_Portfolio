
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

VS_OUTPUT_3D Standard3DVS(VS_INPUT_3D input)
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

PS_OUTPUT_GBUFFER Standard3DPS(VS_OUTPUT_3D input)
{
	PS_OUTPUT_GBUFFER	output = (PS_OUTPUT_GBUFFER)0;

	// Set EffectFlow
	if (g_MtrlFlow == 1)
	{
		if (g_MtrlFlowDirection == 0)
		{
			input.UV.x += g_AccTime * g_MtrlFlowSpeedX;
		}

		else if (g_MtrlFlowDirection == 1)
		{
			input.UV.y += g_AccTime * g_MtrlFlowSpeedY;
		}

		else
		{
			input.UV.x += g_AccTime * g_MtrlFlowSpeedX;
			input.UV.y += g_AccTime * g_MtrlFlowSpeedY;
		}
	}

	float4  BaseColor = g_BaseTexture.Sample(g_AnisotropicSmp, input.UV);
    //BaseColor = PaperBurn2D(BaseColor, input.UV);
	{
        if (g_MtrlPaperBurnEnable != 0)
        {
            float2 BornUV = input.UV;
            float BurnColor = g_BurnTex.Sample(g_AnisotropicSmp, BornUV).r;

			// 정방향일 경우
			if (g_PaperBurnInverse == 0)
			{
				if (g_PaperBurn >= BurnColor.r)
                    BaseColor.a = 0.f;
				else
				{
					if (g_PaperBurn - g_PaperBurnOutFilter <= BurnColor.r && BurnColor.r <= g_PaperBurn + g_PaperBurnOutFilter)
					{
                        BaseColor.rgb = g_PaperBurnOutLineColor;
					//result.rgb *= g_PaperBurnOutLineColor;
					}

					if (g_PaperBurn - g_PaperBurnCenterFilter <= BurnColor.r && BurnColor.r <= g_PaperBurn + g_PaperBurnCenterFilter)
					{
                        BaseColor.rgb = g_PaperBurnCenterColor;
					//result.rgb *= g_PaperBurnCenterColor;
					}

					if (g_PaperBurn - g_PaperBurnInFilter <= BurnColor.r && BurnColor.r <= g_PaperBurn + g_PaperBurnInFilter)
					{
                        BaseColor.rgb = g_PaperBurnInLineColor;
					//result.rgb *= g_PaperBurnInLineColor;
					}
				}
			}

		// 역방향일 경우
			else
			{
				if (g_PaperBurn <= BurnColor.r)
                    BaseColor.a = 0.f;
				else
				{
					if (g_PaperBurn - g_PaperBurnOutFilter <= BurnColor.r && BurnColor.r <= g_PaperBurn + g_PaperBurnOutFilter)
					{
                        BaseColor.rgb = g_PaperBurnOutLineColor;
					//result.rgb *= g_PaperBurnOutLineColor;
					}

					if (g_PaperBurn - g_PaperBurnCenterFilter <= BurnColor.r && BurnColor.r <= g_PaperBurn + g_PaperBurnCenterFilter)
					{
                        BaseColor.rgb = g_PaperBurnCenterColor;
					//result.rgb *= g_PaperBurnCenterColor;
					}

					if (g_PaperBurn - g_PaperBurnInFilter <= BurnColor.r && BurnColor.r <= g_PaperBurn + g_PaperBurnInFilter)
					{
                        BaseColor.rgb = g_PaperBurnInLineColor;
					//result.rgb *= g_PaperBurnInLineColor;
					}
				}
			}

        }
    }
   //BaseColor = Distortion(BaseColor, input.UV, input.ProjPos);



	/*LightResult result = ComputeLight(input.ViewPos, input.Normal, input.Tangent,
		input.Binormal, input.UV);*/

	output.Albedo = BaseColor;// *(result.Dif + result.Amb) + result.Spc + result.Emv;
	output.GBuffer1.xyz = ComputeBumpNormal(input.Normal, input.Tangent, input.Binormal, input.UV);
	output.GBuffer1.w = 1.f;

	output.GBuffer2.x = input.ProjPos.z / input.ProjPos.w;
	output.GBuffer2.y = input.ProjPos.w;

	output.GBuffer2.z = g_vMtrlSpecularColor.w;
	float SpecularPower= ComputeBumpSpecularPower(input.UV);
	if (SpecularPower != 0.f)
	{
		output.GBuffer2.z = SpecularPower;
	}
	output.GBuffer2.w = g_MtrlReceiveDecal;
	
	output.GBuffer4.xyz = input.Tangent;
	output.GBuffer4.a = g_MtrlShadowEnable;
	output.GBuffer5.xyz = input.Binormal;
	//a는 임의값으로 명암값을 넣을것..
	float Threshold = ComputeBumpThreshold(input.UV);
	output.GBuffer5.w = Threshold;

	output.GBuffer3.x = ConvertColor(g_vMtrlBaseColor);
	output.GBuffer3.y = ConvertColor(g_vMtrlAmbientColor);

	float4	MtrlSpc = g_vMtrlSpecularColor;

	if (g_MtrlSpcTex)
		MtrlSpc = g_SpecularTexture.Sample(g_AnisotropicSmp, input.UV).rrrr;

	output.GBuffer3.z = ConvertColor(MtrlSpc);
	float4 SpecularColor = ComputeBumpSpecularMasking(input.UV);
	if (SpecularColor.x != 0.f)
	{
		output.GBuffer3.z = ConvertColor(SpecularColor);
	}
	float4	MtrlEmv = g_vMtrlEmissiveColor;

	if (g_MtrlEmvTex)
		MtrlEmv = g_EmissiveTexture.Sample(g_AnisotropicSmp, input.UV);

	output.GBuffer3.w = ConvertColor(MtrlEmv);




	//output.Albedo = Bloom(input.Albedo, input.UV);

	return output;
}


PS_OUTPUT_BLOOM Bloom(VS_OUTPUT_3D input)
{
	/*if (!g_MtrlBloomEnable == 0)
		return Color;*/

	PS_OUTPUT_BLOOM	Result = (PS_OUTPUT_BLOOM)0;

	Result.Color = float4(g_BloomColor, 1.f);

	Result.Color = Blur(Result.Color, input.UV);

	//float4	DistortionNormal = g_DistortionNormalTex.Sample(g_AnisotropicSmp, UV);

	//// NormalTexture에서 얻어온 r, g 값을 이용해서 0 ~ 1 사이의 값을
	//// -1 ~ 1 사이의 값으로 변경한다.
	//float2	Weight = (DistortionNormal.rg * 2.f - 1.f) * g_DistortionWeight;

	//Result = UV + Weight;

	//// frac : 소수점 이하 부분을 리턴한다.
	//Result = frac(Result);

	//if (Result.x < 0.f)
	//	Result.x = 1.f + Result.x;

	//if (Result.y < 0.f)
	//	Result.y = 1.f + Result.y;

	return Result;
}