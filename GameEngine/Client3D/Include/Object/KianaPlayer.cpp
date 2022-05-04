#include "KianaPlayer.h"
#include "Resource/BoneSocket.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "../PublicData.h"
#include "PlayerAttCol.h"
#include "KianaFire.h"
#include "HitEffect.h"
CKianaPlayer::CKianaPlayer() :
	m_IdleCount(0)
{
	m_ClientClassType = ClientClassType::Kiana;
}

CKianaPlayer::CKianaPlayer(const CKianaPlayer& obj) :
	CPlayer(obj)
{
	m_IdleCount = obj.m_IdleCount;
	m_RightGunPoint = (CSceneComponent*)FindSceneComponent("RightGunPoint");
	m_LeftGunPoint = (CSceneComponent*)FindSceneComponent("LeftGunPoint");
}

CKianaPlayer::~CKianaPlayer()
{
}

void CKianaPlayer::Start()
{
	CPlayer::Start();
}

bool CKianaPlayer::Init()
{

	if (!CPlayer::Init())
		return false;

	m_Mesh->SetMesh("KianaMesh");

	for (int i = 0; i < m_Mesh->GetMaterialCount(); ++i)
	{
		m_Mesh->GetMaterial(i)->SetReceiveDecal(false);
	}

	m_Animation->SetRootBoneIndex("Bip001 Pelvis");
	//Socket
	m_PlayerStatus = CPublicData::GetInst()->FindPlayerData("Kiana");

	CSkeleton* Skel = m_Animation->GetSkeleton();

#pragma region Weapon
	Skel->AddSocket("Bip001 Prop1", "RightGun");
	CBoneSocket* RightGunSocket = Skel->GetSocket("RightGun");
	RightGunSocket->SetOffset(0.000588f, -0.001253f, 0.009635f);
	RightGunSocket->SetOffsetRotation(-179.987701f, -3.559177f, 179.604233f);



	m_WeaponMesh->SetMesh("KianaRightPistol");
	m_WeaponMesh->SetWorldScale(1.f, 1.f, 1.f);
	m_Mesh->AddChild(m_WeaponMesh, "RightGun");

	Skel->AddSocket("Bip001 Prop2", "LeftGun");
	CBoneSocket* LeftGunSocket = Skel->GetSocket("LeftGun");
	LeftGunSocket->SetOffset(-0.000319f, 0.000428f, -0.009618f);
	LeftGunSocket->SetOffsetRotation(0.015346f, -3.546651f, 179.504333f);

	m_WeaponMesh2->SetMesh("KianaLeftPistol");
	m_WeaponMesh2->SetWorldScale(1.f, 1.f, 1.f);

	m_Mesh->AddChild(m_WeaponMesh2, "LeftGun");
#pragma endregion

#pragma region FirePoint
	m_RightGunPoint = CreateSceneComponent<CSceneComponent>("RightGunPoint");
	m_RightGunPoint->SetRelativePos(-0.132f, 0.059f, -0.0149f);
	m_RightGunPoint->SetRelativeRotation(90.051254f, -90.f, 89.893f);
	m_LeftGunPoint = CreateSceneComponent<CSceneComponent>("LeftGunPoint");
	m_RightGunPoint->SetRelativePos(0.13f, 0.059f, -0.0149f);
	m_RightGunPoint->SetRelativeRotation(0.f, -90.f, 0.f);
	m_Mesh->AddChild(m_RightGunPoint, "RightGun");
	m_Mesh->AddChild(m_LeftGunPoint, "LeftGun");

#pragma endregion



	m_CombatDelayMax = 0.f;

	//Anim
	{
		m_Animation->AddAnimationSequence_Player("Avatar_Kiana_C1_Idle_01", AnimType::Idle, 15, true, 0, true);
		m_Animation->AddAnimationSequence_Player("Avatar_Kiana_C1_RunStopRight", AnimType::MoveToIdle, 30, true);
		m_Animation->AddAnimationSequence_Player("Avatar_Kiana_C1_Run", AnimType::Move, 30, true);
		m_Animation->AddAnimationSequence_Player("Avatar_Kiana_C1_Appear", AnimType::Appear, 30, false, 12);
		m_Animation->AddAnimationSequence_Player("Avatar_Kiana_C1_Attack_Gun_01", AnimType::Attack1Combat, 30, true, 0, true, true, true);
		m_Animation->AddAnimationSequence_Player("Avatar_Kiana_C1_Attack_Gun_01", AnimType::Attack1, 30, true, 0, true, true, true);
		m_Animation->AddAnimationSequence_Player("Avatar_Kiana_C1_Attack_Gun_02", AnimType::Attack2, 30, true, 0, true, true, true);
		m_Animation->AddAnimationSequence_Player("Avatar_Kiana_C1_Attack_Gun_03", AnimType::Attack3, 30, true, 0, true, true, true);
		//얕은공격
		m_Animation->AddAnimationSequence_Player("Avatar_Kiana_C1_Attack_Gun_04_01", AnimType::Attack4, 30, true, 0, true, true, true);
		//깊공격(마지막공격)
		m_Animation->AddAnimationSequence_Player("Avatar_Kiana_C1_Attack_Gun_04_02", AnimType::AttackCharge, 30, true);

		m_Animation->AddAnimationSequence_Player("Avatar_Kiana_C1_StandBy", AnimType::Combat, 60);
		m_Animation->AddAnimationSequence_Player("Avatar_Kiana_C1_StandBy", AnimType::CombatIdle, 60);
		m_Animation->AddAnimationSequence_Player("Avatar_Kiana_C1_StandBy", AnimType::StandBy, 60);
		m_Animation->AddAnimationSequence_Player("Avatar_Kiana_C1_Die", AnimType::Die, 60, true);
		m_Animation->AddAnimationSequence_Player("Avatar_Kiana_C1_Failure_01", AnimType::Failure, 60, true);
		//m_Animation->AddAnimationSequence_Player("Avatar_Yae_Sakura_Ani_Failure_Loop", 1.f);
		m_Animation->AddAnimationSequence_Player("Avatar_Kiana_C1_Hit_H", AnimType::Hit_H, 60, true);
		m_Animation->AddAnimationSequence_Player("Avatar_Kiana_C1_Hit_L", AnimType::Hit_L, 60, true);
		//m_Animation->AddAnimationSequence_Player("Avatar_Yae_Sakura_Ani_Skill_01", AnimType::Skill1, 60, true);
		m_Animation->AddAnimationSequence_Player("Avatar_Kiana_C1_Skill_Ultra", AnimType::UltraSkill, 30, true);
		//m_Animation->AddAnimationSequence_Player("Avatar_Yae_sakura_Ani_win", AnimType::Win, 60, true);
		m_Animation->AddAnimationSequence_Player("Avatar_Kiana_C1_EvadeBackward_fix", AnimType::EvadeBackward, 60, true);
		m_Animation->AddAnimationSequence_Player("Avatar_Kiana_C1_EvadeForward", AnimType::EvadeForward, 60, true);
		m_Animation->AddAnimationSequence_Player("Avatar_Kiana_C1_Victory_01", AnimType::Victory, 60, false);
		m_Animation->AddAnimationSequence_Player("Avatar_Kiana_C1_Victory_Idle", AnimType::VictoryIdle, 60, false);
		m_Animation->AddAnimationSequence_Player("Avatar_Kiana_C1_EvadeForward", AnimType::EvadeForward, 60, true);
		m_Animation->AddAnimationSequence_Player("Avatar_Kiana_C1_SwitchIn", AnimType::SwitchIn, 30, true, 6);
		m_Animation->AddAnimationSequence_Player("Avatar_Kiana_C1_SwitchOut", AnimType::SwitchOut, 30, true, 6);


		m_Animation->AddSound("KianaAttack1", AnimType::Attack1Combat);
		m_Animation->AddSound("KianaAttack1", AnimType::Attack1);
		m_Animation->AddSound("KianaAttack2", AnimType::Attack2);
		m_Animation->AddSound("KianaAttack3", AnimType::Attack3);
		m_Animation->AddSound("KianaAttack4_1", AnimType::Attack4);
		m_Animation->AddSound("KianaAttack4_2Charge", AnimType::AttackCharge);

		m_Animation->AddSound("SakuraCombatToIdle", AnimType::CombatIdle);
		m_Animation->AddSound("KianaUltraSkill", AnimType::UltraSkill);
		m_Animation->AddSound("KianaEvade", AnimType::EvadeBackward);
		m_Animation->AddSound("KianaEvade", AnimType::EvadeForward);
		m_Animation->AddSound("AppearEffectSound", AnimType::Appear);

		m_Animation->AddSoundCV("KianaAttack1CV", AnimType::Attack1Combat);
		m_Animation->AddSoundCV("KianaAttack1CV", AnimType::Attack1);
		m_Animation->AddSoundCV("KianaAttack2CV", AnimType::Attack2);
		m_Animation->AddSoundCV("KianaAttack3CV", AnimType::Attack3);
		m_Animation->AddSoundCV("KianaAttack4_1CV", AnimType::Attack4);
		m_Animation->AddSoundCV("KianaAttack4_2CV", AnimType::AttackCharge);

		m_Animation->AddSoundCV("KianaHit1CV", AnimType::Hit_H);

		m_Animation->AddSoundCV("KianaUltraSkillCV", AnimType::UltraSkill);
		m_Animation->AddSoundCV("KianaAppearCV", AnimType::Appear);
	}
	m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Kiana_C1_Attack_Gun_01", "AttackCombo", 28);
	m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Kiana_C1_Attack_Gun_02", "AttackCombo", 30);
	m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Kiana_C1_Attack_Gun_03", "AttackCombo", 40);
	m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Kiana_C1_Attack_Gun_03", "AttackCharge", 28);
	m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Kiana_C1_Attack_Gun_04_01", "AttackReset", 80);
	m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Kiana_C1_Attack_Gun_04_02", "AttackReset", 130);

	m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Kiana_C1_Attack_Gun_01", "Sound", 5);
	m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Kiana_C1_Attack_Gun_02", "Sound", 5);
	m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Kiana_C1_Attack_Gun_03", "Sound", 5);
	m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Kiana_C1_Attack_Gun_04_01", "Sound", 10);
	m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Kiana_C1_Attack_Gun_04_02", "Sound", 22);

	m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Kiana_C1_Hit_L", "Sound", 2);

	m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Kiana_C1_Appear", "Sound", 5);
	m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Kiana_C1_Skill_Ultra", "Sound", 5);

	m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Kiana_C1_Attack_Gun_01", "AttackRight", 9);
	m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Kiana_C1_Attack_Gun_02", "AttackLeft", 9);
	m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Kiana_C1_Attack_Gun_03", "AttackRight", 15);
	m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Kiana_C1_Attack_Gun_04_01", "AttackCollision", 20);
	m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Kiana_C1_Attack_Gun_04_02", "AttackCollision", 39);
	m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Kiana_C1_Skill_Ultra", "AttackCollision", 60);
	m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Kiana_C1_Skill_Ultra", "AttackCollision", 70);
	m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Kiana_C1_Skill_Ultra", "AttackCollision", 80);
	m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Kiana_C1_Skill_Ultra", "AttackCollision", 90);
	m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Kiana_C1_Skill_Ultra", "AttackCollision", 100);
	m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Kiana_C1_Skill_Ultra", "AttackCollision", 110);

	m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Kiana_C1_Run", "RunSound", 6);
	m_pScene->GetResource()->AddAnimationSequenceNotify("Avatar_Kiana_C1_Run", "RunSound", 15);
	m_Mesh->GetMaterial(0)->BloomEnable(true);

	return true;
}

void CKianaPlayer::Update(float DeltaTime)
{
	CPlayer::Update(DeltaTime);

}

void CKianaPlayer::PostUpdate(float DeltaTime)
{
	CPlayer::PostUpdate(DeltaTime);
}

void CKianaPlayer::Collision(float DeltaTime)
{
	CPlayer::Collision(DeltaTime);
}

void CKianaPlayer::Render(float DeltaTime)
{
	CPlayer::Render(DeltaTime);
}

CKianaPlayer* CKianaPlayer::Clone()
{
	return new CKianaPlayer(*this);
}


void CKianaPlayer::IdleStart()
{
	//이동과 공격상태일때의 교체
	if (PlayerState::Move == m_State)
	{
		m_Animation->ChangeAnimType(AnimType::MoveToIdle);
	}
	else if (PlayerState::Combat == m_State)
	{
		m_Animation->ChangeAnimType(AnimType::CombatIdle);
	}
	else //조건이무얼까..
	{
		m_Animation->ChangeAnimType(AnimType::StandBy);
	}
	m_State = PlayerState::Idle;

	m_IdleCount = 0;
}

void CKianaPlayer::IdleStay()
{
	if (m_Animation->IsEndNextFrame())
	{
		m_Animation->ChangeAnimType(AnimType::StandBy);
		m_IdleCount++;
	}
}

void CKianaPlayer::AnimationNotify(const std::string& Name)
{
	CPlayer::AnimationNotify(Name);
	if (Name == "AttackLeft")
	{
		CKianaFire* KianaFire = m_pScene->SpawnObject<CKianaFire>("KianaFire");
		KianaFire->SetMatrixPos(m_LeftGunPoint->GetWorldMatrix());
		KianaFire->SetWorldRotation(GetWorldRotation().y - 90.f, 0.f, 90.f);

		CPlayerAttCol* CollisionPlayerAtt = m_pScene->SpawnObject<CPlayerAttCol>("PlayerAttLeft");
		CollisionPlayerAtt->SetDamage(m_PlayerStatus->Damage);
		CollisionPlayerAtt->SetDamageMax(m_PlayerStatus->DamageMax);
		CollisionPlayerAtt->SetMatrixPos(m_LeftGunPoint->GetWorldMatrix());
		CollisionPlayerAtt->SetBox3DLength(0.1f, 0.1f, 10.f);
		CollisionPlayerAtt->SetWorldRotation(GetWorldRotation());
		CollisionPlayerAtt->SetType(ClientClassType::Kiana);
	}
	if (Name == "AttackRight")
	{
		CKianaFire* KianaFire = m_pScene->SpawnObject<CKianaFire>("KianaFire");
		KianaFire->SetMatrixPos(m_RightGunPoint->GetWorldMatrix());
		KianaFire->SetWorldRotation(GetWorldRotation().y - 90.f, 0.f, 90.f);


		CPlayerAttCol* CollisionPlayerAtt = m_pScene->SpawnObject<CPlayerAttCol>("PlayerAttRight");
		CollisionPlayerAtt->SetDamage(m_PlayerStatus->Damage);
		CollisionPlayerAtt->SetDamageMax(m_PlayerStatus->DamageMax);
		CollisionPlayerAtt->SetMatrixPos(m_RightGunPoint->GetWorldMatrix());
		CollisionPlayerAtt->SetBox3DLength(0.1f, 0.1f, 10.f);
		CollisionPlayerAtt->SetWorldRotation(GetWorldRotation());
		CollisionPlayerAtt->SetType(ClientClassType::Kiana);

	}
	if (Name == "AttackCollision")
	{
		CPlayerAttCol* CollisionPlayerAtt = m_pScene->SpawnObject<CPlayerAttCol>("PlayerAttRight");
		CollisionPlayerAtt->SetDamage(m_PlayerStatus->Damage);
		CollisionPlayerAtt->SetDamageMax(m_PlayerStatus->DamageMax);
		CollisionPlayerAtt->SetMatrixPos(m_RightGunPoint->GetWorldMatrix());
		CollisionPlayerAtt->SetBox3DLength(0.1f, 0.1f, 10.f);
		CollisionPlayerAtt->SetWorldRotation(GetWorldRotation());
		CollisionPlayerAtt->SetType(ClientClassType::Kiana);
	}

	if (Name == "AttackSkillCollision")
	{
		CSkeleton* Skel = m_Animation->GetSkeleton();
		CBoneSocket* RightGun = Skel->GetSocket("RightGun");

		CPlayerAttCol* CollisionPlayerAtt = m_pScene->SpawnObject<CPlayerAttCol>("PlayerAttRight");
		CollisionPlayerAtt->SetDamage(m_PlayerStatus->Damage);
		CollisionPlayerAtt->SetDamageMax(m_PlayerStatus->DamageMax);
		CollisionPlayerAtt->SetMatrixPos(RightGun->GetSocketMatrix());
		CollisionPlayerAtt->SetBox3DLength(0.1f, 0.1f, 10.f);
		CollisionPlayerAtt->SetWorldRotation(GetWorldRotation());
		CollisionPlayerAtt->SetType(ClientClassType::Kiana);


		CBoneSocket* LeftGun = Skel->GetSocket("LeftGun");
		CollisionPlayerAtt = m_pScene->SpawnObject<CPlayerAttCol>("PlayerAttLeft");
		CollisionPlayerAtt->SetDamage(m_PlayerStatus->Damage);
		CollisionPlayerAtt->SetDamageMax(m_PlayerStatus->DamageMax);
		CollisionPlayerAtt->SetMatrixPos(LeftGun->GetSocketMatrix());
		CollisionPlayerAtt->SetBox3DLength(0.1f, 0.1f, 10.f);
		CollisionPlayerAtt->SetWorldRotation(GetWorldRotation());
		CollisionPlayerAtt->SetType(ClientClassType::Kiana);
	}
}
