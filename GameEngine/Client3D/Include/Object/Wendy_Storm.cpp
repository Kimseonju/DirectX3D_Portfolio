
#include "Wendy_Storm.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Resource/Material.h"
#include "../PublicData.h"
#include "Resource/BoneSocket.h"
#include "Player.h"

CWendyStorm::CWendyStorm() :
	m_Setting(false),
	m_Coll(false),
	m_Timer(3.5f),
	m_Tornado(false),
	m_Point(nullptr)
{
}
CWendyStorm::CWendyStorm(const CWendyStorm& obj) : CAttackObject(obj)
{
}
CWendyStorm::~CWendyStorm()
{
	if (m_Effect)
	{
		m_Effect->Active(false);
	}
	m_Effect = nullptr;
}

void CWendyStorm::CollisionBegin(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Name == "Player")
	{
		m_pScene->GetResource()->FindSound3D("Wendy_AirHit")->Play3D(GetWorldPos());
	}
}
void CWendyStorm::CollisionMiddle(const HitResult& result, CCollider* Collider)
{
	
}
void CWendyStorm::CollisionEnd(const HitResult& result, CCollider* Collider)
{
}

void CWendyStorm::Start()
{
	CAttackObject::Start();
}
bool CWendyStorm::Init()
{
	CAttackObject::Init();

	SetDamage(10);
	SetDamageMax(20);

	m_Box->Enable(false);
	m_Sphere->Enable(true);
	m_Sphere->SetWorldPos(Vector3::One);
	m_Sphere->SetCollisionProfile("MonsterAttack");
	m_Point = m_pScene->SpawnObject<CGameObject>("Point");
	SetWorldRotation(Vector3::Zero);


	m_Effect = m_pScene->SpawnObject<CTornadoEffect>("obj");
	m_Effect->SetWorldPos(GetWorldPos());

	return true;
}
void CWendyStorm::Update(float DeltaTime)
{
	CAttackObject::Update(DeltaTime);
	m_DeltaTime = DeltaTime;
	if (!m_Setting)
	{
		m_Setting = true;
		if (m_Tornado)
		{
			m_Timer = 20.f;
			LookAtObject(m_Point);
			LookAtObjectActive(true);
		}
		m_Sphere->SetRadius(1.5f);
		m_Sphere->SetWorldScale(1.5f, 3.f, 1.5f);
		m_Sphere->AddWorldPos(-0.5f, -1.f, 0.f);
	}
	m_Timer -= DeltaTime;

	if (m_Tornado)
	{
		AddRelativePos(GetAxis(AXIS_X) * 6.f * -DeltaTime);
		AddRelativeRotationY(100 * DeltaTime);
	}
	else
	{
	

		SetWorldPos(m_Point->GetWorldPos() - (m_Point->GetWorldScale() * 0.5f));
		AddWorldPos(GetAxis(AXIS_X) * -0.f);
		AddWorldPos(GetAxis(AXIS_Y) * 0.f);
		AddWorldPos(GetAxis(AXIS_Z) * -0.5f);
	}

	AddRelativePos(GetAxis(AXIS_Z) * DeltaTime);


	if (m_Effect)
	{
		m_Effect->SetWorldPos(m_Sphere->GetWorldPos());
		m_Effect->AddWorldPos(0.f, 0.7f, 0.f);
	}


	if (0 >= m_Timer)
	{
		this->Active(false);
	}
}
void CWendyStorm::PostUpdate(float DeltaTime)
{
	CAttackObject::PostUpdate(DeltaTime);
}
void CWendyStorm::Collision(float DeltaTime)
{
	CAttackObject::Collision(DeltaTime);
}
void CWendyStorm::Render(float DeltaTime)
{
	CAttackObject::Render(DeltaTime);
}
CWendyStorm* CWendyStorm::Clone()
{
	return new CWendyStorm(*this);
}
