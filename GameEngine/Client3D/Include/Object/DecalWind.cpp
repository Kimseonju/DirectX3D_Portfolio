
#include "DecalWind.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Resource/Material.h"

CDecalWind::CDecalWind() : m_Enable(true)
{
}

CDecalWind::CDecalWind(const CDecalWind& obj) :
    CGameObject(obj)
{
    m_Decal = (CDecalComponent*)FindSceneComponent("Decal");
}

CDecalWind::~CDecalWind()
{
}

void CDecalWind::Start()
{
    CGameObject::Start();
}

bool CDecalWind::Init()
{
    CGameObject::Init();

    m_Decal = CreateSceneComponent<CDecalComponent>("Decal");

    SetRootComponent(m_Decal);

    CMaterial* Material = m_Decal->GetMaterial(0);

    Material->SetTexture("DefaultDecal", "BloodDecal", TEXT("Monster/Decal/Windcir_01.png"));
    Material->SetTexture("DefaultDecalNormal", "BloodDecalNormal", TEXT("Monster/Decal/Windcir_01_NRM.png"));

    m_Decal->SetFadeInTime(1.f);
    m_Decal->SetDuration(1000.f);
    m_Decal->SetFadeLoop(true);
    m_Decal->SetFadeOutTime(1.f);

    return true;
}

void CDecalWind::Update(float DeltaTime)
{
    CGameObject::Update(DeltaTime);

    m_Decal->AddRelativeRotationY(180.f* 2.f * DeltaTime);

    if (!m_Enable)
    {
        m_Decal->SetDuration(0.f);
    }
}

void CDecalWind::PostUpdate(float DeltaTime)
{
    CGameObject::PostUpdate(DeltaTime);
}

void CDecalWind::Collision(float DeltaTime)
{
    CGameObject::Collision(DeltaTime);
}

void CDecalWind::Render(float DeltaTime)
{
    CGameObject::Render(DeltaTime);
}

CDecalWind* CDecalWind::Clone()
{
    return new CDecalWind(*this);
}
