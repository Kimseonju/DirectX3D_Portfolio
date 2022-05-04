#pragma once

#include "Component/AnimationMeshComponent.h"
#include "Component/ColliderSphere.h"
#include "Component/ColliderBox3D.h"
#include "ClientObject.h"
class CMonster : public CClientObject
{
    friend class CScene;

protected:
    CMonster();
    CMonster(const CMonster& obj);
    virtual ~CMonster();


protected:
	int                 m_Hp;
	int                 m_HpMax;
    bool                m_Setting;
    CSharedPtr<CSceneComponent> m_Root;
    CSharedPtr<CAnimationMeshComponent> m_Mesh;
    CSharedPtr<CColliderBox3D> m_Body;
    CSharedPtr<CColliderBox3D> m_MapBody;

public:
    void SetHp(int Hp)
    {
        m_Hp = Hp;
        m_HpMax = Hp;
    }
    int GetHp()
    {return m_Hp;}
    int GetHpMax()
    {
        return m_HpMax;
    }
    void MinusHp(int Value)
    {m_Hp -= Value;}
public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Collision(float DeltaTime);
    virtual void Render(float DeltaTime);
    virtual CMonster* Clone();
public:
	virtual void CollisionBegin(const HitResult& result, CCollider* Collider);
	virtual void CollisionMiddle(const HitResult& result, CCollider* Collider);
	virtual void CollisionEnd(const HitResult& result, CCollider* Collider);
public:
	void CreateHitDamage(int Damage);
	void CreateHitBillboard(const Vector3& Pos);
};

