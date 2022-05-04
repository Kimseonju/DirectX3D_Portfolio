#include "PoseableAnimation.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "StructuredBuffer.h"
#include "ComputeShader.h"
#include "AnimationUpdateConstantBuffer.h"
#include "ShaderManager.h"
#include "../Component/AnimationMeshComponent.h"
#include "../Device.h"
#include "../Engine.h"

CPoseableAnimation::CPoseableAnimation() :
	m_Skeleton(nullptr),
	m_AnimationUpdateShader(nullptr),
	m_CBuffer(nullptr),
	m_OutputBuffer(nullptr),
	m_BoneBuffer(nullptr),
	m_BoneDataBuffer(nullptr),
	m_BoneResourceAddress(nullptr),
	m_GlobalTime(0.f),
	m_RootBoneIndex(-1),
	m_Owner(nullptr),
	m_Scene(nullptr),
	m_BoneOutputDataBuffer(nullptr),
	m_BoneOutputResourceAddress(nullptr)
{
}
CPoseableAnimation::CPoseableAnimation(const CPoseableAnimation& Anim)
{
	if (Anim.m_Skeleton)
		m_Skeleton = Anim.m_Skeleton->Clone();

	m_GlobalTime = 0.f;
	m_Scene = Anim.m_Scene;
	if (Anim.m_CBuffer)
		m_CBuffer = Anim.m_CBuffer->Clone();

	if (Anim.m_OutputBuffer)
		m_OutputBuffer = Anim.m_OutputBuffer->Clone();

	if (Anim.m_BoneBuffer)
		m_BoneBuffer = Anim.m_BoneBuffer->Clone();



	//���� ����(�ʱ�ȭ)

	m_vecBoneMatrix.resize(m_Skeleton->GetBoneCount());


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

}
CPoseableAnimation::~CPoseableAnimation()
{
	SAFE_RELEASE(m_BoneDataBuffer);
	SAFE_RELEASE(m_BoneOutputDataBuffer);
	SAFE_DELETE(m_CBuffer);
	SAFE_DELETE(m_OutputBuffer);
	SAFE_DELETE(m_BoneBuffer);


	SAFE_RELEASE(m_Skeleton);
}

void CPoseableAnimation::SetSkeleton(CSkeleton* Skeleton)
{

	SAFE_RELEASE(m_Skeleton);

	if (Skeleton)
		m_Skeleton = Skeleton->Clone();
}
CSkeleton* CPoseableAnimation::GetSkeleton()
{
	return m_Skeleton;
}

void CPoseableAnimation::SetRootBoneIndex(const std::string& Name)
{
	m_Skeleton->SetRootBoneIndex(Name);
	m_RootBoneIndex = m_Skeleton->m_RootBoneIndex;
	m_CBuffer->SetRootBoneIndex(m_RootBoneIndex);
}

void CPoseableAnimation::AddAnimationSequence(const std::string& Name, float fTime)
{
	CAnimationSequence* Sequence=nullptr;

	Sequence = m_Scene->GetResource()->FindAnimationSequence(Name);
	if (!Sequence)
		return;
	Sequence->SetPlayFrame(60);

	if (!m_Sequence)
	{
		m_Sequence = Sequence;
		//�������� �̰��� �����Ͷ�� �Ѵٸ� RootMotion�� �⺻������ false
	}
}


void CPoseableAnimation::Init()
{
	m_AnimationUpdateShader = (CComputeShader*)CShaderManager::GetInst()->FindShader("AnimationUpdateShader");

	m_CBuffer = new CAnimationUpdateConstantBuffer;

	m_CBuffer->Init();
	m_CBuffer->SetRootBoneIndex(-1);
}
void CPoseableAnimation::Start()
{
	m_vecBoneMatrix.resize(m_Skeleton->GetBoneCount());
	m_OutputBuffer = new CStructuredBuffer;

	m_OutputBuffer->Init("OutputBone", sizeof(Matrix), (unsigned int)m_Skeleton->GetBoneCount(), 0, false, CBT_COMPUTE);

	m_BoneBuffer = new CStructuredBuffer;

	m_BoneBuffer->Init("BoneBuffer", sizeof(Matrix), (unsigned int)m_Skeleton->GetBoneCount(), 1, false, CBT_COMPUTE);

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
}
void CPoseableAnimation::Update(float DeltaTime)
{
	if (!m_Skeleton)
		return;

	m_CBuffer->SetChangeAnimation(false);
	m_CBuffer->SetChangeRatio(0.f);
	m_CBuffer->SetChangeFrameCount(0);

	float	AnimationTime = m_GlobalTime + m_Sequence->m_StartTime;

	int	StartFrame = 0;
	int	EndFrame = m_Sequence->m_FrameLength;

	int Frame = (int)(AnimationTime / m_Sequence->m_FrameTime);
	int	NextFrameIndex = Frame + 1;

	if (NextFrameIndex >= EndFrame)
	{
		NextFrameIndex = StartFrame;
	}
	
	float	Ratio = (AnimationTime - m_Sequence->m_FrameTime * Frame) / m_Sequence->m_FrameTime;

	m_CBuffer->SetFrameCount(m_Sequence->m_FrameLength);
	m_CBuffer->SetCurrentFrame(Frame);
	m_CBuffer->SetNextFrame(NextFrameIndex);
	m_CBuffer->SetRatio(Ratio);
	m_CBuffer->SetBoneCount((int)m_Skeleton->GetBoneCount());
		
	m_CBuffer->SetRowIndex(0);

	// Bone ��� ���� ����
	m_OutputBuffer->SetShader(0);

	// ������۸� �����Ѵ�.
	m_CBuffer->UpdateCBuffer();

	// Sequence�� �ִ� ����ȭ ���۸� �����Ѵ�.
	m_Sequence->SetShader();

	// Offset ����� �����Ѵ�.
	m_Skeleton->SetShader();

	m_BoneBuffer->SetShader(1);
	unsigned int	GroupX = (unsigned int)m_Skeleton->GetBoneCount() / 256 + 1;

	m_AnimationUpdateShader->Excute(GroupX, 1, 1);

	m_BoneBuffer->ResetShader(1);
	m_Skeleton->ResetShader();
	m_Sequence->ResetShader();
	m_OutputBuffer->ResetShader(0);


	CDevice::GetInst()->GetContext()->CopyResource(m_BoneDataBuffer, m_BoneBuffer->GetBuffer());
	memcpy(&m_vecBoneMatrix[0], m_BoneResourceAddress, sizeof(Matrix) * m_vecBoneMatrix.size());

	m_Skeleton->Update(DeltaTime, m_vecBoneMatrix, m_Owner->GetWorldMatrix());
}
void CPoseableAnimation::PostUpdate(float DeltaTime)
{
}
void CPoseableAnimation::SetShader()
{
	m_OutputBuffer->SetShader(106, CBT_VERTEX);
}
void CPoseableAnimation::ResetShader()
{
	m_OutputBuffer->ResetShader(106, CBT_VERTEX);
}
CPoseableAnimation* CPoseableAnimation::Clone()
{
	return new CPoseableAnimation(*this);
}