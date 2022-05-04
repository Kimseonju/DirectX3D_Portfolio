
#include "KianaFire.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Resource/Material.h"

CKianaFire::CKianaFire():
	m_AnimationLeft(nullptr),
	m_AnimationRight(nullptr),
	m_State(nullptr)
{
}

CKianaFire::CKianaFire(const CKianaFire& obj) : CClientObject(obj)
{
	m_BillboardLeft = (CBillboardComponent*)FindSceneComponent("BillboardLeft");
	m_BillboardRight = (CBillboardComponent*)FindSceneComponent("BillboardRight");
}

CKianaFire::~CKianaFire()
{
}

void CKianaFire::Start()
{
	CClientObject::Start();
}

bool CKianaFire::Init()
{
	CClientObject::Init();

	m_BillboardLeft = CreateSceneComponent<CBillboardComponent>("BillboardLeft");
	m_BillboardRight = CreateSceneComponent<CBillboardComponent>("BillboardRight");

	SetRootComponent(m_BillboardLeft);
	m_BillboardLeft->AddChild(m_BillboardRight);
	m_BillboardRight->SetRelativeRotationX(180.f);
	m_BillboardRight->SetRelativeRotationY(180.f);
	m_BillboardRight->SetRelativeRotationZ(90.f);

	m_BillboardLeft->CreateAnimation3D_Tex<CAnimation3D_Tex>();
	m_BillboardRight->CreateAnimation3D_Tex<CAnimation3D_Tex>();
	m_AnimationLeft = m_BillboardLeft->GetAnimation3D_Tex();
	m_AnimationLeft->AddAnimationSequence2D("Effect_Wave08");
	m_AnimationRight = m_BillboardRight->GetAnimation3D_Tex();
	m_AnimationRight->AddAnimationSequence2D("Effect_Wave08");
	m_BillboardLeft->SetAnimation2DEnable(true);
	m_BillboardRight->SetAnimation2DEnable(true);

	CMaterial* Mtrl = m_pScene->GetResource()->FindMaterial("KianaFire");
	Mtrl->SetBaseColor(1.5f, 1.5f, 0.f, 1.f);
	m_BillboardLeft->AddMaterial(Mtrl);
	m_BillboardLeft->SetWorldScale(1.f, 1.f, 1.f);
	m_BillboardRight->AddMaterial(Mtrl);
	m_BillboardRight->SetWorldScale(1.f, 1.f, 1.f);
	return true;
}

void CKianaFire::Update(float DeltaTime)
{
	CClientObject::Update(DeltaTime);
	m_BillboardRight->SetRelativeRotationX(-GetWorldRotation().x);
	if (m_AnimationLeft->IsFrameEnd())
	{
		Active(false);
	}
}

void CKianaFire::PostUpdate(float DeltaTime)
{
	CClientObject::PostUpdate(DeltaTime);
}

void CKianaFire::Collision(float DeltaTime)
{
	CClientObject::Collision(DeltaTime);
}

void CKianaFire::Render(float DeltaTime)
{
	CClientObject::Render(DeltaTime);
}

CKianaFire* CKianaFire::Clone()
{
	return new CKianaFire(*this);
}

void CKianaFire::SetMatrixPos(const Matrix& mat)
{
	Matrix mmat;
	mmat = mmat.GetXMMatrixDecompose(mat);
	SetWorldPos(Vector3(mmat[0][0], mmat[0][1], mmat[0][2]));
}

void CKianaFire::SetRotation(const Vector3& Rot)
{
	m_BillboardLeft->SetWorldPos(Rot);
}
