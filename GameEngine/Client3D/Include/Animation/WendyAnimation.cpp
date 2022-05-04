#include "WendyAnimation.h"
#include "Scene/Scene.h"

CWendyAnimation::CWendyAnimation() :
	m_Owner(nullptr),
	m_AnimationEndFunc(nullptr)
{
}

CWendyAnimation::CWendyAnimation(const CWendyAnimation& Anim) :CAnimation(Anim)
{
	m_AnimationEndFunc = nullptr;
}

CWendyAnimation::~CWendyAnimation()
{
}

void CWendyAnimation::Init()
{
	CAnimation::Init();

	AddAnimationSequence("Wendy_Born",false,35,true,0,false, false, false);

	AddAnimationSequence("Wendy_Idle",true,60,true,0,true,true,true);
	AddAnimationSequence("Wendy_Run",true,60,true,0,true,true,true);
	AddAnimationSequence("Wendy_RunStart",true,60,true,0,true,true,true);
	AddAnimationSequence("Wendy_GlideBack",true,60,true,0,true,true,true);
	AddAnimationSequence("Wendy_GlideLeft",true,60,true,0,true,true,true);
	AddAnimationSequence("Wendy_GlideRight",true,60,true,0,true,true,true);
	
	AddAnimationSequence("Wendy_AirShoot",true,60,true,0,true,true,true); // 90
	AddAnimationSequence("Wendy_AirHole",true,60,true,63,true,true,true); // 363
	AddAnimationSequence("Wendy_Brandish",true,60,true,0,true,true,true); // 105
	AddAnimationSequence("Wendy_Brandish_1",true,60,true,0,true,true,true); // 150
	AddAnimationSequence("Wendy_LongAttack",true,60,true,0,true,true,true); // 262
	AddAnimationSequence("Wendy_Storm",false, 35,true,0,true,true,true); // 268

	AddAnimationSequence("Wendy_StunStart", true, 60, true, 0, true, true, true);
	AddAnimationSequence("Wendy_StunEnd", true, 60, true, 0, true, true, true);
	AddAnimationSequence("Wendy_Die",false,10,true,0,true,true,true);

	ChangeAnimation("Wendy_Born");
	// 플레이어 서치
	{
		m_Scene->GetResource()->AddAnimationSequenceNotify("Wendy_Born", "StormStart", 1);
		m_Scene->GetResource()->AddAnimationSequenceNotify("Wendy_Born", "CameraShake", 120);

		m_Scene->GetResource()->AddAnimationSequenceNotify("Wendy_Storm", "StormStart", 1);
		m_Scene->GetResource()->AddAnimationSequenceNotify("Wendy_Storm", "StormEnd", 120);

		m_Scene->GetResource()->AddAnimationSequenceNotify("Wendy_Brandish", "BrandishFirst", 20);
		m_Scene->GetResource()->AddAnimationSequenceNotify("Wendy_Brandish", "BrandishSecond",40);

		m_Scene->GetResource()->AddAnimationSequenceNotify("Wendy_GlideLeft",	"PlayerSearch_Start", 5);
		m_Scene->GetResource()->AddAnimationSequenceNotify("Wendy_GlideRight",	"PlayerSearch_Start", 5);
		m_Scene->GetResource()->AddAnimationSequenceNotify("Wendy_GlideBack",	"PlayerSearch_Start", 5);

		m_Scene->GetResource()->AddAnimationSequenceNotify("Wendy_GlideLeft",	"PlayerSearch_End",  5);
		m_Scene->GetResource()->AddAnimationSequenceNotify("Wendy_GlideRight",	"PlayerSearch_End",  5);
		m_Scene->GetResource()->AddAnimationSequenceNotify("Wendy_GlideBack",	"PlayerSearch_End",  5);
		m_Scene->GetResource()->AddAnimationSequenceNotify("Wendy_AirShoot",	"PlayerSearch_End", 45);
		m_Scene->GetResource()->AddAnimationSequenceNotify("Wendy_AirHole",		"PlayerSearch_End", 10);
		m_Scene->GetResource()->AddAnimationSequenceNotify("Wendy_Brandish",	"PlayerSearch_End", 10);
		m_Scene->GetResource()->AddAnimationSequenceNotify("Wendy_Brandish_1",	"PlayerSearch_End", 100);
		m_Scene->GetResource()->AddAnimationSequenceNotify("Wendy_LongAttack",	"PlayerSearch_End", 10);
		m_Scene->GetResource()->AddAnimationSequenceNotify("Wendy_Storm",		"PlayerSearch_End", 10);
		m_Scene->GetResource()->AddAnimationSequenceNotify("Wendy_StunStart",	"PlayerSearch_End", 10);


		m_Scene->GetResource()->AddAnimationSequenceNotify("Wendy_AirShoot", "ShootAir", 45);
		m_Scene->GetResource()->AddAnimationSequenceNotify("Wendy_AirHole", "ShootHole", 5);
		m_Scene->GetResource()->AddAnimationSequenceNotify("Wendy_Storm", "StartStorm", 2);
		m_Scene->GetResource()->AddAnimationSequenceNotify("Wendy_Brandish", "StartBrandish", 20);
		m_Scene->GetResource()->AddAnimationSequenceNotify("Wendy_Brandish", "StartBrandish", 40);


		m_Scene->GetResource()->AddAnimationSequenceNotify("Wendy_LongAttack", "LongAttack1", 60);
		m_Scene->GetResource()->AddAnimationSequenceNotify("Wendy_LongAttack", "LongAttack2", 110);
		m_Scene->GetResource()->AddAnimationSequenceNotify("Wendy_LongAttack", "LongAttack3", 180);
	}

	// Sound
	{
		m_Scene->GetResource()->AddAnimationSequenceSound3DNotify("Wendy_Born", "Wendy_Born", 1);
		m_Scene->GetResource()->AddAnimationSequenceSound3DNotify("Wendy_Storm", "Wendy_Born", 1);
		m_Scene->GetResource()->AddAnimationSequenceSound3DNotify("Wendy_GlideBack", "Wendy_Glide_2", 1);
		m_Scene->GetResource()->AddAnimationSequenceSound3DNotify("Wendy_GlideLeft", "Wendy_Glide_1", 1);
		m_Scene->GetResource()->AddAnimationSequenceSound3DNotify("Wendy_GlideRight", "Wendy_Glide_1", 1);
		m_Scene->GetResource()->AddAnimationSequenceSound3DNotify("Wendy_AirHole", "Wendy_AirHole", 40);
		m_Scene->GetResource()->AddAnimationSequenceSound3DNotify("Wendy_Brandish", "Wendy_Brandish_1", 1);
		m_Scene->GetResource()->AddAnimationSequenceSound3DNotify("Wendy_Brandish", "Wendy_Brandish_2", 20);
		m_Scene->GetResource()->AddAnimationSequenceNotify("Wendy_Born", "CameraShake", 120);
		//m_Scene->GetResource()->AddAnimationSequenceSoundNotify("Wendy_Brandish", "Wendy_Glide_2", 0);
	}
}

void CWendyAnimation::Start()
{
	CAnimation::Start();

}

void CWendyAnimation::Update(float DeltaTime)
{
	CAnimation::Update(DeltaTime);

}

void CWendyAnimation::PostUpdate(float DeltaTime)
{
	CAnimation::PostUpdate(DeltaTime);


	if (m_End)
	{
		(m_Owner->*m_AnimationEndFunc)(GetSequence()->GetName());
	}
}

void CWendyAnimation::SetShader()
{
	CAnimation::SetShader();
}

void CWendyAnimation::ResetShader()
{
	CAnimation::ResetShader();
}

CWendyAnimation* CWendyAnimation::Clone()
{
	return new CWendyAnimation(*this);
}



void CWendyAnimation::AddAnimationSequence(const std::string& Name, bool Loop, int iFrame, bool RootMotion, int RootLastFrame, bool RootMotionX, bool RootMotionY, bool RootMotionZ)
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