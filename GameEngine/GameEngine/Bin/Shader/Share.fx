
struct PS_OUTPUT_SINGLE
{
	// Target은 렌더타겟을 의미한다.
	// BackBuffer가 0번 렌더타겟에 묶여있으므로 SV_TARGET 을 하면 0번 타겟에 색상을 출력하겠다는
	// 의미가 된다.
	float4  Color : SV_TARGET;
};


struct PS_OUTPUT_GBUFFER
{
	float4	Albedo		: SV_TARGET;
	float4	GBuffer1	: SV_TARGET1;
	float4	GBuffer2	: SV_TARGET2;
	float4	GBuffer3	: SV_TARGET3;
	float4	GBuffer4	: SV_TARGET4;
	float4	GBuffer5	: SV_TARGET5;
};

struct PS_OUTPUT_BLOOM
{
	float4 Color	: SV_TARGET;
};

cbuffer Transform : register(b0)
{
    matrix	g_matPos;
    matrix  g_matRot;
    matrix  g_matScale;
	matrix  g_matWorld;
	matrix  g_matView;
	matrix  g_matProj;
	matrix  g_matWV;
	matrix	g_matVP;
	matrix  g_matWVP;
	matrix	g_matInvView;
	matrix	g_matInvProj;
	matrix	g_matInvVP;
	matrix	g_matInvWVP;
	float3  g_vPivot;
	int		g_Animation2DEnable;
	float3  g_vMeshSize;
	float   g_fTrEmpty2;
};

cbuffer Material : register(b1)
{
	float4  g_vMtrlBaseColor;
	float4	g_vMtrlAmbientColor;
	float4	g_vMtrlSpecularColor;
	float4  g_vMtrlEmissiveColor;
	float	g_MtrlOpacity;
	int		g_MtrlPaperBurnEnable;
	int		g_MtrlDistortionEnable;
	int		g_MtrlBloomEnable;
	int		g_MtrlBumpEnable;
	int		g_MtrlAnimation3DEnable;
	int		g_MtrlSpcTex;
	int		g_MtrlEmvTex;
	int		g_MtrlReceiveDecal;
	int		g_MtrlShadowEnable;
	float2 g_MtrlEmpty;


	////// UV Flow
	int g_MtrlFlow;
	int g_MtrlFlowDirection;
	float g_MtrlFlowSpeedX;
	float g_MtrlFlowSpeedY;
};

cbuffer GlobalCBuffer : register(b2)
{
	float	g_CameraBottom;
	float	g_DeltaTime;
	float	g_AccTime;
	float	g_GlobalEmpty;
	float2	g_Resolution;
	float2	g_NoiseResolution;
};

cbuffer PostProcess : register(b3)
{
	int		g_PostProcessBlur;
	int		g_PostProcessDistortion;
	int		g_PostProcessBloom;
	int		g_PostProcessOutline;

	int		g_PostProcessCelShader;
	int		g_PostProcessToonShader;
	float2  g_PostProcessTexelSize;
	int		g_PostProcessFXAA;
	float3 g_PostProcessFEmpty;
};

cbuffer PaperBurn	: register(b4)
{
	float	g_PaperBurn;
	float3	g_PaperBurnOutLineColor;
	float3	g_PaperBurnCenterColor;
	int		g_PaperBurnInverse;
	float3	g_PaperBurnInLineColor;
	float	g_PaperBurnInFilter;
	float	g_PaperBurnCenterFilter;
	float	g_PaperBurnOutFilter;
	float2	g_PaperBurnEmpty;
};

cbuffer Distortion2DCBuffer : register(b5)
{
	float	g_DistortionWeight;
	int		g_DistortionSelf;
	float	g_DistortionSpeed;
	float	g_DistortionEmpty;
};

cbuffer Animation2D : register(b6)
{
	float2  g_vAnimation2DStartUV;
	float2  g_vAnimation2DEndUV;
	int		g_Animation2DType;
	float3	g_vAnimation2DEmpty;
};

cbuffer LightCBuffer : register(b7)
{
	float4	g_LightDiffuse;
	float4	g_LightAmbient;
	float4	g_LightSpecular;
	int		g_LightLightType;
	float3	g_LightPos;
	float3	g_LightDir;
	float	g_LightDistance;
	float	g_LightAngleIn;
	float	g_LightAngleOut;
	float	g_LightAtt1;
	float	g_LightAtt2;
	float	g_LightAtt3;
	float3	g_LightEmpty;
};

cbuffer Bloom	: register(b8)
{
	float	g_BloomWeight;
	float3	g_BloomColor;
}

SamplerState    g_PointSmp  : register(s0);
SamplerState    g_LinearSmp  : register(s1);
SamplerState    g_AnisotropicSmp  : register(s2);

Texture2D       g_BaseTexture   : register(t0);
Texture2D       g_EmissiveTexture : register(t1);
Texture2D		g_NormalTexture : register(t2);
Texture2D		g_SpecularTexture : register(t3);

Texture2D	g_RandNoiseTex	: register(t100);
Texture2D	g_BurnTex	: register(t101);
Texture2D	g_DistortionNormalTex	: register(t102);
Texture2D	g_DistortionFilterTex	: register(t103);
Texture2D	g_SceneTex : register(t104);
Texture2D	g_DistortionNoiseTex	: register(t105);

Texture2D	g_BloomTex	: register(t107);

StructuredBuffer<matrix>	g_SkinningBoneMatrixArray	: register(t106);


float ConvertColor(float4 Color)
{
	uint4	Convert = (uint4)0;

	Convert.r = uint(Color.r * 255);
	Convert.g = uint(Color.g * 255);
	Convert.b = uint(Color.b * 255);
	Convert.a = uint(Color.a * 255);

	uint	Result = 0;

	Result = Convert.a;
	Result = (Result << 8) | Convert.r;
	Result = (Result << 8) | Convert.g;
	Result = (Result << 8) | Convert.b;

	return asfloat(Result);
}

float4 ConvertColor(float Color)
{
	uint Convert = asuint(Color);

	float4	Result;
	Result.b = (Convert & 0x000000ff) / 255.f;
	Result.g = ((Convert >> 8) & 0x000000ff) / 255.f;
	Result.r = ((Convert >> 16) & 0x000000ff) / 255.f;
	Result.a = ((Convert >> 24) & 0x000000ff) / 255.f;

	return Result;
}



// 조명 처리
struct LightResult
{
	float4	Dif;
	float4	Amb;
	float4	Spc;
	float4	Emv;
};

#define	LightTypeDir	0
#define	LightTypePoint	1
#define	LightTypeSpot	2

float3 ComputeBumpNormal(float3 Normal, float3 Tangent, float3 Binormal, float2 UV)
{
	float3	result = Normal;

	if (g_MtrlBumpEnable == 1)
	{
		//float4	NormalColor = g_NormalTexture.Sample(g_AnisotropicSmp, UV);
		//
		////B = T x N
		//float3	ConvertNormal = NormalColor.xyz * 2.f - 1.f;
		//ConvertNormal.z = 1.f;
		//ConvertNormal = normalize(ConvertNormal);
		//
		//float3x3 mat =
		//{
		//	Tangent,
		//	Binormal,
		//	Normal
		//};
		//result = normalize(mul(ConvertNormal, mat));
		
	}

	return result;
}

float ComputeBumpSpecularPower(float2 UV)
{
	//R
	float	result = 0.f;
	if (g_MtrlBumpEnable == 1 && g_PostProcessToonShader==1)
	{
		float4	NormalColor = g_NormalTexture.Sample(g_AnisotropicSmp, UV);
		result = NormalColor.r;
	}
	return result;
}
float4 ComputeBumpSpecularMasking(float2 UV)
{
	//B
	float4	result = 0.f;
	if (g_MtrlBumpEnable == 1 && g_PostProcessToonShader == 1)
	{
		float4	NormalColor = g_NormalTexture.Sample(g_AnisotropicSmp, UV);
		result = float4(NormalColor.b, NormalColor.b, NormalColor.b, NormalColor.b);
	}
	return result;
}
float ComputeBumpThreshold(float2 UV)
{
	//G
	float	result = 1.f;
	if (g_MtrlBumpEnable == 1 && g_PostProcessToonShader == 1)
	{
		float4	NormalColor = g_NormalTexture.Sample(g_AnisotropicSmp, UV);
		result = NormalColor.g;
	}
	return result;
}

LightResult ComputeLight(float3 Pos, float3 Normal, float3 Tangent, float3 Binormal,
	float2 UV)
{
	LightResult	result = (LightResult)0.f;

	float3	LightDir = (float3)0.f;
	float	Attn = 1.f;

	if (g_LightLightType == LightTypeDir)
	{
		LightDir = -g_LightDir;
		LightDir = normalize(LightDir);
	}

	if (g_LightLightType == LightTypePoint)
	{
		LightDir = g_LightPos - Pos;
		LightDir = normalize(LightDir);

		float	Dist = distance(g_LightPos, Pos);

		if (Dist > g_LightDistance)
			Attn = 0.f;

		else
		{
			Attn = 1.f / (g_LightAtt1 + g_LightAtt2 * Dist + g_LightAtt3 * (Dist * Dist));
		}
	}

	if (g_LightLightType == LightTypeSpot)
	{
	}

	float3	ViewNormal = ComputeBumpNormal(Normal, Tangent, Binormal, UV);
	//ViewNormal = Normal;

	float	Intensity = max(0.f, dot(ViewNormal, LightDir));

	result.Dif = g_LightDiffuse * g_vMtrlBaseColor * Intensity * Attn;
	result.Amb = g_LightAmbient * g_vMtrlAmbientColor * Attn;

	// 비금속 표면에 대한 Specular 처리를 위해 반사벡터를 구한다.
	float3	Reflect = 2.f * dot(ViewNormal, LightDir) * ViewNormal - LightDir;
	Reflect = normalize(Reflect);

	float3	View = -Pos;
	View = normalize(View);

	float4	MtrlSpc = g_vMtrlSpecularColor;

	if (g_MtrlSpcTex)
		MtrlSpc = g_SpecularTexture.Sample(g_AnisotropicSmp, UV).rrrr;

	MtrlSpc.w = 1.f;

	result.Spc = g_LightSpecular * MtrlSpc *
		pow(max(0.f, dot(View, Reflect)), g_vMtrlSpecularColor.w) * Attn;


	float4	MtrlEmv = g_vMtrlEmissiveColor;

	if (g_MtrlEmvTex)
		MtrlEmv = g_EmissiveTexture.Sample(g_AnisotropicSmp, UV);

	result.Emv = MtrlEmv;

	return result;
}


#define	Animation2DAtlas	0
#define	Animation2DFrame	1
#define	Animation2DArray	2


static float gaussian5x5[25] =
{
	0.003765, 0.015019, 0.023792, 0.015019, 0.003765,
	0.015019, 0.059912, 0.094907, 0.059912, 0.015019,
	0.023792, 0.094907, 0.150342, 0.094907, 0.023792,
	0.015019, 0.059912, 0.094907, 0.059912, 0.015019,
	0.003765, 0.015019, 0.023792, 0.015019, 0.003765,
};

float Gaussian5x5Sample(int2 UV, Texture2D Tex)
{
	float4	Output = (float4)0.f;

	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			Output += Tex[UV + int2(i - 2, j - 2)] * gaussian5x5[i * 5 + j];
		}
	}

	return Output.x;
}

float Rand(float Key)
{
	float2	UV = float2(Key + g_AccTime, g_AccTime);
	UV.y += sin(UV.x * 2.f * 3.141592f);

	if (UV.x > 0.f)
		UV.x = frac(UV.x);

	else
		UV.x = 1.f - abs(UV.x);

	if (UV.y > 0.f)
		UV.y = frac(UV.y);

	else
		UV.y = 1.f - abs(UV.y);

	UV = UV * g_NoiseResolution;

	return Gaussian5x5Sample(UV, g_RandNoiseTex);
}

float4	PaperBurn2D(float4 Color, float2 UV)
{
	if (g_MtrlPaperBurnEnable == 0)
		return Color;

	float	BurnColor = g_BurnTex.Sample(g_AnisotropicSmp, UV).r;

	float4	result = Color;

	// 정방향일 경우
	if (g_PaperBurnInverse == 0)
	{
		if (g_PaperBurn >= BurnColor.r)
			result.a = 0.f;

		else
		{
			if (g_PaperBurn - g_PaperBurnOutFilter <= BurnColor.r &&
				BurnColor.r <= g_PaperBurn + g_PaperBurnOutFilter)
			{
				result.rgb = g_PaperBurnOutLineColor;
				//result.rgb *= g_PaperBurnOutLineColor;
			}

			if (g_PaperBurn - g_PaperBurnCenterFilter <= BurnColor.r &&
				BurnColor.r <= g_PaperBurn + g_PaperBurnCenterFilter)
			{
				result.rgb = g_PaperBurnCenterColor;
				//result.rgb *= g_PaperBurnCenterColor;
			}

			if (g_PaperBurn - g_PaperBurnInFilter <= BurnColor.r &&
				BurnColor.r <= g_PaperBurn + g_PaperBurnInFilter)
			{
				result.rgb = g_PaperBurnInLineColor;
				//result.rgb *= g_PaperBurnInLineColor;
			}
		}
	}

	// 역방향일 경우
	else
	{
		if (g_PaperBurn <= BurnColor.r)
			result.a = 0.f;

		else
		{
			if (g_PaperBurn - g_PaperBurnOutFilter <= BurnColor.r &&
				BurnColor.r <= g_PaperBurn + g_PaperBurnOutFilter)
			{
				result.rgb = g_PaperBurnOutLineColor;
				//result.rgb *= g_PaperBurnOutLineColor;
			}

			if (g_PaperBurn - g_PaperBurnCenterFilter <= BurnColor.r &&
				BurnColor.r <= g_PaperBurn + g_PaperBurnCenterFilter)
			{
				result.rgb = g_PaperBurnCenterColor;
				//result.rgb *= g_PaperBurnCenterColor;
			}

			if (g_PaperBurn - g_PaperBurnInFilter <= BurnColor.r &&
				BurnColor.r <= g_PaperBurn + g_PaperBurnInFilter)
			{
				result.rgb = g_PaperBurnInLineColor;
				//result.rgb *= g_PaperBurnInLineColor;
			}
		}
	}

	return result;
}

float2 Distortion2DUV(float2 UV)
{
	float2	Result = UV;

	float4	DistortionNormal = g_DistortionNormalTex.Sample(g_AnisotropicSmp, UV);

	// NormalTexture에서 얻어온 r, g 값을 이용해서 0 ~ 1 사이의 값을
	// -1 ~ 1 사이의 값으로 변경한다.
	float2	Weight = (DistortionNormal.rg * 2.f - 1.f) * g_DistortionWeight;

	Result = UV + Weight;

	// frac : 소수점 이하 부분을 리턴한다.
	Result = frac(Result);

	if (Result.x < 0.f)
		Result.x = 1.f + Result.x;

	if (Result.y < 0.f)
		Result.y = 1.f + Result.y;

	return Result;
}

float2 DistortionUV(float2 UV)
{
	float2 DUV = UV;
	DUV += 0.1f * g_AccTime;

	float	Noise = g_DistortionNoiseTex.SampleLevel(g_AnisotropicSmp, DUV, 0).r;
	Noise*= 0.02f;


	return UV + Noise;
}

float4 Distortion(float4 Color, float2 UV, float4 ProjPos)
{
	if (g_MtrlDistortionEnable == 0)
		return Color;

	else if (Color.a == 0.f)
		return Color;

	/*
	로컬정점 * 월드뷰투영 = NDC

	이때 x, y, z, w 가 나올것이다.

	x / w, y / w, z / w, w / w 를 해주게 된다.

	-1 ~ 1 사이를 Screen 좌표로 변환해주게 된다.
	1280, 720 이라면

	-1 ~ 1 사이의 x값을 1280/2 를 곱한다.
	-640 ~ 640이 되고 여기에 1280/2 를 더한다.
	0 ~ 1280 사이의 화면좌표로 변환이 된다.
	*/

	// 화면의 전체 혹은 일정 부분을 왜곡 처리를 해야 한다.
	// 그렇기 때문에 현재 인자로 들어온 ProjPos를 이용해서 화면에서의 UV 좌표를
	// 구해줄 수 있어야 한다.
	// 실제 화면에 출력될때는 NDC 좌표를 NDC좌표의 w로 나누어서 Screen좌표로
	// 변환을 해서 최종 Screen 좌표를 구해주게 된다.
	// 그러므로 화면에서의 UV를 구하기 위해서는 ProjPos를 w로 나누어준 후에
	// -1 ~ 1 좌표를 0 ~ 1로 만들어주어야 한다.
	float2	ScreenUV;
	ScreenUV.x = ProjPos.x / ProjPos.w * 0.5f + 0.5f;
	// 투영으로 변환한 y값은 위가 + 값이다. 그런데 uv공간은 아래가 + 값이
	// 되어야 하므로 위 아래를 반전시켜주도록 한다.
	ScreenUV.y = ProjPos.y / ProjPos.w * -0.5f + 0.5f;

	// https://docs.microsoft.com/en-us/windows/win32/direct3dhlsl/dx-graphics-hlsl-to-samplelevel
	float2	NormalUV = ScreenUV;

	NormalUV.x += g_DistortionSpeed * g_AccTime;

	float4	Normal = g_DistortionNormalTex.Sample(g_AnisotropicSmp, NormalUV);

	Normal.xy *= 2.f - 1.f;
	Normal.xy *= g_DistortionWeight;

	//float	Noise = g_DistortionNoiseTex.SampleLevel(g_AnisotropicSmp, UV, 0).r;


	// Filter를 얻어올때는 일반 UV를 이용해서 얻어온다.
	float4	Filter = g_DistortionFilterTex.Sample(g_AnisotropicSmp, UV);

	// 위에서 얻어온 Noise 값을 이용해서 uv를 조금 더 랜덤하게 가공한다.
	//ScreenUV.x += cos(Noise * g_DistortionSpeed * g_AccTime) * Filter.r * g_DistortionWeight;
	//ScreenUV.y += sin(Noise * g_DistortionSpeed * g_AccTime) * Filter.r * g_DistortionWeight;

	// frac : 소수점 이하 부분을 리턴한다.
	//ScreenUV = frac(ScreenUV);

	//if (ScreenUV.x < 0.f)
	//	ScreenUV.x = 1.f + ScreenUV.x;

	//if (ScreenUV.y < 0.f)
	//	ScreenUV.y = 1.f + ScreenUV.y;

	float4	SceneColor = g_SceneTex.Sample(g_AnisotropicSmp, ScreenUV + Normal.xy);

	float4	Result = SceneColor;

	if (g_DistortionSelf == 1)
		Result.rgb = Color.rgb * Color.a + SceneColor.rgb * (1.f - Color.a);

	Result.a = Color.a;

	return Result;
}

float4 DistortionPostProcess(float4 Color, float2 UV, float4 ProjPos)
{
	if (g_PostProcessDistortion == 0)
		return Color;

	//else if (Color.a == 0.f)
	//	return Color;

	/*
	로컬정점 * 월드뷰투영 = NDC

	이때 x, y, z, w 가 나올것이다.

	x / w, y / w, z / w, w / w 를 해주게 된다.

	-1 ~ 1 사이를 Screen 좌표로 변환해주게 된다.
	1280, 720 이라면

	-1 ~ 1 사이의 x값을 1280/2 를 곱한다.
	-640 ~ 640이 되고 여기에 1280/2 를 더한다.
	0 ~ 1280 사이의 화면좌표로 변환이 된다.
	*/

	// 화면의 전체 혹은 일정 부분을 왜곡 처리를 해야 한다.
	// 그렇기 때문에 현재 인자로 들어온 ProjPos를 이용해서 화면에서의 UV 좌표를
	// 구해줄 수 있어야 한다.
	// 실제 화면에 출력될때는 NDC 좌표를 NDC좌표의 w로 나누어서 Screen좌표로
	// 변환을 해서 최종 Screen 좌표를 구해주게 된다.
	// 그러므로 화면에서의 UV를 구하기 위해서는 ProjPos를 w로 나누어준 후에
	// -1 ~ 1 좌표를 0 ~ 1로 만들어주어야 한다.
	float2	ScreenUV;
	ScreenUV.x = ProjPos.x / ProjPos.w * 0.5f + 0.5f;
	// 투영으로 변환한 y값은 위가 + 값이다. 그런데 uv공간은 아래가 + 값이
	// 되어야 하므로 위 아래를 반전시켜주도록 한다.
	ScreenUV.y = ProjPos.y / ProjPos.w * -0.5f + 0.5f;

	// https://docs.microsoft.com/en-us/windows/win32/direct3dhlsl/dx-graphics-hlsl-to-samplelevel
	//float	Noise = g_DistortionNoiseTex.SampleLevel(g_AnisotropicSmp, UV, 0).r;

	// Normal을 가져올때 사용하는 UV좌표를 변환시켜서 Normal을 가져온다.
	float2	NormalUV = UV;

	NormalUV.x += g_DistortionSpeed * g_AccTime;

	float4	Normal = g_DistortionNormalTex.Sample(g_AnisotropicSmp, NormalUV);

	Normal.xy *= 2.f - 1.f;
	Normal.xy *= g_DistortionWeight;

	// 위에서 얻어온 Noise 값을 이용해서 uv를 조금 더 랜덤하게 가공한다.
	// -0.01 ~ 0.01 사이를 왔다갔다 하는 값을 만들어서 처리
	//ScreenUV.x += cos(Normal.x * g_DistortionSpeed * g_AccTime) * g_DistortionWeight;
	//ScreenUV.y += sin(Normal.y * g_DistortionSpeed * g_AccTime) * g_DistortionWeight;
	//ScreenUV.x += Normal.x * g_DistortionWeight;
	//ScreenUV.y += Normal.y * g_DistortionWeight;

	/*if (ScreenUV.x < 0.f)
		ScreenUV.x = 0.f;

	else if (ScreenUV.x > 1.f)
		ScreenUV.x = 1.f;

	if (ScreenUV.y < 0.f)
		ScreenUV.y = 0.f;

	else if (ScreenUV.y > 1.f)
		ScreenUV.y = 1.f;*/

	// frac : 소수점 이하 부분을 리턴한다.
	//ScreenUV = frac(ScreenUV);

	/*if (ScreenUV.x < 0.f)
		ScreenUV.x = 1.f + ScreenUV.x;

	if (ScreenUV.y < 0.f)
		ScreenUV.y = 1.f + ScreenUV.y;*/

	float4	SceneColor = g_BaseTexture.Sample(g_AnisotropicSmp, ScreenUV + Normal.xy);

	float4	Result = SceneColor;

	/*if (g_DistortionSelf == 1)
		Result.rgb = Color.rgb * Color.a + SceneColor.rgb * (1.f - Color.a);

	Result.a = Color.a;*/

	return Result;
}


static const float2 g_NullPos[4] =
{
	float2(-1.f, 1.f),
	float2(1.f, 1.f),
	float2(-1.f, -1.f),
	float2(1.f, -1.f)
};

static const float2 g_NullUV[4] =
{
	float2(0.f, 0.f),
	float2(1.f, 0.f),
	float2(0.f, 1.f),
	float2(1.f, 1.f)
};

struct VS_OUTPUT_NULLBUFFER
{
	float4	Pos : SV_POSITION;
	float2	UV	: TEXCOORD;
	float4	ProjPos : POSITION;
};

struct SkinningInfo
{
	float3	Pos;
	float3	Normal;
	float3	Tangent;
	float3	Binormal;
};

matrix GetBoneMatrix(int Index)
{
	return g_SkinningBoneMatrixArray[Index];
}

SkinningInfo Skinning(float3 Pos, float3 Normal, float3 Tangent, float3 Binormal,
	float4 Weight, float4 Index)
{
	SkinningInfo	Info = (SkinningInfo)0;

	if (g_MtrlAnimation3DEnable == 0)
	{
		Info.Pos = Pos;
		Info.Normal = Normal;
		Info.Tangent = Tangent;
		Info.Binormal = Binormal;

		return Info;
	}

	for (int i = 0; i < 4; ++i)
	{
		if (Weight[i] == 0.f)
			continue;

		matrix	matBone = GetBoneMatrix((int)Index[i]);

		Info.Pos += (mul(float4(Pos, 1.f), matBone) * Weight[i]).xyz;
		Info.Normal += (mul(float4(Normal, 0.f), matBone) * Weight[i]).xyz;
		Info.Tangent += (mul(float4(Tangent, 0.f), matBone) * Weight[i]).xyz;
		Info.Binormal += (mul(float4(Binormal, 0.f), matBone) * Weight[i]).xyz;
	}

	Info.Normal = normalize(Info.Normal);
	Info.Tangent = normalize(Info.Tangent);
	Info.Binormal = normalize(Info.Binormal);

	return Info;
}

float3 SkinningShadow(float3 Pos, float4 Weight, float4 Index)
{
	float3	Info = (float3)0;

	if (g_MtrlAnimation3DEnable == 0)
	{
		return Pos;
	}

	for (int i = 0; i < 4; ++i)
	{
		if (Weight[i] == 0.f)
			continue;

		matrix	matBone = GetBoneMatrix((int)Index[i]);

		Info += (mul(float4(Pos, 1.f), matBone) * Weight[i]).xyz;
	}

	return Info;
}


static const float Weight[13] =
{
	0.0561f, 0.1356f, 0.278f, 0.4868f, 0.7261f, 0.9231f,
	1.f, 0.9231f, 0.7261f, 0.4868f, 0.278f, 0.1356f, 0.0561f
};

float4 Blur(float Color, float2 UV)
{
	float4 Out = 0;

	float2 t = UV;
	float2 uv = 0;

	float tu = 1.f / g_Resolution.x;

	for (int i = 6; i < 6; ++i)
	{
		uv = t + float2 (tu * i, 0);
		Out += Weight[6 + i] * tex2D(g_LinearSmp, uv);
	}

	Out /= 6.2108f;

	return Out;
}