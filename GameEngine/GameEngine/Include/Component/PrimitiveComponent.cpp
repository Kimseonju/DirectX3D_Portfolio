
#include "PrimitiveComponent.h"
#include "../Render/RenderManager.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "Transform.h"

CPrimitiveComponent::CPrimitiveComponent()
{
    m_SceneComponentType = SceneComponent_Type::Primitive;
    m_PrimitiveType = PrimitiveComponent_Type::Primitive3D;

    m_2DType = RT2D_None;
    m_3DType = RT3D_None;

    m_pTransform->SetDefaultZ(0.3f);

    m_DistortionEnable = false;
    m_BloomEnable = false;
}

CPrimitiveComponent::CPrimitiveComponent(const CPrimitiveComponent& com)    :
    CSceneComponent(com)
{
    m_PrimitiveType = com.m_PrimitiveType;
    m_2DType = com.m_2DType;
    m_3DType = com.m_3DType;
    m_vecMaterialSlot = com.m_vecMaterialSlot;
    m_DistortionEnable = com.m_DistortionEnable;
    m_BloomEnable = com.m_BloomEnable;
}

CPrimitiveComponent::~CPrimitiveComponent()
{
}

void CPrimitiveComponent::SetAllColor(float Color)
{
    size_t Size = m_vecMaterialSlot.size();
    for (size_t i = 0; i < Size; ++i)
    {
        m_vecMaterialSlot[i]->SetBaseColor(Color, Color, Color, 1.f);
    }
}

void CPrimitiveComponent::SetAllColor(const Vector3& Color)
{
	size_t Size = m_vecMaterialSlot.size();
	for (size_t i = 0; i < Size; ++i)
	{
		m_vecMaterialSlot[i]->SetBaseColor(Color.x, Color.y, Color.z, 1.f);
	}
}

void CPrimitiveComponent::SetAllEmissiveColor(const Vector3& Color)
{
	size_t Size = m_vecMaterialSlot.size();
	for (size_t i = 0; i < Size; ++i)
	{
		m_vecMaterialSlot[i]->SetEmissiveColor(Color.x, Color.y, Color.z, 1.f);
	}
}

void CPrimitiveComponent::SetEmissiveColor(const Vector3& Color)
{
	size_t Size = m_vecMaterialSlot.size();
	for (size_t i = 0; i < Size; ++i)
	{
		m_vecMaterialSlot[i]->SetEmissiveColor(Color.x, Color.y, Color.z, 1.f);
	}
}

void CPrimitiveComponent::SetAllOpacity(float Opacity)
{
	size_t Size = m_vecMaterialSlot.size();
	for (size_t i = 0; i < Size; ++i)
	{
		m_vecMaterialSlot[i]->SetOpacity(Opacity);
	}
}

void CPrimitiveComponent::SetAllTransparency(bool Enable, bool Check)
{
	size_t Size = m_vecMaterialSlot.size();
	for (size_t i = 0; i < Size; ++i)
	{
		m_vecMaterialSlot[i]->SetTransparency(Enable, Check);
	}
}

void CPrimitiveComponent::SetAllBumpEnable(bool Enable)
{
	size_t Size = m_vecMaterialSlot.size();
	for (size_t i = 0; i < Size; ++i)
	{
		m_vecMaterialSlot[i]->SetBumpEnable(Enable);
	}
}

void CPrimitiveComponent::AddChild(CSceneComponent* Child, const std::string& SocketName)
{
    CSceneComponent::AddChild(Child, SocketName);
}

void CPrimitiveComponent::SetMaterial(int SlotIndex, CMaterial* pMaterial)
{
    m_vecMaterialSlot[SlotIndex] = pMaterial;
}

void CPrimitiveComponent::SetMaterial(int SlotIndex, const std::string& Name)
{
    m_vecMaterialSlot[SlotIndex] = m_pScene->GetResource()->FindMaterial(Name);
}

void CPrimitiveComponent::AddMaterial(CMaterial* pMaterial)
{
    m_vecMaterialSlot.push_back(pMaterial);
}

void CPrimitiveComponent::AddMaterial(const std::string& Name)
{
    CMaterial* pMaterial = m_pScene->GetResource()->FindMaterial(Name);
    m_vecMaterialSlot.push_back(pMaterial);
}

CMesh* CPrimitiveComponent::GetMesh() const
{
    return nullptr;
}

void CPrimitiveComponent::SetMesh(CMesh* pMesh)
{
}

void CPrimitiveComponent::SetMesh(const std::string& Name)
{
}

void CPrimitiveComponent::Start()
{
    CSceneComponent::Start();
}

bool CPrimitiveComponent::Init()
{
    if (!CSceneComponent::Init())
        return false;

    return true;
}

void CPrimitiveComponent::Update(float DeltaTime)
{
    CSceneComponent::Update(DeltaTime);
}

void CPrimitiveComponent::PostTransformUpdate(float DeltaTime)
{
    CSceneComponent::PostTransformUpdate(DeltaTime);
}

void CPrimitiveComponent::PostUpdate(float DeltaTime)
{
    CSceneComponent::PostUpdate(DeltaTime);
}

void CPrimitiveComponent::Collision(float DeltaTime)
{
    CSceneComponent::Collision(DeltaTime);
}

void CPrimitiveComponent::PrevRender(float DeltaTime)
{
    CSceneComponent::PrevRender(DeltaTime);

    CRenderManager::GetInst()->AddPrimitiveComponent(this);
}

void CPrimitiveComponent::Render(float DeltaTime)
{
    CSceneComponent::Render(DeltaTime);
}

void CPrimitiveComponent::RenderDebug(float DeltaTime)
{
    CSceneComponent::RenderDebug(DeltaTime);
}

CPrimitiveComponent* CPrimitiveComponent::Clone()
{
    return new CPrimitiveComponent(*this);
}

void CPrimitiveComponent::RenderShadow(float DeltaTime)
{
    m_pTransform->SetShadowTransform();
}

void CPrimitiveComponent::Save(FILE* pFile)
{
	CSceneComponent::Save(pFile);
	fwrite(&m_PrimitiveType, sizeof(PrimitiveComponent_Type), 1, pFile);
    fwrite(&m_2DType, sizeof(Render_Type_2D), 1, pFile);
    fwrite(&m_3DType, sizeof(Render_Type_3D), 1, pFile);

	size_t Size = m_vecMaterialSlot.size();
    fwrite(&Size, sizeof(size_t), 1, pFile);
    for (size_t i = 0; i < Size; ++i)
    {
        m_vecMaterialSlot[i]->Save(pFile);
    }
}

void CPrimitiveComponent::Load(FILE* pFile)
{
	CSceneComponent::Load(pFile);
	fread(&m_PrimitiveType, sizeof(PrimitiveComponent_Type), 1, pFile);
	fread(&m_2DType, sizeof(Render_Type_2D), 1, pFile);
	fread(&m_3DType, sizeof(Render_Type_3D), 1, pFile);
	size_t Size = -1;

    m_vecMaterialSlot.clear();
	fread(&Size, sizeof(size_t), 1, pFile);
	for (size_t i = 0; i < Size; ++i)
	{
		CMaterial* mtrl= new CMaterial;
        mtrl->Init();
        mtrl->Load(pFile);
        m_vecMaterialSlot.push_back(mtrl);
        SAFE_RELEASE(mtrl);
	}
}
