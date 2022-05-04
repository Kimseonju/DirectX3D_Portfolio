#pragma once
#include "Monster.h"
#include "../Animation/AxeSoldierAnimation.h"
#include "../PublicData.h"
#include "FSM.h"
#include "Component/ColliderBox3D.h"
#include "Component/ColliderSphere.h"
#include "MonsterSpawnEffect.h"
#include "Component/PaperBurnComponent.h"
class CAxeSoldier : public CMonster
{
	friend class CScene;

private:
    float               m_DeltaTime;
    bool                m_DeadGradientOn;
    float               m_DeadGradientTimer;
    bool                m_FAttackOn;
    bool                m_DeathOn;
    FSM<CAxeSoldier>    m_FSM;
    CAxeSoldierAnimation* m_Animation;
    Axe_State m_AxeCurState;
    Axe_AttState m_AxeCurAttState;
    Axe_AttState m_NextAttack;
    Axe_MoveState m_MoveState;
    Axe_MoveState m_BMoveState;
    Axe_HitState m_HitState;
    Axe_HitAniState m_HitAniState;
    CSharedPtr<CColliderBox3D> m_AttackColl;
    bool                m_AttackRun;


    CMonsterSpawnEffect* m_SpawnEffect;
    float                       m_SpawnTimer1;
    float                       m_SpawnTimer2;


    CSharedPtr<CPaperBurnComponent>    m_PaperBurn0;
    CSharedPtr<CPaperBurnComponent>    m_PaperBurn1;
    CSharedPtr<CPaperBurnComponent>    m_PaperBurn2;
public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Collision(float DeltaTime);
    virtual void Render(float DeltaTime);
    virtual CAxeSoldier* Clone();
protected:
	CAxeSoldier();
	CAxeSoldier(const CAxeSoldier& obj);
	virtual ~CAxeSoldier();


public:

    void PaperBurnEndFunction();
    virtual void CollisionBegin(const HitResult& result, CCollider* Collider);
    virtual void CollisionMiddle(const HitResult& result, CCollider* Collider);
    virtual void CollisionEnd(const HitResult& result, CCollider* Collider);
public:
    void EndAnimation(std::string	AniName);
    void AnimationNotify(const std::string& Name);
public://////////////////////////////////////////////////////////////////////// FSM
	void CreateFSM();
	void IsFSMPlay(bool _Play);


    //  Spawn
    void Axe_Spawn_Start();
    void Axe_Spawn_Stay();
    void Axe_Spawn_End();

    //  IDLE
    void Axe_Idle_Start();
    void Axe_Idle_Stay();
    void Axe_Idle_End();

    //  Move
    int  m_MoveRandom;
    bool m_MoveEnd;
    void Axe_Move_Start();
    void Axe_Move_Stay();
    void Axe_Move_End();

    //  Attack Hub
    void Axe_AttackHub_Start();
    void Axe_AttackHub_Stay();
    void Axe_AttackHub_End();

    //  Hit Hub
    void Axe_HitHub_Start();
    void Axe_HitHub_Stay();
    void Axe_HitHub_End();
    void IsHit(Axe_HitState State);

    //  Attack Hub
    void Axe_Dead_Start();
    void Axe_Dead_Stay();
    void Axe_Dead_End();
    void IsDead(int DeadType = 0);

    ////  NAttack
    //void Axe_NAttack_Start();
    //void Axe_NAttack_Stay();
    //void Axe_NAttack_End();

    ////  FAttack
    //void Axe_FAttack_Start();
    //void Axe_FAttack_Stay();
    //void Axe_FAttack_End();
    //void Axe_FAttack2_Start();
    //void Axe_FAttack2_Stay();
    //void Axe_FAttack2_End();


    ////  TAttack
    //void Axe_TAttack_Start();
    //void Axe_TAttack_Stay();
    //void Axe_TAttack_End();

    ////  RAttack
    //void Axe_RAttack_Start();
    //void Axe_RAttack_Stay();
    //void Axe_RAttack_End();
};