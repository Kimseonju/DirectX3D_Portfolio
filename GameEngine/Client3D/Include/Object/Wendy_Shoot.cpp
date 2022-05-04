
#include "Wendy_Shoot.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Resource/Material.h"
#include "../PublicData.h"
#include "Resource/BoneSocket.h"
#include "Player.h"
#include "Wendy_AirHitEffect.h"

CWendyShoot::CWendyShoot() :
	m_Setting(false),
	m_Sound(nullptr),
	m_BoomSound(nullptr),
	m_Coll(false),
	m_Timer(0.f)
{
}
CWendyShoot::CWendyShoot(const CWendyShoot& obj) : CAttackObject(obj)
{
}
CWendyShoot::~CWendyShoot()
{
}

void CWendyShoot::CollisionBegin(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Name == "Player")
	{
		m_BoomSound->Play();
		m_Sphere->Enable(false);
		m_Coll = true;
		m_Sound->Stop();
		m_Mesh->Active(false);
		m_Sphere->Active(false);

		CWendyAirHitEffect* Effect = m_pScene->SpawnObject<CWendyAirHitEffect>("Effect");
		Effect->SetWorldPos(CPublicData::GetInst()->GetCurPlayer()->GetWorldPos());
		Effect->Power2();
		Effect->AddWorldPos(0.f, 0.5f, 0.f);
		Effect->HitOn();
	}
}
void CWendyShoot::CollisionMiddle(const HitResult& result, CCollider* Collider)
{
}
void CWendyShoot::CollisionEnd(const HitResult& result, CCollider* Collider)
{
}

void CWendyShoot::Start()
{
	CAttackObject::Start();
}
bool CWendyShoot::Init()
{
	CAttackObject::Init();


	SetDamage(10);
	SetDamageMax(20);

	m_Mesh->SetMesh("WendyAirShootMesh");
	m_Mesh->SetWorldScale(1.f, 1.f, 1.f);
	m_Box->Enable(false);
	m_Sphere->Enable(true);
	m_Sphere->SetCollisionProfile("MonsterAttack");
	m_Mesh->SetMaterial(0,"Wendy_AirShootMaterial");
	m_Mesh->GetMaterial(0)->SetTransparency(true);
	m_Mesh->GetMaterial(0)->SetFlowDirection(true);
	m_Mesh->AddWorldRotationX(180.f);
	m_Sound = m_pScene->GetResource()->FindSound3D("Wendy_AirShoot");
	m_BoomSound = m_pScene->GetResource()->FindSound3D("Wendy_AirShoot_Boom");
	m_pScene->GetResource()->FindMaterial("Wendy_AirShootMaterial")->SetOpacity(0.1f);
	return true;
}
void CWendyShoot::Update(float DeltaTime)
{
	CAttackObject::Update(DeltaTime);
	if (!m_Setting)
	{
		m_Timer = 10.f;
		m_Setting = true;
		m_Sound->Play();
	}
	if (!m_Coll)
		AddRelativePos(GetAxis(AXIS_Z) * ( - Sniper_BulletSpeed * 0.5f)* DeltaTime);

	m_Timer -= DeltaTime;
	if (0>= m_Timer)
	{
		this->Active(false);
	}
}
void CWendyShoot::PostUpdate(float DeltaTime)
{
	CAttackObject::PostUpdate(DeltaTime);
}
void CWendyShoot::Collision(float DeltaTime)
{
	CAttackObject::Collision(DeltaTime);
}
void CWendyShoot::Render(float DeltaTime)
{
	CAttackObject::Render(DeltaTime);
}
CWendyShoot* CWendyShoot::Clone()
{
	return new CWendyShoot(*this);
}
