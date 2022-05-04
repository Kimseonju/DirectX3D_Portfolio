#pragma once
#include "AttackObject.h"
#include "Component/AnimationMeshComponent.h"
#include "Component/ColliderSphere.h"
#include "Component/ColliderBox3D.h"
class CPlayerAttCol
	: public CAttackObject
{
	friend class CScene;
private:

protected:
	CPlayerAttCol();
	CPlayerAttCol(const CPlayerAttCol& obj);
	virtual ~CPlayerAttCol();
private:
	ClientClassType m_Type;
	bool m_SoundPlay;
public:
	void SetType(ClientClassType Type)
	{
		m_Type = Type;
	}
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CPlayerAttCol* Clone();

	virtual void CollisionBegin(const HitResult& result, CCollider* Collider);
	virtual void CollisionMiddle(const HitResult& result, CCollider* Collider);
	virtual void CollisionEnd(const HitResult& result, CCollider* Collider);
	
};

