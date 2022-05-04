
#include "PoseCopy.h"
#include "Resource/Animation.h"
CPoseCopy::CPoseCopy() :
	m_Animation(nullptr)
{
}

CPoseCopy::CPoseCopy(const CPoseCopy& obj) :
	CClientObject(obj)
{
	m_Root = (CSceneComponent*)FindSceneComponent("Root");
	m_Mesh = (CAnimationMeshComponent*)FindSceneComponent("Mesh");
}

CPoseCopy::~CPoseCopy()
{
}

void CPoseCopy::Start()
{
	CClientObject::Start();
}

bool CPoseCopy::Init()
{
	CClientObject::Init();
	m_Root = CreateSceneComponent<CSceneComponent>("Root");
	m_Mesh = CreateSceneComponent<CAnimationMeshComponent>("Mesh");

	SetRootComponent(m_Root);

	m_Root->AddChild(m_Mesh);
	m_Mesh->SetInheritRotY(true);
	m_Mesh->SetInheritPosZ(true);


	m_Animation = new CPoseableAnimation;
	m_Mesh->SetPoseableAnimation(m_Animation);
	m_Animation->Init();


	m_Mesh->SetWorldScale(1.f, 1.f, 1.f);
	m_Mesh->SetWorldPos(0.f, 0.f, 0.f);
	m_Mesh->SetRelativeRotation(-90.f, 0.f, 0.f);

	SetLifeTime(0.5f);
	return true;
}

void CPoseCopy::Update(float DeltaTime)
{
	CClientObject::Update(DeltaTime);
	m_Mesh->SetAllOpacity(m_LifeTime *2.f);
}

void CPoseCopy::PostUpdate(float DeltaTime)
{
	CClientObject::PostUpdate(DeltaTime);
}

void CPoseCopy::Collision(float DeltaTime)
{
	CClientObject::Collision(DeltaTime);
}

void CPoseCopy::Render(float DeltaTime)
{
	CClientObject::Render(DeltaTime);
}

CPoseCopy* CPoseCopy::Clone()
{
	return new CPoseCopy(*this);
}

void CPoseCopy::PoseCopy(CAnimationMeshComponent* Mesh, const Vector3& Color)
{
	m_Mesh->SetMesh(Mesh->GetMesh());
	CAnimation* CopyAnimation=Mesh->GetAnimation();
	m_Animation->SetGlobalTime(CopyAnimation->GetGlobalTime());
	m_Animation->AddAnimationSequence(CopyAnimation->GetSequence()->GetName());
	m_Animation->SetRootBoneIndex(CopyAnimation->GetRootBoneName());
	SetWorldPos(Mesh->GetWorldPos());
	SetWorldRotation(Mesh->GetWorldRotation());
	m_Mesh->SetAllColor(Color);
	m_Mesh->SetEmissiveColor(Vector3(1.f,1.f,1.f));
	m_Mesh->SetAllTransparency(true);
	m_Mesh->SetAllBumpEnable(false);
	
}
