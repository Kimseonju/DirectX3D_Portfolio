#pragma once
#include "AttackObject.h"
#include "Component/AnimationMeshComponent.h"
#include "Component/ColliderSphere.h"
#include "Component/ColliderBox3D.h"
#include "Resource/Sound.h"
#include "TornadoEffect.h"
class CWendyStorm : public CAttackObject
{
    friend class CScene;
private:
    bool m_Setting;
    bool m_Tornado;
    bool    m_Coll;
    float   m_Timer;
    float   m_DeltaTime;
    CGameObject* m_Point;
    CTornadoEffect* m_Effect;
protected:
    CWendyStorm();
    CWendyStorm(const CWendyStorm& obj);
    virtual ~CWendyStorm();
private:
    virtual void CollisionBegin(const HitResult& result, CCollider* Collider);
    virtual void CollisionMiddle(const HitResult& result, CCollider* Collider);
    virtual void CollisionEnd(const HitResult& result, CCollider* Collider);
public:
    void IsTornado()
    {m_Tornado = true;}
    void SetPoint(Vector3 Pos)
    {m_Point->SetWorldPos(Pos);}

    void SetObject(CGameObject* Obj)
    {
        m_Point = Obj;
    }
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Collision(float DeltaTime);
    virtual void Render(float DeltaTime);
    virtual CWendyStorm* Clone();
};


#define HoleSpeed		2.5