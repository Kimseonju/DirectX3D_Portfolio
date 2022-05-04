#include "AxeSoldierAnimation.h"
#include "Scene/Scene.h"
// #include "Resource/AnimationSequence.h"

CAxeSoldierAnimation::CAxeSoldierAnimation() :
	m_Owner (nullptr),
	m_AnimationEndFunc(nullptr)
{
}

CAxeSoldierAnimation::CAxeSoldierAnimation(const CAxeSoldierAnimation& Anim):CAnimation(Anim)
{
	m_AnimationEndFunc = nullptr;
}

CAxeSoldierAnimation::~CAxeSoldierAnimation()
{
}

void CAxeSoldierAnimation::Init()
{
	CAnimation::Init();

	// Idle 모션
	AddAnimationSequence_Axe("AxeSoldier_Idle");

	// Move 모션
															//    좌우   앞뒤  // 위아래
	AddAnimationSequence_Axe("AxeSoldier_Run", true, 30, true, 0, true, true, false);
	AddAnimationSequence_Axe("AxeSoldier_Run+", true, 30, true, 0, true, true, false);
	AddAnimationSequence_Axe("AxeSoldier_BWalk", true, 30, true, 0, true, true, false);
	AddAnimationSequence_Axe("AxeSoldier_LWalk", true, 30, true, 0, true, true, false);
	AddAnimationSequence_Axe("AxeSoldier_RWalk", true, 30, true, 0, true, true, false);

	m_Scene->GetResource()->AddAnimationSequenceNotify("AxeSoldier_Run", "PlayerSearch_Start", 0);
	m_Scene->GetResource()->AddAnimationSequenceNotify("AxeSoldier_BWalk", "PlayerSearch_Start", 0);
	m_Scene->GetResource()->AddAnimationSequenceNotify("AxeSoldier_LWalk", "PlayerSearch_Start", 0);
	m_Scene->GetResource()->AddAnimationSequenceNotify("AxeSoldier_RWalk", "PlayerSearch_Start", 0);

	m_Scene->GetResource()->AddAnimationSequenceNotify("AxeSoldier_Run",	"PlayerSearch_End", 5);
	m_Scene->GetResource()->AddAnimationSequenceNotify("AxeSoldier_BWalk",	"PlayerSearch_End", 5);
	m_Scene->GetResource()->AddAnimationSequenceNotify("AxeSoldier_LWalk",	"PlayerSearch_End", 5);
	m_Scene->GetResource()->AddAnimationSequenceNotify("AxeSoldier_RWalk",	"PlayerSearch_End", 5);

	// Attack 모션
	AddAnimationSequence_Axe("AxeSoldier_NAttack", true, 30, true, 0, true, true, false);
	AddAnimationSequence_Axe("AxeSoldier_FAttack_1",true,30,true, 0, true, true, false);
	AddAnimationSequence_Axe("AxeSoldier_FAttack_2", true, 30, true, 0, true, true, false);
	AddAnimationSequence_Axe("AxeSoldier_TAttack", true, 30, true, 0, true, true, false);
	AddAnimationSequence_Axe("AxeSoldier_RAttack", true, 30, true, 0, true, true, false);
	
	m_Scene->GetResource()->AddAnimationSequenceNotify("AxeSoldier_FAttack_1",	"PlayerSearch_Start", 0);
	m_Scene->GetResource()->AddAnimationSequenceNotify("AxeSoldier_FAttack_2",	"PlayerSearch_Start", 0);
	m_Scene->GetResource()->AddAnimationSequenceNotify("AxeSoldier_TAttack",	"PlayerSearch_Start", 0);
	m_Scene->GetResource()->AddAnimationSequenceNotify("AxeSoldier_RAttack",	"PlayerSearch_Start", 0);
	m_Scene->GetResource()->AddAnimationSequenceNotify("AxeSoldier_FAttack_1",	"PlayerSearch_End",	 5);
	m_Scene->GetResource()->AddAnimationSequenceNotify("AxeSoldier_FAttack_2",	"PlayerSearch_End",	 5);
	m_Scene->GetResource()->AddAnimationSequenceNotify("AxeSoldier_TAttack",	"PlayerSearch_End",	 5);
	m_Scene->GetResource()->AddAnimationSequenceNotify("AxeSoldier_RAttack",	"PlayerSearch_End",	 5);



	m_Scene->GetResource()->AddAnimationSequenceNotify("AxeSoldier_NAttack",   "StartAttack", 15);
	m_Scene->GetResource()->AddAnimationSequenceNotify("AxeSoldier_FAttack_1", "StartAttack", 30);
	m_Scene->GetResource()->AddAnimationSequenceNotify("AxeSoldier_FAttack_2", "StartAttack", 30);
	m_Scene->GetResource()->AddAnimationSequenceNotify("AxeSoldier_TAttack",   "StartAttack", 10);
	m_Scene->GetResource()->AddAnimationSequenceNotify("AxeSoldier_TAttack",   "TAttack", 35);
	m_Scene->GetResource()->AddAnimationSequenceNotify("AxeSoldier_RAttack",   "StartAttack", 20);


	// Hit 모션
	AddAnimationSequence_Axe("AxeSoldier_Hit", true, 30, true, 0, true, true, false); // 기본 Hit
	AddAnimationSequence_Axe("AxeSoldier_Hit_HFly", true, 30, true, 0, true, true, false);
	AddAnimationSequence_Axe("AxeSoldier_Hit_LFly", true, 30, true, 0, true, true, false);
	AddAnimationSequence_Axe("AxeSoldier_FlyToKnockBack", true, 30, true, 0, true, true, false);
	AddAnimationSequence_Axe("AxeSoldier_StandUp", true, 30, true, 0, true, true, false);
	AddAnimationSequence_Axe("AxeSoldier_StandBy", true, 90, true, 0, true, true, false);
	AddAnimationSequence_Axe("AxeSoldier_Stun", true, 30, true, 0, true, true, false);
	AddAnimationSequence_Axe("AxeSoldier_HThrow_1", true, 30, true, 0, true, true, false);
	AddAnimationSequence_Axe("AxeSoldier_LThrow_1", true, 30, true, 0, true, true, false);
	AddAnimationSequence_Axe("AxeSoldier_KnockBack", true, 30, true, 0, true, true, false);


	m_Scene->GetResource()->AddAnimationSequenceNotify("AxeSoldier_HThrow_1", "AxeSoldier_HThrow_1_End", 41);

	// Die 모션
	AddAnimationSequence_Axe("AxeSoldier_NDie",false,30,true, 0, true, true, false);
	AddAnimationSequence_Axe("AxeSoldier_BDie",false,30,true, 0, true, true, false);
	AddAnimationSequence_Axe("AxeSoldier_FDie",false,30,true, 0, true, true, false);

	ChangeAnimation("AxeSoldier_Idle");

	// Sound
	{
		m_Scene->GetResource()->AddAnimationSequenceSound3DNotify("AxeSoldier_Run", "Axe_HumanStep_1", 5);
		m_Scene->GetResource()->AddAnimationSequenceSound3DNotify("AxeSoldier_Run", "Axe_HumanStep_2", 20);
		m_Scene->GetResource()->AddAnimationSequenceSound3DNotify("AxeSoldier_Run+", "Axe_HumanStep_3", 5);
		m_Scene->GetResource()->AddAnimationSequenceSound3DNotify("AxeSoldier_Run+", "Axe_HumanStep_4", 20);
		m_Scene->GetResource()->AddAnimationSequenceSound3DNotify("AxeSoldier_BWalk", "Axe_HumanStep_2", 25);
		m_Scene->GetResource()->AddAnimationSequenceSound3DNotify("AxeSoldier_BWalk", "Axe_HumanStep_1", 50);
		m_Scene->GetResource()->AddAnimationSequenceSound3DNotify("AxeSoldier_LWalk", "Axe_HumanStep_1", 5);
		m_Scene->GetResource()->AddAnimationSequenceSound3DNotify("AxeSoldier_LWalk", "Axe_HumanStep_2", 35);
		m_Scene->GetResource()->AddAnimationSequenceSound3DNotify("AxeSoldier_RWalk", "Axe_HumanStep_3", 5);
		m_Scene->GetResource()->AddAnimationSequenceSound3DNotify("AxeSoldier_RWalk", "Axe_HumanStep_4", 35);


		m_Scene->GetResource()->AddAnimationSequenceSound3DNotify("AxeSoldier_NAttack", "AxeAttack_2", 10);
		m_Scene->GetResource()->AddAnimationSequenceSound3DNotify("AxeSoldier_FAttack_1", "Axe_HumanStep_1_Short", 20);
		m_Scene->GetResource()->AddAnimationSequenceSound3DNotify("AxeSoldier_FAttack_1", "Axe_HumanStep_4", 45);
		m_Scene->GetResource()->AddAnimationSequenceSound3DNotify("AxeSoldier_FAttack_1", "AxeAttack_1", 21);
		m_Scene->GetResource()->AddAnimationSequenceSound3DNotify("AxeSoldier_FAttack_2", "Axe_HumanStep_1", 0);
		m_Scene->GetResource()->AddAnimationSequenceSound3DNotify("AxeSoldier_FAttack_2", "Axe_HumanStep_2", 10);
		m_Scene->GetResource()->AddAnimationSequenceSound3DNotify("AxeSoldier_FAttack_2", "Axe_HumanStep_1_Short", 65);
		m_Scene->GetResource()->AddAnimationSequenceSound3DNotify("AxeSoldier_FAttack_2", "AxeAttack_1", 25);
		m_Scene->GetResource()->AddAnimationSequenceSound3DNotify("AxeSoldier_TAttack", "Axe_HumanStep_2", 10);
		m_Scene->GetResource()->AddAnimationSequenceSound3DNotify("AxeSoldier_TAttack", "Axe_HumanStep_1", 15);
		m_Scene->GetResource()->AddAnimationSequenceSound3DNotify("AxeSoldier_TAttack", "Axe_Dash_1", 7);
		m_Scene->GetResource()->AddAnimationSequenceSound3DNotify("AxeSoldier_TAttack", "AxeAttack_0", 20);


		m_Scene->GetResource()->AddAnimationSequenceSound3DNotify("AxeSoldier_RAttack", "Axe_HumanStep_1", 0);
		m_Scene->GetResource()->AddAnimationSequenceSound3DNotify("AxeSoldier_RAttack", "Axe_HumanStep_1", 8);
		m_Scene->GetResource()->AddAnimationSequenceSound3DNotify("AxeSoldier_RAttack", "Axe_HumanStep_1", 12);
		m_Scene->GetResource()->AddAnimationSequenceSound3DNotify("AxeSoldier_RAttack", "AxeAttack_3", 8);
		// m_Scene->GetResource()->AddAnimationSequenceSoundNotify("AxeSoldier_RAttack", "Axe_HumanStep_1", 0);
	}
}

void CAxeSoldierAnimation::Start()
{
	CAnimation::Start();

}

void CAxeSoldierAnimation::Update(float DeltaTime)
{
	CAnimation::Update(DeltaTime);
	
}

void CAxeSoldierAnimation::PostUpdate(float DeltaTime)
{
	CAnimation::PostUpdate(DeltaTime);

	
	if (m_End)
	{
		(m_Owner->*m_AnimationEndFunc)(GetSequence()->GetName());
	}
}

void CAxeSoldierAnimation::SetShader()
{
	CAnimation::SetShader();
}

void CAxeSoldierAnimation::ResetShader()
{
	CAnimation::ResetShader();
}

CAxeSoldierAnimation* CAxeSoldierAnimation::Clone()
{
	return new CAxeSoldierAnimation(*this);
}



void CAxeSoldierAnimation::AddAnimationSequence_Axe(const std::string& Name,bool Loop , int iFrame, bool RootMotion, int RootLastFrame, bool RootMotionX, bool RootMotionY, bool RootMotionZ)
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