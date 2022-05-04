
#include "StaticMeshComponent.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "Transform.h"
#include "../Resource/Material.h"
CStaticMeshComponent::CStaticMeshComponent()
{
	m_PrimitiveType = PrimitiveComponent_Type::Primitive3D;
	m_ClassType = Component_Class_Type::StaticMesh;
	m_3DType = RT3D_Default;

	SetTransformState(Transform_State::None);
}

CStaticMeshComponent::CStaticMeshComponent(const CStaticMeshComponent& com) :
	CPrimitiveComponent(com)
{
	if(com.m_pMesh)
		SetMesh(com.m_pMesh);
	SetTransformState(Transform_State::None);
	
}

CStaticMeshComponent::~CStaticMeshComponent()
{
}

CStaticMesh* CStaticMeshComponent::GetStaticMesh()
{
	return m_pMesh;
}

CMesh* CStaticMeshComponent::GetMesh() const
{
	return (CMesh*)m_pMesh.Get();
}

void CStaticMeshComponent::SetMesh(CMesh* pMesh)
{
	m_pMesh = (CStaticMesh*)pMesh;

	Vector3 Min = m_pMesh->GetMin();
	Vector3 Max = m_pMesh->GetMax();

	m_pTransform->SetMeshSize(Max - Min);

	m_vecMaterialSlot.clear();

	const std::vector<CSharedPtr<CMaterial>>* pMaterialSlots =
		m_pMesh->GetMaterialSlots();

	auto    iter = pMaterialSlots->begin();
	auto    iterEnd = pMaterialSlots->end();

	for (; iter != iterEnd; ++iter)
	{
		CMaterial* pClone = (*iter)->Clone();

		pClone->SetScene(m_pScene);
		m_vecMaterialSlot.push_back(pClone);

		SAFE_RELEASE(pClone);
	}
}

void CStaticMeshComponent::SetMesh(const std::string& Name)
{
	m_pMesh = (CStaticMesh*)m_pScene->GetResource()->FindMesh(Name);

	Vector3 Min = m_pMesh->GetMin();
	Vector3 Max = m_pMesh->GetMax();

	m_pTransform->SetMeshSize(Max - Min);

	m_vecMaterialSlot.clear();

	const std::vector<CSharedPtr<CMaterial>>* pMaterialSlots = m_pMesh->GetMaterialSlots();

	auto    iter = pMaterialSlots->begin();
	auto    iterEnd = pMaterialSlots->end();

	for (; iter != iterEnd; ++iter)
	{
		CMaterial* pClone = (*iter)->Clone();

		pClone->SetScene(m_pScene);
		m_vecMaterialSlot.push_back(pClone);

		SAFE_RELEASE(pClone);
	}
}

void CStaticMeshComponent::Start()
{
	CPrimitiveComponent::Start();
}

bool CStaticMeshComponent::Init()
{
	if (!CPrimitiveComponent::Init())
		return false;
	return true;
}

void CStaticMeshComponent::Update(float DeltaTime)
{
	CPrimitiveComponent::Update(DeltaTime);
}

void CStaticMeshComponent::PostUpdate(float DeltaTime)
{
	CPrimitiveComponent::PostUpdate(DeltaTime);
}

void CStaticMeshComponent::Collision(float DeltaTime)
{
	CPrimitiveComponent::Collision(DeltaTime);
}

void CStaticMeshComponent::Render(float DeltaTime)
{
	CPrimitiveComponent::Render(DeltaTime);

	for (int i = 0; i < (int)m_vecMaterialSlot.size(); ++i)
	{
		m_vecMaterialSlot[i]->SetMaterial();
		if (m_NotLightShader)
			m_NotLightShader->SetShader();
		m_pMesh->Render(i);
		m_vecMaterialSlot[i]->ResetMaterial();
	}
}

CStaticMeshComponent* CStaticMeshComponent::Clone()
{
	return new CStaticMeshComponent(*this);
}

void CStaticMeshComponent::RenderShadow(float DeltaTime)
{
	CPrimitiveComponent::RenderShadow(DeltaTime);

	for (int i = 0; i < (int)m_vecMaterialSlot.size(); ++i)
	{
		m_vecMaterialSlot[i]->SetShadowMaterial();
		m_pMesh->Render(i);

		m_vecMaterialSlot[i]->ResetShadowMaterial();
	}
}

void CStaticMeshComponent::SetNotLight()
{
	m_NotLightShader = CShaderManager::GetInst()->FindShader("NotLightShader");
}

void CStaticMeshComponent::Save(FILE* pFile)
{
	CPrimitiveComponent::Save(pFile);
	std::string str = m_pMesh->GetName();

	int Length = (int)strlen(str.c_str());
	fwrite(&Length, sizeof(int), 1, pFile);
	fwrite(str.c_str(), sizeof(char), Length, pFile);
}

void CStaticMeshComponent::Load(FILE* pFile)
{
	CPrimitiveComponent::Load(pFile);
	int Length = -1;
	char	Name[256] = {};
	fread(&Length, sizeof(int), 1, pFile);
	fread(Name, sizeof(char), Length, pFile);
	std::vector<CSharedPtr<CMaterial>> vecMaterialSlot = m_vecMaterialSlot;
	SetMesh(Name);
	m_vecMaterialSlot = vecMaterialSlot;
	SetTransformState(Transform_State::None);
}
