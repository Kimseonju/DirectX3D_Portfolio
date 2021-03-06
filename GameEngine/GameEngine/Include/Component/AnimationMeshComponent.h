#pragma once

#include "PrimitiveComponent.h"
#include "../Resource/AnimationMesh.h"
#include "../Resource/Skeleton.h"

class CAnimationMeshComponent :
    public CPrimitiveComponent
{
    friend class CGameObject;

protected:
    CAnimationMeshComponent();
    CAnimationMeshComponent(const CAnimationMeshComponent& com);
    virtual ~CAnimationMeshComponent();

protected:
    CSharedPtr<CAnimationMesh>     m_pMesh;
	class CAnimation* m_Animation;
	class CPoseableAnimation* m_PoseableAnimation;
	CSharedPtr<class CShader>   m_PoseableShader;
	CSharedPtr<class CShader>   m_NotLightShader;
    CSharedPtr<CSkeleton> m_Skeleton;

public:
    virtual void AddChild(CSceneComponent* Child, const std::string& SocketName = "");
	void SetAnimation(class CAnimation* Animation);
	void SetPoseableAnimation(class CPoseableAnimation* Animation);
    CAnimation* GetAnimation()
    {
        return m_Animation;
    }

    CPoseableAnimation* GetPoseableAnimation()
	{
		return m_PoseableAnimation;
	}
    CSkeleton* GetSkeleton()
    {
        return m_Skeleton;
    }

public:
    virtual class CMesh* GetMesh()  const;
	virtual void SetMesh(class CMesh* pMesh);
    virtual void SetMesh(const std::string& Name);

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostTransformUpdate(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Collision(float DeltaTime);
    virtual void Render(float DeltaTime);
    virtual CAnimationMeshComponent* Clone();
    virtual void RenderShadow(float DeltaTime);

public:
	void CallNotify(const std::string& Name);
	void SetNotLight();
public:
	void SetRootBoneIndex(const std::string& BoneName);
public:
	virtual void Save(FILE* pFile);
	virtual void Load(FILE* pFile);

};

