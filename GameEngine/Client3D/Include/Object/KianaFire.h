#pragma once
#include "GameObject.h"
#include "ClientObject.h"
#include "Component/BillboardComponent.h"
class CKianaFire : 
	public CClientObject
{
	friend class CScene;

protected:
	CKianaFire();
	CKianaFire(const CKianaFire& obj);
	virtual ~CKianaFire();

protected:
	CSharedPtr<CBillboardComponent> m_BillboardLeft;
	CSharedPtr<CBillboardComponent> m_BillboardRight;
	class CAnimation3D_Tex* m_AnimationLeft;
	class CAnimation3D_Tex* m_AnimationRight;
	class CRenderState* m_State;
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CKianaFire* Clone();

public:
	void SetMatrixPos(const Matrix& mat);
	void SetRotation(const Vector3& Rot);
};