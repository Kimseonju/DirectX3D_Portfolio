#include "SakuraPlayer.h"
#include "Resource/BoneSocket.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "../PublicData.h"
#include "PlayerAttCol.h"
#include "../StageManager.h"
#include "PoseCopy.h"
CSakuraPlayer::CSakuraPlayer():
	m_PoseCopy(false),
	m_PoseCopyTimer(0.f)
{
	m_ClientClassType = ClientClassType::Sakura;
}

CSakuraPlayer::CSakuraPlayer(const CSakuraPlayer& obj) :
	CPlayer(obj)
{
	m_PoseCopy = obj.m_PoseCopy;
	m_PoseCopyTimer = obj.m_PoseCopyTimer;
}

CSakuraPlayer::~CSakuraPlayer()
{
}

void CSakuraPlayer::Start()
{
	CPlayer::Start();
}

bool CSakuraPlayer::Init()
{
	if (!CPlayer::Init())
		return false;
	m_PlayerStatus = CPublicData::GetInst()->FindPlayerData("Sakura");
	// ClientEvade
	//회피상태는 Hit일때는 발생하지않고 공격할때도 발생하지않는다.
	//단           


	m_TrailComponent = CreateSceneComponent<CTrailComponent>("TrailComponent");
	m_TrailComponentCharge = CreateSceneComponent<CTrailComponent>("TrailComponentCharge");

	CMaterial* Mtrl = m_pScene->GetResource()->FindMaterial("SakuraTrail");
	m_TrailComponent->AddMaterial(Mtrl);
	m_TrailComponent->SetSize(0.5f);
	m_TrailComponent->Enable(true);
	m_TrailComponent->SetTrailUpdate(false);
	m_Mesh->SetMesh("SakuraMesh");
	for (int i = 0; i < m_Mesh->GetMaterialCount(); ++i)
	{
		m_Mesh->GetMaterial(i)->SetReceiveDecal(false);
	}

	Mtrl = m_pScene->GetResource()->FindMaterial("SakuraChargeTrail");
	m_TrailComponentCharge->AddMaterial(Mtrl);
	m_TrailComponentCharge->SetSize(0.5f);
	m_TrailComponentCharge->Enable(true);
	m_TrailComponentCharge->SetTrailUpdate(false);
	for (int i = 0; i < m_Mesh->GetMaterialCount(); ++i)
	{
		m_Mesh->GetMaterial(i)->SetReceiveDecal(false);
	}


	m_Animation->SetRootBoneIndex("Bip001 Pelvis");

#pragma region Weapon
	CSkeleton* Skel = m_Animation->GetSkeleton();
	Skel->AddSocket("Bip001 Prop1", "Weapon");
	CBoneSocket* WeaponSocket = Skel->GetSocket("Weapon");
	WeaponSocket->SetOffsetRotation(0.f, -10.f, 0.f);

	m_WeaponMesh->SetMesh("Katana_1");
	m_WeaponMesh->SetWorldScale(1.f, 1.f, 1.f);
	m_Mesh->AddChild(m_WeaponMesh, "Weapon");
	m_Mesh->AddChild(m_WeaponMesh2, "Weapon");

	Skel->AddSocket("Bip001 Prop1", "WeaponTrail");
	m_Mesh->AddChild(m_TrailComponent, "WeaponTrail");
	m_Mesh->AddChild(m_TrailComponentCharge, "WeaponTrail");
	CBoneSocket* WeaponTrailSocket = Skel->GetSocket("WeaponTrail");
	WeaponTrailSocket->SetOffset(0.f, 0.6f, 0.f);
	WeaponTrailSocket->SetOffsetRotation(0.f, 0.f, 90.f);

#pragma endregion

	//Anim
	{
		//m_Animation->AddAnimationSequence_Player()
		//m_Animation->AddAnimationSequence("Avatar_Yae_Sakura_Ani_Run", 1.f, true, 2);
		m_Animation->AddAnimationSequence_Player("Avatar_Yae_Sakura_Ani_Idle", AnimType::Idle, 60);
		m_Animation->AddAnimationSequence_Player("Avatar_Yae_Sakura_Ani_Run", AnimType::Move, 60, true, 2, false, true, false, 1);
		m_Animation->AddAnimationSequence_Player("Avatar_Yae_Sakura_Ani_RunStopLeft", AnimType::MoveToIdle, 60);
		m_Animation->AddAnimationSequence_Player("Avatar_Sakura_C1_YS_Appear", AnimType::Appear, 60, false, 8);
		m_Animation->AddAnimationSequence_Player("Avatar_Yae_Sakura_Ani_Attack_01_Combat", AnimType::Attack1Combat, 60, true, 0);
		m_Animation->AddAnimationSequence_Player("Avatar_Yae_Sakura_Ani_Attack_01_StandBy", AnimType::Attack1, 60, true, 0);
		m_Animation->AddAnimationSequence_Player("Avatar_Yae_Sakura_Ani_Attack_02", AnimType::Attack2, 60, true, 0);
		m_Animation->AddAnimationSequence_Player("Avatar_Yae_Sakura_Ani_Attack_03", AnimType::Attack3, 60, true, 0);
		m_Animation->AddAnimationSequence_Player("Avatar_Yae_Sakura_Ani_Attack_04", AnimType::Attack4, 60, true, 0);
		m_Animation->AddAnimationSequence_Player("Avatar_Yae_Sakura_Ani_Charge_01_C3Ult", AnimType::Attack5, 60, true, 0);
		m_Animation->AddAnimationSequence_Player("Avatar_Yae_Sakura_Ani_Charge_01_C3Ult", AnimType::AttackCharge, 60, true);
		m_Animation->AddAnimationSequence_Player("Avatar_Yae_Sakura_Ani_Charge_01_Quick", AnimType::UltraAttack, 60, true);
		m_Animation->AddAnimationSequence_Player("Avatar_Yae_Sakura_Ani_Combat", AnimType::Combat, 60, true);
		m_Animation->AddAnimationSequence_Player("Avatar_Yae_sakura_Ani_Die", AnimType::Die, 60, true);
		m_Animation->AddAnimationSequence_Player("Avatar_Yae_Sakura_Ani_Failure_01", AnimType::Failure, 60, true);
		//m_Animation->AddAnimationSequence_Player("Avatar_Yae_Sakura_Ani_Failure_Loop", 1.f);
		m_Animation->AddAnimationSequence_Player("Avatar_Yae_Sakura_Ani_CombatToStandBy", AnimType::CombatIdle, 60, true);

		m_Animation->AddAnimationSequence_Player("Avatar_Yae_Sakura_Ani_Hit_H", AnimType::Hit_H, 60, true);
		m_Animation->AddAnimationSequence_Player("Avatar_Yae_Sakura_Ani_Hit_L", AnimType::Hit_L, 60, true);
		m_Animation->AddAnimationSequence_Player("Avatar_Yae_Sakura_Ani_Skill_01", AnimType::Skill1, 60, true);
		m_Animation->AddAnimationSequence_Player("Avatar_Yae_sakura_Ani_win", AnimType::Victory, 60, false);
		m_Animation->AddAnimationSequence_Player("Avatar_Yae_sakura_Ani_win_idle", AnimType::VictoryIdle, 60, false);
		m_Animation->AddAnimationSequence_Player("Avatar_Yae_sakura_Ani_Skill_Ultra_01", AnimType::UltraSkill, 60, true);
		m_Animation->AddAnimationSequence_Player("Avatar_Yae_Sakura_EvadeBackward", AnimType::EvadeBackward, 60, true);
		m_Animation->AddAnimationSequence_Player("Avatar_Yae_Sakura_EvadeForward", AnimType::EvadeForward, 60, true);
		m_Animation->AddAnimationSequence_Player("Avatar_Yae_Sakura_Ani_SwitchIn", AnimType::SwitchIn, 60, true, 6);
		m_Animation->AddAnimationSequence_Player("Avatar_Yae_Sakura_Ani_SwitchRole", AnimType::SwitchOut, 60, true, 6);


		m_Animation->AddSound("SakuraAttackCombo1", AnimType::Attack1Combat);
		m_Animation->AddSound("SakuraAttackCombo1", AnimType::Attack1);
		m_Animation->AddSound("SakuraAttackCombo2", AnimType::Attack2);
		m_Animation->AddSound("SakuraAttackCombo3", AnimType::Attack3);
		m_Animation->AddSound("SakuraAttackCombo4", AnimType::Attack4);
		m_Animation->AddSound("SakuraAttackCombo5", AnimType::Attack5);
		m_Animation->AddSound("SakuraCombatToIdle", AnimType::CombatIdle);
		m_Animation->AddSound("SakuraCombatToIdle", AnimType::UltraSkill);

		m_Animation->AddSound("SakuraEvade", AnimType::EvadeBackward);
		m_Animation->AddSound("SakuraEvade", AnimType::EvadeForward);
		m_Animation->AddSound("SakuraUltraSkill", AnimType::UltraSkill);
		m_Animation->AddSound("SakuraAttackCombo5", AnimType::AttackCharge);
		m_Animation->AddSound("SakuraAttackCombo5", AnimType::UltraAttack);
		m_Animation->AddSound("AppearEffectSound", AnimType::Appear);

		m_Animation->AddSoundCV("SakuraAttackCV1", AnimType::Attack1Combat);
		m_Animation->AddSoundCV("SakuraAttackCV1", AnimType::Attack1);
		m_Animation->AddSoundCV("SakuraAttackCV2", AnimType::Attack2);
		m_Animation->AddSoundCV("SakuraAttackCV3", AnimType::Attack3);
		m_Animation->AddSoundCV("SakuraAttackCV4", AnimType::Attack4);
		m_Animation->AddSoundCV("SakuraAttackCV5", AnimType::Attack5);
		m_Animation->AddSoundCV("SakuraAttackChargeCV", AnimType::AttackCharge);
		m_Animation->AddSoundCV("SakuraAppearCV", AnimType::Appear);
		m_Animation->AddSoundCV("SakuraUltraSkillCV", AnimType::UltraSkill);

		m_Animation->AddSoundCV("SakuraUltraSkillCV", AnimType::UltraSkill);

		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_sakura_Ani_Skill_Ultra_01", "UltraSkill", 22);
		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_sakura_Ani_Skill_Ultra_01", "UltraSkillEffect1", 22);
		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_sakura_Ani_Skill_Ultra_01", "UltraSkillEffect2", 90);
		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_Sakura_Ani_Attack_01_Combat", "AttackCombo", 20);
		//m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_Sakura_Ani_Attack_01_Combat", "AttackCharge", 35);
		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_Sakura_Ani_Attack_01_StandBy", "AttackCombo", 20);
		//m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_Sakura_Ani_Attack_01_StandBy", "AttackCharge", 35);
		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_Sakura_Ani_Attack_02", "AttackCombo", 30);
		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_Sakura_Ani_Attack_03", "AttackCombo", 30);
		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_Sakura_Ani_Attack_04", "AttackCombo", 40);
		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_Sakura_Ani_Charge_01_C3Ult", "AttackReset", 50);
		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_Sakura_Ani_Charge_01_Quick", "AttackReset", 20);
		  
		  
		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_Sakura_Ani_Attack_01_Combat", "Sound", 5);
		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_Sakura_Ani_Attack_01_StandBy", "Sound", 5);
		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_sakura_Ani_Skill_Ultra_01", "Sound", 0);
		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_Sakura_Ani_Attack_02", "Sound", 5);
		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_Sakura_Ani_Attack_03", "Sound", 5);
		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_Sakura_Ani_Attack_04", "Sound", 5);
		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_Sakura_Ani_Charge_01_C3Ult", "Sound", 22);
		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_Sakura_Ani_Charge_01_Quick", "Sound", 22);
		  
		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_Sakura_Ani_CombatToStandBy", "Sound", 0);
		  
		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Sakura_C1_YS_Appear", "Sound", 5);


		//트레일 노티파이만들기
		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_Sakura_Ani_Attack_01_Combat", "TrailStart", 7);
		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_Sakura_Ani_Attack_01_Combat", "TrailEnd", 12);
		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_Sakura_Ani_Attack_01_StandBy", "TrailStart", 7);
		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_Sakura_Ani_Attack_01_StandBy", "TrailEnd", 16);
		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_Sakura_Ani_Attack_02", "TrailStart", 5);
		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_Sakura_Ani_Attack_02", "TrailEnd", 12);
		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_Sakura_Ani_Attack_02", "TrailStart", 20);
		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_Sakura_Ani_Attack_02", "TrailEnd", 24);

		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_Sakura_Ani_Attack_03", "TrailStart", 20);
		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_Sakura_Ani_Attack_03", "TrailEnd", 31);

		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_Sakura_Ani_Attack_04", "TrailStart", 8);
		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_Sakura_Ani_Attack_04", "TrailEnd", 18);
		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_Sakura_Ani_Attack_04", "TrailStart", 20);
		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_Sakura_Ani_Attack_04", "TrailEnd", 25);
		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_Sakura_Ani_Attack_04", "TrailStart", 30);
		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_Sakura_Ani_Attack_04", "TrailEnd", 40);

		//차지공격이펙트
		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_Sakura_Ani_Charge_01_C3Ult", "Charge_01_C3Ult", 45);
		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_Sakura_Ani_Charge_01_Quick", "Charge_01_C3Ult", 20);


		//피격이나 기타등등시 트레일 종료(모든 애니메이션 1프레임에서 트레일끄게만들자)
		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_Sakura_Ani_Hit_H", "TrailEnd", 0);
		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_Sakura_Ani_Hit_L", "TrailEnd", 0);

		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_Sakura_Ani_Charge_01_C3Ult", "TrailChargeStart",40);
		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_Sakura_Ani_Charge_01_C3Ult", "TrailChargeEnd", 60);
		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_Sakura_Ani_Charge_01_Quick", "TrailChargeStart", 8);
		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_Sakura_Ani_Charge_01_Quick", "TrailChargeEnd", 16);

		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_Sakura_Ani_Charge_01_C3Ult", "MotionTrailStart", 38);
		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_Sakura_Ani_Charge_01_C3Ult", "MotionTrailEnd", 51);

		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_Sakura_Ani_Charge_01_Quick", "MotionTrailStart", 10);
		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_Sakura_Ani_Charge_01_Quick", "MotionTrailEnd", 15);


		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_Sakura_EvadeBackward", "MotionTrailStart", 4);
		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_Sakura_EvadeBackward", "MotionTrailEnd",24);

		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_Sakura_EvadeForward", "MotionTrailStart", 4);
		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_Sakura_EvadeForward", "MotionTrailEnd", 20);
		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_Sakura_Ani_Run", "RunSound", 16);
		m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Yae_Sakura_Ani_Run", "RunSound", 35);

	}

	return true;
}

void CSakuraPlayer::Update(float DeltaTime)
{
	CPlayer::Update(DeltaTime);
	if (m_PoseCopy)
	{
		m_PoseCopyTimer += DeltaTime;
		if (m_PoseCopyTimer >= 0.03f)
		{
			m_PoseCopyTimer -= 0.03f;
			CPoseCopy* PoseCopy = m_pScene->SpawnObject<CPoseCopy>("PoseCopy");
			PoseCopy->PoseCopy(m_Mesh, Vector3(1.f, 0.f, 1.f));
		}
	}
}

void CSakuraPlayer::PostUpdate(float DeltaTime)
{
	CPlayer::PostUpdate(DeltaTime);
}

void CSakuraPlayer::Collision(float DeltaTime)
{
	CPlayer::Collision(DeltaTime);
}

void CSakuraPlayer::Render(float DeltaTime)
{
	CPlayer::Render(DeltaTime);
}

CSakuraPlayer* CSakuraPlayer::Clone()
{
	return new CSakuraPlayer(*this);
}


void CSakuraPlayer::AnimationNotify(const std::string& Name)
{
	CPlayer::AnimationNotify(Name);

	if ("TrailStart"==Name)
	{
		m_TrailComponent->SetTrailUpdate(true);
		CPlayerAttCol* CollisionPlayerAtt = m_pScene->SpawnObject<CPlayerAttCol>("PlayerAttRight");
		CollisionPlayerAtt->SetDamage(m_PlayerStatus->Damage);
		CollisionPlayerAtt->SetDamageMax(m_PlayerStatus->DamageMax);
		CollisionPlayerAtt->SetWorldPos(GetWorldPos());
		CollisionPlayerAtt->AddWorldPos(0.f, 1.f, 0.f);
		CollisionPlayerAtt->SetBox3DLength(0.1f, 0.1f, 0.1f);
		CollisionPlayerAtt->SetWorldRotation(GetWorldRotation());
		CollisionPlayerAtt->SetType(ClientClassType::Sakura);
	}
	else if ("TrailEnd" == Name)
	{
		m_TrailComponent->SetTrailUpdate(false);
	}
	else if ("MotionTrailStart" == Name)
	{

		m_PoseCopy = true;
	}
	else if ("MotionTrailEnd" == Name)
	{
		m_PoseCopy = false;
		
	}
	if ("TrailChargeStart" == Name)
	{
		m_TrailComponentCharge->SetTrailUpdate(true);
	}
	else if ("TrailChargeEnd" == Name)
	{
		m_TrailComponentCharge->SetTrailUpdate(false);
	}
	else if ("Charge_01_C3Ult" == Name)
	{
		CPlayerAttCol* CollisionPlayerAtt = m_pScene->SpawnObject<CPlayerAttCol>("PlayerAttRight");
		CollisionPlayerAtt->SetDamage(m_PlayerStatus->Damage);
		CollisionPlayerAtt->SetDamageMax(m_PlayerStatus->DamageMax);
		CollisionPlayerAtt->SetWorldPos(GetWorldPos());
		CollisionPlayerAtt->SetBox3DLength(0.1f, 0.1f, 10.f);
		CollisionPlayerAtt->SetWorldRotation(GetWorldRotation());
		CollisionPlayerAtt->SetType(ClientClassType::Sakura);
	}
	else if ("UltraSkill" == Name)
	{
		if (!m_UltraSkillAttack)
		{
			m_UltraSkillAttack = true;
			m_UltraSkillTimeMax = 12.f;
		}
	}
	else if ("UltraSkillEffect1" == Name)
	{
		if (!m_UltraSkillEffect1)
		{
			m_UltraSkillEffect1 = true;
			UltraSkillEffect1();
		}
	}
	else if ("UltraSkillEffect2" == Name)
	{
		if (!m_UltraSkillEffect2)
		{
			m_UltraSkillEffect2 = true;
			//빌보드로 반짝거리는이펙트 ㄱ
		}
	}
}

void CSakuraPlayer::EvadeStart()
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
	m_EvadeBody->Enable(true);

}

void CSakuraPlayer::SwitchInStart()
{
	CPlayer::SwitchInStart();
	m_TrailComponent->SetTrailUpdate(false);
	m_TrailComponentCharge->SetTrailUpdate(false);
	m_PoseCopy = false;
}

void CSakuraPlayer::SwitchOutStart()
{
	CPlayer::SwitchOutStart();
	m_TrailComponent->SetTrailUpdate(false);
	m_TrailComponentCharge->SetTrailUpdate(false);
	m_PoseCopy = false;
}

void CSakuraPlayer::VictoryStart()
{
	CPlayer::VictoryStart();
	m_TrailComponent->SetTrailUpdate(false);
	m_TrailComponentCharge->SetTrailUpdate(false);
	m_PoseCopy = false;
}

void CSakuraPlayer::VictoryIdleStart()
{
	CPlayer::VictoryIdleStart();
	m_TrailComponent->SetTrailUpdate(false);
	m_TrailComponentCharge->SetTrailUpdate(false);
	m_PoseCopy = false;
}

void CSakuraPlayer::EvadeStay()
{
	if (m_Animation->IsEndNextFrame())
	{
		PlayerFSM.ChangeState("Combat");
		m_State = PlayerState::Combat;
		m_Body->Enable(true);
		m_EvadeBody->Enable(false);
	}
}

void CSakuraPlayer::EvadeEnd()
{
}

void CSakuraPlayer::UltraSkillAttack()
{
	m_Animation->ChangeAnimType(AnimType::UltraAttack);
}

void CSakuraPlayer::UltraSkillEffect1()
{
	CStageManager::GetInst()->SetMapMeshDarkness(true);
	CStageManager::GetInst()->WorldSpeed(0.5f, m_UltraSkillTimeMax);
}

void CSakuraPlayer::UltraSkillEffect2()
{
}

void CSakuraPlayer::UltraSkillEffect1End()
{
	CStageManager::GetInst()->SetMapMeshDarkness(false);
}

void CSakuraPlayer::UltraSkillEffect2End()
{
}

void CSakuraPlayer::AttackStart()
{
	CPlayer::AttackStart();
	m_TrailComponent->SetTrailUpdate(false);
	m_TrailComponentCharge->SetTrailUpdate(false);
	m_PoseCopy = false;
}

void CSakuraPlayer::MoveStart()
{
	CPlayer::MoveStart();
	m_TrailComponent->SetTrailUpdate(false);
	m_TrailComponentCharge->SetTrailUpdate(false);
	m_PoseCopy = false;
}

void CSakuraPlayer::Hit_LStart()
{
	CPlayer::Hit_LStart();
	m_TrailComponent->SetTrailUpdate(false);
	m_TrailComponentCharge->SetTrailUpdate(false);
	m_PoseCopy = false;
}

void CSakuraPlayer::Hit_HStart()
{
	CPlayer::Hit_HStart();
	m_TrailComponent->SetTrailUpdate(false);
	m_TrailComponentCharge->SetTrailUpdate(false);
	m_PoseCopy = false;
}

void CSakuraPlayer::CombatStart()
{
	CPlayer::CombatStart();
	m_TrailComponent->SetTrailUpdate(false);
	m_TrailComponentCharge->SetTrailUpdate(false);
	m_PoseCopy = false;
}

void CSakuraPlayer::UltraSkillStart()
{
	CPlayer::UltraSkillStart();
	m_TrailComponent->SetTrailUpdate(false);
	m_TrailComponentCharge->SetTrailUpdate(false);
	m_PoseCopy = false;
}
