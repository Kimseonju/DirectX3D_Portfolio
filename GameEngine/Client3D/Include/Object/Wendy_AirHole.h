#pragma once
#include "AttackObject.h"
#include "Component/AnimationMeshComponent.h"
#include "Component/ColliderSphere.h"
#include "Component/ColliderBox3D.h"
#include "Resource/Sound.h"
#include "Wendy_AirHoleEffect.h"
class CWendyAirHole : public CAttackObject
{
    friend class CScene;
private:
    bool m_Setting;
    CSound* m_Sound;
    bool    m_Coll;
    float   m_Timer;
    float   m_DeltaTime;
    CWendy_AirHoleEffect* m_Effect;
    CSharedPtr<CColliderSphere>  m_AttColl;
protected:
    CWendyAirHole();
    CWendyAirHole(const CWendyAirHole& obj);
    virtual ~CWendyAirHole();
private:
    virtual void CollisionBegin(const HitResult& result, CCollider* Collider);
    virtual void CollisionMiddle(const HitResult& result, CCollider* Collider);
    virtual void CollisionEnd(const HitResult& result, CCollider* Collider);
public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Collision(float DeltaTime);
    virtual void Render(float DeltaTime);
    virtual CWendyAirHole* Clone();
};


#define HoleSpeed		2.5