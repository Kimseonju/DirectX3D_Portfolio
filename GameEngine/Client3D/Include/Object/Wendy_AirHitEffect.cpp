#include "Wendy_AirHitEffect.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Resource/Material.h"
#include "../PublicData.h"
CWendyAirHitEffect::CWendyAirHitEffect() : m_Timer(1.f), m_Scale(0.f), m_Mtrl(nullptr), m_PowerX2(false), m_HitAniOn(false)
{
}

CWendyAirHitEffect::CWendyAirHitEffect(const CWendyAirHitEffect& obj) : CClientObject(obj)
{
	m_Billboard = (CBillboardComponent*)FindSceneComponent("Billboard");
}

CWendyAirHitEffect::~CWendyAirHitEffect()
{
}

void CWendyAirHitEffect::Start()
{
	CClientObject::Start();
}

bool CWendyAirHitEffect::Init()
{
	CClientObject::Init();

	m_Billboard = CreateSceneComponent<CBillboardComponent>("Billboard");
	m_Billboard2 = CreateSceneComponent<CBillboardComponent>("Billboard");

	SetRootComponent(m_Billboard);
	m_Billboard->AddChild(m_Billboard2);

	m_Billboard->CreateAnimation3D_Tex<CAnimation3D_Tex>();
	m_Billboard->SetAnimation2DEnable(true);
	m_Billboard->EnableYBillboard();
	m_Billboard->SetBillboardEnable(false);
	m_Billboard->AddRelativeRotationX(90.f);

	m_Billboard2->CreateAnimation3D_Tex<CAnimation3D_Tex>();
	m_Billboard2->SetAnimation2DEnable(true);
	m_Billboard2->SetBillboardEnable(true);


	m_Animation = m_Billboard->GetAnimation3D_Tex();
	m_Animation->AddAnimationSequence2D("Wendy_AirBall");
	m_Animation->AddSequencePlayRate("Wendy_AirBall", 1.f);

	m_Animation2 = m_Billboard2->GetAnimation3D_Tex();
	m_Animation2->AddAnimationSequence2D("Wendy_AirBall");
	m_Animation2->AddSequencePlayRate("Wendy_AirBall", 1.f);

	m_pScene->GetResource()->CreateMaterial("AirHit");
	m_Mtrl = m_pScene->GetResource()->FindMaterial("AirHit");
	m_Mtrl->SetShader("BillboardShader");



	m_Billboard->AddMaterial(m_Mtrl);
	m_Billboard->SetWorldScale(1.f, 1.f, 1.f);

	m_Billboard2->AddMaterial(m_Mtrl);
	m_Billboard2->SetWorldScale(1.f, 1.f, 1.f);

	return true;
}

void CWendyAirHitEffect::Update(float DeltaTime)
{
	CClientObject::Update(DeltaTime);
	if (m_HitAniOn)
	{
		m_HitAniOn = false;
		m_Billboard3 = CreateSceneComponent<CBillboardComponent>("Billboard");
		m_Billboard->AddChild(m_Billboard3);
		m_Billboard3->CreateAnimation3D_Tex<CAnimation3D_Tex>();
		m_Billboard3->SetAnimation2DEnable(true);
		m_Billboard3->SetBillboardEnable(true);
		m_Animation3 = m_Billboard3->GetAnimation3D_Tex();
		m_Animation3->AddAnimationSequence2D("Air_HitEffect", false);
		m_Animation3->AddSequencePlayRate("Air_HitEffect", 1.f);
		m_Billboard3->AddMaterial(m_Mtrl);
		Vector3 PlayerPos = CPublicData::GetInst()->GetCurPlayer()->GetWorldPos() + CPublicData::GetInst()->GetCurPlayer()->GetWorldScale() * 0.5f;
		PlayerPos = PlayerPos - GetWorldPos();

		//m_Billboard3->SetWorldPos(CPublicData::GetInst()->GetCurPlayer()->GetWorldPos() + CPublicData::GetInst()->GetCurPlayer()->GetWorldScale() * 0.5f);
		m_Billboard3->SetWorldPos(GetWorldPos());
		m_Billboard3->AddWorldPos((PlayerPos * 0.5f));
		m_Billboard3->SetWorldScale(2.5f, 2.5f, 2.5f);
	}

	if (0.f >= m_Timer)
	{
		this->Active(false);
	}
	else
	{
		m_Timer -= DeltaTime * 2.f;
		m_Scale += DeltaTime * 10.f;
	}

	m_Mtrl->SetOpacity(m_Timer);
	if (m_PowerX2)
	{
		m_Billboard->SetWorldScale(m_Scale * 2.f, m_Scale * 2.f, m_Scale * 2.f);
		m_Billboard2->SetWorldScale(m_Scale * 2.f, m_Scale * 2.f, m_Scale * 2.f);
	}
	else
	{
		m_Billboard->SetWorldScale(m_Scale, m_Scale, m_Scale);
		m_Billboard2->SetWorldScale(m_Scale, m_Scale, m_Scale);
	}


	/*if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_Mtrl->AddOpacity(DeltaTime);
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_Mtrl->AddOpacity(-DeltaTime);
	}*/
	
}

void CWendyAirHitEffect::PostUpdate(float DeltaTime)
{
	CClientObject::PostUpdate(DeltaTime);
}

void CWendyAirHitEffect::Collision(float DeltaTime)
{
	CClientObject::Collision(DeltaTime);
}

void CWendyAirHitEffect::Render(float DeltaTime)
{
	CClientObject::Render(DeltaTime);
}

CWendyAirHitEffect* CWendyAirHitEffect::Clone()
{
	return new CWendyAirHitEffect(*this);
}
