#pragma once
#include "Resource/Animation.h"
#include "../Global.h"

#include "Resource/Sound.h"
class CPlayerAnimation :
    public CAnimation
{
public:
	CPlayerAnimation();
	CPlayerAnimation(const CPlayerAnimation& Anim);
	virtual ~CPlayerAnimation();


private:
	std::vector<CSharedPtr<CAnimationSequence>> m_Sequence_Player;
	std::vector<CSound*> m_vecSound;
	std::vector<CSound*> m_vecSoundCV;

	FMOD::ChannelGroup* m_SoundGroup;
	FMOD::ChannelGroup* m_SoundCVGroup;

	AnimType m_CurType;
public:
	void AddAnimationSequence_Player(const std::string& Name, AnimType Type, int iFrame=60, bool RootMotion = false, int RootLastFrame = 0, bool RootMotionX = false, bool RootMotionY = true, bool RootMotionZ = false, int StartFrame=0);

	void AddSound(const std::string& Name, AnimType Type);
	void AddSoundCV(const std::string& Name, AnimType Type);

	void SoundPlay();

	void ChangeAnimType(AnimType Type);
public:
	void Init();
	void Start();
	void Update(float DeltaTime);
	void PostUpdate(float DeltaTime);
	void SetShader();
	void ResetShader();
	CPlayerAnimation* Clone();
};

