
#include "TornadoTrailComponent.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "Transform.h"
#include "../Resource/Material.h"
#include "../PathManager.h"
#include "../Resource/Texture.h"
#include "../Navigation3D.h"
#include "../NavigationManager.h"
#include "Camera.h"
#include "../Scene/CameraManager.h"
#include "../Resource/StructuredBuffer.h"
#include "../Resource/TrailCBuffer.h"
#include "../Render/RenderStateManager.h"
#include "../Render/RenderState.h"
#include "../Resource/ResourceManager.h"
CTornadoTrailComponent::CTornadoTrailComponent() :
	m_TrailShader(nullptr),
	m_TrailUpdate(true)
{
	m_PrimitiveType = PrimitiveComponent_Type::Primitive3D;
	m_ClassType = Component_Class_Type::Billboard;
	m_3DType = RT3D_Particle;

	SetTransformState(Transform_State::None);
	m_Time = 0.f;
	m_VecSize = 10;
	m_vecRenderPos.resize(m_VecSize);
	m_vecRenderMat.resize(m_VecSize);
	m_CallmullCount = 3;
}

CTornadoTrailComponent::CTornadoTrailComponent(const CTornadoTrailComponent& com) :
	CPrimitiveComponent(com)
{
	m_TrailCBuffer = com.m_TrailCBuffer->Clone();
	m_pMesh = com.m_pMesh;
	m_State = com.m_State;
	m_RenderShader = com.m_RenderShader;

}

CTornadoTrailComponent::~CTornadoTrailComponent()
{
	SAFE_DELETE(m_TrailCBuffer);
}

void CTornadoTrailComponent::SetTrailUpdate(bool Update)
{
	//m_TrailUpdate = Update;
	//if (m_TrailUpdate)
	//{
	//	Matrix mat = GetWorldMatrix();
	//	SetPositionAllList(mat);
	//}
}

void CTornadoTrailComponent::SetPositionAllList()
{
	Vector3 Pos = Vector3::Zero;
	Pos.x = 0.2f;
	m_vecPos.push_back(Pos);
	
	for (int i = 1; i < m_VecSize; ++i)
	{
		Pos.x = (float)GetRandomFloat2(2000*i, 3400*i, 10000.f);
		Pos.y += (float)GetRandomFloat2(3000, 5000, 10000.f);
		m_vecPos.push_back(Pos);
	}
		
}

void CTornadoTrailComponent::Start()
{
	CPrimitiveComponent::Start();
	SetPositionAllList();
}

bool CTornadoTrailComponent::Init()
{
	if (!CPrimitiveComponent::Init())
		return false;
	m_TrailCBuffer = new CTrailCBuffer;
	m_TrailCBuffer->Init();
	m_pMesh = CResourceManager::GetInst()->FindMesh("ParticlePoint");
	m_State = CRenderStateManager::GetInst()->FindRenderState("CullNone");

	m_RenderShader = CShaderManager::GetInst()->FindShader("TrailShader");
	return true;
}

void CTornadoTrailComponent::Update(float DeltaTime)
{
	CPrimitiveComponent::Update(DeltaTime);
	
	float RotY = GetWorldRotation().y;
	
	//S,T,R
	Vector3 ParentPos = GetWorldPos();
	Vector3 ParentRot = Vector3(0.f, RotY, 0.f);
	Vector3 Rotation = Vector3(-30.f, RotY, 0.f);
	Matrix matRot, matPos;

	for (int i = 0; i < m_VecSize; ++i)
	{
		matRot.Rotation(ParentRot);
		memcpy(&matRot._41, &ParentPos, sizeof(Vector3));
		Vector3 Pos= m_vecPos[i].TransformCoord(matRot);
		matRot.Rotation(Rotation);
		matPos.Translation(Pos);
		m_vecRenderMat[i] = matRot * matPos;
		ParentRot.y += 90.f;
	}

	auto iter = m_vecRenderMat.begin();
	auto iterEnd = m_vecRenderMat.end();
	
	int iCount = 0;
	int Count=0;
	float TrailSize = m_Size/(float)(m_VecSize-1);
	for (; iter != iterEnd; ++iter)
	{
		Matrix Pos = (*iter);
		Count++;
		m_LocalSwordLow = Vector3(0.f, TrailSize*Count, 0.f);
		m_LocalSwordHigh = Vector3(0.f, -TrailSize*Count, 0.f);

		m_LocalSwordLow = m_LocalSwordLow.TransformCoord(Pos);
		m_LocalSwordHigh = m_LocalSwordHigh.TransformCoord(Pos);
		m_TrailCBuffer->SetVelocity(iCount, m_LocalSwordLow, m_LocalSwordHigh);

		++iCount;
	}
	std::vector<Vector3> vecHigh;
	std::vector<Vector3> vecLow;
	for (int i = 0; i < m_VecSize; ++i)
	{
		if (i == 0)
		{
			for (int j = 0; j < m_CallmullCount; ++j)
			{
				float Progress = (float)j / (float)m_CallmullCount;
				Vector3 vec;
				Vector3 HighDraw = vec.CatmullRom(m_TrailCBuffer->GetVelocityHigh(i), m_TrailCBuffer->GetVelocityHigh(i),
					m_TrailCBuffer->GetVelocityHigh(i), m_TrailCBuffer->GetVelocityHigh(i), Progress);
	
	
				Vector3 LowDraw = vec.CatmullRom(m_TrailCBuffer->GetVelocityLow(i), m_TrailCBuffer->GetVelocityLow(i),
					m_TrailCBuffer->GetVelocityLow(i), m_TrailCBuffer->GetVelocityLow(i), Progress);
				vecHigh.push_back(HighDraw);
				vecLow.push_back(LowDraw);
			}
		}
		else if (i == m_VecSize-2)
		{
			for (int j = 0; j < m_CallmullCount; ++j)
			{
				float Progress = (float)j / (float)m_CallmullCount;
				Vector3 vec;
				Vector3 HighDraw = vec.CatmullRom(m_TrailCBuffer->GetVelocityHigh(i - 1), m_TrailCBuffer->GetVelocityHigh(i),
					m_TrailCBuffer->GetVelocityHigh(i + 1), m_TrailCBuffer->GetVelocityHigh(i + 1), Progress);
	
	
				Vector3 LowDraw = vec.CatmullRom(m_TrailCBuffer->GetVelocityLow(i - 1), m_TrailCBuffer->GetVelocityLow(i),
					m_TrailCBuffer->GetVelocityLow(i + 1), m_TrailCBuffer->GetVelocityLow(i + 1), Progress);
				vecHigh.push_back(HighDraw);
				vecLow.push_back(LowDraw);
			}
	
		}
		else if (i == m_VecSize-1)
		{
			for (int j = 0; j < m_CallmullCount; ++j)
			{
				float Progress = (float)j / (float)m_CallmullCount;
				Vector3 vec;
				Vector3 HighDraw = vec.CatmullRom(m_TrailCBuffer->GetVelocityHigh(i), m_TrailCBuffer->GetVelocityHigh(i),
					m_TrailCBuffer->GetVelocityHigh(i), m_TrailCBuffer->GetVelocityHigh(i), Progress);
	
	
				Vector3 LowDraw = vec.CatmullRom(m_TrailCBuffer->GetVelocityLow(i), m_TrailCBuffer->GetVelocityLow(i),
					m_TrailCBuffer->GetVelocityLow(i), m_TrailCBuffer->GetVelocityLow(i), Progress);
				vecHigh.push_back(HighDraw);
				vecLow.push_back(LowDraw);
			}
		}
		else
		{
			for (int j = 0; j < m_CallmullCount; ++j)
			{
				float Progress = (float)j / (float)m_CallmullCount;
				Vector3 vec;
				Vector3 HighDraw = vec.CatmullRom(m_TrailCBuffer->GetVelocityHigh(i - 1), m_TrailCBuffer->GetVelocityHigh(i),
					m_TrailCBuffer->GetVelocityHigh(i + 1), m_TrailCBuffer->GetVelocityHigh(i + 2), Progress);
	
	
				Vector3 LowDraw = vec.CatmullRom(m_TrailCBuffer->GetVelocityLow(i - 1), m_TrailCBuffer->GetVelocityLow(i),
					m_TrailCBuffer->GetVelocityLow(i + 1), m_TrailCBuffer->GetVelocityLow(i + 2), Progress);
				vecHigh.push_back(HighDraw);
				vecLow.push_back(LowDraw);
			}
		}
	}
	
	for (int i = 0; i < vecLow.size(); ++i)
	{
		m_TrailCBuffer->SetVelocity(i, vecLow[i], vecHigh[i]);
	}
}

void CTornadoTrailComponent::PostUpdate(float DeltaTime)
{
	CPrimitiveComponent::PostUpdate(DeltaTime);
}

void CTornadoTrailComponent::Collision(float DeltaTime)
{
	CPrimitiveComponent::Collision(DeltaTime);
}

void CTornadoTrailComponent::Render(float DeltaTime)
{
	CPrimitiveComponent::Render(DeltaTime);

	m_TrailCBuffer->UpdateCBuffer();
	for (int i = 0; i < (int)m_vecMaterialSlot.size(); ++i)
	{
		m_vecMaterialSlot[i]->SetMaterial();
		m_State->SetState();
		m_pMesh->Render(i);
		m_State->ResetState();
		m_vecMaterialSlot[i]->ResetMaterial();
	}
}

CTornadoTrailComponent* CTornadoTrailComponent::Clone()
{
	return new CTornadoTrailComponent(*this);
}

