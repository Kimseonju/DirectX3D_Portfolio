#pragma once
#include "AttackObject.h"
#include "Component/AnimationMeshComponent.h"
#include "Component/ColliderSphere.h"
#include "Component/ColliderBox3D.h"
class CSniperGrenade : public CAttackObject
{
    friend class CScene;
private:
    bool m_Setting;
    bool m_Up;
    float m_Speed;
    float m_MinY;
    bool m_Move;
    bool m_Check1;
    bool m_Sound;
protected:
    CSniperGrenade();
    CSniperGrenade(const CSniperGrenade& obj);
    virtual ~CSniperGrenade();
public:
    void SetMinY(float Y)
    {
        m_MinY = Y;
    }
    class CStaticMeshComponent* GetMesh()
    {
        return m_Mesh;
    }
public:
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
    virtual CSniperGrenade* Clone();
};