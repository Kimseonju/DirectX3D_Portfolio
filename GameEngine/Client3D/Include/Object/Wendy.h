#pragma once
#include "Monster.h"
#include "../Animation/WendyAnimation.h"
#include "../PublicData.h"
#include "TornadoEffect.h"
#include "FSM.h"
#include "Component/PaperBurnComponent.h"
class CWendy : public CMonster
{
    friend class CScene;

private:
    float               m_DeltaTime;
    float               m_PlayerDir;
    float               m_PointDir;
    Wendy_State         m_State;
    Wendy_AttackState   m_AttackState;
    int                 m_RandomCount;
    FSM<CWendy>    m_FSM;
    CWendyAnimation* m_Animation;
    CTornadoEffect* m_Effect;

    bool                                m_ParperBurnOn;
    CSharedPtr<CPaperBurnComponent>    m_PaperBurn0;
    CSharedPtr<CPaperBurnComponent>    m_PaperBurn1;
    CSharedPtr<CPaperBurnComponent>    m_PaperBurn2;
    CSharedPtr<CPaperBurnComponent>    m_PaperBurn3;
    CSharedPtr<CPaperBurnComponent>    m_PaperBurn4;
    CSharedPtr<CPaperBurnComponent>    m_PaperBurn5;
    CSharedPtr<CPaperBurnComponent>    m_PaperBurn6;
public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Collision(float DeltaTime);
    virtual void Render(float DeltaTime);
    virtual CWendy* Clone();

protected:
    CWendy();
    CWendy(const CWendy& obj);
    virtual ~CWendy();


public:
    void PaperBurnEndFunction();
    void LookObject();
    void LookObject(bool Enable);
    void EndAnimation(std::string	AniName);
    void AnimationNotify(const std::string& Name);
public://////////////////////////////////////////////////////////////////////// FSM
    void CreateFSM();
    void IsFSMPlay(bool _Play);
    //  Spawn
    void Wendy_Spawn_Start();
    void Wendy_Spawn_Stay();
    void Wendy_Spawn_End();

    //  IDLE
    void Wendy_Idle_Start();
    void Wendy_Idle_Stay();
    void Wendy_Idle_End();
    
    //  Move
    void Wendy_Move_Start();
    void Wendy_Move_Stay();
    void Wendy_Move_End();

    //  Attack Hub
    void Wendy_AttackHub_Start();
    void Wendy_AttackHub_Stay();
	void Wendy_AttackHub_End();

    void Wendy_Death_Start();
    void Wendy_Death_Stay();
    void Wendy_Death_End();
    void IsDeath();
public:
	virtual void CollisionBegin(const HitResult& result, CCollider* Collider);
	virtual void CollisionMiddle(const HitResult& result, CCollider* Collider);
	virtual void CollisionEnd(const HitResult& result, CCollider* Collider);
	virtual void CameraAction();
};