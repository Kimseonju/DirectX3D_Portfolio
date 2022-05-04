
#include "HitEffect.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Resource/Material.h"

CHitEffect::CHitEffect():
	m_Animation(nullptr)
{
}

CHitEffect::CHitEffect(const CHitEffect& obj) : CClientObject(obj)
{
	m_Billboard = (CBillboardComponent*)FindSceneComponent("Billboard");
}

CHitEffect::~CHitEffect()
{
}

void CHitEffect::Start()
{
	CClientObject::Start();
}

bool CHitEffect::Init()
{
	CClientObject::Init();
	
	m_Billboard = CreateSceneComponent<CBillboardComponent>("Billboard");

	SetRootComponent(m_Billboard);
	m_Billboard->SetBillboardEnable(true);
	
	m_Billboard->CreateAnimation3D_Tex<CAnimation3D_Tex>();
	m_Billboard->SetAnimation2DEnable(true);
	m_Animation =m_Billboard->GetAnimation3D_Tex();
	
	m_Animation->AddAnimationSequence2D("Hit_Small_01");
	m_Animation->SetFrameEndFunction(this, &CHitEffect::AnimationEnd);
	m_Billboard->SetWorldScale(2.f, 2.f, 2.f);
	m_Billboard->EnableYBillboard();
	m_Billboard->SetBillboardEnable(true);
	CMaterial* Mtrl = m_pScene->GetResource()->FindMaterial("PlayerHitEffect");
	m_Billboard->AddMaterial(Mtrl);
	return true;
}

void CHitEffect::Update(float DeltaTime)
{
	CClientObject::Update(DeltaTime);
}

void CHitEffect::PostUpdate(float DeltaTime)
{
	CClientObject::PostUpdate(DeltaTime);
}

void CHitEffect::Collision(float DeltaTime)
{
	CClientObject::Collision(DeltaTime);
}

void CHitEffect::Render(float DeltaTime)
{
	CClientObject::Render(DeltaTime);
}

CHitEffect* CHitEffect::Clone()
{
	return new CHitEffect(*this);
}

void CHitEffect::AnimationEnd(const std::string& Name)
{
	Active(false);
}
