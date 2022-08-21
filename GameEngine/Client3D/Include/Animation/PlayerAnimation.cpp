#include "PlayerAnimation.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"

CPlayerAnimation::CPlayerAnimation():
	m_CurType(AnimType::Idle)
{
}

CPlayerAnimation::CPlayerAnimation(const CPlayerAnimation& Anim)
    :CAnimation(Anim)
{
}

CPlayerAnimation::~CPlayerAnimation()
{
}

void CPlayerAnimation::AddAnimationSequence_Player(const std::string& Name, AnimType Type, 
	int iFrame, bool RootMotion, int RootLastFrame, bool RootMotionX, bool RootMotionY, 
	bool RootMotionZ, int StartFrame)
{
	CAnimationSequence* Sequence = FindSequence(Name);
	if (Sequence)
	{}
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
	Sequence->SetStartFrame(StartFrame);
	Sequence->SetLoop(true);
	if (!m_Sequence)
		m_Sequence = Sequence;
	m_Sequence_Player[Type] = Sequence;
}

void CPlayerAnimation::AddSound(const std::string& Name, AnimType Type)
{
	CSound* Sound = m_Scene->GetResource()->FindSound2D(Name);
	m_vecSound[Type] = Sound;
}

void CPlayerAnimation::AddSoundCV(const std::string& Name, AnimType Type)
{
	CSound* Sound = m_Scene->GetResource()->FindSound2D(Name);
	m_vecSoundCV[Type] = Sound;
}

void CPlayerAnimation::SoundPlay()
{
	if (m_vecSound[m_CurType])
		m_vecSound[m_CurType]->Play();
	if (m_vecSoundCV[m_CurType])
		m_vecSoundCV[m_CurType]->Play();
}

void CPlayerAnimation::ChangeAnimType(AnimType Type)
{
	if (m_mapSequence.empty())
		return;
	if (m_Sequence == m_Sequence_Player[Type])
		return;
	m_CurType = Type;
	m_ChangeSequence = m_Sequence_Player[Type];
	m_SoundGroup->stop();
	m_SoundCVGroup->stop();
}

void CPlayerAnimation::Init()
{
	CAnimation::Init();
	m_Sequence_Player.resize(AnimType::End);
	m_vecSound.resize(AnimType::End);
	m_vecSoundCV.resize(AnimType::End);
	m_SoundGroup = m_Scene->GetResource()->FindSoundChannelGroup("Player");
	m_SoundCVGroup = m_Scene->GetResource()->FindSoundChannelGroup("PlayerCV");
}

void CPlayerAnimation::Start()
{
	CAnimation::Start();
}

void CPlayerAnimation::Update(float DeltaTime)
{
	CAnimation::Update(DeltaTime);
}

void CPlayerAnimation::PostUpdate(float DeltaTime)
{
	CAnimation::PostUpdate(DeltaTime);
}

void CPlayerAnimation::SetShader()
{
	CAnimation::SetShader();
}

void CPlayerAnimation::ResetShader()
{
	CAnimation::ResetShader();
}

CPlayerAnimation* CPlayerAnimation::Clone()
{
	return new CPlayerAnimation(*this);
}
