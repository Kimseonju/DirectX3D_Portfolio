#include "Wendy.h"
#include "Scene/Scene.h"
#include "../PublicData.h"
#include "Player.h"
#include "Wendy_Shoot.h"
#include "Wendy_AirHole.h"
#include "Wendy_AirStar.h"
#include "Wendy_AirBullet.h"
#include "Wendy_Storm.h"
#include "Axe_Weapon.h"
#include "Wendy_Brandish.h"
#include "../StageManager.h"

CWendy::CWendy()
{
	m_Animation = nullptr;
	m_ParperBurnOn = false;
	m_RandomCount = 0;
	m_DeltaTime = 0.f;
	m_PlayerDir = 0.f;
	m_PointDir = 0.f;

	SetClientClassType(ClientClassType::Wendy);

	m_State = Wendy_State::Spawn;
	m_AttackState = Wendy_AttackState::None;
}
CWendy::CWendy(const CWendy& obj) :
	CMonster(obj)
{
	m_Animation = (CWendyAnimation*)m_Mesh->GetAnimation();
}
CWendy::~CWendy()
{
}


void CWendy::Start()
{
	CMonster::Start();

	CreateFSM();
}
bool CWendy::Init()
{
	CMonster::Init();
	SetHp(10000);

	m_Mesh->SetInheritRotY(true);
	m_Mesh->SetMesh("WendyMesh");
	m_Mesh->SetWorldScale(1.f, 1.f, 1.f);
	m_Mesh->SetRelativeRotationX(-90.f);
	m_Animation = new CWendyAnimation;
	m_Mesh->SetAnimation(m_Animation);
	m_Animation->SetScene(m_pScene);
	m_Animation->Init();
	m_Animation->m_Owner = this;
	m_Animation->SetAnimationEndFunc(&CWendy::EndAnimation);
	m_Animation->SetRootBoneIndex("Bip001 Pelvis");

	for (int i = 0; i < m_Mesh->GetMaterialCount(); ++i)
	{
		m_Mesh->GetMaterial(i)->SetReceiveDecal(false);
	}
	{
		m_PaperBurn0 = CreateObjectComponent<CPaperBurnComponent>("PaperBurn0");
		m_PaperBurn0->SetBurnTime(3.f);
		m_PaperBurn0->SetEndFunction<CWendy>(this, &CWendy::PaperBurnEndFunction);
		m_PaperBurn0->SetTargetMaterial(m_Mesh->GetMaterial(0));
		m_PaperBurn0->SetOutLineColorUNorm(0.2f, 0.2f, 0.2f);
		m_PaperBurn0->SetCenterLineColor(255, 69, 0);
		m_PaperBurn0->SetInLineColorUNorm(0.7f, 0.7f, 0.7f);

		m_PaperBurn1 = CreateObjectComponent<CPaperBurnComponent>("PaperBurn1");
		m_PaperBurn1->SetBurnTime(3.f);
		m_PaperBurn1->SetTargetMaterial(m_Mesh->GetMaterial(1));
		m_PaperBurn1->SetOutLineColorUNorm(0.2f, 0.2f, 0.2f);
		m_PaperBurn1->SetCenterLineColor(255, 69, 0);
		m_PaperBurn1->SetInLineColorUNorm(0.7f, 0.7f, 0.7f);

		m_PaperBurn2 = CreateObjectComponent<CPaperBurnComponent>("PaperBurn1");
		m_PaperBurn2->SetBurnTime(3.f);
		m_PaperBurn2->SetTargetMaterial(m_Mesh->GetMaterial(2));
		m_PaperBurn2->SetOutLineColorUNorm(0.2f, 0.2f, 0.2f);
		m_PaperBurn2->SetCenterLineColor(255, 69, 0);
		m_PaperBurn2->SetInLineColorUNorm(0.7f, 0.7f, 0.7f);

		m_PaperBurn3 = CreateObjectComponent<CPaperBurnComponent>("PaperBurn1");
		m_PaperBurn3->SetBurnTime(3.f);
		m_PaperBurn3->SetTargetMaterial(m_Mesh->GetMaterial(3));
		m_PaperBurn3->SetOutLineColorUNorm(0.2f, 0.2f, 0.2f);
		m_PaperBurn3->SetCenterLineColor(255, 69, 0);
		m_PaperBurn3->SetInLineColorUNorm(0.7f, 0.7f, 0.7f);

		m_PaperBurn4 = CreateObjectComponent<CPaperBurnComponent>("PaperBurn1");
		m_PaperBurn4->SetBurnTime(3.f);
		m_PaperBurn4->SetTargetMaterial(m_Mesh->GetMaterial(4));
		m_PaperBurn4->SetOutLineColorUNorm(0.2f, 0.2f, 0.2f);
		m_PaperBurn4->SetCenterLineColor(255, 69, 0);
		m_PaperBurn4->SetInLineColorUNorm(0.7f, 0.7f, 0.7f);

		m_PaperBurn5 = CreateObjectComponent<CPaperBurnComponent>("PaperBurn1");
		m_PaperBurn5->SetBurnTime(3.f);
		m_PaperBurn5->SetTargetMaterial(m_Mesh->GetMaterial(5));
		m_PaperBurn5->SetOutLineColorUNorm(0.2f, 0.2f, 0.2f);
		m_PaperBurn5->SetCenterLineColor(255, 69, 0);
		m_PaperBurn5->SetInLineColorUNorm(0.7f, 0.7f, 0.7f);

		m_PaperBurn6 = CreateObjectComponent<CPaperBurnComponent>("PaperBurn1");
		m_PaperBurn6->SetBurnTime(3.f);
		m_PaperBurn6->SetTargetMaterial(m_Mesh->GetMaterial(6));
		m_PaperBurn6->SetOutLineColorUNorm(0.2f, 0.2f, 0.2f);
		m_PaperBurn6->SetCenterLineColor(255, 69, 0);
		m_PaperBurn6->SetInLineColorUNorm(0.7f, 0.7f, 0.7f);
	}
	return true;
}
void CWendy::Update(float DeltaTime)
{
	DeltaTime /**= CStageManager::GetInst()->GetWorldSpeed()*/;
	CMonster::Update(DeltaTime);
	m_DeltaTime = DeltaTime;
	if (false == m_Setting)
	{
		m_Setting = true;
		m_Body->Enable(true);

		m_Body->SetWorldScale(0.5f, 1.f, 0.5f);
		m_MapBody->SetWorldScale(0.5f, 1.f, 0.5f);
	}
	
	m_FSM.Update();
	LookObject(false);
}
void CWendy::PostUpdate(float DeltaTime)
{
	DeltaTime *= CStageManager::GetInst()->GetWorldSpeed();
	CMonster::PostUpdate(DeltaTime);

	if (CPublicData::GetInst()->GetCurPlayer())
	{
		m_PlayerDir = CPublicData::GetInst()->DistanceToPlayer(Vector3(GetWorldPos().x, 0.f, GetWorldPos().z));
		SetWorldPos(GetWorldPos().x, CPublicData::GetInst()->GetCurPlayer()->GetWorldPos().y + 0.5f, GetWorldPos().z);
	}
}
void CWendy::Collision(float DeltaTime)
{
	CMonster::Collision(DeltaTime);
}
void CWendy::Render(float DeltaTime)
{
	CMonster::Render(DeltaTime);
}

void CWendy::AnimationNotify(const std::string& Name)
{
	if (Name == "CameraShake")
	{
		m_pScene->GetCameraManager()->GetCurrentCamera()->StartShake(0.005f, 0.005f, 1.f);
		if (m_Effect)
		{
			m_Effect->Active(false);
		}
		m_Effect = nullptr;
	}
	if (Name == "StormStart")
	{
		if (!m_Effect && m_State == Wendy_State::Spawn)
		{
			m_Effect = m_pScene->SpawnObject<CTornadoEffect>("obj");
			m_Effect->SetWorldPos(m_Mesh->GetWorldPos());
		}
	}
	if (Name == "BrandishFirst")
	{
		CWendyBrandish* Obj = m_pScene->SpawnObject<CWendyBrandish>("Brandish");
		Obj->SetWendy(this);
		Obj->FirstAttack(true);
	}
	if (Name == "BrandishSecond")
	{
		CWendyBrandish* Obj = m_pScene->SpawnObject<CWendyBrandish>("Brandish");
		Obj->SetWendy(this);
		Obj->FirstAttack(false);
	}
	if (Name == "StormEnd")
	{
		if (m_Effect)
		{
			m_Effect->Active(false);
		}
		m_Effect = nullptr;
	}
	if(Name == "PlayerSearch_Start")
	{
		LookObject();
	}
	if (Name == "PlayerSearch_End")
	{
		LookObject(false);
	}
	if (Name == "ShootAir")
	{
		CWendyShoot* Obj = m_pScene->SpawnObject<CWendyShoot>("obj");
		Obj->SetWorldPos(GetWorldPos());
		Obj->SetWorldRotation(GetWorldRotation());
	}
	if (Name == "ShootHole")
	{
		CWendyAirHole* Obj = m_pScene->SpawnObject<CWendyAirHole>("obj");
		Obj->SetWorldPos(GetWorldPos());
		Obj->SetWorldRotation(GetWorldRotation());
		Obj->AddRelativePos(GetAxis(AXIS_Z) * -1.5f);
	}
	if (Name == "StartStorm")
	{
		CWendyStorm* Obj = m_pScene->SpawnObject<CWendyStorm>("obj");
		Obj->SetWorldPos(m_Mesh->GetWorldPos());
		Obj->SetObject(this);
	}

	if (Name == "LongAttack1")
	{
		switch (m_AttackState)
		{
		case Wendy_AttackState::AirStar:
		{
			CWendyAirStar* Obj = m_pScene->SpawnObject<CWendyAirStar>("obj");
			Obj->SetWorldPos(GetWorldPos().x - 1.f, GetWorldPos().y + 2.f, GetWorldPos().z + 1.f);
		}
		break;
		case Wendy_AttackState::Tornado:
		{
		}
		break;
		}
	}
	if (Name == "LongAttack2")
	{
		switch (m_AttackState)
		{
		case Wendy_AttackState::Storm:
		{
		}
		break;
		case Wendy_AttackState::AirBullet:
		{
			{
				CWendyAirBullet* Obj = m_pScene->SpawnObject<CWendyAirBullet>("obj");
				Obj->SetWorldPos(GetWorldPos());
				Obj->SetWorldRotation(GetWorldRotation());
				Obj->SetWorldPos(GetWorldPos().x + 1.f, GetWorldPos().y + 1.f, GetWorldPos().z + 1.f);
			}
			{
				CWendyAirBullet* Obj = m_pScene->SpawnObject<CWendyAirBullet>("obj");
				Obj->SetWorldPos(GetWorldPos());
				Obj->SetWorldRotation(GetWorldRotation());
				Obj->SetWorldPos(GetWorldPos().x - 1.f, GetWorldPos().y + 1.f, GetWorldPos().z + 1.f);
			}
		}
		break;
		case Wendy_AttackState::AirStar:
		{
			CWendyAirStar* Obj = m_pScene->SpawnObject<CWendyAirStar>("obj");
			Obj->SetWorldPos(GetWorldPos().x, GetWorldPos().y + 2.f, GetWorldPos().z + 1.f);
		}
		break;
		case Wendy_AttackState::Tornado:
		{
			m_pScene->GetResource()->FindSound3D("Wendy_Tornado")->Play3D(GetWorldPos());
			Vector3 Pos = GetWorldPos() - (GetWorldScale() * 0.5f);
			{
				CWendyStorm* Obj = m_pScene->SpawnObject<CWendyStorm>("obj");

				Obj->SetWorldPos(Pos);
				Obj->SetPoint(Pos);
				Obj->AddWorldPos(-1.f, 0.f, 0.f);
				Obj->IsTornado();
			}
			{
				CWendyStorm* Obj = m_pScene->SpawnObject<CWendyStorm>("obj");

				Obj->SetWorldPos(Pos);
				Obj->SetPoint(Pos);
				Obj->AddWorldPos(1.f, 0.f, 0.f);
				Obj->IsTornado();
			}
			{
				CWendyStorm* Obj = m_pScene->SpawnObject<CWendyStorm>("obj");

				Obj->SetWorldPos(Pos);
				Obj->SetPoint(Pos);
				Obj->AddWorldPos(0.f, 0.f, 1.f);
				Obj->IsTornado();
			}
			{
				CWendyStorm* Obj = m_pScene->SpawnObject<CWendyStorm>("obj");

				Obj->SetWorldPos(Pos);
				Obj->SetPoint(Pos);
				Obj->AddWorldPos(0.f, 0.f, -1.f);
				Obj->IsTornado();
			}
		}
		break;
		}
	}
	if (Name == "LongAttack3")
	{
		switch (m_AttackState)
		{
		case Wendy_AttackState::Storm:
		{
		}
		break;
		case Wendy_AttackState::AirBullet:
		{
		}
		break;
		case Wendy_AttackState::AirStar:
		{
			CWendyAirStar* Obj = m_pScene->SpawnObject<CWendyAirStar>("obj");
			Obj->SetWorldPos(GetWorldPos().x + 1.f, GetWorldPos().y + 2.f, GetWorldPos().z + 1.f);
		}
		break;
		case Wendy_AttackState::Tornado:
		{
		}
		break;
		}
	}

	if (Name == "CameraShake")
	{
		m_pScene->GetCameraManager()->GetCurrentCamera()->StartShake(0.005f, 0.005f, 1.f);
	}
}
void CWendy::PaperBurnEndFunction()
{
	this->Active(false);
}
void CWendy::LookObject()
{
	LookAtObject(CPublicData::GetInst()->m_CurPlayer);
	LookAtObjectActive(true);
}
void CWendy::LookObject(bool Enable)
{
	LookAtObject(CPublicData::GetInst()->m_CurPlayer);
	LookAtObjectActive(Enable);
}
void CWendy::EndAnimation(std::string	AniName)
{
	LookObject();
	switch (m_State)
	{
	case Wendy_State::Spawn:
	{
		if (AniName == "Wendy_Born")
		{
			m_FSM.ChangeState("Idle");
		}
	}
	break;
	case Wendy_State::Idle:
		break;
	case Wendy_State::Move:
	{
		if (AniName == "Wendy_RunStart")
		{
			m_Animation->ChangeAnimation("Wendy_Run");
		}
	}
	break;
	case Wendy_State::Attack:
	{
		if (AniName == "Wendy_GlideLeft" || AniName == "Wendy_GlideRight" || AniName == "Wendy_GlideBack")
		{
			if (0 != m_RandomCount)
			{
				int Ani = GetRandom(1, 2);

				if (1 == Ani)
					m_Animation->ChangeAnimation("Wendy_GlideLeft");
				else
					m_Animation->ChangeAnimation("Wendy_GlideRight");

				m_RandomCount--;
			}
			else
			{
				switch (m_AttackState)
				{
				case Wendy_AttackState::AIrShoot:
				{
					if (Wendy_LongAttack_Dir >= m_PlayerDir)
					{
						m_Animation->ChangeAnimation("Wendy_AirShoot");
					}
					else
					{
						m_PointDir = Wendy_LongAttack_Dir - 2;
						m_FSM.ChangeState("Move");
					}
				}
				break;
				case Wendy_AttackState::AirHole:
				{
					if (Wendy_ShortAttack_Dir >= m_PlayerDir)
					{
						m_Animation->ChangeAnimation("Wendy_AirHole");
					}
					else
					{
						m_PointDir = Wendy_ShortAttack_Dir;
						m_FSM.ChangeState("Move");
					}
				}
				break;
				case Wendy_AttackState::Brandish:
				{
					if (Wendy_ShortAttack_Dir >= m_PlayerDir)
					{
						m_Animation->ChangeAnimation("Wendy_Brandish");
					}
					else
					{
						m_PointDir = Wendy_ShortAttack_Dir;
						m_FSM.ChangeState("Move");
					}
				}
				break;
				case Wendy_AttackState::Storm:
				{
					if (Wendy_ShortAttack_Dir >= m_PlayerDir)
					{
						m_Animation->ChangeAnimation("Wendy_Storm");
					}
					else
					{
						m_PointDir = Wendy_ShortAttack_Dir;
						m_FSM.ChangeState("Move");
					}
				}
				break;
				case Wendy_AttackState::AirBullet:
				{
					if (Wendy_LongAttack_Dir >= m_PlayerDir)
					{
						m_Animation->ChangeAnimation("Wendy_LongAttack");
					}
					else
					{
						m_PointDir = Wendy_LongAttack_Dir - 2;
						m_FSM.ChangeState("Move");
					}
				}
				break;
				case Wendy_AttackState::AirStar:
				{
					if (Wendy_LongAttack_Dir >= m_PlayerDir)
					{
						m_Animation->ChangeAnimation("Wendy_LongAttack");
					}
					else
					{
						m_PointDir = Wendy_LongAttack_Dir - 2;
						m_FSM.ChangeState("Move");
					}
				}
				break;
				case Wendy_AttackState::Tornado:
				{
					if (Wendy_LongAttack_Dir >= m_PlayerDir)
					{
						m_Animation->ChangeAnimation("Wendy_LongAttack");
					}
					else
					{
						m_PointDir = Wendy_LongAttack_Dir - 2;
						m_FSM.ChangeState("Move");
					}
				}
				break;
				}
			}
		}
		else
		{
			m_AttackState = Wendy_AttackState::None;
			m_FSM.ChangeState("Idle");
		}
	}
	break;
	case Wendy_State::Hit:
		break;
	case Wendy_State::Dead:
		if (!m_ParperBurnOn)
		{
			m_Mesh->GetMaterial(0)->SetTransparency(true);
			m_Mesh->GetMaterial(1)->SetTransparency(true);
			m_Mesh->GetMaterial(2)->SetTransparency(true);
			m_Mesh->GetMaterial(3)->SetTransparency(true);
			m_Mesh->GetMaterial(4)->SetTransparency(true);
			m_Mesh->GetMaterial(5)->SetTransparency(true);
			m_Mesh->GetMaterial(6)->SetTransparency(true);
			m_ParperBurnOn = true;
			m_PaperBurn0->StartPaperBurn();
			m_PaperBurn1->StartPaperBurn();
			m_PaperBurn2->StartPaperBurn();
			m_PaperBurn3->StartPaperBurn();
			m_PaperBurn4->StartPaperBurn();
			m_PaperBurn5->StartPaperBurn();
			m_PaperBurn6->StartPaperBurn();
		}
		break;
	}
}

CWendy* CWendy::Clone()
{
	return new CWendy(*this);
}

void CWendy::CollisionBegin(const HitResult& result, CCollider* Collider)
{
	CMonster::CollisionBegin(result, Collider);

	if (result.DestCollider->GetProfile()->Name == "PlayerAttack")
	{
		CAttackObject* obj = dynamic_cast<CAttackObject*>(result.DestObject);
		int Damage = 1;
		if (obj)
		{
			Damage = obj->GetDamage();
		}
		else
		{
			CPlayer* Player = (CPlayer*)result.DestObject;
			Damage = Player->GetStatus()->GetDamage();
		}
		MinusHp(Damage);
		CreateHitDamage(Damage);
		if (m_Hp <= 0.f)
		{
			IsDeath();
		}
	}
}
void CWendy::CollisionMiddle(const HitResult& result, CCollider* Collider)
{
}
void CWendy::CollisionEnd(const HitResult& result, CCollider* Collider)
{
}

void CWendy::CameraAction()
{
	m_Animation->ResetSequence();
}
