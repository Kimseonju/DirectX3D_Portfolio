#pragma once
#include "Resource/Animation.h"
#include "../Global.h"
#include "Resource/Sound.h"

class CAxeSoldierAnimation :public CAnimation
{
public:
	CAxeSoldierAnimation();
	CAxeSoldierAnimation(const CAxeSoldierAnimation& Anim);
	virtual ~CAxeSoldierAnimation();
public:
	void Init();
	void Start();
	void Update(float DeltaTime);
	void PostUpdate(float DeltaTime);
	void SetShader();
	void ResetShader();
	CAxeSoldierAnimation* Clone();

public:
	class CAxeSoldier* m_Owner;
	void(CAxeSoldier::* m_AnimationEndFunc)(std::string);

public:
	void SetAnimationEndFunc(void(CAxeSoldier::* EndFunc)(std::string))
	{
		m_AnimationEndFunc = EndFunc;
	}
	void AddAnimationSequence_Axe(const std::string& Name,bool Loop = false, int iFrame = 60, bool RootMotion = false, int RootLastFrame = 0, bool RootMotionX = false, bool RootMotionY = true, bool RootMotionZ = false);

//private:
//	std::vector<CSharedPtr<CAnimationSequence>> m_Sequence_AxeSoldier;
//	std::vector<CSound*> m_vecSound;
//	
//	FMOD::ChannelGroup* m_SoundGroup;
//
//	AnimType m_CurType;
//public:
//	void AddAnimationSequence_AxeSoldier(const std::string& Name, AnimType Type, int iFrame = 60, bool RootMotion = false, int RootLastFrame = 0, bool RootMotionX = false, bool RootMotionY = true, bool RootMotionZ = false);
//	void AddSound(const std::string& Name, AnimType Type);
//	void AddSoundCV(const std::string& Name, AnimType Type);
//	void SoundPlay();
//	void ChangeAnimType(AnimType Type);
};