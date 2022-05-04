
#include "TrailComponent.h"
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
CTrailComponent::CTrailComponent() :
	m_TrailShader(nullptr),
	m_TrailUpdate(true)
{
	m_PrimitiveType = PrimitiveComponent_Type::Primitive3D;
	m_ClassType = Component_Class_Type::Billboard;
	m_3DType = RT3D_Particle;

	SetTransformState(Transform_State::None);
	m_Time = 0.f;
	m_Length = 0.005f;
	m_Size = 100.f;
	m_LocalSwordLow = Vector3(0.f, -0.5f, 0.f);
	m_LocalSwordHigh = Vector3(0.f, 0.5f, 0.f);
	m_VecSize = 6;
}

CTrailComponent::CTrailComponent(const CTrailComponent& com) :
	CPrimitiveComponent(com)
{
	m_TrailCBuffer = com.m_TrailCBuffer->Clone();
	m_pMesh = com.m_pMesh;
	m_State = com.m_State;
	m_RenderShader = com.m_RenderShader;

}

CTrailComponent::~CTrailComponent()
{
	SAFE_DELETE(m_TrailCBuffer);
}

void CTrailComponent::SetTrailUpdate(bool Update)
{
	m_TrailUpdate = Update;
	if (m_TrailUpdate)
	{
		Matrix mat = GetWorldMatrix();
		SetPositionAllList(mat);
	}
}

void CTrailComponent::SetPositionAllList(const Matrix& mat)
{
	m_vecMatrix.clear();
	for (int i = 0; i < m_VecSize; ++i)
		m_vecMatrix.push_front(mat);
}

void CTrailComponent::Start()
{
	CPrimitiveComponent::Start();

}

bool CTrailComponent::Init()
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

void CTrailComponent::Update(float DeltaTime)
{
	CPrimitiveComponent::Update(DeltaTime);
	m_Time += DeltaTime;

	if (m_Time > 0.005f)
	{
		m_Time -= 0.005f;
		if (m_TrailUpdate)
		{
			Matrix mat = GetWorldMatrix();
			m_vecMatrix.push_front(mat);
			m_Prevmat = mat;
		}	
		else
		{
			m_vecMatrix.push_front(m_Prevmat);
		}
	}

	m_TrailCBuffer->SetScale(m_Size);

	auto iter = m_vecMatrix.begin();
	auto iterEnd = m_vecMatrix.end();

	int iCount = 0;

	for (; iter != iterEnd; ++iter)
	{
		if (iCount >= m_VecSize)
		{
			iCount = m_VecSize;
			// 10 ~ 마지막은 범위를 벗어나므로..
			m_vecMatrix.erase(iter, iterEnd);
			break;
		}
		Matrix Pos = (*iter);
		m_LocalSwordLow =m_LocalSwordLow.TransformCoord(Pos);
		m_LocalSwordHigh =m_LocalSwordHigh.TransformCoord(Pos);



		m_TrailCBuffer->SetVelocity(iCount, m_LocalSwordLow, m_LocalSwordHigh);

		m_LocalSwordLow = Vector3(m_Size, 0.f, 0.f);
		m_LocalSwordHigh = Vector3(-m_Size, 0.f, 0.f);
		++iCount;
	}
	std::vector<Vector3> vecHigh;
	std::vector<Vector3> vecLow;
	int CallmullCount=5;
	for (int i = 0; i < m_VecSize; ++i)
	{
		if (i == 0)
		{
			for (int j = 0; j < CallmullCount; ++j)
			{
				float Progress = (float)j / (float)CallmullCount;
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
			for (int j = 0; j < CallmullCount; ++j)
			{
				float Progress = (float)j / (float)CallmullCount;
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
			for (int j = 0; j < CallmullCount; ++j)
			{
				float Progress = (float)j / (float)CallmullCount;
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
			for (int j = 0; j < CallmullCount; ++j)
			{
				float Progress = (float)j / (float)CallmullCount;
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

void CTrailComponent::PostUpdate(float DeltaTime)
{
	CPrimitiveComponent::PostUpdate(DeltaTime);
}

void CTrailComponent::Collision(float DeltaTime)
{
	CPrimitiveComponent::Collision(DeltaTime);
}

void CTrailComponent::Render(float DeltaTime)
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

CTrailComponent* CTrailComponent::Clone()
{
	return new CTrailComponent(*this);
}

