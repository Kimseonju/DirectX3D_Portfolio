#include "Wendy_AirBullet.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Resource/Material.h"
#include "../PublicData.h"
#include "Resource/BoneSocket.h"
#include "Player.h"
#include "Wendy_AirHitEffect.h"

CWendyAirBullet::CWendyAirBullet() :
	m_Setting(false),
	m_Sound(nullptr),
	m_SoundBoom(nullptr),
	m_SoundHit(nullptr),
	m_Coll(false),
	m_DeltaTime(0.f),
	m_Timer(0.5f),
	m_EffectDeath(false)
{
}

CWendyAirBullet::CWendyAirBullet(const CWendyAirBullet& obj) : CAttackObject(obj)
{
}

CWendyAirBullet::~CWendyAirBullet()
{
	m_Effect->SetOwner(nullptr);
	m_Effect->Active(false);
	m_Effect2->Active(false);
	m_Effect3->Active(false);
	m_Effect4->Active(false);
	m_Effect5->Active(false);
}

void CWendyAirBullet::CollisionBegin(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Name == "Player")
	{
		m_EffectDeath = true;
		m_Sound->Stop();
		m_SoundBoom->Play3D(m_Effect->GetWorldPos());
		m_SoundHit->Play3D(m_Effect->GetWorldPos());
		CWendyAirHitEffect* Effect = m_pScene->SpawnObject<CWendyAirHitEffect>("Effect");
		Effect->SetWorldPos(m_Effect->GetWorldPos());
		Effect->HitOn();
		this->Active(false);
	}
}

void CWendyAirBullet::CollisionMiddle(const HitResult& result, CCollider* Collider)
{
}

void CWendyAirBullet::CollisionEnd(const HitResult& result, CCollider* Collider)
{
}

void CWendyAirBullet::Start()
{
	CAttackObject::Start();
}

bool CWendyAirBullet::Init()
{
	CAttackObject::Init();


	SetDamage(10);
	SetDamageMax(20);


	m_Box->Enable(false);
	m_Sphere->Enable(true);
	m_Sphere->SetWorldPos(Vector3::One);
	m_Sphere->SetRadius(0.25f);
	m_Sphere->SetCollisionProfile("MonsterAttack");

	m_Effect = m_pScene->SpawnObject<CWendyAirBallEffect>("Effect");
	m_Effect2 = m_pScene->SpawnObject<CWendyAirBallEffect>("Effect");
	m_Effect3 = m_pScene->SpawnObject<CWendyAirBallEffect>("Effect");
	m_Effect4 = m_pScene->SpawnObject<CWendyAirBallEffect>("Effect");
	m_Effect5 = m_pScene->SpawnObject<CWendyAirBallEffect>("Effect");

	m_Effect->SetOwner(this);
	m_Effect->SetOffSet(Vector3(1.12234008f, 1.12234008f, 0.951897502f));

	m_Effect2->SetWorldScale(m_Effect->GetWorldScale() * 0.7f);
	m_Effect2->SetOwner(m_Effect);
	m_Effect2->SetOffSet(Vector3(0.f, 0.1f, 0.f));
	m_Effect2->SetAnimationRate(1.25f);

	m_Effect3->SetWorldScale(m_Effect->GetWorldScale() * 0.5f);
	m_Effect3->SetOwner(m_Effect);
	m_Effect3->SetOffSet(Vector3(0.f, 0.2f, 0.f));
	m_Effect3->SetAnimationRate(1.5f);

	m_Effect4->SetWorldScale(m_Effect->GetWorldScale() * 0.7f);
	m_Effect4->SetOwner(m_Effect);
	m_Effect4->SetOffSet(Vector3(0.f, -0.1f, 0.f));
	m_Effect4->SetAnimationRate(1.25f);
	
	m_Effect5->SetWorldScale(m_Effect->GetWorldScale() * 0.5f);
	m_Effect5->SetOwner(m_Effect);
	m_Effect5->SetOffSet(Vector3(0.f, -0.2f, 0.f));
	m_Effect5->SetAnimationRate(1.5f);


	m_Sound = m_pScene->GetResource()->FindSound3D("Wendy_BulletShoot");
	m_SoundBoom = m_pScene->GetResource()->FindSound3D("Wendy_AirBoom");
	m_SoundHit = m_pScene->GetResource()->FindSound3D("Wendy_AirHit");

	return true;
}

void CWendyAirBullet::Update(float DeltaTime)
{
	CAttackObject::Update(DeltaTime);
	m_DeltaTime = DeltaTime;
	if (!m_Setting)
	{
		m_Sound->Play3D(GetWorldPos());
		m_Point = CPublicData::GetInst()->GetCurPlayer()->GetWorldPos() - (CPublicData::GetInst()->GetCurPlayer()->GetWorldScale() * 0.5f);
		m_Point = m_Point - GetWorldPos();
		m_Setting = true;
	}
	m_Timer -= DeltaTime;
	if (0 > m_Timer)
	{
		AddWorldPos(0.f, m_Timer * DeltaTime * 20.f, 0.f);
	}
	else
	{
		AddWorldPos(0.f, m_Timer * DeltaTime * 20.f, 0.f);
	}
	AddWorldPos(m_Point * DeltaTime);
	
}

void CWendyAirBullet::PostUpdate(float DeltaTime)
{
	CAttackObject::PostUpdate(DeltaTime);

	if (1 >= GetWorldPos().y && !m_Coll)
	{
		m_Coll = true;
		if (!m_EffectDeath)
		{
			CWendyAirHitEffect* Effect = m_pScene->SpawnObject<CWendyAirHitEffect>("Effect");
			Effect->SetWorldPos(m_Effect->GetWorldPos());
			m_SoundBoom->Play3D(m_Effect->GetWorldPos());
		}
	}
	if (-2 >= GetWorldPos().y)
	{
		this->Active(false);
	}
}

void CWendyAirBullet::Collision(float DeltaTime)
{
	CAttackObject::Collision(DeltaTime);
}

void CWendyAirBullet::Render(float DeltaTime)
{
	CAttackObject::Render(DeltaTime);
}

CWendyAirBullet* CWendyAirBullet::Clone()
{
	return new CWendyAirBullet(*this);
}
