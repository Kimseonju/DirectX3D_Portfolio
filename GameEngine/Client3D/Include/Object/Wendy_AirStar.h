#pragma once
#include "AttackObject.h"
#include "Component/AnimationMeshComponent.h"
#include "Component/ColliderSphere.h"
#include "Component/ColliderBox3D.h"
#include "Component/TrailComponent.h"
#include "Resource/Sound.h"
#include "Component/BillboardComponent.h"

class CWendyAirStar : public CAttackObject
{
    friend class CScene;
private:
    bool m_Setting;
    CSound* m_SoundBorn;
    CSound* m_SoundBoom;
    CSound* m_SoundShoot;
    CSound* m_BoomSound;
    float m_LeftTime;
    bool    m_Coll;
    float   m_Timer;
    bool    m_Check;
    CSharedPtr<CTrailComponent> m_Trail;
    CSharedPtr<CTrailComponent> m_Trail2;
    CSharedPtr<CBillboardComponent> m_AirEffect;
    
protected:
    CWendyAirStar();
    CWendyAirStar(const CWendyAirStar& obj);
    virtual ~CWendyAirStar();
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
    virtual CWendyAirStar* Clone();
};

#define AirStarSpeed	7.f
