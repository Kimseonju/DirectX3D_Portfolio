#pragma once

#include "../Ref.h"
#include "../Resource/Sound.h"

struct KeyFrame
{
	double	dTime;
	Vector3	vPos;
	Vector3	vScale;
	Vector4	vRot;
};

struct BoneKeyFrame
{
	int		iBoneIndex;
	std::vector<KeyFrame*>	vecKeyFrame;
	int			iRefCount;

	BoneKeyFrame() :
		iRefCount(1),
		iBoneIndex(0)
	{
	}

	~BoneKeyFrame()
	{
		size_t	Size = vecKeyFrame.size();

		for (size_t i = 0; i < Size; ++i)
		{
			SAFE_DELETE(vecKeyFrame[i]);
		}

		vecKeyFrame.clear();
	}
};

struct AnimationFrameTrans
{
	Vector4 vTranslate;
	Vector4 vScale;
	Vector4 qRot;
};

struct AnimationNotify
{
	std::string			Name;
	class CAnimationSequence* pOwner;
	float			Time;
	bool			Call;

	AnimationNotify()
	{
		pOwner = nullptr;
		Call = false;
		Time = 0.f;
	}
};

struct AnimationSoundNotify
{
	std::string			Name;
	class CAnimationSequence* pOwner;
	CSound*				m_Sound;
	float			Time;
	bool			Call;

	AnimationSoundNotify()
	{
		m_Sound = nullptr;
		pOwner = nullptr;
		Call = false;
		Time = 0.f;
	}
};

class CAnimationSequence :
    public CRef
{
	friend class CAnimation;
	friend class CPoseableAnimation;
	friend class CResourceManager;
	friend class CSceneResource;

private:
	CAnimationSequence();
	CAnimationSequence(const CAnimationSequence& Anim);
	~CAnimationSequence();

private:
	class CScene* m_Scene;
	class CAnimation*			m_Anim;
	bool						m_Loop;
	float						m_StartTime;
	float						m_EndTime;
	float						m_TimeLength;
	float						m_FrameTime;
	float						m_PlayTime;
	float						m_PlayScale;
	int							m_StartFrame;
	int							m_EndFrame;
	int							m_FrameLength;
	int							m_FrameMode;
	int							m_ChangeFrame;
	bool						m_End;
	std::vector<BoneKeyFrame*>	m_vecKeyFrame;
	char						m_FullPath[MAX_PATH];
	class CStructuredBuffer*	m_KeyFrameBuffer;
	std::vector<AnimationNotify*>	m_vecNotify;
	std::vector<AnimationSoundNotify*>	m_vecSoundNotify;
	bool			m_RootMotion;
	bool			m_RootMotionX;
	bool			m_RootMotionY;
	bool			m_RootMotionZ;
	int				m_RootLastFrame;

public:
	int GetStartFrame()
	{
		return m_StartFrame;
	}
	void SetStartFrame(int Frame)
	{
		m_StartFrame = Frame;
	}
	float GetFrameTime() const
	{
		return m_FrameTime;
	}
	float GetPlayTime()	const
	{
		return m_PlayTime;
	}
	int GetKeyFrameCount()	const
	{
		return m_FrameLength;
	}
	void SetRootLastFrame(int Frame)
	{
		m_RootLastFrame = Frame;;
	}
	int GetRootLastFrame()	const
	{
		return m_RootLastFrame;
	}
	bool IsRootMotion()
	{
		return m_RootMotion;
	}
	bool IsRootMotionX()
	{
		return m_RootMotionX;
	}
	bool IsRootMotionY()
	{
		return m_RootMotionY;
	}
	bool IsRootMotionZ()
	{
		return m_RootMotionZ;
	}
	void SetRootMotion(bool Motion)
	{
		m_RootMotion = Motion;
		m_RootMotionY = Motion;
	}
	void SetRootMotionX(bool Motion)
	{
		m_RootMotionX = Motion;
	}
	void SetRootMotionY(bool Motion)
	{
		m_RootMotionY = Motion;
	}
	void SetRootMotionZ(bool Motion)
	{
		m_RootMotionZ = Motion;
	}
public:
	CAnimationSequence* Clone();
	bool IsSequenceEnd()	const;
	void GetKeyFrame(std::vector<BoneKeyFrame*>& vecFrame);
	bool LoadFbxAnimation(const char* pFullPath, bool bLoop = false);
	bool Save(const TCHAR* pFileName, const std::string& strPathName = MESH_PATH);
	bool SaveMultibyte(const char* pFileName, const std::string& strPathName = MESH_PATH);
	bool SaveFullPath(const TCHAR* pFullPath);
	bool SaveFullPathMultibyte(const char* pFullPath);
	bool Load(const TCHAR* pFileName, const std::string& strPathName = MESH_PATH);
	bool LoadMultibyte(const char* pFileName, const std::string& strPathName = MESH_PATH);
	bool LoadFullPath(const TCHAR* pFullPath);
	bool LoadFullPathMultibyte(const char* pFullPath);

public:
	void SetEndFrame(int Frame);
	void SetPlayScale(float fScale);
	void SetPlayTime(float fTime);
	void SetPlayFrame(int Frame);
	void SetLoop(bool bLoop)
	{
		m_Loop = bLoop;
	}

public:
	bool CreateSequence(bool bLoop, struct _tagFbxAnimationClip* pClip);
	bool CreateSequence(const std::string& strName, bool bLoop,int iStartFrame, int iEndFrame, float fPlayTime,const std::vector<BoneKeyFrame*>& vecFrame);
	bool CreateSequence(const TCHAR* pFullPath);
	bool CreateSequenceMultibyte(const char* pFullPath);
	bool CreateSequence(bool bLoop, const std::string& strName, const TCHAR* pFileName,const std::string& strPathName = MESH_PATH);
	void SetShader();
	void ResetShader();
	void SetChangeShader();
	void ResetChangeShader();
	void Clear();
	void AddNotify(const std::string& Name, float Time);
	void AddSoundNotify(CSound& Sound, float Time);
};

