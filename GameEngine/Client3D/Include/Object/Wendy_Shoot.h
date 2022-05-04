#pragma once
#include "AttackObject.h"
#include "Component/AnimationMeshComponent.h"
#include "Component/ColliderSphere.h"
#include "Component/ColliderBox3D.h"
#include "Resource/Sound.h"
class CWendyShoot : public CAttackObject
{
    friend class CScene;
private:
    bool m_Setting;
    CSound* m_Sound;
    CSound* m_BoomSound;
    bool    m_Coll;
    float   m_Timer;
protected:
    CWendyShoot();
    CWendyShoot(const CWendyShoot& obj);
    virtual ~CWendyShoot();
private:
    virtual void CollisionBegin(const HitResult& result, CCollider* Collider);
    virtual void CollisionMiddle(const HitResult& result, CCollider* Collider);
    virtual void CollisionEnd(const HitResult& result, CCollider* Collider);
public:
    CStaticMeshComponent* GetMesh()
    {
        return m_Mesh;
    }
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Collision(float DeltaTime);
    virtual void Render(float DeltaTime);
    virtual CWendyShoot* Clone();
};