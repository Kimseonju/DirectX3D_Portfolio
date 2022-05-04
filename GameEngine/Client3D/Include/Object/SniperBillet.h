#pragma once
#include "AttackObject.h"
#include "Component/AnimationMeshComponent.h"
#include "Component/ColliderSphere.h"
#include "Component/ColliderBox3D.h"
class CSniperBullet : public CAttackObject
{
    friend class CScene;
private:
    bool m_Setting;
    Vector3 m_Point;
    Vector3 m_PrevPos;
    bool m_NAttack;
protected:
    CSniperBullet();
    CSniperBullet(const CSniperBullet& obj);
    virtual ~CSniperBullet();
public:
    void IsNAttack(bool Enable)
    {
        m_NAttack = Enable;
    }
    class CStaticMeshComponent* GetMesh()
    {
        return m_Mesh;
    }
public:
    virtual void CollisionBegin(const HitResult& result, CCollider* Collider);
    virtual void CollisionMiddle(const HitResult& result, CCollider* Collider);
    virtual void CollisionEnd(const HitResult& result, CCollider* Collider);
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Collision(float DeltaTime);
    virtual void Render(float DeltaTime);
    virtual CSniperBullet* Clone();
};

