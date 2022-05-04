#pragma once
#include "Resource/Animation.h"
#include "../Global.h"
#include "Resource/Sound.h"

class CWendyAnimation :public CAnimation
{
public:
	CWendyAnimation();
	CWendyAnimation(const CWendyAnimation& Anim);
	virtual ~CWendyAnimation();
public:
	void Init();
	void Start();
	void Update(float DeltaTime);
	void PostUpdate(float DeltaTime);
	void SetShader();
	void ResetShader();
	CWendyAnimation* Clone();

public:
	class CWendy* m_Owner;
	void(CWendy::* m_AnimationEndFunc)(std::string);

public:
	void SetAnimationEndFunc(void(CWendy::* EndFunc)(std::string))
	{
		m_AnimationEndFunc = EndFunc;
	}
	void AddAnimationSequence(const std::string& Name, bool Loop = false, int iFrame = 60, bool RootMotion = false, int RootLastFrame = 0, bool RootMotionX = false, bool RootMotionY = true, bool RootMotionZ = false);
};