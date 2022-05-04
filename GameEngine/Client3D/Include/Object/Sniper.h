#pragma once
#include "Monster.h"
#include "../Animation/SniperAnimation.h"
#include "../PublicData.h"
#include "FSM.h"
#include "MonsterSpawnEffect.h"
#include "Component/PaperBurnComponent.h"
class CSniper : public CMonster
{
    friend class CScene;

private:
    float                       m_DeltaTime;
    bool                        m_DeadGradientOn;
    float                       m_DeadGradientTimer;
    FSM<CSniper>                m_FSM;
    CSniperAnimation*           m_Animation;
    Sniper_State                m_SniperCurState;
    Sniper_AttState             m_SniperCurAttState;
    Sniper_AttState             m_SniperPrevAttState;
    Sniper_AttState             m_NextAttack;
    Sniper_HitState             m_HitState;
    Sniper_HitAniState          m_HitAniState;
    CMonsterSpawnEffect*        m_SpawnEffect;
    float                       m_SpawnTimer1;
    float                       m_SpawnTimer2;
    bool                        m_Death;

    CSharedPtr<CPaperBurnComponent>    m_PaperBurn0;
    CSharedPtr<CPaperBurnComponent>    m_PaperBurn1;
public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Collision(float DeltaTime);
    virtual void Render(float DeltaTime);
    virtual CSniper* Clone();
protected:
    CSniper();
    CSniper(const CSniper& obj);
    virtual ~CSniper();


public:
    void PaperBurnEndFunction();
    virtual void CollisionBegin(const HitResult& result, CCollider* Collider);
    virtual void CollisionMiddle(const HitResult& result, CCollider* Collider);
    virtual void CollisionEnd(const HitResult& result, CCollider* Collider);
    
    void EndAnimation(std::string	AniName);
    void AnimationNotify(const std::string& Name);
public://////////////////////////////////////////////////////////////////////// FSM
	void CreateFSM();
	void IsFSMPlay(bool _Play);


    //  Spawn
    void Sniper_Spawn_Start();
    void Sniper_Spawn_Stay();
    void Sniper_Spawn_End();

    //  IDLE
    float m_IdleTime;
    void Sniper_Idle_Start();
    void Sniper_Idle_Stay();
    void Sniper_Idle_End();

    //  Move
    float m_PointDir;
    void Sniper_Move_Start();
    void Sniper_Move_Stay();
    void Sniper_Move_End();

    //  Attack Hub
    int m_AttType;
    void Sniper_AttackHub_Start();
    void Sniper_AttackHub_Stay();
    void Sniper_AttackHub_End();

    //  Hit Hub
    void Sniper_HitHub_Start();
    void Sniper_HitHub_Stay();
    void Sniper_HitHub_End();
    void IsHit(Sniper_HitState State);

    //  Dead
    void Sniper_Dead_Start();
    void Sniper_Dead_Stay();
    void Sniper_Dead_End();
    void IsDead(int DeadType = 0);

    ////  NAttack
    //void Sniper_NAttack_Start();
    //void Sniper_NAttack_Stay();
    //void Sniper_NAttack_End();

    ////  FAttack
    //void Sniper_FAttack_Start();
    //void Sniper_FAttack_Stay();
    //void Sniper_FAttack_End();
    //void Sniper_FAttack2_Start();
    //void Sniper_FAttack2_Stay();
    //void Sniper_FAttack2_End();


    ////  TAttack
    //void Sniper_TAttack_Start();
    //void Sniper_TAttack_Stay();
    //void Sniper_TAttack_End();

    ////  RAttack
    //void Sniper_RAttack_Start();
    //void Sniper_RAttack_Stay();
    //void Sniper_RAttack_End();
};

enum AttType
{
    None = 0,
    Run,
    Back
};