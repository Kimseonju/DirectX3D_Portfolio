#include "AxeSoldier.h"
#include "Scene/Scene.h"
#include "../PublicData.h"
#include "Axe_Weapon.h"
#include "../StageManager.h"
#include "../UI/UIManager.h"
CAxeSoldier::CAxeSoldier()
{
	m_ClientClassType = ClientClassType::Axe;
	m_Animation = nullptr;

	m_MoveRandom = 0;
	m_DeltaTime = 0.f;
	m_DeadGradientTimer = 10.f;
	m_SpawnTimer1 = 1.f;
	m_SpawnTimer2 = 2.f;


	m_FAttackOn = false;
	m_MoveEnd = false;
	m_DeadGradientOn = false;
	m_AttackRun = false;
	m_DeathOn = false;

	SetClientClassType(ClientClassType::Axe);

	m_AxeCurAttState = Axe_AttState::None;
	m_NextAttack = Axe_AttState::None;
	m_AxeCurState = Axe_State::Spawn;
	m_MoveState = Axe_MoveState::None;
	m_BMoveState = Axe_MoveState::None;
	m_HitState = Axe_HitState::None;
	m_HitAniState = Axe_HitAniState::None;
}
CAxeSoldier::CAxeSoldier(const CAxeSoldier& obj) :
	CMonster(obj)
{
	m_Animation = (CAxeSoldierAnimation*)m_Mesh->GetAnimation();
	m_FSM.m_Play = obj.m_FSM.m_Play;
}
CAxeSoldier::~CAxeSoldier()
{
}

void CAxeSoldier::Start()
{
	CMonster::Start();

	CreateFSM();
}
bool CAxeSoldier::Init()
{
	CMonster::Init();
	SetHp(1000);
	m_Mesh->SetInheritRotY(true);
	m_Mesh->SetMesh("AxesoldierMesh");

	m_Mesh->SetWorldScale(1.f, 1.f, 1.f);

	//m_Mesh->SetRelativeRotationY(-180.f);
	m_Mesh->SetRelativeRotationX(-90.f);
	m_Mesh->AddWorldPos(0.f, -2.f, 0.f);
	m_Animation = new CAxeSoldierAnimation;
	m_Mesh->SetAnimation(m_Animation);
	m_Animation->SetScene(m_pScene);
	m_Animation->Init();
	m_Animation->m_Owner = this;
	m_Animation->SetAnimationEndFunc(&CAxeSoldier::EndAnimation);
	m_Animation->SetRootBoneIndex("Bip001 Pelvis");

	m_AttackColl = CreateSceneComponent<CColliderBox3D>("Box");
	m_AttackColl->Enable(false);
	m_AttackColl->SetWorldScale(Vector3::Zero);
	m_Mesh->AddChild(m_AttackColl);

	//m_Weapon->SetInheritRotX(true);
	//m_Weapon->SetInheritRotY(true);
	//m_Weapon->SetInheritRotZ(true);
	//m_Weapon->SetInheritPosZ(true);
	//m_Weapon->SetWorldScale(0.5f, 0.1f, 0.1f);
	//m_Weapon->SetCollisionProfile("MonsterAttack");

	//CSkeleton* Skel = m_Animation->GetSkeleton();
	//Skel->AddSocket("Bone030", "Axe_Weapon");
	//m_Mesh->AddChild(m_Weapon, "Axe_Weapon");
	//CBoneSocket* WeaponCollisionSocket = Skel->GetSocket("Axe_Weapon");

	{
		m_Mesh->GetMaterial(0)->SetTransparency(true);
		m_Mesh->GetMaterial(1)->SetTransparency(true);
		m_Mesh->GetMaterial(2)->SetTransparency(true);
		m_PaperBurn0 = CreateObjectComponent<CPaperBurnComponent>("PaperBurn0");
		m_PaperBurn0->SetBurnTime(3.f);
		m_PaperBurn0->SetEndFunction<CAxeSoldier>(this, &CAxeSoldier::PaperBurnEndFunction);
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

		m_PaperBurn2 = CreateObjectComponent<CPaperBurnComponent>("PaperBurn2");
		m_PaperBurn2->SetBurnTime(3.f);
		m_PaperBurn2->SetTargetMaterial(m_Mesh->GetMaterial(2));
		m_PaperBurn2->SetOutLineColorUNorm(0.2f, 0.2f, 0.2f);
		m_PaperBurn2->SetCenterLineColor(255, 69, 0);
		m_PaperBurn2->SetInLineColorUNorm(0.7f, 0.7f, 0.7f);
	}
	return true;
}
void CAxeSoldier::Update(float DeltaTime)
{
	DeltaTime *= CStageManager::GetInst()->GetWorldSpeed();
	m_DeltaTime = DeltaTime;
	CMonster::Update(DeltaTime);

	if (false == m_Setting)
	{
		m_Setting = true;
		m_Body->Enable(true);
		m_Body->SetWorldScale(0.5f, 1.5f, 0.5f);
		m_MapBody->SetWorldScale(0.5f, 1.5f, 0.5f);
	}

	if (0 >= m_Hp && m_AxeCurState != Axe_State::Dead)
	{
		IsDead();
	}

	if (m_AxeCurState != Axe_State::Spawn)
	{
		SetWorldPos(GetWorldPos().x, CPublicData::GetInst()->GetCurPlayer()->GetWorldPos().y, GetWorldPos().z);
	}
	m_FSM.Update();
}
void CAxeSoldier::PostUpdate(float DeltaTime)
{
	DeltaTime *= CStageManager::GetInst()->GetWorldSpeed();
	CMonster::PostUpdate(m_DeltaTime);
}
void CAxeSoldier::Collision(float DeltaTime)
{
	CMonster::Collision (m_DeltaTime);


}
void CAxeSoldier::Render(float DeltaTime)
{
	CMonster::Render(m_DeltaTime);


}

void CAxeSoldier::PaperBurnEndFunction()
{
	this->Active(false);
}
void CAxeSoldier::AnimationNotify(const std::string& Name)
{
	if ("PlayerSearch_Start" == Name)
	{
		LookAtObjectActive(true);
	}
	if ("PlayerSearch_End" == Name)
	{
		LookAtObjectActive(false);
	}
	if ("TAttack" == Name)
	{
		CAxeWeapon* Weapon = m_pScene->SpawnObject<CAxeWeapon>("Weapon");
		Weapon->SetMonster(this);
		Weapon->SetAttackType(m_AxeCurAttState);
		Weapon->TAttack2();
	}
	if ("StartAttack" == Name)
	{
		CAxeWeapon* Weapon = m_pScene->SpawnObject<CAxeWeapon>("Weapon");
		Weapon->SetMonster(this);
		Weapon->SetAttackType(m_AxeCurAttState);
		if (m_AxeCurAttState == Axe_AttState::RAttack)
		{
			Weapon->SetWorldRotation(GetWorldRotation());
		}
	}
}
void CAxeSoldier::EndAnimation(std::string	AniName)
{
	if (AniName == "AxeSoldier_Run")
	{
		m_Animation->ChangeAnimation("AxeSoldier_Run+");
	}
	else if (AniName == "AxeSoldier_Run+")
	{
		m_Animation->ChangeAnimation("AxeSoldier_Run");
	}
	switch (m_AxeCurState)
	{
	case Axe_State::Idle:
		break;
	case Axe_State::Move:
	{
		if (AniName == "AxeSoldier_BWalk")
		{
			m_MoveEnd = true;
		}
		if (AniName == "AxeSoldier_LWalk")
		{
			m_MoveEnd = true;
		}
		if (AniName == "AxeSoldier_RWalk")
	{
		m_MoveEnd = true;
	}
	}
		break;
	case Axe_State::Attack:
	{
		if (AniName == "AxeSoldier_NAttack")
	{
		m_AxeCurAttState = Axe_AttState::None;
		m_MoveState = Axe_MoveState::None;
		m_FSM.ChangeState("Axe_Idle");
	}
		else if (AniName == "AxeSoldier_FAttack_1")
	{
		float Dir = CPublicData::GetInst()->DistanceToPlayer(GetWorldPos());


		if (Axe_NAttack_Dir >= Dir)
		{
			m_AxeCurAttState = Axe_AttState::NAttack;
			m_Animation->ChangeAnimation("AxeSoldier_NAttack");
		}
		else if (Axe_RAttack_Dir >= Dir)
		{
			m_AxeCurAttState = Axe_AttState::RAttack;
			m_Animation->ChangeAnimation("AxeSoldier_RAttack");
		}
		else if (Axe_FAttack_2_Dir >= Dir)
		{
			m_AxeCurAttState = Axe_AttState::FAttack2;
			m_Animation->ChangeAnimation("AxeSoldier_FAttack_2");
		}
		else if (Axe_TAttack_Dir >= Dir)
		{
			m_AxeCurAttState = Axe_AttState::TAttack;
			m_Animation->ChangeAnimation("AxeSoldier_TAttack");
		}
		else
		{
			m_AxeCurAttState = Axe_AttState::None;
			m_MoveState = Axe_MoveState::None;
			m_FSM.ChangeState("Axe_Idle");
		}
	}
		else if (AniName == "AxeSoldier_FAttack_2")
	{
		m_AxeCurAttState = Axe_AttState::None;
		m_MoveState = Axe_MoveState::None;
		m_FSM.ChangeState("Axe_Idle");

	}
		else if (AniName == "AxeSoldier_TAttack")
	{
		float Dir = CPublicData::GetInst()->DistanceToPlayer(GetWorldPos());
		if (Axe_NAttack_Dir >= Dir)
		{
			m_AxeCurAttState = Axe_AttState::NAttack;
			m_Animation->ChangeAnimation("AxeSoldier_NAttack");
		}
		else if (Axe_RAttack_Dir >= Dir)
		{
			m_AxeCurAttState = Axe_AttState::RAttack;
			m_Animation->ChangeAnimation("AxeSoldier_RAttack");
		}
		else if (Axe_FAttack_2_Dir >= Dir)
		{
			m_AxeCurAttState = Axe_AttState::FAttack2;
			m_Animation->ChangeAnimation("AxeSoldier_FAttack_2");
		}
		else if (Axe_TAttack_Dir >= Dir)
		{
			m_AxeCurAttState = Axe_AttState::TAttack;
			m_Animation->ChangeAnimation("AxeSoldier_TAttack");
		}
		else
		{
			m_AxeCurAttState = Axe_AttState::None;
			m_MoveState = Axe_MoveState::None;
			m_FSM.ChangeState("Axe_Idle");
		}

	}
		else if (AniName == "AxeSoldier_RAttack")
	{
		m_AxeCurAttState = Axe_AttState::None;
		m_MoveState = Axe_MoveState::None;
		m_FSM.ChangeState("Axe_Idle");

	}
		else
	{

	}
	}
		break;
	case Axe_State::Hit:
	{
		if (AniName == "AxeSoldier_Hit")
		{
			m_HitAniState = Axe_HitAniState::None;
			m_FSM.ChangeState("Axe_Idle");
		}
		else if (AniName == "AxeSoldier_HThrow_1")
		{
			m_HitAniState = Axe_HitAniState::StandUp;
			m_Animation->ChangeAnimation("AxeSoldier_StandUp");
		}
		else if (AniName == "AxeSoldier_StandUp")
		{
			m_HitAniState = Axe_HitAniState::StandBy;
			m_Animation->ChangeAnimation("AxeSoldier_StandBy");
		}
		else if (AniName == "AxeSoldier_StandBy")
		{
			m_HitAniState = Axe_HitAniState::None;
			m_FSM.ChangeState("Axe_Idle");
		}
		else if (AniName == "AxeSoldier_Hit_HFly")
		{
			m_HitAniState = Axe_HitAniState::FlyToKnockBack;
			m_Animation->ChangeAnimation("AxeSoldier_FlyToKnockBack");
		}
		else if (AniName == "AxeSoldier_FlyToKnockBack")
		{
			m_HitAniState = Axe_HitAniState::StandUp;
			m_Animation->ChangeAnimation("AxeSoldier_StandUp");
		}
		else if (AniName == "AxeSoldier_KnockBack")
		{
			m_HitAniState = Axe_HitAniState::StandUp;
			m_Animation->ChangeAnimation("AxeSoldier_StandUp");
		}
		else if (AniName == "AxeSoldier_LThrow_1")
		{
			m_HitAniState = Axe_HitAniState::StandUp;
			m_Animation->ChangeAnimation("AxeSoldier_StandUp");
		}
		else if (AniName == "AxeSoldier_Hit_LFly")
		{
			m_HitAniState = Axe_HitAniState::FlyToKnockBack;
			m_Animation->ChangeAnimation("AxeSoldier_FlyToKnockBack");
		}
	}
		break;
	case Axe_State::Dead:
	{
		if (AniName == "AxeSoldier_NDie")
		{
			m_DeathOn = true;
			m_PaperBurn0->StartPaperBurn();
			m_PaperBurn1->StartPaperBurn();
			m_PaperBurn2->StartPaperBurn();
		}
		else if (AniName == "AxeSoldier_BDie")
		{
			m_DeathOn = true;
			m_PaperBurn0->StartPaperBurn();
			m_PaperBurn1->StartPaperBurn();
			m_PaperBurn2->StartPaperBurn();
		}
		else if (AniName == "AxeSoldier_FDie")
		{
			m_DeathOn = true;
			m_PaperBurn0->StartPaperBurn();
			m_PaperBurn1->StartPaperBurn();
			m_PaperBurn2->StartPaperBurn();
		}
	}
		break;
	default:
		break;
	}
}

void CAxeSoldier::CollisionBegin(const HitResult& result, CCollider* Collider)
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
		if (m_AxeCurState != Axe_State::Spawn)
		{
			MinusHp(Damage);
			CreateHitDamage(Damage);
			if (m_AxeCurState != Axe_State::Attack)
				IsHit(Axe_HitState::Normal);
			CStageManager::GetInst()->MonsterHit();
			//m_pScene->GetCameraManager()->GetCurrentCamera()->StartShake(0.015f, 0.015f, 0.5f);
		}
	}
}
void CAxeSoldier::CollisionMiddle(const HitResult& result, CCollider* Collider)
{
}
void CAxeSoldier::CollisionEnd(const HitResult& result, CCollider* Collider)
{
}
void CAxeSoldier::IsFSMPlay(bool _Play)
{
	m_FSM.IsPlay(_Play);
}


CAxeSoldier* CAxeSoldier::Clone()
{
	return new CAxeSoldier(*this);
}