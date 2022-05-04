
#include "TestParticle.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "../PublicData.h"

CTestParticle::CTestParticle() :
	m_ChildFire(false),
	m_ChildFireTime(0.f),
	m_ChildFireTimeMax(0.2f),
	m_ChildFireDurationTime(0.f),
	m_ChildFireDurationTimeMax(5.f)
{
}

CTestParticle::CTestParticle(const CTestParticle& obj) :
	CGameObject(obj)
{
	m_Particle = (CParticleSystemComponent*)FindSceneComponent("Particle");
}

CTestParticle::~CTestParticle()
{
}

void CTestParticle::Start()
{
	CGameObject::Start();
}

bool CTestParticle::Init()
{
	CGameObject::Init();

	m_Particle = CreateSceneComponent<CParticleSystemComponent>("Particle");

	m_Particle->SetParticle("DustParticle");
	m_Particle->SetSpawnTime(0.01f);
	m_Particle->SetGravityEnable(false);
	SetRootComponent(m_Particle);
	LookAtObject(CPublicData::GetInst()->GetCurPlayer());
	LookAtObjectActive(true);

	return true;
}

void CTestParticle::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	m_Particle->SetWorldPos(GetWorldPos());
	m_Particle->SetWorldRotation(GetWorldRotation());
}

void CTestParticle::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CTestParticle::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CTestParticle::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CTestParticle* CTestParticle::Clone()
{
	return new CTestParticle(*this);
}

void CTestParticle::Animation2DNotify(const std::string& Name)
{
}
