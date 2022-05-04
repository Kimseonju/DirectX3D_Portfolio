
#include "Wendy_AirHole.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Resource/Material.h"
#include "../PublicData.h"
#include "Resource/BoneSocket.h"
#include "Player.h"
CWendyAirHole::CWendyAirHole() :
	m_Setting(false),
	m_Sound(nullptr),
	m_Coll(false),
	m_Timer(2.8f),
	m_Effect(nullptr)
{
}

CWendyAirHole::CWendyAirHole(const CWendyAirHole& obj) : CAttackObject(obj)
{
}

CWendyAirHole::~CWendyAirHole()
{
}

void CWendyAirHole::CollisionBegin(const HitResult& result, CCollider* Collider)
{
	/*m_Sphere->Enable(false);
	m_Coll = true;
	m_Sound->Stop();
	m_Mesh->Active(false);
	m_Sphere->Active(false);*/



}

void CWendyAirHole::CollisionMiddle(const HitResult& result, CCollider* Collider)
{
	if (!m_Coll)
	{
		if (result.DestCollider->GetProfile()->Name == "Player")
		{
			Vector3 PlayerPos = result.DestObject->GetWorldPos();
			Vector3 Pos = (GetWorldPos() + (GetWorldScale() * 0.5f)) - PlayerPos;

			Vector3 MovePos = {};
			if (0 > Pos.x)
			{
				MovePos.x = -HoleSpeed * m_DeltaTime;
			}
			else if (0 < Pos.x)
			{
				MovePos.x = HoleSpeed * m_DeltaTime;
			}

			if (0 > Pos.z)
			{
				MovePos.z = -HoleSpeed * m_DeltaTime;
			}
			else if (0 < Pos.z)
			{
				MovePos.z = HoleSpeed * m_DeltaTime;
			}

			result.DestObject->AddWorldPos(MovePos);
		}
	}
	else
	{
		if (result.DestCollider->GetProfile()->Name == "Player")
		{
			
			m_pScene->GetResource()->FindSound3D("Wendy_AirHit")->Play3D(GetWorldPos());
		}
		m_Sphere->Enable(false);
	}
}

void CWendyAirHole::CollisionEnd(const HitResult& result, CCollider* Collider)
{
}

void CWendyAirHole::Start()
{
	CAttackObject::Start();
}

bool CWendyAirHole::Init()
{
	CAttackObject::Init();
	m_AttColl = CreateSceneComponent<CColliderSphere>("Sphere");
	m_Sphere->AddChild(m_AttColl);
	m_AttColl->SetWorldScale(Vector3::One);
	m_AttColl->SetCollisionProfile("MonsterAttack");
	m_AttColl->AddWorldPos(0.f, 10.f, 0.f);

	m_Box->Enable(false);
	m_Sphere->Enable(true);
	m_Sphere->SetWorldPos(Vector3::One);
	m_Sphere->SetCollisionProfile("Monster");


	m_Effect = m_pScene->SpawnObject<CWendy_AirHoleEffect>("Effect");
	m_Effect->SetWorldPos(GetWorldPos());

	SetDamage(30);
	SetDamageMax(50);

	//m_Sound = m_pScene->GetResource()->FindSound("Wendy_AirHole");
	return true;
}

void CWendyAirHole::Update(float DeltaTime)
{
	CAttackObject::Update(DeltaTime);
	m_DeltaTime = DeltaTime;
	if (!m_Setting)
	{
		m_Setting = true;
		//m_Sound->Play();
		m_Effect->SetWorldPos(GetWorldPos() + m_Sphere->GetWorldScale() * 0.5f);
	}
	m_Timer -= DeltaTime;
	if (0.1f >= m_Timer)
	{
		m_AttColl->AddWorldPos(0.f, -100.f * DeltaTime, 0.f);
	}

	if (0 >= m_Timer && !m_Coll)
	{
		m_Timer = 0.2f;
		m_Coll = true;
		m_Effect->EffectDeath();
		m_Sphere->SetCollisionProfile("MonsterAttack");

	}
	else if (m_Coll)
	{
		if (0 >= m_Timer)
		{
			this->Active(false);
		}
	}


}

void CWendyAirHole::PostUpdate(float DeltaTime)
{
	CAttackObject::PostUpdate(DeltaTime);
}

void CWendyAirHole::Collision(float DeltaTime)
{
	CAttackObject::Collision(DeltaTime);
}

void CWendyAirHole::Render(float DeltaTime)
{
	CAttackObject::Render(DeltaTime);
}

CWendyAirHole* CWendyAirHole::Clone()
{
	return new CWendyAirHole(*this);
}
