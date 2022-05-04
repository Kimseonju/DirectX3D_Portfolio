
#include "AnimationMeshComponent.h"
#include "../Resource/Animation.h"
#include "../Resource/PoseableAnimation.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "Transform.h"
#include "../Resource/Material.h"
#include "../Resource/AnimationMesh.h"
#include "../Resource/Skeleton.h"

CAnimationMeshComponent::CAnimationMeshComponent()
{
	m_PrimitiveType = PrimitiveComponent_Type::Primitive3D;
	m_ClassType = Component_Class_Type::AnimationMesh;
	m_3DType = RT3D_Default;
	m_Animation = nullptr;
	m_Skeleton = nullptr;
	m_PoseableAnimation = nullptr;
	SetTransformState(Transform_State::None);
}

CAnimationMeshComponent::CAnimationMeshComponent(const CAnimationMeshComponent& com) :
	CPrimitiveComponent(com)
{
	SetMesh(com.m_pMesh);

	if (com.m_Animation)
		m_Animation = com.m_Animation->Clone();

	if (com.m_PoseableAnimation)
		m_PoseableAnimation = com.m_PoseableAnimation->Clone();
	m_Animation->SetOwner(this);

	if (m_Skeleton)
	{
		m_BoneSocket = m_Skeleton->GetSocket(m_SocketName);

		m_pTransform->SetSocket(m_BoneSocket);
	}
}

CAnimationMeshComponent::~CAnimationMeshComponent()
{
	SAFE_DELETE(m_Animation);
	SAFE_DELETE(m_PoseableAnimation);
}

void CAnimationMeshComponent::AddChild(CSceneComponent* Child, const std::string& SocketName)
{
	CPrimitiveComponent::AddChild(Child, SocketName);

	if (m_Animation)
	{
		CSkeleton* Skeleton = m_Animation->GetSkeleton();
		m_BoneSocket = Skeleton->GetSocket(m_SocketName);

		Child->SetSocket(m_BoneSocket);
	}
	else if (m_PoseableAnimation)
	{
		CSkeleton* Skeleton = m_PoseableAnimation->GetSkeleton();
		m_BoneSocket = Skeleton->GetSocket(m_SocketName);

		Child->SetSocket(m_BoneSocket);
	}
	else
	{
		if (m_Skeleton)
		{
			m_BoneSocket = m_Skeleton->GetSocket(m_SocketName);

			Child->SetSocket(m_BoneSocket);
		}
	}
	
}

void CAnimationMeshComponent::SetAnimation(CAnimation* Animation)
{
	m_Animation = Animation;

	if (m_Animation)
	{
		m_Animation->SetScene(m_pScene);
		m_Animation->SetOwner(this);

		m_Animation->SetSkeleton(m_Skeleton);
	}
}

void CAnimationMeshComponent::SetPoseableAnimation(CPoseableAnimation* Animation)
{
	m_PoseableAnimation = Animation;

	if (m_PoseableAnimation)
	{
		m_PoseableAnimation->SetScene(m_pScene);
		m_PoseableAnimation->SetOwner(this);

		m_PoseableAnimation->SetSkeleton(m_Skeleton);
		m_3DType = RT3D_Particle;
	}
}

CMesh* CAnimationMeshComponent::GetMesh() const
{
	return (CMesh*)m_pMesh.Get();
}

void CAnimationMeshComponent::SetMesh(CMesh* pMesh)
{
	m_pMesh = (CAnimationMesh*)m_pScene->GetResource()->FindMesh(pMesh->GetName());

	m_Skeleton = m_pMesh->GetSkeleton();

	if (m_Animation)
		m_Animation->SetSkeleton(m_Skeleton);

	if (m_PoseableAnimation)
		m_PoseableAnimation->SetSkeleton(m_Skeleton);
	Vector3 Min = m_pMesh->GetMin();
	Vector3 Max = m_pMesh->GetMax();

	m_pTransform->SetMeshSize(Max - Min);

	m_vecMaterialSlot.clear();

	const std::vector<CSharedPtr<CMaterial>>* pMaterialSlots = m_pMesh->GetMaterialSlots();

	auto    iter = pMaterialSlots->begin();
	auto    iterEnd = pMaterialSlots->end();

	for (; iter != iterEnd; ++iter)
	{
		CMaterial* pClone = (*iter)->Clone();

		pClone->SetScene(m_pScene);
		m_vecMaterialSlot.push_back(pClone);

		SAFE_RELEASE(pClone);
	}
}

void CAnimationMeshComponent::SetMesh(const std::string& Name)
{
	m_pMesh = (CAnimationMesh*)m_pScene->GetResource()->FindMesh(Name);

	m_Skeleton = m_pMesh->GetSkeleton();

	if (m_Animation)
		m_Animation->SetSkeleton(m_Skeleton);

	if (m_PoseableAnimation)
		m_PoseableAnimation->SetSkeleton(m_Skeleton);
	Vector3 Min = m_pMesh->GetMin();
	Vector3 Max = m_pMesh->GetMax();

	m_pTransform->SetMeshSize(Max - Min);

	m_vecMaterialSlot.clear();

	const std::vector<CSharedPtr<CMaterial>>* pMaterialSlots =
		m_pMesh->GetMaterialSlots();

	auto    iter = pMaterialSlots->begin();
	auto    iterEnd = pMaterialSlots->end();

	for (; iter != iterEnd; ++iter)
	{
		CMaterial* pClone = (*iter)->Clone();

		pClone->SetScene(m_pScene);
		m_vecMaterialSlot.push_back(pClone);

		SAFE_RELEASE(pClone);
	}
}

void CAnimationMeshComponent::Start()
{
	CPrimitiveComponent::Start();

	if (m_Animation)
		m_Animation->Start();

	if (m_PoseableAnimation)
		m_PoseableAnimation->Start();
	if (m_Skeleton)
	{
		m_BoneSocket = m_Skeleton->GetSocket(m_SocketName);

		m_pTransform->SetSocket(m_BoneSocket);
	}
}

bool CAnimationMeshComponent::Init()
{
	if (!CPrimitiveComponent::Init())
		return false;

	m_PoseableShader = CShaderManager::GetInst()->FindShader("PoseableAnimationShader");
	return true;
}

void CAnimationMeshComponent::Update(float DeltaTime)
{
	CPrimitiveComponent::Update(DeltaTime);

	if (m_Animation)
		m_Animation->Update(DeltaTime);
	if (m_PoseableAnimation)
		m_PoseableAnimation->Update(DeltaTime);
}

void CAnimationMeshComponent::PostTransformUpdate(float DeltaTime)
{
	CPrimitiveComponent::PostTransformUpdate(DeltaTime);

	if (m_Animation)
		m_Animation->PostUpdate(DeltaTime);
	if (m_PoseableAnimation)
		m_PoseableAnimation->PostUpdate(DeltaTime);
}

void CAnimationMeshComponent::PostUpdate(float DeltaTime)
{
	CPrimitiveComponent::PostUpdate(DeltaTime);

}

void CAnimationMeshComponent::Collision(float DeltaTime)
{
	CPrimitiveComponent::Collision(DeltaTime);
}

void CAnimationMeshComponent::Render(float DeltaTime)
{
	CPrimitiveComponent::Render(DeltaTime);

	if (m_Animation)
		m_Animation->SetShader();
	if (m_PoseableAnimation)
		m_PoseableAnimation->SetShader();

	for (int i = 0; i < (int)m_vecMaterialSlot.size(); ++i)
	{
		m_vecMaterialSlot[i]->SetMaterial();
		if (m_PoseableAnimation)
		{
			m_PoseableShader->SetShader();
		}

		if (m_NotLightShader)
		{
			m_NotLightShader->SetShader();
		}
		m_pMesh->Render(i);

		m_vecMaterialSlot[i]->ResetMaterial();
	}

	if (m_Animation)
		m_Animation->ResetShader();
	if (m_PoseableAnimation)
		m_PoseableAnimation->ResetShader();
}

CAnimationMeshComponent* CAnimationMeshComponent::Clone()
{
	return new CAnimationMeshComponent(*this);
}

void CAnimationMeshComponent::RenderShadow(float DeltaTime)
{
	CPrimitiveComponent::RenderShadow(DeltaTime);

	if (m_Animation)
		m_Animation->SetShader();

	if (m_PoseableAnimation)
		m_PoseableAnimation->SetShader();
	for (int i = 0; i < (int)m_vecMaterialSlot.size(); ++i)
	{
		m_vecMaterialSlot[i]->SetShadowMaterial();

		m_pMesh->Render(i);

		m_vecMaterialSlot[i]->ResetShadowMaterial();
	}

	if (m_Animation)
		m_Animation->ResetShader();
	if (m_PoseableAnimation)
		m_PoseableAnimation->ResetShader();
}

void CAnimationMeshComponent::CallNotify(const std::string& Name)
{
	m_pOwner->AnimationNotify(Name);
}

void CAnimationMeshComponent::SetNotLight()
{
	m_NotLightShader = CShaderManager::GetInst()->FindShader("NotLightShader");
}

void CAnimationMeshComponent::SetRootBoneIndex(const std::string& BoneName)
{
	m_Skeleton->SetRootBoneIndex(BoneName);
}

void CAnimationMeshComponent::Save(FILE* pFile)
{
	CPrimitiveComponent::Save(pFile);
	std::string str = m_pMesh->GetName();

	int Length = (int)strlen(str.c_str());
	fwrite(&Length, sizeof(int), 1, pFile);
	fwrite(str.c_str(), sizeof(char), Length, pFile);
}

void CAnimationMeshComponent::Load(FILE* pFile)
{
	CPrimitiveComponent::Load(pFile);
	int Length = -1;
	char	Name[256] = {};
	fread(&Length, sizeof(int), 1, pFile);
	fread(Name, sizeof(char), Length, pFile);
	SetMesh(Name);
}
