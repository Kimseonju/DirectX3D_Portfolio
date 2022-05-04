#pragma once

#include "ClientObject.h"
#include "Component/AnimationMeshComponent.h"
#include "Component/StaticMeshComponent.h"
#include "Component/Camera.h"
#include "Component/SpringArm3D.h"
#include "Resource/Animation.h"
#include "Component/ColliderBox3D.h"
#include "Component/ColliderSphere.h"
#include "../Animation/PlayerAnimation.h"
#include "Monster.h"
class CPlayer :
    public CClientObject
{
    friend class CScene;

protected:
    CPlayer();
    CPlayer(const CPlayer& obj);
    virtual ~CPlayer();

protected:
    CSharedPtr<CSceneComponent> m_Root;
	CSharedPtr<CAnimationMeshComponent> m_Mesh;
	CSharedPtr<CStaticMeshComponent> m_WeaponMesh;
	CSharedPtr<CStaticMeshComponent> m_WeaponMesh2;
    CSharedPtr<CCamera> m_Camera;
	CSharedPtr<CSpringArm3D> m_Arm;
	CSharedPtr<CColliderBox3D> m_Body;
	CSharedPtr<CColliderBox3D> m_EvadeBody;
	CSharedPtr<CMonster> m_Target;
	FSM<CPlayer> PlayerFSM;
protected:
    CPlayerAnimation* m_Animation;
	PlayerStatus* m_PlayerStatus;
	bool m_FSMEnable;
    PlayerState m_State;
	int m_AttackCombo;
	bool m_AttackChargeCombo;
	float m_CombatDelay;
	float m_CombatDelayMax;
    float m_DeltaTime; //임시 DeltaTime
    bool m_Move;
	bool m_AttackClick;
	bool m_AttackComboPlay;
	bool m_UltraSkillEffect1;
	bool m_UltraSkillEffect2;
	bool m_UltraSkillAttack;
	float m_UltraSkillTime;
	float m_UltraSkillTimeMax;
	std::vector<PlayerDir> m_KeyPush;
	bool m_KeyLeftMove;
	bool m_KeyRightMove;
	bool m_KeyMoveFront;
	bool m_KeyMoveBack;
	//UI에서 받을것
	float m_MoveDirAngle;
	float m_PlayerDeltaTime;
public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Collision(float DeltaTime);
    virtual void Render(float DeltaTime);
    virtual CPlayer* Clone();
public:
	bool IsKeyPush()
	{
		return !m_KeyPush.empty();
	}
	bool IsMove()
	{
		return m_Move;
	}
	float GetFinshMoveDirAngle()
	{
		return m_MoveDirAngle;
	}
	PlayerStatus* GetStatus()
	{
		return m_PlayerStatus;
	}
	CClientObject* GetMonsterTarget()
	{
		return m_Target;
	}
	void SetFSMEnable(bool _Enable)
	{
		m_FSMEnable = _Enable;
	}
    CAnimation* GetAnimation()
    {
        return m_Animation;
    }
    PlayerState GetState()
    {
        return m_State;
    }
	CSpringArm3D* GetArm()
	{
		return m_Arm;
	}
public:
	virtual void MoveFront(float Time);
	virtual void MoveBack(float Time);
	virtual void LeftMove(float Time);
	virtual void RightMove(float Time);

	virtual void ReleaseMoveFront(float Time);
	virtual void ReleaseMoveBack(float Time);
	virtual void ReleaseLeftMove(float Time);
	virtual void ReleaseRightMove(float Time);

	virtual void Attack(float Time);
	virtual void UltraSkill(float Time);
	virtual void Evade(float Time);
	virtual void UltraSkillAttack();
public:
    //아래는 이후 캐릭터에따라 분류할것(virtual선언)
	virtual void IdleStart();
	virtual void IdleStay();
	virtual void IdleEnd();

	virtual void AttackStart();
	virtual void AttackStay();
	virtual void AttackEnd();

	virtual void MoveStart();
	virtual void MoveStay();
	virtual void MoveEnd();

	virtual void Hit_LStart();
	virtual void Hit_LStay();
	virtual void Hit_LEnd();

	virtual void Hit_HStart();
	virtual void Hit_HStay();
	virtual void Hit_HEnd();

	virtual void AppearStart();
	virtual void AppearStay();
	virtual void AppearEnd();

	virtual void CombatStart();
	virtual void CombatStay();
	virtual void CombatEnd();

	virtual void UltraSkillStart();
	virtual void UltraSkillStay();
	virtual void UltraSkillEnd();

	virtual void EvadeStart();
	virtual void EvadeStay();
	virtual void EvadeEnd();

	virtual void SwitchInStart();
	virtual void SwitchInStay();
	virtual void SwitchInEnd();

	virtual void SwitchOutStart();
	virtual void SwitchOutStay();
	virtual void SwitchOutEnd();

	virtual void VictoryStart();
	virtual void VictoryStay();
	virtual void VictoryEnd();

	virtual void VictoryIdleStart();
	virtual void VictoryIdleStay();
	virtual void VictoryIdleEnd();
	virtual void AnimationNotify(const std::string& Name);

	virtual void UltraSkillEffect1();
	virtual void UltraSkillEffect2();
	virtual void UltraSkillEffect1End();
	virtual void UltraSkillEffect2End();
	//플레이어 바뀔때 대기
	virtual void PlayerWait();
	//플레이어 바뀔때 등장
	virtual void PlayerAppear();

	//플레이어 바뀔때 등장(어택콤보)
	virtual void PlayerAppear_Attack();

	void Change1(float Time);
	void Change2(float Time);


	virtual void CollisionBegin(const HitResult& result, CCollider* Collider);
	virtual void CollisionMiddle(const HitResult& result, CCollider* Collider);
	virtual void CollisionEnd(const HitResult& result, CCollider* Collider);

	virtual void CollisionEvadeBegin(const HitResult& result, CCollider* Collider);
	virtual void CollisionEvadeMiddle(const HitResult& result, CCollider* Collider);
	virtual void CollisionEvadeEnd(const HitResult& result, CCollider* Collider);

	void StartAnimation();
	virtual void CameraAction();
public:
	float GetDirAngle(PlayerDir InputNum);
};

