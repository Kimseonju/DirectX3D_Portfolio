#include "Sniper.h"
#include "Scene/Scene.h"
#include "../PublicData.h"
#include "Player.h"
#include "SniperBillet.h"
#include "SniperGrenade.h"
#include "../StageManager.h"
#include "Axe_Weapon.h"

CSniper::CSniper()
{
	m_ClientClassType = ClientClassType::Sniper;
	m_Animation = nullptr;
	m_AttType = 0;
	
	m_PointDir = 0.f;
	m_DeltaTime = 0.f;
	m_DeadGradientTimer = 10.f;

	m_IdleTime = 1.f;
	m_SpawnTimer1 = 1.f;
	m_SpawnTimer2 = 2.f;

	m_DeadGradientOn = false;
	m_Death = false;


	SetClientClassType(ClientClassType::Sniper);

	m_SniperCurAttState = Sniper_AttState::None;
	m_SniperPrevAttState = Sniper_AttState::None;
	m_NextAttack = Sniper_AttState::None;
	m_SniperCurState = Sniper_State::Spawn;
	m_HitState = Sniper_HitState::None;
	m_HitAniState = Sniper_HitAniState::None;
}
CSniper::CSniper(const CSniper& obj) : CMonster(obj)
{
	m_Animation = (CSniperAnimation*)m_Mesh->GetAnimation();
	m_FSM.m_Play = obj.m_FSM.m_Play;
}
CSniper::~CSniper()
{
}

void CSniper::Start()
{
	CMonster::Start();

	CreateFSM();
}
bool CSniper::Init()
{
	CMonster::Init();
	SetHp(100);
	m_Mesh->SetInheritRotY(true);
	m_Mesh->SetMesh(m_pScene->GetResource()->FindMesh("SniperMesh"));
	m_Mesh->SetWorldScale(1.f, 1.f, 1.f);
	// m_Mesh->SetRelativeRotationY(-180.f);
	m_Mesh->SetRelativeRotationX(-90.f);
	m_Mesh->AddWorldPos(0.f, -2.f, 0.f);
	m_Animation = new CSniperAnimation;
	m_Mesh->SetAnimation(m_Animation);
	m_Animation->SetScene(m_pScene);
	m_Animation->Init();
	m_Animation->m_Owner = this;
	m_Animation->SetAnimationEndFunc(&CSniper::EndAnimation);
	m_Animation->SetRootBoneIndex("Bip001 Pelvis");

	{
		m_Mesh->GetMaterial(0)->SetTransparency(true);
		m_Mesh->GetMaterial(1)->SetTransparency(true);
		m_PaperBurn0 = CreateObjectComponent<CPaperBurnComponent>("PaperBurn0");
		m_PaperBurn0->SetBurnTime(3.f);
		m_PaperBurn0->SetEndFunction<CSniper>(this, &CSniper::PaperBurnEndFunction);
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
	}
	return true;
}
void CSniper::Update(float DeltaTime)
{
	DeltaTime *= CStageManager::GetInst()->GetWorldSpeed();
	CMonster::Update(DeltaTime);
	if (false == m_Setting)
	{
		m_Setting = true;
		m_Body->Enable(true);

		m_Body->SetWorldScale(0.5f, 1.5f, 0.5f);
		m_MapBody->SetWorldScale(0.5f, 1.5f, 0.5f);
	}
	m_DeltaTime = DeltaTime;


	if ((0 >= m_Hp && m_SniperCurState != Sniper_State::Dead))
	{
		IsDead();
	}

	m_FSM.Update();
}
void CSniper::PostUpdate(float DeltaTime)
{
	DeltaTime *= CStageManager::GetInst()->GetWorldSpeed();
	CMonster::PostUpdate(DeltaTime);

	if (m_SniperCurState != Sniper_State::Spawn)
	{
		SetWorldPos(GetWorldPos().x, CPublicData::GetInst()->GetCurPlayer()->GetWorldPos().y, GetWorldPos().z);
	}
}
void CSniper::Collision(float DeltaTime)
{
	CMonster::Collision(DeltaTime);


}
void CSniper::Render(float DeltaTime)
{
	CMonster::Render(DeltaTime);


}
CSniper* CSniper::Clone()
{
	return new CSniper(*this);
}

void CSniper::AnimationNotify(const std::string& Name)
{
	if ("RAttack" == Name)
	{
		CAxeWeapon* Weapon = m_pScene->SpawnObject<CAxeWeapon>("Weapon");
		Weapon->SetMonster(this);
		Weapon->SetAttackType(Axe_AttState::NAttack);
	}
	if ("PlayerSearch_Start" == Name)
	{
		LookAtObject(CPublicData::GetInst()->m_CurPlayer);
		LookAtObjectActive(true);
	}
	else if ("PlayerSearch_End" == Name)
	{
		LookAtObject(CPublicData::GetInst()->m_CurPlayer);
		LookAtObjectActive(false);
	}
	if ("Body_false" == Name)
	{
		m_Body->Enable(false);
	}
	if ("Body_true" == Name)
	{
		m_Body->Enable(true);
	}
	if ("AttackCollStart" == Name)
	{
		switch (m_SniperCurAttState)
		{
		case Sniper_AttState::NAttack:
		{
			Vector3 BullPos = GetWorldPos();
			CSniperBullet* Bullet = m_pScene->SpawnObject<CSniperBullet>("Bullet");
			Bullet->SetWorldRotation(GetWorldRotation());
			Bullet->GetMesh()->SetRelativeRotationY(GetRelativeRotation().y);
			Bullet->SetWorldPos(BullPos);
		}
			break;
		case Sniper_AttState::GAttack:
		{
			CSniperGrenade* Bullet = m_pScene->SpawnObject<CSniperGrenade>("Grenade");
			Bullet->SetWorldPos(GetWorldPos());
			Bullet->SetWorldRotation(GetWorldRotation()* 0.5f);
			Bullet->GetMesh()->SetRelativeRotationY(-GetRelativeRotation().y);
			Bullet->SetMinY(GetWorldPos().y);
		}
			break;
		case Sniper_AttState::FAttack:
		{
			Vector3 BullPos = GetWorldPos();
			CSniperBullet* Bullet = m_pScene->SpawnObject<CSniperBullet>("Bullet");
			Bullet->SetWorldRotation(GetWorldRotation());
			Bullet->GetMesh()->SetRelativeRotationY(-GetRelativeRotation().y);
			Bullet->SetWorldPos(BullPos);
			Bullet->AddWorldPos(0.f, -1.f, 0.f);
			Bullet->IsNAttack(false);
		}
			break;
		default:
			break;
		}
	}
}
void CSniper::EndAnimation(std::string	AniName)
{
	if ("Sniper_Run" == AniName)
	{
		m_Animation->ChangeAnimation("Sniper_Run+");
	}
	else if ("Sniper_Run+" == AniName)
	{
		m_Animation->ChangeAnimation("Sniper_Run");
	}
	switch (m_SniperCurState)
	{
	case Sniper_State::Spawn:
		break;
	case Sniper_State::Idle:
		break;
	case Sniper_State::Move:
		break;
	case Sniper_State::Attack:
		if ("Sniper_NAttack" == AniName)
		{
			m_SniperPrevAttState = m_SniperCurAttState;
			m_SniperCurAttState = Sniper_AttState::None;
			m_SniperCurState = Sniper_State::Idle;
			m_FSM.ChangeState("Sniper_Idle");
		}
		else if ("Sniper_GAttack" == AniName)
		{
			m_SniperPrevAttState = m_SniperCurAttState;
			m_SniperCurAttState = Sniper_AttState::None;
			m_SniperCurState = Sniper_State::Idle;
			m_FSM.ChangeState("Sniper_Idle");
		}
		else if ("Sniper_RAttack" == AniName)
		{
			m_SniperPrevAttState = m_SniperCurAttState;
			m_SniperCurAttState = Sniper_AttState::None;
			m_SniperCurState = Sniper_State::Idle;
			m_FSM.ChangeState("Sniper_Idle");
		}
		else if ("Sniper_FAttack" == AniName)
		{
			m_Body->Enable(true);
			m_Root->AddRelativeRotationY(-180.f);
			m_SniperPrevAttState = m_SniperCurAttState;
			m_SniperCurAttState = Sniper_AttState::None;
			m_SniperCurState = Sniper_State::Idle;
			m_FSM.ChangeState("Sniper_Idle");
		}
		else if ("Sniper_Backward" == AniName)
		{
			m_Animation->ChangeAnimation("Sniper_Idle");
		}
		break;
	case Sniper_State::Hit:
	{
		if ("Sniper_HFlyALL" == AniName)
		{
			m_HitAniState = Sniper_HitAniState::None;
			m_SniperCurState = Sniper_State::Idle;
			m_Animation->ChangeAnimation("Sniper_Idle");
		}
		else if ("Sniper_HFly" == AniName)
		{
			m_HitAniState = Sniper_HitAniState::HFlyToStand;
			m_Animation->ChangeAnimation("Sniper_HFlyToStand");
		}
		else if ("Sniper_HFlyToStand" == AniName)
		{
			m_HitAniState = Sniper_HitAniState::None;
			m_SniperCurState = Sniper_State::Idle;
			m_Animation->ChangeAnimation("Sniper_Idle");
		}
		else if ("Sniper_LFly" == AniName)
		{
			m_HitAniState = Sniper_HitAniState::FlyToKnockDown;
			m_Animation->ChangeAnimation("Sniper_FlyToKnockDown");
		}
		else if ("Sniper_FlyToKnockDown" == AniName)
		{
			m_HitAniState = Sniper_HitAniState::StandUp;
			m_Animation->ChangeAnimation("Sniper_StandUp");
		}
		else if ("Sniper_StandUp" == AniName)
		{
			m_HitAniState = Sniper_HitAniState::None;
			m_SniperCurState = Sniper_State::Idle;
			m_Animation->ChangeAnimation("Sniper_Idle");
		}
		else if ("Sniper_Stun" == AniName)
		{
			m_HitAniState = Sniper_HitAniState::None;
			m_SniperCurState = Sniper_State::Idle;
			m_Animation->ChangeAnimation("Sniper_Idle");
		}
		else if ("Sniper_HHit" == AniName)
		{
			m_HitAniState = Sniper_HitAniState::None;
			m_SniperCurState = Sniper_State::Idle;
			m_Animation->ChangeAnimation("Sniper_Idle");
		}
		else if ("Sniper_LHit" == AniName)
		{
			m_HitAniState = Sniper_HitAniState::None;
			m_SniperCurState = Sniper_State::Idle;
			m_Animation->ChangeAnimation("Sniper_Idle");
		}
	}
		break;
	case Sniper_State::Dead:
	{
		if ("Sniper_Die" == AniName)
		{
			m_Death = true;
			m_PaperBurn0->StartPaperBurn();
			m_PaperBurn1->StartPaperBurn();
		}
	}
		break;
	default:
		break;
	}
}
void CSniper::PaperBurnEndFunction()
{
	this->Active(false);
}
void CSniper::CollisionBegin(const HitResult& result, CCollider* Collider)
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
			Damage=Player->GetStatus()->GetDamage();
			
		}
		if (m_SniperCurState != Sniper_State::Spawn)
		{
			MinusHp(Damage);
			CreateHitDamage(Damage);
			if (m_SniperCurState != Sniper_State::Attack)
				IsHit(Sniper_HitState::Normal);

			IsHit(Sniper_HitState::Normal);
			CStageManager::GetInst()->MonsterHit();
			//m_pScene->GetCameraManager()->GetCurrentCamera()->StartShake(0.015f, 0.015f, 0.5f);
		}
	}
}
void CSniper::CollisionMiddle(const HitResult& result, CCollider* Collider)
{
}
void CSniper::CollisionEnd(const HitResult& result, CCollider* Collider)
{
}