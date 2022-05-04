#pragma once
#include "AttackObject.h"
#include "Component/AnimationMeshComponent.h"
#include "Component/ColliderSphere.h"
#include "Component/ColliderBox3D.h"
#include "Resource/Sound.h"
#include "Wendy_AirBallEffect.h"
class CWendyAirBullet : public CAttackObject
{
    friend class CScene;
private:
    bool m_Setting;
    CSound* m_Sound;
    CSound* m_SoundHit;
    CSound* m_SoundBoom;
    bool    m_Coll;
    float   m_Timer;
    float   m_DeltaTime;

    Vector3 m_Point;

    CSharedPtr<CWendyAirBallEffect> m_Effect;
    CSharedPtr<CWendyAirBallEffect> m_Effect2;
    CSharedPtr<CWendyAirBallEffect> m_Effect3;
    CSharedPtr<CWendyAirBallEffect> m_Effect4;
    CSharedPtr<CWendyAirBallEffect> m_Effect5;

    bool m_EffectDeath;
protected:
    CWendyAirBullet();
    CWendyAirBullet(const CWendyAirBullet& obj);
    virtual ~CWendyAirBullet();
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
    virtual CWendyAirBullet* Clone();
};


#define BulletSpeed		2.5