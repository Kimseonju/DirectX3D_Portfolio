
#include "Wendy_AirStar.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Resource/Material.h"
#include "../PublicData.h"
#include "Resource/BoneSocket.h"
#include "Player.h"
#include "Wendy_AirHitEffect.h"
CWendyAirStar::CWendyAirStar() :
	m_Setting(false),
	m_SoundBorn(nullptr),
	m_SoundBoom(nullptr),
	m_SoundShoot(nullptr),
	m_Check(false),
	m_BoomSound(nullptr),
	m_Coll(false),
	m_Timer(1.f),
	m_LeftTime(4.f)

{
}
CWendyAirStar::CWendyAirStar(const CWendyAirStar& obj) : CAttackObject(obj)
{
}
CWendyAirStar::~CWendyAirStar()
{
}

void CWendyAirStar::CollisionBegin(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Name == "Player")
	{
		m_SoundShoot->Stop();
		m_SoundBoom->Play();

		CWendyAirHitEffect* Effect = m_pScene->SpawnObject<CWendyAirHitEffect>("Effect");
		Effect->SetWorldPos(m_Mesh->GetWorldPos());
		Effect->HitOn();
		m_pScene->GetResource()->FindSound3D("Wendy_AirHit")->Play3D(m_Mesh->GetWorldPos());
		m_Timer = 1.0f;
		m_Coll = true;
		m_Sphere->Enable(false);
		m_Mesh->Enable(false);
	}
}
void CWendyAirStar::CollisionMiddle(const HitResult& result, CCollider* Collider)
{
}
void CWendyAirStar::CollisionEnd(const HitResult& result, CCollider* Collider)
{
}

void CWendyAirStar::Start()
{
	CAttackObject::Start();
}
bool CWendyAirStar::Init()
{
	CAttackObject::Init();

	SetDamage(10);
	SetDamageMax(20);

	m_Mesh->SetMesh("AirStarMesh");
	m_Mesh->SetWorldScale(5.f, 5.f, 5.f);
	m_Mesh->AddWorldRotation(90.f, 0.f, 0.f);
	m_Mesh->SetInheritRotX(false);
	m_Mesh->SetInheritRotY(false);
	m_Mesh->SetInheritRotZ(false);
	m_Box->Enable(false);
	m_Sphere->Enable(true);
	m_Box->SetCollisionProfile("MonsterAttack");
	m_Sphere->SetCollisionProfile("MonsterAttack");


	m_SoundBorn = m_pScene->GetResource()->FindSound3D("AirStarBorn");
	m_SoundBoom = m_pScene->GetResource()->FindSound3D("AirStarBoom");
	m_SoundShoot = m_pScene->GetResource()->FindSound3D("AirStarShoot");

	m_SoundBorn->Play3D(GetWorldPos());
	//m_Mesh->LookAtObject(CPublicData::GetInst()->m_CurPlayer);
	//m_Mesh->LookAtObjectActive(true);

	{
		m_Trail = CreateSceneComponent<CTrailComponent>("TrailComponent");
		CMaterial* Mtrl = m_pScene->GetResource()->FindMaterial("AirStarTrail_G");
		m_Trail->AddMaterial(Mtrl);
		m_Trail->SetSize(0.01f);
		m_Trail->SetTrailLength(0.05f);
		m_Trail->Enable(true);
		m_Mesh->AddChild(m_Trail);
		m_Trail->SetInheritPosZ(true);
		m_Trail->SetInheritRotX(true);
		m_Trail->SetInheritRotY(true);
		m_Trail->SetInheritRotZ(true);
		m_Trail->SetWorldPos(m_Mesh->GetWorldPos());
		m_Trail->AddWorldPos(1.f, 0.f, 0.f);
	}

	{
		m_Trail2 = CreateSceneComponent<CTrailComponent>("TrailComponent");
		CMaterial* Mtrl = m_pScene->GetResource()->FindMaterial("AirStarTrail_W");
		m_Trail2->AddMaterial(Mtrl);
		m_Trail2->SetSize(0.01f);
		m_Trail2->SetTrailLength(0.05f);
		m_Trail2->Enable(true);
		m_Mesh->AddChild(m_Trail2);
		m_Trail2->SetInheritPosZ(true);
		m_Trail2->SetInheritRotX(true);
		m_Trail2->SetInheritRotY(true);
		m_Trail2->SetInheritRotZ(true);
		m_Trail2->SetWorldPos(m_Mesh->GetWorldPos());
		m_Trail2->AddWorldPos(-1.f, 0.f, 0.f);
	}

	{
		m_AirEffect = CreateSceneComponent<CBillboardComponent>("BillboardComponent");
		m_Mesh->AddChild(m_AirEffect);
		m_AirEffect->AddMaterial("Tornado_00");
		m_AirEffect->SetWorldRotationX(90.f);
		m_AirEffect->SetBillboardEnable(false);
		m_AirEffect->SetWorldScale(Vector3::One * 2.f);
	}
	return true;
}
void CWendyAirStar::Update(float DeltaTime)
{
	CAttackObject::Update(DeltaTime);
	
	if (!m_Coll)
	{
		m_LeftTime -= DeltaTime;
		if (0 >= m_LeftTime)
		{
			m_SoundShoot->Stop();
			m_SoundBoom->Play();

			m_Timer = 1.0f;
			m_Coll = true;
			CWendyAirHitEffect* Effect = m_pScene->SpawnObject<CWendyAirHitEffect>("Effect");
			Effect->SetWorldPos(m_Mesh->GetWorldPos());
			m_Sphere->Enable(false);
			m_Mesh->Enable(false);
		}
		if (!m_Setting)
		{
			m_Root->LookAtObject(CPublicData::GetInst()->m_CurPlayer);
			m_Root->LookAtObjectActive(true);

			SetDamage(10);
			SetDamageMax(40);
			m_Setting = true;
			m_Sphere->SetRadius(0.5f);
		}
		//LookAtObjectActive(false);

		m_Root->AddRelativeRotationY(-5.f);
		if (0.5 >= m_Timer && !m_Check)
		{
			m_Check = true;
			m_SoundShoot->Play();
		}
		if (0 >= m_Timer)
		{
			if (m_Root->GetWorldPos().y >= (CPublicData::GetInst()->m_CurPlayer->GetWorldPos().y) + (CPublicData::GetInst()->m_CurPlayer->GetWorldScale().y * 0.5f))
			{
				m_Root->AddRelativePos(GetAxis(AXIS_Y) * (-AirStarSpeed * 0.1f) * DeltaTime);
			}
			m_Root->AddRelativePos(GetAxis(AXIS_Z) * -AirStarSpeed * DeltaTime);
		}
		else
		{
			m_Timer -= DeltaTime;
		}

		m_Mesh->AddRelativeRotationY(1000.f * DeltaTime);
	}
	else
	{
		m_Timer -= DeltaTime;
		if (0 >= m_Timer)
		{
			this->Active(false);
		}
	}
	m_AirEffect->AddRelativeRotationY(1000.f * DeltaTime);
	m_Mesh->AddRelativeRotationY(1000.f * DeltaTime);
}
void CWendyAirStar::PostUpdate(float DeltaTime)
{
	CAttackObject::PostUpdate(DeltaTime);
}
void CWendyAirStar::Collision(float DeltaTime)
{
	CAttackObject::Collision(DeltaTime);
}
void CWendyAirStar::Render(float DeltaTime)
{
	CAttackObject::Render(DeltaTime);
}
CWendyAirStar* CWendyAirStar::Clone()
{
	return new CWendyAirStar(*this);
}
