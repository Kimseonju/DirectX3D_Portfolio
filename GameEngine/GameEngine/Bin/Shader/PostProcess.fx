#include "Share.fx"


#define OVERSTATE_DESATURATION	1.f // 0.4


Texture2D       g_AlbedoTarget	   : register(t50);
Texture2D       g_GBuffer1Target   : register(t51);
Texture2D       g_GBuffer2Target   : register(t52);
Texture2D       g_PostLightDifTex   : register(t53);
Texture2D       g_GBuffer5Target   : register(t54);


static const int screen_height = 720.0f;
static const int screen_width = 1280.0f;

float4 FXAA(float2 uv) {
	const float fxaa_reduce_min = 1.0f / 128.0f;
	const float fxaa_reduce_mul = 1.0f / 8.0f;
	const float fxaa_span_max = 8.0f;

	float2 pixel = float2(1.0f / screen_width, 1.0f / screen_height);
	float2 frag_coord = uv * float2(screen_width, screen_height);

	float4 fxaa_uv;
	fxaa_uv.xy = uv.xy;
	fxaa_uv.zw = uv.xy - (pixel * (0.5));

	float4 Albedo_color = g_BaseTexture.Sample(g_AnisotropicSmp, uv);
	float3 rgbNW = g_BaseTexture.Sample(g_AnisotropicSmp, fxaa_uv.zw).rgb;
	float3 rgbNE = g_BaseTexture.Sample(g_AnisotropicSmp, fxaa_uv.zw + float2(1.0f, 0.0f) * pixel).rgb;
	float3 rgbSW = g_BaseTexture.Sample(g_AnisotropicSmp, fxaa_uv.zw + float2(0.0f, 1.0f) * pixel).rgb;
	float3 rgbSE = g_BaseTexture.Sample(g_AnisotropicSmp, fxaa_uv.zw + float2(1.0f, 1.0f) * pixel).rgb;


	//가장자리 추출
	float3 rgbM = Albedo_color.xyz;
	float3 luma = float3(0.299, 0.587, 0.114);
	float lumaNW = dot(rgbNW, luma);
	float lumaNE = dot(rgbNE, luma);
	float lumaSW = dot(rgbSW, luma);
	float lumaSE = dot(rgbSE, luma);
	float lumaM = dot(rgbM, luma);

	float lumaMin = min(lumaM, min(min(lumaNW, lumaNE), min(lumaSW, lumaSE)));
	float lumaMax = max(lumaM, max(max(lumaNW, lumaNE), max(lumaSW, lumaSE)));

	
	float2 dir;
	dir.x = -((lumaNW + lumaNE) - (lumaSW + lumaSE));
	dir.y = ((lumaNW + lumaSW) - (lumaNE + lumaSE));

	// 네방향의 변화도, 정규화
	float dirReduce = max((lumaNW + lumaNE + lumaSW + lumaSE) *
		(0.25 * fxaa_reduce_mul), fxaa_reduce_min);

	float rcpDirMin = 1.0f / (min(abs(dir.x), abs(dir.y)) + dirReduce);

	dir = min(float2(fxaa_span_max, fxaa_span_max),
		max(float2(-fxaa_span_max, -fxaa_span_max),
			dir * rcpDirMin)) * pixel;

	float3 rgbA = 0.5 * (
		g_BaseTexture.Sample(g_AnisotropicSmp, frag_coord * pixel + dir * (1.0f / 3.0f - 0.5f)).rgb +
		//texture2D( texture_, frag_coord * pixel + dir * ( 2.0 / 3.0 - 0.5 ) ).xyz );
		g_BaseTexture.Sample(g_AnisotropicSmp, frag_coord * pixel + dir * (2.0f / 3.0f - 0.5f)).rgb);
	float3 rgbB = rgbA * 0.5 + 0.25 * (
		g_BaseTexture.Sample(g_AnisotropicSmp, frag_coord * pixel + dir * -0.5f).rgb +
		g_BaseTexture.Sample(g_AnisotropicSmp, frag_coord * pixel + dir * 0.5f).rgb);

	float lumaB = dot(rgbB, luma);
	float4 color;
	if ((lumaB < lumaMin) || (lumaB > lumaMax)) {
		return float4(rgbA, Albedo_color.a);
	}
	else {
		return float4(rgbB, Albedo_color.a);
	}
}


VS_OUTPUT_NULLBUFFER FullScreenVS(uint VertexID : SV_VertexID)
{
	VS_OUTPUT_NULLBUFFER	output = (VS_OUTPUT_NULLBUFFER)0;

	output.ProjPos = float4(g_NullPos[VertexID], 0.f, 1.f);
	output.Pos = output.ProjPos;
	output.UV = g_NullUV[VertexID];

	return output;
}

static float BlurOffset[4] = { -2.f, -1.f, 1.f, 2.f };
static float BlurWeight[4] = { 0.00015f, 0.002f, 0.002f, 0.00015f };

PS_OUTPUT_SINGLE FullScreenPS(VS_OUTPUT_NULLBUFFER input)
{
	PS_OUTPUT_SINGLE    output = (PS_OUTPUT_SINGLE)0;

	float4	BaseColor = g_BaseTexture.Sample(g_AnisotropicSmp, input.UV);
	if (BaseColor.a == 0.f)
		clip(-1);
	float4 AlbedoColor;
	if (g_PostProcessFXAA ==1)
	{
		output.Color = FXAA(input.UV);
	}
	else
	{
		output.Color = g_BaseTexture.Sample(g_AnisotropicSmp, input.UV);
	}
	//float3 LightColor = float3(1.f, 1.f, 1.f);
	//float4 GBuffer5 = g_GBuffer5Target.Sample(g_AnisotropicSmp, input.UV);
	//if (g_PostProcessCelShader)
	//{
	//	float4 LightMap = BaseColor / AlbedoColor;
	//	float Grey = dot(LightMap.rgb, float3(0.212671f, 0.715160f, 0.072169f));
	//	Grey = sqrt(Grey);
	//	//빛의 계층화
	//	//{
	//	//	if (Grey > 1.f)
	//	//	{
	//	//		LightColor = float3(1.f, 1.f, 1.f);
	//	//	}
	//	//	else if (Grey > 0.9f)
	//	//	{
	//	//		LightColor = float3(0.9f, 0.9f, 0.9f);
	//	//	}
	//	//	else
	//	//	{
	//	//	}
	//	//}
	//	LightColor = float3(Grey, Grey, Grey);;
	//}
	//if (g_PostProcessToonShader)
	//{
	//	//AlbedoColor = ceil(AlbedoColor * 5.f) / 5.f;
	//}
	//
	//output.Color = float4(AlbedoColor.rgb * LightColor.rgb, 1.f);
	float4	BlurColor = (float4)0;

	if (g_PostProcessBlur == 1)
	{
		for (int i = 0; i < 4; ++i)
		{
			BlurColor += g_BaseTexture.Sample(g_AnisotropicSmp, input.UV + float2(BlurOffset[i], 0.f) * BlurWeight[i]);
			BlurColor += g_BaseTexture.Sample(g_AnisotropicSmp, input.UV + float2(0.f, BlurOffset[i]) * BlurWeight[i]);
		}

		BaseColor += BlurColor;
		BaseColor /= 9.f;
	}
	if (g_PostProcessOutline == 1)
	{
		float2 UV = input.UV;
		float4	DepthIn = g_GBuffer2Target.Sample(g_AnisotropicSmp, input.UV);
	
		float4	Depth1 = g_GBuffer2Target.Sample(g_AnisotropicSmp, float2(input.UV.x - g_PostProcessTexelSize.x, input.UV.y));
		float4	Depth2 = g_GBuffer2Target.Sample(g_AnisotropicSmp, float2(input.UV.x + g_PostProcessTexelSize.x, input.UV.y));
		float4	Depth3 = g_GBuffer2Target.Sample(g_AnisotropicSmp, float2(input.UV.x, input.UV.y + g_PostProcessTexelSize.y));
		float4	Depth4 = g_GBuffer2Target.Sample(g_AnisotropicSmp, float2(input.UV.x, input.UV.y - g_PostProcessTexelSize.y));
	
		float Depth = Depth1.y + Depth2.y + Depth3.y + Depth4.y;
		Depth = Depth * 0.25f;
	
		float Depth_Main = DepthIn.y;
	
		Depth_Main = abs(Depth_Main - Depth);
		if (Depth_Main > 0.02f)
		{
			output.Color = float4(0.f, 0.f, 0.f, 1.f);
		}
	}





	return output;
}


PS_OUTPUT_SINGLE FullScreenDistortionPS(VS_OUTPUT_NULLBUFFER input)
{
	PS_OUTPUT_SINGLE    output = (PS_OUTPUT_SINGLE)0;

	float4	BaseColor = g_BaseTexture.Sample(g_AnisotropicSmp, input.UV);
	/*float4	BlurColor = (float4)0;

	if (g_PostProcessBlur == 1)
	{
		for (int i = 0; i < 4; ++i)
		{
			BlurColor += g_BaseTexture.Sample(g_AnisotropicSmp, input.UV + float2(BlurOffset[i], 0.f) * BlurWeight[i]);
			BlurColor += g_BaseTexture.Sample(g_AnisotropicSmp, input.UV + float2(0.f, BlurOffset[i]) * BlurWeight[i]);
		}

		BaseColor += BlurColor;
		BaseColor /= 9.f;
	}*/

	//float4  BaseColor = g_BaseTexture.Sample(g_AnisotropicSmp, input.UV);
	float4	EmissiveColor = g_EmissiveTexture.Sample(g_AnisotropicSmp, input.UV);

	float4	Result;
	Result.rgb = BaseColor.rgb * g_vMtrlBaseColor.rgb + EmissiveColor.rgb * g_vMtrlEmissiveColor.rgb;
	Result.a = BaseColor.a * g_MtrlOpacity;

	Result = DistortionPostProcess(Result, input.UV, input.ProjPos);

	output.Color = Result;

	return output;
}




