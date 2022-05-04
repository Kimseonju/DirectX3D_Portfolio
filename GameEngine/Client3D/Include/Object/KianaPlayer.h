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
	//�Ʒ��� ���� ĳ���Ϳ����� �з��Ұ�(virtual����)
	virtual void IdleStart();
	virtual void IdleStay();
	virtual void AnimationNotify(const std::string& Name);
};

