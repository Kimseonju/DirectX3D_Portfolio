
#include "ExplosionEffect.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Resource/Material.h"

CExplosionEffect::CExplosionEffect() : m_Enable(true), m_Setting(false), m_Type(ExplosionEffectType::Type_1),m_Animation(nullptr),
m_EffectScaleMult(1.f)
{
}

CExplosionEffect::CExplosionEffect(const CExplosionEffect& obj) : CGameObject(obj)
{
}

CExplosionEffect::~CExplosionEffect()
{
}

void CExplosionEffect::AnimationEnd(const std::string& Name)
{
	m_Enable = false;

	if ("Explosion_01" == Name)
	{
		this->Active(false);
	}
}

void CExplosionEffect::Start()
{
	CGameObject::Start();
}

bool CExplosionEffect::Init()
{
	CGameObject::Init();
	m_Effect = CreateSceneComponent<CBillboardComponent>("Billboard");
	SetRootComponent(m_Effect);
	m_Effect->SetBillboardEnable(true);
	m_Effect->EnableYBillboard();
	m_Effect->CreateAnimation3D_Tex<CAnimation3D_Tex>();
	m_Effect->SetAnimation2DEnable(true);
	m_Animation = m_Effect->GetAnimation3D_Tex();
	m_Animation->AddAnimationSequence2D("Explosion_01",false);
	m_Animation->AddAnimationSequence2D("Explosion_02", false);
	m_Animation->AddAnimationSequence2D("Explosion_03", false);
	m_Animation->AddSequencePlayRate("Explosion_01", 0.01f);
	m_Animation->AddSequencePlayRate("Explosion_02", 0.01f);
	m_Animation->AddSequencePlayRate("Explosion_03", 0.01f);
	m_pScene->GetResource()->CreateMaterial("Explosion");
	m_Animation->SetFrameEndFunction(this, &CExplosionEffect::AnimationEnd);
	CMaterial* Mtrl = m_pScene->GetResource()->FindMaterial("Explosion");
	Mtrl->SetShader("BillboardShader");
	m_Effect->AddMaterial(Mtrl);
	m_Effect->GetMaterial(0)->SetOpacity(1.f);
	
	return true;
}

void CExplosionEffect::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	if (!m_Setting)
	{
		m_Setting = true;

		switch (m_Type)
		{
		case ExplosionEffectType::Type_1:
		{
			m_Animation->ChangeAnimation("Explosion_01");
			m_Effect->SetWorldScale(18.285f / 100.f, 42.666f / 100.f,1.f);
			m_Effect->SetWorldScale(m_Effect->GetWorldScale() * m_EffectScaleMult);
		}
		break;
		case ExplosionEffectType::Type_2:
		{
			m_Animation->ChangeAnimation("Explosion_02");
			m_Effect->SetWorldScale(102.4f / 100.f, 170.66f / 100.f, 1.f);
			m_Effect->SetWorldScale(m_Effect->GetWorldScale() * m_EffectScaleMult);
		}
		break;
		case ExplosionEffectType::Type_3:
		{
			m_Animation->ChangeAnimation("Explosion_03");
			m_Effect->SetWorldScale(85.333f / 100.f, 128.f / 100.f, 1.f);
			m_Effect->SetWorldScale(m_Effect->GetWorldScale() * m_EffectScaleMult);
		}
		break;
		}
	}

	if (!m_Enable)
	{
		switch (m_Type)
		{
		case ExplosionEffectType::Type_1:
		{

		}
		break;
		case ExplosionEffectType::Type_2:
		{
			m_Effect->GetMaterial(0)->AddOpacity(-DeltaTime * 2.f);
			if (0 >= m_Effect->GetMaterial(0)->GetOpacity())
				this->Active(false);
		}
		break;
		case ExplosionEffectType::Type_3:
		{
			m_Effect->GetMaterial(0)->AddOpacity(-DeltaTime * 2.f);
			if (0 >= m_Effect->GetMaterial(0)->GetOpacity())
				this->Active(false);
		}
		break;
		}
	}
}

void CExplosionEffect::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CExplosionEffect::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CExplosionEffect::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CExplosionEffect* CExplosionEffect::Clone()
{
	return new CExplosionEffect(*this);
}
