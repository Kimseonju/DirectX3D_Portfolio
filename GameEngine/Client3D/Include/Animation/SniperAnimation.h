#pragma once
#include "Resource/Animation.h"
#include "../Global.h"
//#include "Resource/Sound.h"

class CSniperAnimation :public CAnimation
{
public:
	CSniperAnimation();
	CSniperAnimation(const CSniperAnimation& Anim);
	virtual ~CSniperAnimation();
public:
	void Init();
	void Start();
	void Update(float DeltaTime);
	void PostUpdate(float DeltaTime);
	void SetShader();
	void ResetShader();
	CSniperAnimation* Clone();

public:
	class CSniper* m_Owner;
	void(CSniper::* m_AnimationEndFunc)(std::string);

private:

public:
	void SetAnimationEndFunc(void(CSniper::* EndFunc)(std::string))
	{
		m_AnimationEndFunc = EndFunc;
	}

	void AddAnimationSequence_Sniper(const std::string& Name, bool Loop = false, int iFrame = 60, bool RootMotion = false, int RootLastFrame = 0, bool RootMotionX = false, bool RootMotionY = true, bool RootMotionZ = false);
};