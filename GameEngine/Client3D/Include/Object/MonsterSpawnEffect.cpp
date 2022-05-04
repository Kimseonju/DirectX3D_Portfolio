
#include "MonsterSpawnEffect.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Resource/Material.h"

CMonsterSpawnEffect::CMonsterSpawnEffect() : m_Scale(0.f)
{
}

CMonsterSpawnEffect::CMonsterSpawnEffect(const CMonsterSpawnEffect& obj) :
    CGameObject(obj)
{
}

CMonsterSpawnEffect::~CMonsterSpawnEffect()
{
}

void CMonsterSpawnEffect::Start()
{
    CGameObject::Start();
}

bool CMonsterSpawnEffect::Init()
{
    CGameObject::Init();



    {
        {
            m_BlackCircle = CreateSceneComponent<CBillboardComponent>("Billboard");
            SetRootComponent(m_BlackCircle);
            m_BlackCircle->AddMaterial("BlackCircle");
            m_BlackCircle->SetWorldScale(0.f, 0.f, 0.f);
            m_BlackCircle->SetBillboardEnable(false);
            m_BlackCircle->SetWorldRotationX(90.f);
        }
        {
            m_BlackWind = CreateSceneComponent<CBillboardComponent>("Billboard");
            m_BlackCircle->AddChild(m_BlackWind);
            m_BlackWind->SetBillboardEnable(false);
            m_BlackWind->CreateAnimation3D_Tex<CAnimation3D_Tex>();
            m_BlackWind->SetAnimation2DEnable(true);
            m_Animation = m_BlackWind->GetAnimation3D_Tex();
            m_Animation->AddAnimationSequence2D("Black_Circle");
            m_Animation->AddSequencePlayRate("Black_Circle", 1.f);
            m_pScene->GetResource()->CreateMaterial("BlackCircle");
            CMaterial* Mtrl = m_pScene->GetResource()->FindMaterial("BlackCircle");
            Mtrl->SetShader("BillboardShader");
            m_BlackWind->AddMaterial(Mtrl);
            m_BlackWind->SetWorldScale(m_BlackCircle->GetWorldScale());
            m_BlackWind->SetWorldRotationX(90.f);
            m_BlackWind->AddWorldPos(0.f, 0.05f, 0.f);
        }
        {
            m_BlackWind2 = CreateSceneComponent<CBillboardComponent>("Billboard");
            m_BlackCircle->AddChild(m_BlackWind2);
            m_BlackWind2->SetBillboardEnable(false);
            m_BlackWind2->CreateAnimation3D_Tex<CAnimation3D_Tex>();
            m_BlackWind2->SetAnimation2DEnable(true);
            m_Animation = m_BlackWind2->GetAnimation3D_Tex();
            m_Animation->AddAnimationSequence2D("Black_Circle");
            m_Animation->AddSequencePlayRate("Black_Circle", 0.8f);
            m_pScene->GetResource()->CreateMaterial("BlackCircle");
            CMaterial* Mtrl = m_pScene->GetResource()->FindMaterial("BlackCircle");
            Mtrl->SetShader("BillboardShader");
            m_BlackWind2->AddMaterial(Mtrl);
            m_BlackWind2->SetWorldScale(m_BlackWind->GetWorldScale() * 1.1f);
            m_BlackWind2->SetWorldRotationX(90.f);
            m_BlackWind2->SetWorldRotationY(90.f);
            m_BlackWind2->AddWorldPos(0.f, 0.1f, 0.f);
        }
        {
            m_BlackWind3 = CreateSceneComponent<CBillboardComponent>("Billboard");
            m_BlackCircle->AddChild(m_BlackWind3);
            m_BlackWind3->SetBillboardEnable(false);
            m_BlackWind3->CreateAnimation3D_Tex<CAnimation3D_Tex>();
            m_BlackWind3->SetAnimation2DEnable(true);
            m_Animation = m_BlackWind3->GetAnimation3D_Tex();
            m_Animation->AddAnimationSequence2D("Black_Circle");
            m_Animation->AddSequencePlayRate("Black_Circle", 0.6f);
            m_pScene->GetResource()->CreateMaterial("BlackCircle");
            CMaterial* Mtrl = m_pScene->GetResource()->FindMaterial("BlackCircle");
            Mtrl->SetShader("BillboardShader");
            m_BlackWind3->AddMaterial(Mtrl);
            m_BlackWind3->SetWorldScale(m_BlackWind2->GetWorldScale() * 1.2f);
            m_BlackWind3->SetWorldRotationX(90.f);
            m_BlackWind3->SetWorldRotationY(90.f);
            m_BlackWind3->AddWorldPos(0.f, 0.15f, 0.f);
        }
    }
    m_Scale = 0.f;


    return true;
}

void CMonsterSpawnEffect::Update(float DeltaTime)
{
    CGameObject::Update(DeltaTime);

    if (!m_Enable)
    {
        if (0 >= m_Scale)
        {
            this->Active(false);
        }
        else
        {
            m_Scale -= (DeltaTime * 2.5f);
            m_BlackCircle->SetWorldScale(m_Scale, m_Scale, m_Scale);
            m_BlackWind->SetWorldScale(m_BlackCircle->GetWorldScale());
            m_BlackWind2->SetWorldScale(m_BlackWind->GetWorldScale() * 1.1f);
            m_BlackWind3->SetWorldScale(m_BlackWind2->GetWorldScale() * 1.2f);
        }
    }
}

void CMonsterSpawnEffect::ManualUpdate(float DeltaTime)
{
    if (2.5f >= m_Scale)
    {
        m_Scale += (DeltaTime * 2.5f);
        if (2.5 <= m_Scale)
            m_Scale = 2.5f;

        m_BlackCircle->SetWorldScale(m_Scale, m_Scale, m_Scale);
        m_BlackWind->SetWorldScale(m_BlackCircle->GetWorldScale());
        m_BlackWind2->SetWorldScale(m_BlackWind->GetWorldScale() * 1.1f);
        m_BlackWind3->SetWorldScale(m_BlackWind2->GetWorldScale() * 1.2f);
    }
}

void CMonsterSpawnEffect::PostUpdate(float DeltaTime)
{
    CGameObject::PostUpdate(DeltaTime);
}

void CMonsterSpawnEffect::Collision(float DeltaTime)
{
    CGameObject::Collision(DeltaTime);
}

void CMonsterSpawnEffect::Render(float DeltaTime)
{
    CGameObject::Render(DeltaTime);
}

CMonsterSpawnEffect* CMonsterSpawnEffect::Clone()
{
    return new CMonsterSpawnEffect(*this);
}
