
#include "BillboardComponent.h"
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

CBillboardComponent::CBillboardComponent()
{
	m_PrimitiveType = PrimitiveComponent_Type::Primitive3D;
	m_ClassType = Component_Class_Type::Billboard;
	m_3DType = RT3D_Particle;

	SetTransformState(Transform_State::None);
	m_bBillboardEnable = false;
	m_YRotEnable = false;
}

CBillboardComponent::CBillboardComponent(const CBillboardComponent& com) :
	CPrimitiveComponent(com)
{
	m_pMesh = com.m_pMesh;

	if (com.m_Animation)
	{
		m_Animation = com.m_Animation->Clone();
		m_Animation->Release();
	}
}

CBillboardComponent::~CBillboardComponent()
{
}

void CBillboardComponent::Start()
{
	CPrimitiveComponent::Start();

	if (m_Animation)
		m_Animation->Start();
}

bool CBillboardComponent::Init()
{
	if (!CPrimitiveComponent::Init())
		return false;

	m_pMesh = m_pScene->GetResource()->FindMesh("BillboardMesh");

	m_OriginDir = Vector3(0.f, 0.f, -1.f);
	
	return true;
}

void CBillboardComponent::Update(float DeltaTime)
{
	CPrimitiveComponent::Update(DeltaTime);
	if (m_bBillboardEnable)
	{
		CCamera* Camera = m_pScene->GetCameraManager()->GetCurrentCamera();

		if (m_YRotEnable)
		{
			LookAtYAxis(Camera->GetWorldPos(), m_OriginDir);
		}

		else
		{
			LookAt(Camera->GetWorldPos(), m_OriginDir);
		}
	}

	if (m_Animation)
		m_Animation->Update(DeltaTime);
}

void CBillboardComponent::PostUpdate(float DeltaTime)
{
	CPrimitiveComponent::PostUpdate(DeltaTime);
}

void CBillboardComponent::Collision(float DeltaTime)
{
	CPrimitiveComponent::Collision(DeltaTime);
}

void CBillboardComponent::Render(float DeltaTime)
{
	CPrimitiveComponent::Render(DeltaTime);
	for (int i = 0; i < (int)m_vecMaterialSlot.size(); ++i)
	{
		m_vecMaterialSlot[i]->SetMaterial();

		if (m_Animation)
			m_Animation->SetShader();

		m_pMesh->Render(i);

		if (m_Animation)
			m_Animation->ResetShader();

		m_vecMaterialSlot[i]->ResetMaterial();
	}
}

CBillboardComponent* CBillboardComponent::Clone()
{
	return new CBillboardComponent(*this);
}
