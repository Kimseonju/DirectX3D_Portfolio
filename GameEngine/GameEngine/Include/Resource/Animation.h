#pragma once

#include "../Ref.h"
#include "AnimationSequence.h"
#include "Skeleton.h"

class CAnimation :
	public CRef
{
public:
	CAnimation();
	CAnimation(const CAnimation& Anim);
	virtual ~CAnimation();

protected:
	class CScene* m_Scene;

public:
	void SetScene(class CScene* Scene)
	{
		m_Scene = Scene;
	}

protected:
	std::unordered_map<std::string, CSharedPtr<CAnimationSequence>>  m_mapSequence;
	CSharedPtr<CAnimationSequence>  m_Sequence;
	CSharedPtr<CAnimationSequence>  m_ChangeSequence;
	CSkeleton* m_Skeleton;
	class CAnimationMeshComponent* m_Owner;
	bool            m_End;
	bool            m_EndNextFrame;
	float           m_GlobalTime;
	float           m_SequenceProgress;
	float           m_ChangeTimeAcc;
	float           m_ChangeTime;
	int             m_RootBoneIndex;
	Vector3         m_PrevRootMotionPos;
	Vector3         m_FirstRootMotionPos;
	Vector3         m_NextRootMotionPos;
	Vector3         m_MoveRootMotionPos;
	bool			m_SequenceEndFrame;
	int				m_PrevFrame;
	bool			m_Editor;
	bool			m_EditorCheck;
	float			m_EditorTime;
	std::vector<Vector3> m_RootMotion;
	bool			m_IsRootMotionUpdate;
protected:
	CSharedPtr<class CComputeShader> m_AnimationUpdateShader;
	class CAnimationUpdateConstantBuffer* m_CBuffer;
	class CStructuredBuffer* m_OutputBuffer;	// 애니메이션 결과를 저장하기 위헌 버퍼
	class CStructuredBuffer* m_BoneBuffer;
	class CStructuredBuffer* m_BoneRootBuffer;
	ID3D11Buffer* m_BoneRootDataBuffer;
	ID3D11Buffer* m_BoneDataBuffer;
	ID3D11Buffer* m_BoneOutputDataBuffer;
	void* m_BoneRootResourceAddress;
	void* m_BoneResourceAddress;
	void* m_BoneOutputResourceAddress;
	std::vector<Matrix>	m_RootBoneMatrix;
	std::vector<Matrix>	m_vecBoneMatrix;

public:
	float GetGlobalTime()
	{
		return m_GlobalTime;
	}
	void SetEditor(bool _Editor)
	{
		m_Editor = _Editor;
	}
	void SetEditorTime(float _Time)
	{
		m_EditorTime = _Time;
	}
	const Vector3& GetRootMotionPos()
	{
		return m_MoveRootMotionPos;
	}
	const std::string& GetRootBoneName();
	void GetAllBone(std::vector<Bone*>& AllBone);
	void SetPlayTime(float Time)
	{
		m_Sequence->SetPlayTime(Time);
	}
	void ResetSequence();
	CAnimationSequence* GetSequence()
	{
		return m_Sequence;
	}
	void SetOwner(class CAnimationMeshComponent* Owner)
	{
		m_Owner = Owner;
	}
	void SetSkeleton(class CSkeleton* Skeleton);
	class CSkeleton* GetSkeleton();

	Matrix GetSkeletonMatrix(const std::string& Name);
	void SetRootBoneIndex(const std::string& Name);

	bool IsEndNextFrame()
	{
		return m_EndNextFrame;
	}
	bool IsSequenceEndFrame()
	{
		return m_End;
	}
public:
	CAnimationSequence* GetSequence()	const
	{
		return m_Sequence;
	}
	int GetCurFrame();
	int GetEndFrame();
	bool IsRootMotion()
	{
		return m_Sequence->IsRootMotion();
	}
public:
	void AddAnimationSequence(const std::string& Name, float fTime = 1.f, bool RootMotion = false, int RootLastFrame = 0, bool RootMotionX = false,
		bool RootMotionY = true, bool RootMotionZ = false, bool Loop=true);
	void ChangeAnimation(const std::string& Name);

public:
	CAnimationSequence* FindSequence(const std::string& Name);

public:
	virtual void Init();
	virtual void Start();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void SetShader();
	virtual void ResetShader();
	CAnimation* Clone();
};

