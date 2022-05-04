#pragma once
#include "ClientObject.h"
#include "../PublicData.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"
class CMapItem :
	public CClientObject
{
	friend class CScene;

protected:
	CMapItem();
	CMapItem(const CMapItem& obj);
	virtual ~CMapItem();
protected:
	MapItemType m_Type;

	CSharedPtr<CSceneComponent> m_Root;
	CSharedPtr<CStaticMeshComponent> m_Mesh;
	CSharedPtr<CColliderBox3D> m_Body;
	CClientObject* m_Target;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void PrevRender(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CMapItem* Clone();

	virtual void CollisionBegin(const HitResult& result, CCollider* Collider);
};

