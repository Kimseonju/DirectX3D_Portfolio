
#include "Share.fx"

cbuffer ParticleCBuffer : register(b11)
{
    float3 g_ParticlePos;
    uint g_ParticleSpawnCount;
    float3 g_ParticleStartScale;
    uint g_ParticleSpawnCountMax;
    float3 g_ParticleEndScale;
    float g_ParticleLifeTimeMin;
    float3 g_ParticleRange;
    float g_ParticleLifeTimeMax;
    float4 g_ParticleStartColor;
    float4 g_ParticleEndColor;
    float g_MinSpeed;
    float g_MaxSpeed;
    int g_ParticleMove;
    int g_Particle2D;
    float3 g_ParticleMoveDir;
    float g_ParticleDefaultZ;
    float3 g_ParticleMoveAngle;
    int g_ParticleGravity;
    float3 g_ParticleRot;
    int Empty;
};

#define	GRAVITY	9.8f

struct ParticleInfo
{
    float3 WorldPos;
    float3 WorldRot;
    float3 Dir;
    float Speed;
    float AddSpeed;
    float LifeTime;
    float MaxLifeTime;
    int Alive;
    float FallTime;
    float FallStartY;
    int Born;
    float4x4 save;
};

struct ParticleInfoShared
{
    uint SpawnCount;
    uint CurrentCount;

    float3 StartScale;
    float3 EndScale;
	
    float4 StartColor;
    float4 EndColor;

    int GravityEnable;
};

RWStructuredBuffer<ParticleInfo> g_ParticleArray : register(u0);
RWStructuredBuffer<ParticleInfoShared> g_ParticleShare : register(u1);

Texture2D g_GBuffer2 : register(t50);
Texture2D g_LightDif : register(t51);

[numthreads(64, 1, 1)]
void ParticleUpdate(uint3 ThreadID : SV_DispatchThreadID)
{
    g_ParticleShare[0].SpawnCount = g_ParticleSpawnCount;
    g_ParticleShare[0].StartScale = g_ParticleStartScale;
    g_ParticleShare[0].EndScale = g_ParticleEndScale;
    g_ParticleShare[0].StartColor = g_ParticleStartColor;
    g_ParticleShare[0].EndColor = g_ParticleEndColor;
    g_ParticleShare[0].GravityEnable = g_ParticleGravity;

    if (g_ParticleSpawnCountMax <= ThreadID.x)
        return;

    if (g_ParticleArray[ThreadID.x].Alive == 0)
    {
        int SpawnCount = g_ParticleShare[0].SpawnCount;
        int Exchange = 0;
		
        if (g_ParticleShare[0].SpawnCount == 1)
        {
            int InputValue = SpawnCount - 1;

			// ???? ?????? in, out, inout ?? ???? ?? ????.
			// in?? ???????? ???? ?????? ???? ???????? ???? ???????? ????????.
			// out?? ???????? ????????????. ?? ?????? ???????? return ????
			// out???? ???? ???? ?????? ???? ???????? ?? ???? ?? ?????? ??????
			// ???????? ???????? ?????? ?? ????.
			// ??, out?? ???? ?????? ???????? ???????? ???????? ??????.
			// inout?? ?????????? ????.
			// ???? ?????? 3?? ?????? 1???? ???????? ????????.
			// ???????? 1???????? ???? 2???????? ?????? ????????.
            InterlockedExchange(g_ParticleShare[0].SpawnCount, InputValue, Exchange);

            if (Exchange == SpawnCount)
            {
                g_ParticleArray[ThreadID.x].Alive = 1;
                g_ParticleArray[ThreadID.x].Born = 0;
            }
        }
        if (g_ParticleArray[ThreadID.x].Alive == 0)
            return;

		// ?????? ???? ???????????? ?????? ?????? ????????.
        float key = ThreadID.x / (float) g_ParticleSpawnCountMax;

		// Rand?? ?????? 0 ~ 1 ?????? ???? ????????.
        float3 RandomPos = float3(Rand(key), Rand(key * 2.f), Rand(key * 3.f));
		// -0.5?? ???????? -0.5 ~ 0.5 ?????? ?????????? ?????? ??????.
        float3 PosRange = (RandomPos - 0.5f) * g_ParticleRange;
        g_ParticleArray[ThreadID.x].WorldPos = float3(0.f, 0.f, 0.f);
        g_ParticleArray[ThreadID.x].WorldPos = /*g_ParticlePos + */PosRange; // ?????? ???? ??????

        g_ParticleArray[ThreadID.x].FallTime = 0.f;
        g_ParticleArray[ThreadID.x].FallStartY = g_ParticleArray[ThreadID.x].WorldPos.y;

        g_ParticleArray[ThreadID.x].MaxLifeTime = RandomPos.x * (g_ParticleLifeTimeMax - g_ParticleLifeTimeMin) + g_ParticleLifeTimeMin;
        g_ParticleArray[ThreadID.x].LifeTime = 0.f;

        if (g_ParticleMove == 1)
        {
            g_ParticleArray[ThreadID.x].Speed = RandomPos.x * (g_MaxSpeed - g_MinSpeed) + g_MinSpeed;

            //float2 RandomDir = RandomPos.xy * 1.f - 0.5f;
            float2 RandomDir = RandomPos.xy;
            g_ParticleArray[ThreadID.x].Dir = normalize(normalize(float3(RandomDir, 0.f)) + g_ParticleMoveDir);
			//g_ParticleArray[ThreadID.x].Dir = normalize(PosRange);
        }
        g_ParticleArray[ThreadID.x].WorldRot = g_ParticleRot;
        g_ParticleArray[ThreadID.x].save = g_matRot;
    }
	// ???? ???????? ???????? ???????????? ?????? ?????? ????????.
    else
    {
        g_ParticleArray[ThreadID.x].Born = 1;
        g_ParticleArray[ThreadID.x].LifeTime += g_DeltaTime;

        if (g_ParticleMove == 1)
        {
			// ???? ???????? ???? ?????? ?????? ???? ???? Pos ???? ??????????.
            g_ParticleArray[ThreadID.x].WorldPos.xy += g_ParticleArray[ThreadID.x].Dir.xy * g_ParticleArray[ThreadID.x].Speed * g_DeltaTime;

			// ????????
            if (g_ParticleShare[0].GravityEnable)
            {
                g_ParticleArray[ThreadID.x].FallTime += g_DeltaTime * 10.f;

                float Velocity = 0.1f * g_ParticleArray[ThreadID.x].Speed * g_ParticleArray[ThreadID.x].FallTime;

                g_ParticleArray[ThreadID.x].WorldPos.y = g_ParticleArray[ThreadID.x].FallStartY +
					(Velocity - 0.5f * GRAVITY * g_ParticleArray[ThreadID.x].FallTime * g_ParticleArray[ThreadID.x].FallTime);
            }
        }

        if (g_ParticleArray[ThreadID.x].LifeTime >= g_ParticleArray[ThreadID.x].MaxLifeTime)
        {
            g_ParticleArray[ThreadID.x].Alive = 0;
        }
    }
}


StructuredBuffer<ParticleInfo> g_ParticleArrayInput : register(t30);
StructuredBuffer<ParticleInfoShared> g_ParticleShareInput : register(t31);

struct VS_INPUT_PARTICLE
{
    float3 Pos : POSITION;
    uint InstanceID : SV_InstanceID;
};

struct VS_OUTPUT_PARTICLE
{
    uint InstanceID : TEXCOORD;
};

VS_OUTPUT_PARTICLE ParticleVS(VS_INPUT_PARTICLE input)
{
    VS_OUTPUT_PARTICLE output = (VS_OUTPUT_PARTICLE) 0;

    output.InstanceID = input.InstanceID;

    return output;
}

struct GS_PARTICLE_OUTPUT
{
    float4 Pos : SV_Position;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
    float4 ProjPos : POSITION;
};

static float4 g_ParticleLocalPos[4] =
{
    { -0.5f, 0.5f, 0.f, 0.f },
    { 0.5f, 0.5f, 0.f, 0.f },
    { 0.5f, -0.5f, 0.f, 0.f },
    { -0.5f, -0.5f, 0.f, 0.f }
};

[maxvertexcount(6)]
void ParticleGS(point VS_OUTPUT_PARTICLE input[1], inout TriangleStream<GS_PARTICLE_OUTPUT> OutputStream)
{
    uint InstanceID = input[0].InstanceID;

    if (g_ParticleArrayInput[InstanceID].Alive == 0)
        return;

    GS_PARTICLE_OUTPUT OutputArray[4] =
    {
        (GS_PARTICLE_OUTPUT) 0.f,
		(GS_PARTICLE_OUTPUT) 0.f,
		(GS_PARTICLE_OUTPUT) 0.f,
		(GS_PARTICLE_OUTPUT) 0.f
    };

    OutputArray[0].UV = float2(0.f, 0.f);
    OutputArray[1].UV = float2(1.f, 0.f);
    OutputArray[2].UV = float2(1.f, 1.f);
    OutputArray[3].UV = float2(0.f, 1.f);

	// UpdateShader???? ???????? ?????????? ??????????.
	// ?????? ?????? ?? ?????????? ?????? * ?????????? ???? ???????????? ????????.
    float Ratio = g_ParticleArrayInput[InstanceID].LifeTime / g_ParticleArrayInput[InstanceID].MaxLifeTime;

    float3 Scale = lerp(g_ParticleShareInput[0].StartScale, g_ParticleShareInput[0].EndScale, float3(Ratio, Ratio, Ratio)).xyz;

    float4 Color = lerp(g_ParticleShareInput[0].StartColor, g_ParticleShareInput[0].EndColor, float4(Ratio, Ratio, Ratio, Ratio));

	// 4???? ?????????? ??????????.
    for (int i = 0; i < 4; ++i)
    {
        float3 WorldPos = (float3) 0.f;
		
        WorldPos.xy = g_ParticleArrayInput[InstanceID].WorldPos.xy + g_ParticleLocalPos[i].xy * Scale.xy;
        WorldPos.z = g_ParticleArrayInput[InstanceID].WorldPos.z;

        /*
        g_matWorld = g_matScale * g_matRot * g_matPos
	matrix  g_matWorld;
	matrix  g_matView;
	matrix  g_matProj;
        */
        float4x4 WorldMat = g_matRot;
        float4x4 Mat = mul(g_matWorld, g_matView);
        Mat = mul(Mat, g_matProj);
        OutputArray[i].ProjPos = mul(float4(WorldPos, 1.f), Mat);
        OutputArray[i].Pos = OutputArray[i].ProjPos;
        OutputArray[i].Color = Color;
    }

    OutputStream.Append(OutputArray[0]);
    OutputStream.Append(OutputArray[1]);
    OutputStream.Append(OutputArray[2]);
    OutputStream.RestartStrip();

    OutputStream.Append(OutputArray[0]);
    OutputStream.Append(OutputArray[2]);
    OutputStream.Append(OutputArray[3]);
    OutputStream.RestartStrip();
}

float4 ParticlePS(GS_PARTICLE_OUTPUT input) : SV_Target
{
    float4 Color = (float4) 0.f;

    float4 BaseColor = g_BaseTexture.Sample(g_AnisotropicSmp, input.UV);
    float4 EmissiveColor = g_EmissiveTexture.Sample(g_AnisotropicSmp, input.UV);

    float2 ScreenUV;
    ScreenUV.x = input.ProjPos.x / input.ProjPos.w * 0.5f + 0.5f;
    ScreenUV.y = input.ProjPos.y / input.ProjPos.w * -0.5f + 0.5f;

    float4 GBuffer2 = g_GBuffer2.Sample(g_AnisotropicSmp, ScreenUV);

    float Alpha = 1.f;

    if (GBuffer2.w > 0.f)
        Alpha = (GBuffer2.y - input.ProjPos.w) / 2.5f;

    Color.rgb = BaseColor.rgb * g_vMtrlBaseColor.rgb * input.Color.rgb + EmissiveColor.rgb * g_vMtrlEmissiveColor.rgb;
    Color.a = BaseColor.a * g_MtrlOpacity * input.Color.a * Alpha;

    Color = Distortion(Color, input.UV, input.ProjPos);

    return Color;
}

