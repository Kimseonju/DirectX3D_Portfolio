#pragma once

#include "../Ref.h"
#include "AnimationSequence.h"
#include "Skeleton.h"

class CPoseableAnimation :
	public CRef
{
public:
	CPoseableAnimation();
	CPoseableAnimation(const CPoseableAnimation& Anim);
	virtual ~CPoseableAnimation();

protected:
	class CScene* m_Scene;

public:
	void SetScene(class CScene* Scene)
	{
		m_Scene = Scene;
	}

protected:
	CSharedPtr<CAnimationSequence>  m_Sequence;
	CSkeleton* m_Skeleton;
	class CAnimationMeshComponent* m_Owner;
	float           m_GlobalTime;
protected:
	CSharedPtr<class CComputeShader> m_AnimationUpdateShader;
	class CAnimationUpdateConstantBuffer* m_CBuffer;
	class CStructuredBuffer* m_OutputBuffer;	// 애니메이션 결과를 저장하기 위헌 버퍼
	class CStructuredBuffer* m_BoneBuffer;
	ID3D11Buffer* m_BoneDataBuffer;
	ID3D11Buffer* m_BoneOutputDataBuffer;
	void* m_BoneResourceAddress;
	void* m_BoneOutputResourceAddress;
	std::vector<Matrix>	m_vecBoneMatrix;
	int m_RootBoneIndex;
public:

	void SetOwner(class CAnimationMeshComponent* Owner)
	{
		m_Owner = Owner;
	}
	void SetGlobalTime(float Time)
	{
		m_GlobalTime = Time;
	}

	void SetSkeleton(class CSkeleton* Skeleton);
	class CSkeleton* GetSkeleton();
	void SetRootBoneIndex(const std::string& Name);

public:
public:
	void AddAnimationSequence(const std::string& Name, float fTime = 1.f);

public:
	virtual void Init();
	virtual void Start();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void SetShader();
	virtual void ResetShader();
	CPoseableAnimation* Clone();
};

