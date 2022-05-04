#pragma once
#include "ClientObject.h"
#include "Component/ColliderBox3D.h"
class CMapCollision :
    public CClientObject
{
	friend class CScene;

public:
	CMapCollision();
	CMapCollision(const CMapCollision& obj);
	virtual ~CMapCollision();

protected:
	CSharedPtr<CColliderBox3D> m_CollisionBox3D;

public:
	void SetMatrixPos(const Matrix& mat);
	void SetLength(float X, float Y, float Z);
public:
	virtual void SetWorldScale(const Vector3& Scale);
	virtual void Enable(bool bEnable);
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CMapCollision* Clone();
public:

	virtual void CollisionBegin(const HitResult& result, CCollider* Collider);
	virtual void CollisionMiddle(const HitResult& result, CCollider* Collider);
	virtual void CollisionEnd(const HitResult& result, CCollider* Collider);

};
