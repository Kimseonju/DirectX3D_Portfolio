
#include "KnifeEffect.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Resource/Material.h"

CKnifeEffect::CKnifeEffect() : m_Setting(false), m_Animation(nullptr), m_AxeAtt(false),
m_WendyAtt(false)
{
}

CKnifeEffect::CKnifeEffect(const CKnifeEffect& obj) : CGameObject(obj)
{
}

CKnifeEffect::~CKnifeEffect()
{
}

void CKnifeEffect::AnimationEnd(const std::string& Name)
{
	m_Enable = false;

	if ("KnifeEffect" == Name)
	{
		this->Active(false);
	}
}

void CKnifeEffect::Start()
{
	CGameObject::Start();
}

bool CKnifeEffect::Init()
{
	CGameObject::Init();
	m_Effect = CreateSceneComponent<CBillboardComponent>("Billboard");

	SetRootComponent(m_Effect);
	m_Effect->SetBillboardEnable(true);
	m_Effect->EnableYBillboard();

	m_Effect->CreateAnimation3D_Tex<CAnimation3D_Tex>();
	m_Effect->SetAnimation2DEnable(true);


	m_Animation = m_Effect->GetAnimation3D_Tex();
	m_Animation->AddAnimationSequence2D("KnifeEffect",false);
	m_Animation->AddSequencePlayRate("KnifeEffect", 3.f);
	m_Animation->SetFrameEndFunction(this, &CKnifeEffect::AnimationEnd);
	m_pScene->GetResource()->CreateMaterial("KnifeMateral");
	CMaterial* Mtrl = m_pScene->GetResource()->FindMaterial("KnifeMateral");
	Mtrl->SetShader("BillboardShader");

	m_Effect->AddMaterial(Mtrl);
	m_Effect->SetWorldScale(512.f / 100.f, 85.33333333f / 100.f, 1.f);

	return true;
}

void CKnifeEffect::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	if (!m_Setting)
	{
		m_Setting = true;
		m_Effect->SetWorldScale(m_Effect->GetWorldScale() * 0.5f);
		if (m_WendyAtt)
			m_Effect->GetMaterial(0)->SetBaseColor(0.1f, 0.8f, 0.6f, 0.4f);
		else if (m_AxeAtt)
			m_Effect->GetMaterial(0)->SetBaseColor(0.3f, 0.6f, 0.9f, 0.6f);
		else
			m_Effect->GetMaterial(0)->SetBaseColor(0.8f, 0.8f, 0.8f, 0.8f);
		m_Effect->AddWorldPos(0.f, 0.7f, 0.f);
	}
	else
	{

	}
	
	if (!m_Enable)
	{

	}
}

void CKnifeEffect::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CKnifeEffect::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CKnifeEffect::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CKnifeEffect* CKnifeEffect::Clone()
{
	return new CKnifeEffect(*this);
}
