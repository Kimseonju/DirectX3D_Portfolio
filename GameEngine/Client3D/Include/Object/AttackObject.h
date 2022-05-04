#pragma once
#include "GameObject.h"
#include "ClientObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderSphere.h"
#include "Component/ColliderBox3D.h"
class CAttackObject : public CClientObject
{
    friend class CScene;

protected:
    CAttackObject();
    CAttackObject(const CAttackObject& obj);
    virtual ~CAttackObject();
private:
    int m_Damage;
    int m_DamageMax;
    bool  m_MonsterAttack;
    
protected:
    CSharedPtr<CSceneComponent> m_Root;
    CSharedPtr<CStaticMeshComponent> m_Mesh;
    CSharedPtr<CColliderBox3D>  m_Box;
    CSharedPtr<CColliderSphere> m_Sphere;

public:
    void SetDamage(int Damage)
    {m_Damage = Damage;}

	void SetDamageMax(int Damage)
	{
        m_DamageMax = Damage;
	}
    int GetDamage();
    void SetMonsterAttack(bool MonsterAttack)
    {m_MonsterAttack = MonsterAttack;}

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
    virtual CAttackObject* Clone();
public:
    void SetBox3DLength(float x, float y, float z);
    void SetMatrixPos(const Matrix& mat);
};