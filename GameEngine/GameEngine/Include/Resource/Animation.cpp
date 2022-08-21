#include "Animation.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "StructuredBuffer.h"
#include "ComputeShader.h"
#include "AnimationUpdateConstantBuffer.h"
#include "ShaderManager.h"
#include "../Component/AnimationMeshComponent.h"
#include "../Device.h"
#include "../Engine.h"

CAnimation::CAnimation() :
	m_Skeleton(nullptr),
	m_AnimationUpdateShader(nullptr),
	m_CBuffer(nullptr),
	m_OutputBuffer(nullptr),
	m_BoneBuffer(nullptr),
	m_BoneDataBuffer(nullptr),
	m_BoneResourceAddress(nullptr),
	m_GlobalTime(0.f),
	m_End(false),
	m_Owner(nullptr),
	m_SequenceProgress(0.f),
	m_ChangeTimeAcc(0.f),
	m_ChangeTime(0.f),
	m_RootBoneIndex(-1),
	m_PrevFrame(0),
	m_Editor(false),
	m_Scene(nullptr),
	m_EndNextFrame(false),
	m_SequenceEndFrame(false),
	m_EditorCheck(false),
	m_EditorTime(0.f),
	m_IsRootMotionUpdate(false),
	m_BoneRootBuffer(nullptr),
	m_BoneRootDataBuffer(nullptr),
	m_BoneOutputDataBuffer(nullptr),
	m_BoneOutputResourceAddress(nullptr)
{
}
CAnimation::CAnimation(const CAnimation& Anim)
{
	if (Anim.m_Skeleton)
		m_Skeleton = Anim.m_Skeleton->Clone();

	m_GlobalTime = 0.f;
	m_End = false;
	m_SequenceProgress = 0.f;
	m_ChangeTimeAcc = 0.f;
	m_ChangeTime = Anim.m_ChangeTime;
	m_RootBoneIndex = Anim.m_RootBoneIndex;

	m_Scene = Anim.m_Scene;
	if (Anim.m_CBuffer)
		m_CBuffer = Anim.m_CBuffer->Clone();

	if (Anim.m_OutputBuffer)
		m_OutputBuffer = Anim.m_OutputBuffer->Clone();

	if (Anim.m_BoneBuffer)
		m_BoneBuffer = Anim.m_BoneBuffer->Clone();

	if (Anim.m_BoneRootBuffer)
		m_BoneRootBuffer = Anim.m_BoneRootBuffer->Clone();
	m_AnimationUpdateShader = Anim.m_AnimationUpdateShader;

	m_mapSequence.clear();

	auto	iter = Anim.m_mapSequence.begin();
	auto	iterEnd = Anim.m_mapSequence.end();

	for (; iter != iterEnd; ++iter)
	{
		m_mapSequence.insert(std::make_pair(iter->first, iter->second));
	}

	m_Sequence = FindSequence(Anim.m_Sequence->GetName());


	//직접 생성(초기화)

	m_vecBoneMatrix.resize(m_Skeleton->GetBoneCount());
	m_RootBoneMatrix.resize(2);


	D3D11_BUFFER_DESC	Desc = {};

	Desc.ByteWidth = sizeof(Matrix) * (unsigned int)m_Skeleton->GetBoneCount();
	Desc.BindFlags = 0;
	Desc.Usage = D3D11_USAGE_STAGING;
	Desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;

	CDevice::GetInst()->GetDevice()->CreateBuffer(&Desc, nullptr, &m_BoneDataBuffer);

	D3D11_MAPPED_SUBRESOURCE	Map = {};

	CDevice::GetInst()->GetContext()->Map(m_BoneDataBuffer, 0, D3D11_MAP_READ, 0, &Map);

	m_BoneResourceAddress = Map.pData;

	CDevice::GetInst()->GetContext()->Unmap(m_BoneDataBuffer, 0);

	Desc = {};

	Desc.ByteWidth = sizeof(Matrix) * (unsigned int)m_Skeleton->GetBoneCount();
	Desc.BindFlags = 0;
	Desc.Usage = D3D11_USAGE_STAGING;
	Desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;

	CDevice::GetInst()->GetDevice()->CreateBuffer(&Desc, nullptr, &m_BoneOutputDataBuffer);

	CDevice::GetInst()->GetContext()->Map(m_BoneOutputDataBuffer, 0, D3D11_MAP_READ, 0, &Map);

	m_BoneOutputResourceAddress = Map.pData;

	CDevice::GetInst()->GetContext()->Unmap(m_BoneOutputDataBuffer, 0);

	Desc = {};

	Desc.ByteWidth = sizeof(Matrix) * (UINT)m_RootBoneMatrix.size();
	Desc.BindFlags = 0;
	Desc.Usage = D3D11_USAGE_STAGING;
	Desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;

	CDevice::GetInst()->GetDevice()->CreateBuffer(&Desc, nullptr, &m_BoneRootDataBuffer);

	CDevice::GetInst()->GetContext()->Map(m_BoneRootDataBuffer, 0, D3D11_MAP_READ, 0, &Map);

	m_BoneRootResourceAddress = Map.pData;

	CDevice::GetInst()->GetContext()->Unmap(m_BoneRootDataBuffer, 0);
}
CAnimation::~CAnimation()
{
	SAFE_RELEASE(m_BoneDataBuffer);
	SAFE_RELEASE(m_BoneOutputDataBuffer);
	SAFE_DELETE(m_CBuffer);
	SAFE_DELETE(m_OutputBuffer);
	SAFE_DELETE(m_BoneBuffer);


	SAFE_DELETE(m_BoneRootBuffer);
	SAFE_RELEASE(m_BoneRootDataBuffer);
	SAFE_RELEASE(m_Skeleton);
}

void CAnimation::SetRootBoneIndex(const std::string& Name)
{
	m_Skeleton->SetRootBoneIndex(Name);
	m_RootBoneIndex = m_Skeleton->m_RootBoneIndex;
	m_CBuffer->SetRootBoneIndex(m_RootBoneIndex);
}
void CAnimation::SetSkeleton(CSkeleton* Skeleton)
{

	SAFE_RELEASE(m_Skeleton);

	if (Skeleton)
		m_Skeleton = Skeleton->Clone();
}
CSkeleton* CAnimation::GetSkeleton()
{
	return m_Skeleton;
}
Matrix CAnimation::GetSkeletonMatrix(const std::string& Name)
{
	int Index = m_Skeleton->GetBoneIndex(Name);
	return m_vecBoneMatrix[Index];
}
int CAnimation::GetCurFrame()
{
	return m_CBuffer->GetCurrentFrame();
}
int CAnimation::GetEndFrame()
{
	return m_Sequence->m_FrameLength - m_Sequence->m_RootLastFrame;
}
void CAnimation::AddAnimationSequence(const std::string& Name, float fTime, bool RootMotion, int RootLastFrame, bool RootMotionX, bool RootMotionY, bool RootMotionZ, bool Loop)
{
	CAnimationSequence* Sequence = FindSequence(Name);

	if (Sequence)
		return;

	Sequence = m_Scene->GetResource()->FindAnimationSequence(Name);
	if (!Sequence)
		return;
	Sequence->SetRootMotion(RootMotion);
	Sequence->SetRootMotionX(RootMotionX);
	Sequence->SetRootMotionY(RootMotionY);
	Sequence->SetRootMotionZ(RootMotionZ);
	Sequence->SetRootLastFrame(RootLastFrame);
	Sequence->SetPlayFrame(60);
	Sequence->SetLoop(Loop);
	//Sequence->SetPlayTime(fTime);

	m_mapSequence.insert(std::make_pair(Name, Sequence));

	if (!m_Sequence)
	{
		m_Sequence = Sequence;
		//엔진에서 이것이 에디터라고 한다면 RootMotion는 기본적으로 false
		if (CEngine::GetInst()->IsEditor())
		{
			m_Sequence->m_RootMotion = false;
		}
	}
}
void CAnimation::ChangeAnimation(const std::string& Name)
{
	if (m_mapSequence.empty())
		return;

	if (m_Sequence->GetName() == Name)
		return;

	m_ChangeSequence = FindSequence(Name);

	//엔진에서 이것이 에디터라고 한다면 RootMotion는 기본적으로 false
	if (CEngine::GetInst()->IsEditor())
	{
		m_ChangeSequence->m_RootMotion = false;
	}
}
CAnimationSequence* CAnimation::FindSequence(const std::string& Name)
{
	auto    iter = m_mapSequence.find(Name);

	if (iter == m_mapSequence.end())
		return nullptr;

	return iter->second;
}
const std::string& CAnimation::GetRootBoneName()
{
	Bone* bone = m_Skeleton->GetBone(m_RootBoneIndex);
	return bone->strName;
}
void CAnimation::GetAllBone(std::vector<Bone*>& AllBone)
{
	m_Skeleton->GetAllBone(AllBone);
}
void CAnimation::ResetSequence()
{
	m_GlobalTime = 0.f;
}

void CAnimation::Init()
{
	m_AnimationUpdateShader = (CComputeShader*)CShaderManager::GetInst()->FindShader("AnimationUpdateShader");

	m_CBuffer = new CAnimationUpdateConstantBuffer;

	m_CBuffer->Init();
}
void CAnimation::Start()
{
	m_vecBoneMatrix.resize(m_Skeleton->GetBoneCount());
	m_RootBoneMatrix.resize(2);
	m_OutputBuffer = new CStructuredBuffer;

	m_OutputBuffer->Init("OutputBone", sizeof(Matrix), (unsigned int)m_Skeleton->GetBoneCount(), 0, false, CBT_COMPUTE);

	m_BoneBuffer = new CStructuredBuffer;

	m_BoneBuffer->Init("BoneBuffer", sizeof(Matrix), (unsigned int)m_Skeleton->GetBoneCount(), 1, false, CBT_COMPUTE);

	m_BoneRootBuffer = new CStructuredBuffer;

	m_BoneRootBuffer->Init("BoneRootBuffer", sizeof(Matrix), (unsigned int)m_RootBoneMatrix.size(), 1, false, CBT_COMPUTE);

	D3D11_BUFFER_DESC	Desc = {};

	Desc.ByteWidth = sizeof(Matrix) * (unsigned int)m_Skeleton->GetBoneCount();
	Desc.BindFlags = 0;
	Desc.Usage = D3D11_USAGE_STAGING;
	Desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;

	CDevice::GetInst()->GetDevice()->CreateBuffer(&Desc, nullptr, &m_BoneDataBuffer);

	D3D11_MAPPED_SUBRESOURCE	Map = {};

	CDevice::GetInst()->GetContext()->Map(m_BoneDataBuffer, 0, D3D11_MAP_READ, 0, &Map);

	m_BoneResourceAddress = Map.pData;

	CDevice::GetInst()->GetContext()->Unmap(m_BoneDataBuffer, 0);



	Desc = {};

	Desc.ByteWidth = sizeof(Matrix) * (unsigned int)m_Skeleton->GetBoneCount();
	Desc.BindFlags = 0;
	Desc.Usage = D3D11_USAGE_STAGING;
	Desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;

	CDevice::GetInst()->GetDevice()->CreateBuffer(&Desc, nullptr, &m_BoneOutputDataBuffer);

	CDevice::GetInst()->GetContext()->Map(m_BoneOutputDataBuffer, 0, D3D11_MAP_READ, 0, &Map);

	m_BoneOutputResourceAddress = Map.pData;

	CDevice::GetInst()->GetContext()->Unmap(m_BoneOutputDataBuffer, 0);

	Desc = {};

	Desc.ByteWidth = sizeof(Matrix) * (UINT)m_RootBoneMatrix.size();
	Desc.BindFlags = 0;
	Desc.Usage = D3D11_USAGE_STAGING;
	Desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;

	CDevice::GetInst()->GetDevice()->CreateBuffer(&Desc, nullptr, &m_BoneRootDataBuffer);

	CDevice::GetInst()->GetContext()->Map(m_BoneRootDataBuffer, 0, D3D11_MAP_READ, 0, &Map);

	m_BoneRootResourceAddress = Map.pData;

	CDevice::GetInst()->GetContext()->Unmap(m_BoneRootDataBuffer, 0);
}
void CAnimation::Update(float DeltaTime)
{
	if (!m_Skeleton)
		return;
	m_End = false;
	m_EndNextFrame = false;
	m_GlobalTime += DeltaTime;

	if (m_ChangeSequence)
	{
		m_Sequence = m_ChangeSequence;
		m_ChangeSequence = nullptr;
		m_GlobalTime = DeltaTime;
		m_RootMotion.clear();
		m_IsRootMotionUpdate = false;

		m_PrevRootMotionPos = Vector3::Zero;
		m_NextRootMotionPos = Vector3::Zero;
	}

	if (!m_Editor)
	{
		// 바꿀 모션이 없을 경우
		m_SequenceProgress = m_GlobalTime / m_Sequence->m_TimeLength;

		while (m_GlobalTime >= m_Sequence->m_TimeLength)
		{
			m_GlobalTime -= m_Sequence->m_TimeLength;
			m_End = true;
		}

		m_CBuffer->SetChangeAnimation(false);
		m_CBuffer->SetChangeRatio(0.f);
		m_CBuffer->SetChangeFrameCount(0);

		float	AnimationTime = m_GlobalTime + m_Sequence->m_StartTime;

		int	StartFrame = 0;
		int	EndFrame = m_Sequence->m_FrameLength - m_Sequence->m_RootLastFrame;

		int Frame = (int)(AnimationTime / m_Sequence->m_FrameTime);
		int	NextFrameIndex = Frame + 1;

		if (NextFrameIndex >= EndFrame)
		{
			if (!m_Sequence->m_Loop)
			{
				m_GlobalTime -= DeltaTime;
				AnimationTime = m_GlobalTime + m_Sequence->m_StartTime;
				Frame = Frame - 1;
				NextFrameIndex = NextFrameIndex - 1;
				m_SequenceEndFrame = true;
				m_EndNextFrame = true;
				m_End = true;
			}
			else
			{
				NextFrameIndex = StartFrame;
				m_SequenceEndFrame = true;
				m_IsRootMotionUpdate = true;
			}
		}
		if (NextFrameIndex >= EndFrame - 1)
		{
			m_EndNextFrame = true;
			m_IsRootMotionUpdate = true;
		}
		float	Ratio = (AnimationTime - m_Sequence->m_FrameTime * Frame) / m_Sequence->m_FrameTime;

		m_CBuffer->SetFrameCount(m_Sequence->m_FrameLength);
		m_CBuffer->SetCurrentFrame(Frame);
		m_CBuffer->SetNextFrame(NextFrameIndex);
		m_CBuffer->SetRatio(Ratio);
		m_CBuffer->SetBoneCount((int)m_Skeleton->GetBoneCount());
		//엔진자체에서 에디터가 아닐시
		if (!CEngine::GetInst()->IsEditor())
		{
			{
				auto	iter = m_Sequence->m_vecNotify.begin();
				auto	iterEnd = m_Sequence->m_vecNotify.end();

				for (; iter != iterEnd; ++iter)
				{
					if ((*iter)->Time == Frame && m_PrevFrame != Frame)
					{
						if (m_Owner)
							m_Owner->CallNotify((*iter)->Name);

					}
				}
			}
			{
				auto	iter = m_Sequence->m_vecSoundNotify.begin();
				auto	iterEnd = m_Sequence->m_vecSoundNotify.end();

				for (; iter != iterEnd; ++iter)
				{
					if ((*iter)->Time == Frame && m_PrevFrame != Frame)
					{
						if ((*iter)->m_Sound)
							(*iter)->m_Sound->Play3D(m_Owner->GetWorldPos());
					}
				}
			}
		}
		
		m_PrevFrame = Frame;
		
	}
	//에디터로 애니메이션 직접재생시
#pragma region Editor
	else
	{
		float	AnimationTime = m_EditorTime + m_Sequence->m_StartTime;

		int	StartFrame = 0;
		int	EndFrame = m_Sequence->m_FrameLength - m_Sequence->m_RootLastFrame;

		int Frame = (int)(AnimationTime / m_Sequence->m_FrameTime);
		int	NextFrameIndex = Frame + 1;

		if (NextFrameIndex >= EndFrame)
		{
			NextFrameIndex = StartFrame;
			m_SequenceEndFrame = true;
			m_End = true;
		}

		float	Ratio = (AnimationTime - m_Sequence->m_FrameTime * Frame) / m_Sequence->m_FrameTime;

		m_CBuffer->SetFrameCount(m_Sequence->m_FrameLength);
		m_CBuffer->SetCurrentFrame(Frame);
		m_CBuffer->SetNextFrame(NextFrameIndex);
		m_CBuffer->SetRatio(Ratio);
		m_CBuffer->SetBoneCount((int)m_Skeleton->GetBoneCount());

		m_PrevFrame = Frame;
	}
#pragma endregion


	m_CBuffer->SetRowIndex(0);

	// Bone 결과 버퍼 갱신
	m_OutputBuffer->SetShader(0);

	m_CBuffer->UpdateCBuffer();
	m_Sequence->SetShader();
	m_Skeleton->SetShader();
	m_BoneBuffer->SetShader(1);
	m_BoneRootBuffer->SetShader(2);
	unsigned int	GroupX = (unsigned int)m_Skeleton->GetBoneCount() / 256 + 1;
	m_AnimationUpdateShader->Excute(GroupX, 1, 1);

	m_BoneRootBuffer->ResetShader(2);
	m_BoneBuffer->ResetShader(1);
	m_Skeleton->ResetShader();
	m_Sequence->ResetShader();
	m_OutputBuffer->ResetShader(0);

	CDevice::GetInst()->GetContext()->CopyResource(m_BoneDataBuffer, m_BoneBuffer->GetBuffer());
	memcpy(&m_vecBoneMatrix[0], m_BoneResourceAddress, sizeof(Matrix) * m_vecBoneMatrix.size());
	CDevice::GetInst()->GetContext()->CopyResource(m_BoneRootDataBuffer, m_BoneRootBuffer->GetBuffer());
	memcpy(&m_RootBoneMatrix[0], m_BoneRootResourceAddress, sizeof(Matrix) * m_RootBoneMatrix.size());
	if (m_Sequence->IsRootMotion())
	{
		if (m_RootBoneIndex != -1)
		{
			m_PrevRootMotionPos = m_NextRootMotionPos;
			Matrix mat;
			mat.GetXMMatrixDecompose(m_RootBoneMatrix[0]);
			if (m_Sequence->IsRootMotionX())
			{
				m_NextRootMotionPos.x = mat[0][0];
			}
			//y와 z는 반대이다.
			if (m_Sequence->IsRootMotionY())
			{

				m_NextRootMotionPos.z = -mat[0][1];
			}
			if (m_Sequence->IsRootMotionZ())
			{

				m_NextRootMotionPos.y = mat[0][2];
			}
		}
		if (m_CBuffer->GetCurrentFrame() != 0 && m_CBuffer->GetNextFrame() != 0)
		{
				m_MoveRootMotionPos = m_NextRootMotionPos - m_PrevRootMotionPos;
		}
		if (m_CBuffer->GetCurrentFrame() < m_RootMotion.size())
		{
			m_MoveRootMotionPos = m_RootMotion[m_CBuffer->GetCurrentFrame()];
			if (m_CBuffer->GetCurrentFrame() < m_Sequence->m_EndFrame && m_CBuffer->GetCurrentFrame()+1<m_RootMotion.size())
			{
				m_MoveRootMotionPos += m_RootMotion[m_CBuffer->GetCurrentFrame()+1] ;
				m_MoveRootMotionPos *= 0.5f;
			}
		}
		else if(m_RootMotion.size()==0)
		{
			m_RootMotion.push_back(m_MoveRootMotionPos);
		}
		else
		{
			m_RootMotion.push_back(m_MoveRootMotionPos);
		}
		if (m_CBuffer->GetCurrentFrame() <= m_Sequence->GetStartFrame())
		{
			if (m_IsRootMotionUpdate)
			{
				m_MoveRootMotionPos = m_RootMotion[m_CBuffer->GetNextFrame() + 1];
			}
			else
			{
				m_MoveRootMotionPos = Vector3::Zero;
			}
		}
		CGameObject* Owner = m_Owner->GetOwner();
		if (!m_ChangeSequence)
		{
			if (m_MoveRootMotionPos.z > 0.f && m_PrevRootMotionPos.z < -0.5)
			{

			}
			else if (m_MoveRootMotionPos.z < 0.f && m_PrevRootMotionPos.z > 0.5)
			{

			}
			else
			{

				Owner->AddWorldPos(Owner->GetAxis(AXIS_Z) * (m_MoveRootMotionPos.z));
				//옆
				Owner->AddWorldPos(Owner->GetAxis(AXIS_X) * (m_MoveRootMotionPos.x));
				////위
				//Owner->AddWorldPos(Owner->GetAxis(AXIS_Y) * (m_MoveRootMotionPos.y));
			}
		}
	}
	m_Skeleton->Update(DeltaTime, m_vecBoneMatrix, m_Owner->GetWorldMatrix());
}
void CAnimation::PostUpdate(float DeltaTime)
{
}
void CAnimation::SetShader()
{
	m_OutputBuffer->SetShader(106, CBT_VERTEX);
}
void CAnimation::ResetShader()
{
	m_OutputBuffer->ResetShader(106, CBT_VERTEX);
}
CAnimation* CAnimation::Clone()
{
	return new CAnimation(*this);
}