#pragma once

#include "GameObject.h"
#include "Component/AnimationMeshComponent.h"
#include "Component/Camera.h"
#include "Component/SpringArm3D.h"
#include "Component/ColliderSphere.h"
#include "Resource/Animation.h"

class CPlayerTemp :
	public CGameObject
{
	friend class CScene;

protected:
	CPlayerTemp();
	CPlayerTemp(const CPlayerTemp& obj);
	virtual ~CPlayerTemp();

protected:
	CSharedPtr<CSceneComponent> m_Root;
	CSharedPtr<CAnimationMeshComponent> m_Mesh;
	CSharedPtr<CCamera> m_Camera;
	CSharedPtr<CSpringArm3D> m_Arm;
	CSharedPtr<CColliderSphere> m_Body;
	CAnimation* m_Animation;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CPlayerTemp* Clone();

public:
	void MoveFront(float Time);
	void MoveBack(float Time);

	void RotationY(float Time);
	void RotationYInv(float Time);
};

