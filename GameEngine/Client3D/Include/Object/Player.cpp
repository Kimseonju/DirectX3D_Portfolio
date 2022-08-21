
#include "Player.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Resource/Material.h"
#include "Input.h"
#include "../UI/UIManager.h"
#include "Resource/Skeleton.h"
#include "CollisionManager.h"
#include "../PublicData.h"
#include "../StageManager.h"
#include "AttackObject.h"
#include "PlayerAttCol.h"
CPlayer::CPlayer() :
	m_Animation(nullptr),
	m_State(PlayerState::Idle),
	m_AttackCombo(0),
	m_CombatDelayMax(3.f),
	m_CombatDelay(0.f),
	m_Move(false),
	m_AttackChargeCombo(false),
	m_KeyLeftMove(false),
	m_KeyRightMove(false),
	m_KeyMoveFront(false),
	m_KeyMoveBack(false),
	m_FSMEnable(true),
	m_UltraSkillAttack(false),
	m_UltraSkillTime(0.f),
	m_UltraSkillTimeMax(3.f),
	m_UltraSkillEffect1(false),
	m_UltraSkillEffect2(false),
	m_PlayerDeltaTime(0.f),
	m_PlayerStatus(nullptr),
	m_DeltaTime(0.f),
	m_AttackClick(false),
	m_AttackComboPlay(false),
	m_MoveDirAngle(0.f)
{
}

CPlayer::CPlayer(const CPlayer& obj) :
	CClientObject(obj)
{
	m_Root = (CSceneComponent*)FindSceneComponent("Root");
	m_Mesh = (CAnimationMeshComponent*)FindSceneComponent("Mesh");
	m_WeaponMesh = (CStaticMeshComponent*)FindSceneComponent("WeaponMesh1");
	m_WeaponMesh2 = (CStaticMeshComponent*)FindSceneComponent("WeaponMesh2");
	m_Body = (CColliderBox3D*)FindSceneComponent("Body");
	m_Arm = (CSpringArm3D*)FindSceneComponent("Arm");
	m_EvadeBody = (CColliderBox3D*)FindSceneComponent("EvadeBody");

}

CPlayer::~CPlayer()
{
}

void CPlayer::Start()
{
	CClientObject::Start();
}

bool CPlayer::Init()
{
	CClientObject::Init();
	m_Root = CreateSceneComponent<CSceneComponent>("Root");
	m_Mesh = CreateSceneComponent<CAnimationMeshComponent>("Mesh");
	m_WeaponMesh = CreateSceneComponent<CStaticMeshComponent>("WeaponMesh1");
	m_WeaponMesh2 = CreateSceneComponent<CStaticMeshComponent>("WeaponMesh2");
	m_Body = CreateSceneComponent<CColliderBox3D>("Body");
	m_EvadeBody = CreateSceneComponent<CColliderBox3D>("EvadeBody");
	m_Arm = CreateSceneComponent<CSpringArm3D>("Arm");



	m_pScene->GetCameraManager()->SetCurrentCamera("Player");
	SetRootComponent(m_Root);

	m_Root->AddChild(m_Body);
	m_Root->AddChild(m_EvadeBody);
	m_Body->SetExtent(0.5f,2.f,0.5f);
	m_Body->SetCollisionProfile("Player");

	m_EvadeBody->SetExtent(0.5f, 2.f, 0.5f);
	m_EvadeBody->SetCollisionProfile("PlayerEvade");
	m_EvadeBody->Enable(false);

	m_Root->AddChild(m_Mesh);
	m_Mesh->AddChild(m_Arm);

	//m_Arm->AddChild(m_Camera);

	m_Mesh->SetInheritRotY(true);
	m_Mesh->SetInheritPosZ(true);
	m_Body->SetInheritRotY(true);
	//m_Camera->SetInheritRotX(false);
	//m_Camera->SetInheritRotY(false);
	//m_Camera->SetInheritRotZ(false);

	m_Arm->SetInheritRotY(false);

	m_Arm->SetRelativeRotationX(25.f);
	m_Arm->SetLength(3.f);
	m_Arm->SetOffset(0.f, 1.f, 0.f);

	m_Animation = new CPlayerAnimation;
	m_Mesh->SetAnimation(m_Animation);
	m_Animation->Init();


	m_Mesh->SetWorldScale(1.f, 1.f, 1.f);
	m_Mesh->SetWorldPos(0.f, 0.f, 0.f);
	m_Mesh->SetRelativeRotation(-90.f, 0.f, 0.f);



	CInput::GetInst()->AddKeyCallback("ClientMoveFront", Key_Type::KT_Down, this, &CPlayer::MoveFront);
	CInput::GetInst()->AddKeyCallback("ClientMoveBack", Key_Type::KT_Down, this, &CPlayer::MoveBack);
	CInput::GetInst()->AddKeyCallback("ClientLeftMove", Key_Type::KT_Down, this, &CPlayer::LeftMove);
	CInput::GetInst()->AddKeyCallback("ClientRightMove", Key_Type::KT_Down, this, &CPlayer::RightMove);

	CInput::GetInst()->AddKeyCallback("ClientMoveFront", Key_Type::KT_Up, this, &CPlayer::ReleaseMoveFront);
	CInput::GetInst()->AddKeyCallback("ClientMoveBack", Key_Type::KT_Up, this, &CPlayer::ReleaseMoveBack);
	CInput::GetInst()->AddKeyCallback("ClientLeftMove", Key_Type::KT_Up, this, &CPlayer::ReleaseLeftMove);
	CInput::GetInst()->AddKeyCallback("ClientRightMove", Key_Type::KT_Up, this, &CPlayer::ReleaseRightMove);
	//CInput::GetInst()->AddKeyCallback("ClientMouseLButton", Key_Type::KT_Up, this, &CPlayer::Attack);

	CInput::GetInst()->AddKeyCallback("ClientChange1", Key_Type::KT_Down, this, &CPlayer::Change1);
	CInput::GetInst()->AddKeyCallback("ClientChange2", Key_Type::KT_Down, this, &CPlayer::Change2);
	CInput::GetInst()->AddKeyCallback("ClientUltraSkill", Key_Type::KT_Down, this, &CPlayer::UltraSkill);
	CInput::GetInst()->AddKeyCallback("ClientEvade", Key_Type::KT_Down, this, &CPlayer::Evade);
	PlayerFSM.CreateState("Idle", this, &CPlayer::IdleStay, &CPlayer::IdleStart, &CPlayer::IdleEnd);
	PlayerFSM.CreateState("Attack", this, &CPlayer::AttackStay, &CPlayer::AttackStart, &CPlayer::AttackEnd);
	PlayerFSM.CreateState("Move", this, &CPlayer::MoveStay, &CPlayer::MoveStart, &CPlayer::MoveEnd);
	PlayerFSM.CreateState("Hit_L", this, &CPlayer::Hit_LStay, &CPlayer::Hit_LStart, &CPlayer::Hit_LEnd);
	PlayerFSM.CreateState("Hit_H", this, &CPlayer::Hit_HStay, &CPlayer::Hit_HStart, &CPlayer::Hit_HEnd);
	PlayerFSM.CreateState("Appear", this, &CPlayer::AppearStay, &CPlayer::AppearStart, &CPlayer::AppearEnd);
	PlayerFSM.CreateState("Combat", this, &CPlayer::CombatStay, &CPlayer::CombatStart, &CPlayer::CombatEnd);
	PlayerFSM.CreateState("UltraSkill", this, &CPlayer::UltraSkillStay, &CPlayer::UltraSkillStart, &CPlayer::UltraSkillEnd);
	PlayerFSM.CreateState("Evade", this, &CPlayer::EvadeStay, &CPlayer::EvadeStart, &CPlayer::EvadeEnd);
	PlayerFSM.CreateState("SwitchIn", this, &CPlayer::SwitchInStay, &CPlayer::SwitchInStart, &CPlayer::SwitchInEnd);
	PlayerFSM.CreateState("SwitchOut", this, &CPlayer::SwitchOutStay, &CPlayer::SwitchOutStart, &CPlayer::SwitchOutEnd);
	PlayerFSM.CreateState("Victory", this, &CPlayer::VictoryStay, &CPlayer::VictoryStart, &CPlayer::VictoryEnd);
	PlayerFSM.CreateState("VictoryIdle", this, &CPlayer::VictoryIdleStay, &CPlayer::VictoryIdleStart, &CPlayer::VictoryIdleEnd);
	PlayerFSM.ChangeState("Idle");

	m_Body->AddCollisionCallbackFunction<CPlayer>(Collision_State::Begin, this,
		&CPlayer::CollisionBegin);
	m_Body->AddCollisionCallbackFunction<CPlayer>(Collision_State::Middle, this,
		&CPlayer::CollisionMiddle);
	m_Body->AddCollisionCallbackFunction<CPlayer>(Collision_State::End, this,
		&CPlayer::CollisionEnd);

	m_EvadeBody->AddCollisionCallbackFunction<CPlayer>(Collision_State::Begin, this,
		&CPlayer::CollisionEvadeBegin);
	m_EvadeBody->AddCollisionCallbackFunction<CPlayer>(Collision_State::Middle, this,
		&CPlayer::CollisionEvadeMiddle);
	m_EvadeBody->AddCollisionCallbackFunction<CPlayer>(Collision_State::End, this,
		&CPlayer::CollisionEvadeEnd);

	return true;

}

void CPlayer::Update(float DeltaTime)
{
	CClientObject::Update(DeltaTime);
	m_PlayerDeltaTime = DeltaTime;
	m_DeltaTime = DeltaTime;
	if (m_UltraSkillAttack)
	{
		m_UltraSkillTime += DeltaTime;
		if (m_UltraSkillTimeMax <= m_UltraSkillTime)
		{
			m_UltraSkillTime = 0.f;
			m_UltraSkillAttack = false;
			if (m_UltraSkillEffect1)
			{
				UltraSkillEffect1End();
			}
			if (m_UltraSkillEffect2)
			{
				UltraSkillEffect2End();
			}
			m_UltraSkillEffect1 = false;
			m_UltraSkillEffect2 = false; 
			UltraSkillEffect2End();
		}
	}
	if(m_FSMEnable)
		PlayerFSM.Update();
	if (m_Target)
	{
		if (!m_Target->IsActive())
		{
			m_Target = nullptr;
		}
		else if (m_Target->GetHp() <= 0.f)
		{
			m_Target = nullptr;
		}
	}
	auto iter = m_KeyPush.begin();
	auto iterEnd = m_KeyPush.end();

	for (; iter != iterEnd;)
	{
		if ((*iter) == PlayerDir::Left)
		{
			if (!m_KeyLeftMove)
			{
				iter = m_KeyPush.erase(iter);
				iterEnd = m_KeyPush.end();
				continue;
			}
		}
		if ((*iter) == PlayerDir::Right)
		{
			if (!m_KeyRightMove)
			{
				iter = m_KeyPush.erase(iter);
				iterEnd = m_KeyPush.end();
				continue;
			}

		}
		if ((*iter) == PlayerDir::Front)
		{
			if (!m_KeyMoveFront)
			{
				iter = m_KeyPush.erase(iter);
				iterEnd = m_KeyPush.end();
				continue;
			}
		}
		if ((*iter) == PlayerDir::Back)
		{
			if (!m_KeyMoveBack)
			{
				iter = m_KeyPush.erase(iter);
				iterEnd = m_KeyPush.end();
				continue;
			}
		}
		++iter;
	}
	size_t Size = m_KeyPush.size();
	if (Size!=0)
	{
		m_Move = true;
		float Angle=0.f;
		if (Size >= 2)
		{
			PlayerDir FirstCheckNum = m_KeyPush[Size - 1];
			PlayerDir LastCheckNum = m_KeyPush[Size - 2];
			//우선순위높은것기준으로 움직이기
			if ((FirstCheckNum == PlayerDir::Left && LastCheckNum==PlayerDir::Right) ||
				(FirstCheckNum == PlayerDir::Right && LastCheckNum == PlayerDir::Left) ||
				(FirstCheckNum == PlayerDir::Front && LastCheckNum == PlayerDir::Back)|| 
				(FirstCheckNum == PlayerDir::Back && LastCheckNum == PlayerDir::Front))
			{
				Angle = GetDirAngle(FirstCheckNum);
			}
			else //대각선
			{
				if ((FirstCheckNum == PlayerDir::Back && LastCheckNum == PlayerDir::Right) ||
					(FirstCheckNum == PlayerDir::Right && LastCheckNum == PlayerDir::Back))
				{
					Angle = 315.f;
				}
				else
				{
					Angle = GetDirAngle(FirstCheckNum);
					float LastAngle = GetDirAngle(LastCheckNum);
					Angle += LastAngle;
					Angle *= 0.5f;
				}
			}
		}
		else
		{
			PlayerDir FirstCheckNum = m_KeyPush[Size - 1];
			Angle = GetDirAngle(FirstCheckNum);
		}
#pragma region ChangeState_Move
		if (PlayerState::Idle == m_State
			|| PlayerState::Combat == m_State
			|| PlayerState::CombatToIdle == m_State
			|| PlayerState::Move == m_State)
		{
			PlayerFSM.ChangeState("Move");

			CCamera* Camera = m_pScene->GetCameraManager()->GetCurrentCamera();
			Vector3 Rotation = Camera->GetWorldRotation();
			m_Root->SetWorldRotationY(Rotation.y + Angle);
			m_MoveDirAngle = Angle;
		}
#pragma endregion
	}

}

void CPlayer::PostUpdate(float DeltaTime)
{
	CClientObject::PostUpdate(DeltaTime);
}

void CPlayer::Collision(float DeltaTime)
{
	CClientObject::Collision(DeltaTime);
}

void CPlayer::Render(float DeltaTime)
{
	CClientObject::Render(DeltaTime);
}

CPlayer* CPlayer::Clone()
{
	return new CPlayer(*this);
}


void CPlayer::MoveFront(float Time)
{
	if (!IsEnable())
		return;


	if (PlayerState::Idle== m_State
		|| PlayerState::Combat == m_State
		|| PlayerState::CombatToIdle == m_State
		|| PlayerState::Move == m_State)
	{
		m_KeyMoveFront = true;
		m_KeyPush.push_back(PlayerDir::Front);
	}
}

void CPlayer::MoveBack(float Time)
{
	if (!IsEnable())
		return;
	if (PlayerState::Idle == m_State
		|| PlayerState::Combat == m_State
		|| PlayerState::CombatToIdle == m_State
		|| PlayerState::Move == m_State)
	{
		m_KeyMoveBack = true;
		m_KeyPush.push_back(PlayerDir::Back);
	}
}

void CPlayer::LeftMove(float Time)
{
	if (!IsEnable())
		return;
	if (PlayerState::Idle == m_State
		|| PlayerState::Combat == m_State
		|| PlayerState::CombatToIdle == m_State
		|| PlayerState::Move == m_State)
	{
		m_KeyLeftMove = true;
		m_KeyPush.push_back(PlayerDir::Left);
	}
}

void CPlayer::RightMove(float Time)
{
	if (!IsEnable())
		return;
	if (PlayerState::Idle == m_State
		|| PlayerState::Combat == m_State
		|| PlayerState::CombatToIdle == m_State
		|| PlayerState::Move == m_State)
	{
		m_KeyRightMove = true;
		m_KeyPush.push_back(PlayerDir::Right);
	}
}

void CPlayer::ReleaseMoveFront(float Time)
{
	m_KeyMoveFront = false;
}

void CPlayer::ReleaseMoveBack(float Time)
{
	m_KeyMoveBack = false;
}

void CPlayer::ReleaseLeftMove(float Time)
{
	m_KeyLeftMove = false;
}

void CPlayer::ReleaseRightMove(float Time)
{
	m_KeyRightMove = false;
}


void CPlayer::Attack(float Time)
{
#pragma region CanAttack?

	if (!IsEnable())
		return;
	if (PlayerState::Die == m_State
		|| PlayerState::Evade == m_State
		|| PlayerState::Failure == m_State
		|| PlayerState::Hit_H == m_State
		|| PlayerState::Hit_L == m_State
		|| PlayerState::Win == m_State)
		return;
#pragma endregion
	m_AttackClick = true;
	m_Target = CStageManager::GetInst()->GetMonsterTarget(GetWorldPos());
	if (m_Target)
	{
		Vector3	Dir = m_Target->GetWorldPos() - GetWorldPos();
		Dir.y = 0.f;
		Dir.Normalize();
		Vector3 v1 = Dir;
		Vector3 v2 = Vector3(0, 0, -1);
		v1.Normalize();
		v2.Normalize();
		float   Dot = v1.Dot(v2);
		float Angle = RadianToDegree(acosf(Dot));
		if (m_Target->GetWorldPos().x > GetWorldPos().x)
			Angle = 360.f - Angle;
		SetWorldRotationY(Angle);
	}
	if (PlayerState::Attack == m_State)
	{
	}
	else
	{
		PlayerFSM.ChangeState("Attack");
	}
}

void CPlayer::UltraSkill(float Time)
{
	if (!IsEnable())
		return;



	if (PlayerState::Idle == m_State 
		|| PlayerState::Combat== m_State
		|| PlayerState::Move == m_State )
	{
		PlayerFSM.ChangeState("UltraSkill");
	}
}

void CPlayer::Evade(float Time)
{
	if (!IsEnable())
		return;
	if (PlayerState::Idle == m_State
		|| PlayerState::Combat == m_State
		|| PlayerState::CombatToIdle == m_State
		|| PlayerState::Move == m_State)
	{
		PlayerFSM.ChangeState("Evade");
	}

}

void CPlayer::UltraSkillAttack()
{
}



void CPlayer::IdleStart()
{
	if (PlayerState::Move == m_State)
	{
		m_Animation->ChangeAnimType(AnimType::MoveToIdle);
	}
	else if (PlayerState::Combat == m_State)
	{
		m_Animation->ChangeAnimType(AnimType::CombatIdle);
	}
	else 
	{
		m_Animation->ChangeAnimType(AnimType::Idle);
	}
#pragma region AttackComboClear
	m_AttackCombo = 0;
	m_AttackComboPlay = false;
	m_State = PlayerState::Idle;

#pragma endregion
}

void CPlayer::IdleStay()
{
	//위 애니메이션동작끝났으면 Idle로 동작
	if (m_Animation->IsEndNextFrame())
	{
		m_Animation->ChangeAnimType(AnimType::Idle);
	}
}

void CPlayer::IdleEnd()
{
}

void CPlayer::AttackStart()
{
	if (m_UltraSkillAttack)
	{
		UltraSkillAttack();
	}
	else
	{
		if (PlayerState::Combat == m_State)
		{
			m_Animation->ChangeAnimType(AnimType::Attack1Combat);
		}
		else
		{
			m_Animation->ChangeAnimType(AnimType::Attack1);
		}
	}
	m_Move = false;
	m_State = PlayerState::Attack;
	m_AttackClick = false;
}

void CPlayer::AttackStay()
{
#pragma region UltraSkillAttack
	if (m_UltraSkillAttack)
	{
		if (m_AttackClick)
		{
			UltraSkillAttack();
			m_AttackClick = false;
		}
	}
#pragma endregion
	else if (m_AttackComboPlay)
	{
		if (m_AttackClick)
		{
			if (m_AttackChargeCombo)
			{
				m_Animation->ChangeAnimType(AnimType::AttackCharge);
				m_AttackClick = false;
				m_AttackCombo = 10;
				m_AttackChargeCombo = false;
			}
			else
			{
				switch (m_AttackCombo)
				{
				case 0:
					m_Animation->ChangeAnimType(AnimType::Attack1Combat);
					break;
				case 1:
					m_Animation->ChangeAnimType(AnimType::Attack2);
					break;
#pragma region AttackComboAnimation...
				case 2:
					m_Animation->ChangeAnimType(AnimType::Attack3);
					break;
				case 3:
					m_Animation->ChangeAnimType(AnimType::Attack4);
					break;
				case 4:
					m_Animation->ChangeAnimType(AnimType::Attack5);
					break;
#pragma endregion
				}
				m_AttackClick = false;
				m_AttackComboPlay = false;
			}
		}
	}
	if (m_Animation->IsEndNextFrame())
	{
		m_AttackClick = false;
		PlayerFSM.ChangeState("Combat");
		m_AttackComboPlay = false;
		m_AttackChargeCombo = false;
		m_AttackCombo = 0;
	}
}

void CPlayer::AttackEnd()
{
}

void CPlayer::MoveStart()
{
	if (PlayerState::Combat == m_State)
	{
		m_Animation->ChangeAnimType(AnimType::CombatMove);
	}
	else
	{
		m_Animation->ChangeAnimType(AnimType::Move);
	}
	m_State = PlayerState::Move;
}

void CPlayer::MoveStay()
{
	if (!m_Move)
	{
		PlayerFSM.ChangeState("Idle");
	}
	else
	{

	}
	m_Move = false;
}

void CPlayer::MoveEnd()
{
}

void CPlayer::Hit_LStart()
{
	m_Animation->ChangeAnimType(AnimType::Hit_L);
	m_State = PlayerState::Hit_L;

}

void CPlayer::Hit_LStay()
{
	if (m_Animation->IsEndNextFrame())
	{
		m_Animation->ChangeAnimType(AnimType::Idle);
		m_State = PlayerState::Idle;
	}
}

void CPlayer::Hit_LEnd()
{
}

void CPlayer::Hit_HStart()
{
	m_Animation->ChangeAnimType(AnimType::Hit_H);
	m_State = PlayerState::Hit_H;
}

void CPlayer::Hit_HStay()
{
	if (m_Animation->IsEndNextFrame())
	{
		m_Animation->ChangeAnimType(AnimType::Idle);
	}
}

void CPlayer::Hit_HEnd()
{
}


void CPlayer::AppearStart()
{
	m_Animation->ChangeAnimType(AnimType::Appear);
	m_State = PlayerState::Appear;
}

void CPlayer::AppearStay()
{
	if (m_Animation->IsEndNextFrame())
	{
		//시작
		PlayerFSM.ChangeState("Idle");                                      
		m_State = PlayerState::Idle;
	}
}

void CPlayer::AppearEnd()
{
}

void CPlayer::CombatStart()
{
	m_Animation->ChangeAnimType(AnimType::Combat);
	m_State = PlayerState::Combat;
	m_CombatDelay = 0.f;
}

void CPlayer::CombatStay()
{
	m_CombatDelay += m_DeltaTime;
	if (m_CombatDelay >= m_CombatDelayMax)
	{
		PlayerFSM.ChangeState("Idle");
	}
}

void CPlayer::CombatEnd()
{
}

void CPlayer::UltraSkillStart()
{
	m_Animation->ChangeAnimType(AnimType::UltraSkill);
	m_State = PlayerState::UltraSkill;
	m_CombatDelay = 0.f;
}

void CPlayer::UltraSkillStay()
{
	if (m_Animation->IsEndNextFrame())
	{
		PlayerFSM.ChangeState("Idle");
		m_State = PlayerState::Idle;
	}
}

void CPlayer::UltraSkillEnd()
{
}

void CPlayer::EvadeStart()
{
	if (m_State == PlayerState::Move)
	{
		m_Animation->ChangeAnimType(AnimType::EvadeForward);
	}
	else
	{
		m_Animation->ChangeAnimType(AnimType::EvadeBackward);
	}
	m_State = PlayerState::Evade;
	m_Body->Enable(false);
}

void CPlayer::EvadeStay()
{
	if (m_Animation->IsEndNextFrame())
	{
		PlayerFSM.ChangeState("Combat");
		m_State = PlayerState::Combat;
		m_Body->Enable(true);
	}
}

void CPlayer::EvadeEnd()
{
}

void CPlayer::SwitchInStart()
{
	m_Animation->ChangeAnimType(AnimType::SwitchIn);
	m_State = PlayerState::SwitchIn;
}
void CPlayer::SwitchInStay()
{
	if (m_Animation->IsSequenceEndFrame())
	{
		//시작
		PlayerFSM.ChangeState("Idle");
		m_State = PlayerState::Idle;
	}
}

void CPlayer::SwitchInEnd()
{
}

void CPlayer::SwitchOutStart()
{
	m_Animation->ChangeAnimType(AnimType::SwitchOut);
	m_State = PlayerState::SwitchOut;
}

void CPlayer::SwitchOutStay()
{
	if (m_Animation->IsSequenceEndFrame())
	{
		//여기서 플레이어 체인지가됨
	}
}

void CPlayer::SwitchOutEnd()
{
}

void CPlayer::VictoryStart()
{
	m_Animation->ChangeAnimType(AnimType::Victory);
	m_State = PlayerState::Victory;
}

void CPlayer::VictoryStay()
{
	if (m_Animation->IsEndNextFrame())
	{
		PlayerFSM.ChangeState("VictoryIdle");
	}
}

void CPlayer::VictoryEnd()
{
}

void CPlayer::VictoryIdleStart()
{
	m_Animation->ChangeAnimType(AnimType::VictoryIdle);
	m_State = PlayerState::VictoryIdle;
}

void CPlayer::VictoryIdleStay()
{
}

void CPlayer::VictoryIdleEnd()
{
}

void CPlayer::AnimationNotify(const std::string& Name)
{
#pragma region AttackNotify
	if (Name == "AttackCombo")
	{
		m_AttackCombo++;
		m_AttackComboPlay = true;
	}
	else if (Name == "AttackCharge")
	{
		m_AttackComboPlay = true;
		m_AttackChargeCombo = true;
	}
#pragma endregion
	else if (Name == "Sound")
	{
		m_Animation->SoundPlay();
	}
#pragma region ...
	else if (Name == "ChangeIdle")
	{
		PlayerFSM.ChangeState("Idle");
	}

	else if (Name == "RunSound")
	{
		m_pScene->GetResource()->FindSound3D("PlayerRunSound")->Play3D(GetWorldPos());
	}
#pragma endregion
}

void CPlayer::UltraSkillEffect1()
{
}

void CPlayer::UltraSkillEffect2()
{
}

void CPlayer::UltraSkillEffect1End()
{
}

void CPlayer::UltraSkillEffect2End()
{
}

void CPlayer::PlayerWait()
{
	Enable(false);
	m_Mesh->Enable(false);
}

void CPlayer::PlayerAppear()
{
	Enable(true);
	m_Mesh->Enable(true);
	PlayerFSM.ChangeState("Appear");
}

void CPlayer::PlayerAppear_Attack()
{
}

void CPlayer::Change1(float Time)
{
	CPlayer* pPlayer = CPublicData::GetInst()->GetCurPlayer();
	CPlayer* ChangePlayer = CPublicData::GetInst()->GetPlayer(0);
	if (pPlayer == ChangePlayer)
		return;
	pPlayer->PlayerWait();
	ChangePlayer->PlayerAppear();
	ChangePlayer->SetWorldPos(pPlayer->GetWorldPos());
	ChangePlayer->SetWorldRotation(pPlayer->GetWorldRotation());
	
	CPublicData::GetInst()->SetCurPlayer(ChangePlayer);
}

void CPlayer::Change2(float Time)
{
	CPlayer* pPlayer = CPublicData::GetInst()->GetCurPlayer();
	CPlayer* ChangePlayer = CPublicData::GetInst()->GetPlayer(1);
	if (pPlayer == ChangePlayer)
		return;
	pPlayer->PlayerWait();
	ChangePlayer->PlayerAppear();
	ChangePlayer->SetWorldPos(pPlayer->GetWorldPos());
	ChangePlayer->SetWorldRotation(pPlayer->GetWorldRotation());
	CPublicData::GetInst()->SetCurPlayer(ChangePlayer);
}

void CPlayer::CollisionBegin(const HitResult& result, CCollider* Collider)
{

	if (result.DestCollider->GetProfile()->Name == "MonsterAttack")	
	{
		
		CAttackObject* obj = dynamic_cast<CAttackObject*>(result.DestObject);
		if (obj == nullptr)
		{
			return;
		}
		//몬스터의 정보를 가져와서 공격력만큼 체력을 뺀다.
		PlayerFSM.ChangeState("Hit_L");
		int Damage = obj->GetDamage();
		m_PlayerStatus->HP -= Damage;
		if (m_PlayerStatus->HP <= 0)
		{
			CPlayer* NextPlayer=CPublicData::GetInst()->GetNextPlayer();
			if (nullptr == NextPlayer)
			{
				//남은 플레이어가 없다. 즉 게임오버
				CStageManager::GetInst()->SetFail(true);
			}
			else
			{
				CPlayer* pPlayer = CPublicData::GetInst()->GetCurPlayer();
				//설마 같을리는..
				if (pPlayer == NextPlayer)
					return;
				pPlayer->PlayerWait();
				NextPlayer->PlayerAppear();
				NextPlayer->SetWorldPos(pPlayer->GetWorldPos());
				NextPlayer->SetWorldRotation(pPlayer->GetWorldRotation());
				CPublicData::GetInst()->SetCurPlayer(NextPlayer);
			}
		}
	}
	
}

void CPlayer::CollisionMiddle(const HitResult& result, CCollider* Collider)
{
	// 위와 같음
	/*if (result.DestCollider->GetProfile()->Channel == Collision_Channel::MapCollision)
	{
		Vector3 Velocity = m_Root->GetVelocity();
		m_Root->AddRelativePos(Vector3(-Velocity.x, -Velocity.y, -Velocity.z));
	}*/
}

void CPlayer::CollisionEnd(const HitResult& result, CCollider* Collider)
{
}

void CPlayer::CollisionEvadeBegin(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Name == "MonsterAttack")
	{
		//몬스터들의 속도 저하
		CStageManager::GetInst()->SetMapMeshDarkness(true);
		m_pScene->GetResource()->FindSound2D("PerpectEvade")->Play();
		CStageManager::GetInst()->WorldSpeed(0.5f, 3.f);
		CPlayerAttCol* CollisionPlayerAtt = m_pScene->SpawnObject<CPlayerAttCol>("PlayerAttRight");
		CollisionPlayerAtt->SetDamage(10);
		CollisionPlayerAtt->SetDamageMax(m_PlayerStatus->DamageMax);
		CollisionPlayerAtt->SetWorldPos	(result.DestObject->GetWorldPos());
		CollisionPlayerAtt->SetBox3DLength(0.1f, 0.1f, 0.1f);
	}
}

void CPlayer::CollisionEvadeMiddle(const HitResult& result, CCollider* Collider)
{
}

void CPlayer::CollisionEvadeEnd(const HitResult& result, CCollider* Collider)
{
}

void CPlayer::StartAnimation()
{
	PlayerFSM.ChangeState("Appear");
}

void CPlayer::CameraAction()
{
	PlayerFSM.ChangeState("Victory");
	SetWorldRotation(0.f, 0.f, 0.f);
}

float CPlayer::GetDirAngle(PlayerDir InputNum)
{
	switch (InputNum)
	{
	case PlayerDir::Left:
		return 90.f;
		break;
	case PlayerDir::Right:
		return 270.f;
		break;
	case PlayerDir::Front:
		return 180.f;
		break;
	case PlayerDir::Back:
		return 0.f;
		break;
	}
	return 0.f;
}
