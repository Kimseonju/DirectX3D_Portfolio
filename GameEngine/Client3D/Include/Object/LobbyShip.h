#pragma once
#include "ClientObject.h"
#include "../Global.h"
#include "Component/AnimationMeshComponent.h"
#include "Component/StaticMeshComponent.h"
#include "Component/BillboardComponent.h"
#include "Component/LightComponent.h"
class CLobbyShip :
	public CClientObject
{
	friend class CScene;

protected:
	CLobbyShip();
	CLobbyShip(const CLobbyShip& obj);
	virtual ~CLobbyShip();

protected:

	CSharedPtr<CSceneComponent> m_Root;
	CSharedPtr<CStaticMeshComponent> m_Ship;
	CSharedPtr<CStaticMeshComponent> m_ShipControlRight;
	CSharedPtr<CStaticMeshComponent> m_ShipControlLeft;
	CSharedPtr<CStaticMeshComponent> m_ShipControlCenter;

	CSharedPtr<CAnimationMeshComponent> m_Mesh;
	CSharedPtr<CStaticMeshComponent> m_WeaponMesh;
	CSharedPtr<CStaticMeshComponent> m_WeaponMesh2;

	CSharedPtr<CSceneComponent> m_LobbyCameraPos;

	CSharedPtr<CBillboardComponent> m_Background;



	class CAnimation* m_Animation;

public:
	Vector3 GetLobbyCameraPos() const
	{
		return m_LobbyCameraPos->GetWorldPos();;
	}

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void PrevRender(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CLobbyShip* Clone();

};

