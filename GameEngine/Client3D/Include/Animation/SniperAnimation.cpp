#include "SniperAnimation.h"
#include "Scene/Scene.h"

CSniperAnimation::CSniperAnimation() :
	m_Owner(nullptr),
	m_AnimationEndFunc(nullptr)
{
}

CSniperAnimation::CSniperAnimation(const CSniperAnimation& Anim) :CAnimation(Anim)
{
	m_AnimationEndFunc = nullptr;
}

CSniperAnimation::~CSniperAnimation()
{
}

void CSniperAnimation::Init()
{
	CAnimation::Init();

	//// Idle 모션
	//AddAnimationSequence_Sniper("Sniper_Idle");

	//// Move 모션

	//AddAnimationSequence_Sniper("Sniper_Run", true, 30, true, 0, true, true, true);
	//AddAnimationSequence_Sniper("Sniper_BWalk", true, 30, true, 0, true, true, true);
	//AddAnimationSequence_Sniper("Sniper_LWalk", true, 30, true, 0, true, true, true);
	//AddAnimationSequence_Sniper("Sniper_RWalk", true, 30, true, 0, true, true, true);

	//m_Scene->GetResource()->AddAnimationSequenceNotify("Sniper_Run", "PlayerSearch_Start", 0);
	//m_Scene->GetResource()->AddAnimationSequenceNotify("Sniper_BWalk", "PlayerSearch_Start", 0);
	//m_Scene->GetResource()->AddAnimationSequenceNotify("Sniper_LWalk", "PlayerSearch_Start", 0);
	//m_Scene->GetResource()->AddAnimationSequenceNotify("Sniper_RWalk", "PlayerSearch_Start", 0);

	//m_Scene->GetResource()->AddAnimationSequenceNotify("Sniper_Run", "PlayerSearch_End", 5);
	//m_Scene->GetResource()->AddAnimationSequenceNotify("Sniper_BWalk", "PlayerSearch_End", 5);
	//m_Scene->GetResource()->AddAnimationSequenceNotify("Sniper_LWalk", "PlayerSearch_End", 5);
	//m_Scene->GetResource()->AddAnimationSequenceNotify("Sniper_RWalk", "PlayerSearch_End", 5);

	//// Attack 모션
	//AddAnimationSequence_Sniper("Sniper_NAttack", true, 30, true);
	//AddAnimationSequence_Sniper("Sniper_FAttack_1", true, 30, true);
	//AddAnimationSequence_Sniper("Sniper_FAttack_2", true, 30, true);
	//AddAnimationSequence_Sniper("Sniper_TAttack", true, 30, true);
	//AddAnimationSequence_Sniper("Sniper_RAttack", true, 30, true);

	//m_Scene->GetResource()->AddAnimationSequenceNotify("Sniper_FAttack_1", "PlayerSearch_Start", 0);
	//m_Scene->GetResource()->AddAnimationSequenceNotify("Sniper_FAttack_2", "PlayerSearch_Start", 0);
	//m_Scene->GetResource()->AddAnimationSequenceNotify("Sniper_TAttack", "PlayerSearch_Start", 0);
	//m_Scene->GetResource()->AddAnimationSequenceNotify("Sniper_RAttack", "PlayerSearch_Start", 0);

	//m_Scene->GetResource()->AddAnimationSequenceNotify("Sniper_FAttack_1", "PlayerSearch_End", 5);
	//m_Scene->GetResource()->AddAnimationSequenceNotify("Sniper_FAttack_2", "PlayerSearch_End", 5);
	//m_Scene->GetResource()->AddAnimationSequenceNotify("Sniper_TAttack", "PlayerSearch_End", 5);
	//m_Scene->GetResource()->AddAnimationSequenceNotify("Sniper_RAttack", "PlayerSearch_End", 5);

	//// Hit 모션
	//AddAnimationSequence_Sniper("Sniper_Hit", true, 30, true); // 기본 Hit
	//AddAnimationSequence_Sniper("Sniper_Hit_HFly", true, 30, true);
	//AddAnimationSequence_Sniper("Sniper_Hit_LFly", true, 30, true);
	//AddAnimationSequence_Sniper("Sniper_FlyToKnockBack", true, 30, true);
	//AddAnimationSequence_Sniper("Sniper_StandUp", true, 30, true);
	//AddAnimationSequence_Sniper("Sniper_StandBy", true, 90, true);
	//AddAnimationSequence_Sniper("Sniper_Stun", true, 30, true);
	//AddAnimationSequence_Sniper("Sniper_HThrow_1", true, 30, true);
	//AddAnimationSequence_Sniper("Sniper_LThrow_1", true, 30, true);
	//AddAnimationSequence_Sniper("Sniper_KnockBack", true, 30, true);

	//// Die 모션
	//AddAnimationSequence_Sniper("Sniper_NDie", false, 30, true);
	//AddAnimationSequence_Sniper("Sniper_BDie", false, 30, true);
	//AddAnimationSequence_Sniper("Sniper_FDie", false, 30, true);
	AddAnimationSequence_Sniper("Sniper_Idle", true, 30, true,0,false, false, false);
	AddAnimationSequence_Sniper("Sniper_Run", true, 30, true, 0, true, true, false);
	AddAnimationSequence_Sniper("Sniper_Run+", true, 30, true, 0, true, true, false);
	AddAnimationSequence_Sniper("Sniper_Backward", true, 30, true, 0, true, true, false);
	AddAnimationSequence_Sniper("Sniper_NAttack", true, 30, true, 0, true, true, false);
	AddAnimationSequence_Sniper("Sniper_GAttack", true, 30, true,0,true, true, false);
	AddAnimationSequence_Sniper("Sniper_RAttack", true, 30, true,0,true, true, false);
	AddAnimationSequence_Sniper("Sniper_FAttack", true, 30, true,0,true, true, false);

	m_Scene->GetResource()->AddAnimationSequenceNotify("Sniper_Run", "PlayerSearch_Start", 0);
	m_Scene->GetResource()->AddAnimationSequenceNotify("Sniper_Run", "PlayerSearch_End", 16);

	m_Scene->GetResource()->AddAnimationSequenceNotify("Sniper_Backward", "PlayerSearch_Start", 0);
	m_Scene->GetResource()->AddAnimationSequenceNotify("Sniper_Backward", "PlayerSearch_End", 2);
	m_Scene->GetResource()->AddAnimationSequenceNotify("Sniper_NAttack", "PlayerSearch_Start", 0);
	m_Scene->GetResource()->AddAnimationSequenceNotify("Sniper_GAttack", "PlayerSearch_Start", 0);
	m_Scene->GetResource()->AddAnimationSequenceNotify("Sniper_RAttack", "PlayerSearch_Start", 0);
	m_Scene->GetResource()->AddAnimationSequenceNotify("Sniper_FAttack", "PlayerSearch_Start", 0);
	m_Scene->GetResource()->AddAnimationSequenceNotify("Sniper_NAttack", "PlayerSearch_End", 2);
	m_Scene->GetResource()->AddAnimationSequenceNotify("Sniper_GAttack", "PlayerSearch_End", 2);
	m_Scene->GetResource()->AddAnimationSequenceNotify("Sniper_RAttack", "PlayerSearch_End", 2);
	m_Scene->GetResource()->AddAnimationSequenceNotify("Sniper_FAttack", "PlayerSearch_End", 2);


	m_Scene->GetResource()->AddAnimationSequenceNotify("Sniper_FAttack", "Body_false", 1);
	m_Scene->GetResource()->AddAnimationSequenceNotify("Sniper_RAttack", "RAttack", 15);
	m_Scene->GetResource()->AddAnimationSequenceNotify("Sniper_RAttack", "Body_false", 1);
	m_Scene->GetResource()->AddAnimationSequenceNotify("Sniper_RAttack", "Body_true", 20);


	m_Scene->GetResource()->AddAnimationSequenceNotify("Sniper_NAttack", "AttackCollStart", 5);
	m_Scene->GetResource()->AddAnimationSequenceNotify("Sniper_RAttack", "AttackCollStart", 0);
	m_Scene->GetResource()->AddAnimationSequenceNotify("Sniper_GAttack", "AttackCollStart", 0);
	m_Scene->GetResource()->AddAnimationSequenceNotify("Sniper_RAttack", "AttackCollStart", 0);
	m_Scene->GetResource()->AddAnimationSequenceNotify("Sniper_FAttack", "AttackCollStart", 25);

	AddAnimationSequence_Sniper("Sniper_Stun", true, 30, true,0,true,true, false);
	AddAnimationSequence_Sniper("Sniper_HHit", true, 30, true,0,true,true, false);
	AddAnimationSequence_Sniper("Sniper_LHit", true, 30, false, 0, true, true, false);
	AddAnimationSequence_Sniper("Sniper_HFly", true, 30, true,0,true,true, false);
	AddAnimationSequence_Sniper("Sniper_LFly", true, 30, true,0,true,true, false);
	AddAnimationSequence_Sniper("Sniper_FlyToKnockDown", true, 30, true, 0, true, true, false);
	AddAnimationSequence_Sniper("Sniper_StandUp", true, 30, true,0,true,true, false);
	AddAnimationSequence_Sniper("Sniper_HFlyALL", true, 30, true,0,true,true, false);
	AddAnimationSequence_Sniper("Sniper_HFlyToStand", true, 30, true, 0, true, true, false);
	AddAnimationSequence_Sniper("Sniper_AttToIdle", true, 30, true, 0, true, true, false);
	AddAnimationSequence_Sniper("Sniper_Die", false, 30, true, 0, true, true, false);


	ChangeAnimation("Sniper_Idle");

	m_Scene->GetResource()->AddAnimationSequenceSound3DNotify("Sniper_Run", "HumanStep_1", 7);
	m_Scene->GetResource()->AddAnimationSequenceSound3DNotify("Sniper_Run", "HumanStep_2", 15);
	m_Scene->GetResource()->AddAnimationSequenceSound3DNotify("Sniper_Run+", "HumanStep_3", 7);
	m_Scene->GetResource()->AddAnimationSequenceSound3DNotify("Sniper_Run+", "HumanStep_4", 15);
	m_Scene->GetResource()->AddAnimationSequenceSound3DNotify("Sniper_Backward", "Sniper_JumpBack", 1);
	m_Scene->GetResource()->AddAnimationSequenceSound3DNotify("Sniper_Backward", "HumanStep_2", 25);
	m_Scene->GetResource()->AddAnimationSequenceSound3DNotify("Sniper_Backward", "HumanStep_1", 30);
	m_Scene->GetResource()->AddAnimationSequenceSound3DNotify("Sniper_NAttack", "Sniper_GunShoot", 8);
	m_Scene->GetResource()->AddAnimationSequenceSound3DNotify("Sniper_NAttack", "Sniper_GunSet", 3);
	m_Scene->GetResource()->AddAnimationSequenceSound3DNotify("Sniper_RAttack", "Sniper_RAttack", 10);
	m_Scene->GetResource()->AddAnimationSequenceSound3DNotify("Sniper_GAttack", "Sniper_SetGrenade", 3);
	m_Scene->GetResource()->AddAnimationSequenceSound3DNotify("Sniper_GAttack", "Sniper_ShootGrenade", 10);
	m_Scene->GetResource()->AddAnimationSequenceSound3DNotify("Sniper_FAttack", "Sniper_JumpTurn", 3);
	m_Scene->GetResource()->AddAnimationSequenceSound3DNotify("Sniper_FAttack", "Sniper_GunShoot", 20);
}

void CSniperAnimation::Start()
{
	CAnimation::Start();

}

void CSniperAnimation::Update(float DeltaTime)
{
	CAnimation::Update(DeltaTime);

}

void CSniperAnimation::PostUpdate(float DeltaTime)
{
	CAnimation::PostUpdate(DeltaTime);


	if (m_End)
	{
		(m_Owner->*m_AnimationEndFunc)(GetSequence()->GetName());
	}
}

void CSniperAnimation::SetShader()
{
	CAnimation::SetShader();
}

void CSniperAnimation::ResetShader()
{
	CAnimation::ResetShader();
}

CSniperAnimation* CSniperAnimation::Clone()
{
	return new CSniperAnimation(*this);
}



void CSniperAnimation::AddAnimationSequence_Sniper(const std::string& Name, bool Loop, int iFrame, bool RootMotion, int RootLastFrame, bool RootMotionX, bool RootMotionY, bool RootMotionZ)
{
	CAnimationSequence* Sequence = FindSequence(Name);

	if (Sequence)
	{

	}
	else
	{
		Sequence = m_Scene->GetResource()->FindAnimationSequence(Name);
		if (!Sequence)
			return;
		m_mapSequence.insert(std::make_pair(Name, Sequence));
	}
	Sequence->SetRootMotion(RootMotion);
	Sequence->SetRootMotionX(RootMotionX);
	Sequence->SetRootMotionY(RootMotionY);
	Sequence->SetRootMotionZ(RootMotionZ);
	Sequence->SetRootLastFrame(RootLastFrame);
	Sequence->SetPlayFrame(iFrame);
	Sequence->SetLoop(Loop);

	if (!m_Sequence)
		m_Sequence = Sequence;
}