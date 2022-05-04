#pragma once
#include "AttackObject.h"
#include "Component/AnimationMeshComponent.h"
#include "Component/ColliderSphere.h"
#include "Component/ColliderBox3D.h"
#include "Component/BillboardComponent.h"
#include "../PublicData.h"

enum class EffectType
{
    Wendy_Brandish
};

class CAxeWeapon : public CAttackObject
{
    friend class CScene;
private:
    Axe_AttState    m_AttackType;
    CGameObject*    m_Monster;
    bool m_Setting;
    float m_LifeTime;
    bool m_TAttack2;
    EffectType      m_EffectType;
    CSharedPtr<CBillboardComponent> m_Texture;

protected:
    CAxeWeapon();
    CAxeWeapon(const CAxeWeapon& obj);
    virtual ~CAxeWeapon();
public:
    void SetEffectType(EffectType Type)
    {m_EffectType = Type;}
    void SetMonster(CGameObject* Monster)
    {m_Monster = Monster;}
    void TAttack2()
    {m_TAttack2 = true;}
    void SetAttackType(const Axe_AttState& type)
    {m_AttackType = type;}
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
    virtual CAxeWeapon* Clone();
};
