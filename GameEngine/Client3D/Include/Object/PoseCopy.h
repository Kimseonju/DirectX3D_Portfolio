#pragma once

#include "ClientObject.h"
#include "Component/AnimationMeshComponent.h"
#include "Resource/PoseableAnimation.h"
#include "Monster.h"
class CPoseCopy :
	public CClientObject
{
	friend class CScene;

protected:
	CPoseCopy();
	CPoseCopy(const CPoseCopy& obj);
	virtual ~CPoseCopy();

protected:
	CSharedPtr<CSceneComponent> m_Root;
	CSharedPtr<CAnimationMeshComponent> m_Mesh;
protected:
	CPoseableAnimation* m_Animation;
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CPoseCopy* Clone();
public:
	void PoseCopy(CAnimationMeshComponent* Mesh, const Vector3& Color=Vector3(1.f,1.f,1.f));
};

