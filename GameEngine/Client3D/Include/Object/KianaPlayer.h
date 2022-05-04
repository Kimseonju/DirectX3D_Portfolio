#pragma once
#include "Player.h"
class CKianaPlayer :
    public CPlayer
{
public:
	CKianaPlayer();
	CKianaPlayer(const CKianaPlayer& obj);
	virtual ~CKianaPlayer();
private:
	int m_IdleCount;
	CSharedPtr< CSceneComponent> m_LeftGunPoint;
	CSharedPtr< CSceneComponent> m_RightGunPoint;
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CKianaPlayer* Clone();

public:
	//아래는 이후 캐릭터에따라 분류할것(virtual선언)
	virtual void IdleStart();
	virtual void IdleStay();
	virtual void AnimationNotify(const std::string& Name);
};

