
#include "Wendy_AirHoleEffect.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Resource/Material.h"
#include "Wendy_AirHitEffect.h"
CWendy_AirHoleEffect::CWendy_AirHoleEffect() : m_Enable(true), m_Scale1(0.f), m_Scale2(0.f),m_Start(false)
{
}

CWendy_AirHoleEffect::CWendy_AirHoleEffect(const CWendy_AirHoleEffect& obj) : CGameObject(obj)
{
}

CWendy_AirHoleEffect::~CWendy_AirHoleEffect()
{
}

void CWendy_AirHoleEffect::Start()
{
    CGameObject::Start();
}

bool CWendy_AirHoleEffect::Init()
{
    CGameObject::Init();
    {
        m_BlackCircle = CreateSceneComponent<CBillboardComponent>("Billboard");

        SetRootComponent(m_BlackCircle);

        m_BlackCircle->SetAnimation2DEnable(false);
        m_BlackCircle->EnableYBillboard();
        m_BlackCircle->SetBillboardEnable(false);
        m_BlackCircle->AddRelativeRotationX(90.f);
        m_pScene->GetResource()->FindMaterial("AirHole_Wind")->SetShader("BillboardShader");
        m_BlackCircle->AddMaterial(m_pScene->GetResource()->FindMaterial("AirHole_Wind"));
        m_BlackCircle->SetWorldScale(2.5f, 2.5f, 2.5f);
    }
    {
        m_BlackWind = CreateSceneComponent<CBillboardComponent>("Billboard");

        m_BlackCircle->AddChild(m_BlackWind);

        m_BlackWind->SetAnimation2DEnable(false);
        m_BlackWind->EnableYBillboard();
        m_BlackWind->SetBillboardEnable(false);
        m_BlackWind->AddRelativeRotationX(90.f);
        m_pScene->GetResource()->FindMaterial("AirHole_Circle_1")->SetShader("BillboardShader");
        m_BlackWind->AddMaterial(m_pScene->GetResource()->FindMaterial("AirHole_Circle_1"));
        m_BlackWind->SetWorldPos(m_BlackWind->GetWorldPos());
        m_BlackWind->AddWorldPos(0.f, 0.1f, 0.f);
        m_BlackWind->SetWorldScale(3.5f, 3.5f, 3.5f);
    }

    m_pScene->GetResource()->FindMaterial("AirHole_Wind")->SetOpacity(1.f);
    m_pScene->GetResource()->FindMaterial("AirHole_Circle_1")->SetOpacity(1.f);
    return true;
}

void CWendy_AirHoleEffect::Update(float DeltaTime)
{
    CGameObject::Update(DeltaTime);

    if (!m_Start && m_Enable)
    {
        m_Scale1 += DeltaTime * 5.f;
        if (2.5f <= m_Scale1)
            m_Scale1 = 2.5f;
        m_BlackCircle->SetWorldScale(m_Scale1, m_Scale1, m_Scale1);

        m_Scale2 += DeltaTime * 7.f;
        if (3.5f <= m_Scale2)
            m_Scale2 = 3.5f;
        m_BlackWind->SetWorldScale(m_Scale2, m_Scale2, m_Scale2);

        if (3.5f <= m_Scale2 && 2.5f <= m_Scale1)
        {
            m_Start = true;
        }
    }

    if (!m_Enable && m_Start)
    {
        CWendyAirHitEffect* Effect = m_pScene->SpawnObject<CWendyAirHitEffect>("Effect");
        Effect->SetWorldPos(m_BlackCircle->GetWorldPos());
        Effect->Power2();

        m_Start = false;
    }

    if (!m_Enable && !m_Start)
    {
        m_BlackCircle->GetMaterial(0)->AddOpacity(-DeltaTime * 2.f);
        m_BlackWind->GetMaterial(0)->AddOpacity(-DeltaTime * 2.f);

        if (0.f >= m_BlackCircle->GetMaterial(0)->GetOpacity())
        {
            this->Active(false);
        }
    }

    m_BlackCircle->AddWorldRotation(m_BlackCircle->GetAxis(AXIS_Z) * -500.f * DeltaTime);
    m_BlackWind->AddWorldRotation(m_BlackCircle->GetAxis(AXIS_Z) * -500.f * DeltaTime);
}

void CWendy_AirHoleEffect::PostUpdate(float DeltaTime)
{
    CGameObject::PostUpdate(DeltaTime);
}

void CWendy_AirHoleEffect::Collision(float DeltaTime)
{
    CGameObject::Collision(DeltaTime);
}

void CWendy_AirHoleEffect::Render(float DeltaTime)
{
    CGameObject::Render(DeltaTime);
}

CWendy_AirHoleEffect* CWendy_AirHoleEffect::Clone()
{
    return new CWendy_AirHoleEffect(*this);
}
