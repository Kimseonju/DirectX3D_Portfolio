#include "Wendy_AirBallEffect.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Resource/Material.h"

CWendyAirBallEffect::CWendyAirBallEffect() : m_Owner(nullptr), m_OffSet(Vector3::Zero)
{
}

CWendyAirBallEffect::CWendyAirBallEffect(const CWendyAirBallEffect& obj) : CClientObject(obj)
{
	m_Billboard = (CBillboardComponent*)FindSceneComponent("Billboard");
}

CWendyAirBallEffect::~CWendyAirBallEffect()
{
}

void CWendyAirBallEffect::Start()
{
	CClientObject::Start();
}

bool CWendyAirBallEffect::Init()
{
	CClientObject::Init();

	m_Billboard = CreateSceneComponent<CBillboardComponent>("Billboard");

	SetRootComponent(m_Billboard);
	m_Billboard->SetBillboardEnable(true);

	m_Billboard->CreateAnimation3D_Tex<CAnimation3D_Tex>();
	m_Billboard->SetAnimation2DEnable(true);


	m_Animation = m_Billboard->GetAnimation3D_Tex();
	m_Animation->AddAnimationSequence2D("Wendy_AirBall");
	m_Animation->AddSequencePlayRate("Wendy_AirBall", 1.f);

	m_pScene->GetResource()->CreateMaterial("AirBall");
	CMaterial* Mtrl = m_pScene->GetResource()->FindMaterial("AirBall");
	Mtrl->SetShader("BillboardShader");

	m_Billboard->AddMaterial(Mtrl);
	m_Billboard->SetWorldScale(1.f, 1.f, 1.f);
	return true;
}

void CWendyAirBallEffect::Update(float DeltaTime)
{
	CClientObject::Update(DeltaTime);

	if (m_Owner)
	{
		SetWorldPos(m_Owner->GetWorldPos());
	}
	
	AddWorldPos(m_OffSet);
}

void CWendyAirBallEffect::PostUpdate(float DeltaTime)
{
	CClientObject::PostUpdate(DeltaTime);
}

void CWendyAirBallEffect::Collision(float DeltaTime)
{
	CClientObject::Collision(DeltaTime);
}

void CWendyAirBallEffect::Render(float DeltaTime)
{
	CClientObject::Render(DeltaTime);
}

CWendyAirBallEffect* CWendyAirBallEffect::Clone()
{
	return new CWendyAirBallEffect(*this);
}
