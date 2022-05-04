
#include "SkyComponent.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "Transform.h"
#include "../Resource/Material.h"

CSkyComponent::CSkyComponent()
{
	m_PrimitiveType = PrimitiveComponent_Type::Primitive3D;
	m_ClassType = Component_Class_Type::Sky;
	m_3DType = RT3D_Default;

	SetTransformState(Transform_State::None);
}

CSkyComponent::CSkyComponent(const CSkyComponent& com) :
	CStaticMeshComponent(com)
{
	SetMesh(com.m_pMesh);

}

CSkyComponent::~CSkyComponent()
{
}

CStaticMesh* CSkyComponent::GetStaticMesh()
{
	return m_pMesh;
}

CMesh* CSkyComponent::GetMesh() const
{
	return (CMesh*)m_pMesh.Get();
}

void CSkyComponent::SetMesh(CMesh* pMesh)
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

void CSkyComponent::SetMesh(const std::string& Name)
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

void CSkyComponent::SetSkyTextureFullPath(const std::string& Name, const TCHAR* FullPath)
{
	GetMaterial(0)->SetTextureFullPath(0, Name, FullPath);
	GetMaterial(0)->SetTextureRegister(Name, 20);
	GetMaterial(0)->SetTextureLink(Name, Texture_Link::CustomTexture);
}


void CSkyComponent::Start()
{
	CPrimitiveComponent::Start();
}

bool CSkyComponent::Init()
{
	if (!CPrimitiveComponent::Init())
		return false;

	SetMesh("SpherePos");
	AddMaterial("DefaultSky");
	SetRelativeScale(100000.f, 100000.f, 100000.f);

	//CreateMaterial("DefaultSky");
	//
	//CMaterial* SkyMtrl = FindMaterial("DefaultSky");
	//
	//SkyMtrl->SetShader("SkyShader");
	//SkyMtrl->AddTexture("DefaultSky", TEXT("Sky/Sky.dds"));
	//SkyMtrl->SetTextureRegister("DefaultSky", 20);
	//SkyMtrl->SetTextureLink("DefaultSky", Texture_Link::CustomTexture);
	return true;
}

void CSkyComponent::Update(float DeltaTime)
{
	CPrimitiveComponent::Update(DeltaTime);
	if ("Sky" == m_pOwner->GetName())
	{
		m_pScene->SetSkyObject(m_pOwner);
		m_pScene->SetSkyMesh(this);
	}
}

void CSkyComponent::PostUpdate(float DeltaTime)
{
	CPrimitiveComponent::PostUpdate(DeltaTime);
}

void CSkyComponent::Collision(float DeltaTime)
{
	CPrimitiveComponent::Collision(DeltaTime);
}

void CSkyComponent::Render(float DeltaTime)
{
	CPrimitiveComponent::Render(DeltaTime);

	for (int i = 0; i < (int)m_vecMaterialSlot.size(); ++i)
	{
		m_vecMaterialSlot[i]->SetMaterial();

		m_pMesh->Render(i);

		m_vecMaterialSlot[i]->ResetMaterial();
	}
}

CSkyComponent* CSkyComponent::Clone()
{
	return new CSkyComponent(*this);
}

void CSkyComponent::RenderShadow(float DeltaTime)
{
	CPrimitiveComponent::RenderShadow(DeltaTime);

	for (int i = 0; i < (int)m_vecMaterialSlot.size(); ++i)
	{
		m_vecMaterialSlot[i]->SetShadowMaterial();

		m_pMesh->Render(i);

		m_vecMaterialSlot[i]->ResetShadowMaterial();
	}
}

void CSkyComponent::Save(FILE* pFile)
{
	CPrimitiveComponent::Save(pFile);
	std::string str = m_pMesh->GetName();

	int Length = (int)strlen(str.c_str());
	fwrite(&Length, sizeof(int), 1, pFile);
	fwrite(str.c_str(), sizeof(char), Length, pFile);
}

void CSkyComponent::Load(FILE* pFile)
{
	CPrimitiveComponent::Load(pFile);
	int Length = -1;
	char	Name[256] = {};
	fread(&Length, sizeof(int), 1, pFile);
	fread(Name, sizeof(char), Length, pFile);
	std::vector<CSharedPtr<CMaterial>> vecMaterialSlot = m_vecMaterialSlot;
	SetMesh(Name);
	m_vecMaterialSlot = vecMaterialSlot;
}
