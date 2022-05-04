
#include "PlayerTemp.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Resource/Material.h"
#include "Input.h"

CPlayerTemp::CPlayerTemp() :
	m_Animation(nullptr)
{
}

CPlayerTemp::CPlayerTemp(const CPlayerTemp& obj) :
	CGameObject(obj)
{
	m_Mesh = (CAnimationMeshComponent*)FindSceneComponent("Mesh");
	m_Body = (CColliderSphere*)FindSceneComponent("Body");
	m_Mesh = (CAnimationMeshComponent*)FindSceneComponent("Mesh");
	m_Camera = (CCamera*)FindSceneComponent("Camera");
	m_Arm = (CSpringArm3D*)FindSceneComponent("Arm");
}

CPlayerTemp::~CPlayerTemp()
{
}

void CPlayerTemp::Start()
{
	CGameObject::Start();
}

bool CPlayerTemp::Init()
{
	CGameObject::Init();

	m_Root = CreateSceneComponent<CSceneComponent>("Root");
	m_Mesh = CreateSceneComponent<CAnimationMeshComponent>("Mesh");
	m_Camera = CreateSceneComponent<CCamera>("Camera");
	m_Arm = CreateSceneComponent<CSpringArm3D>("Arm");
	m_Body = CreateSceneComponent<CColliderSphere>("Body");

	SetRootComponent(m_Root);

	m_Root->AddChild(m_Body);

	m_Body->AddChild(m_Mesh);

	m_Mesh->AddChild(m_Arm);

	m_Arm->AddChild(m_Camera);

	m_Body->SetInheritRotY(true);
	m_Mesh->SetInheritRotY(true);

	m_Camera->SetInheritRotX(true);
	m_Camera->SetInheritRotY(true);
	m_Camera->SetInheritRotZ(true);
	m_Arm->SetInheritRotY(false);

	m_Arm->SetRelativeRotationX(25.f);
	m_Arm->SetLength(3.f);
	m_Arm->SetOffset(0.f, 1.f, 0.f);

	m_Mesh->SetMesh("PlayerMesh");

	m_Mesh->SetWorldScale(0.01f, 0.01f, 0.01f);
	m_Mesh->SetWorldPos(0.f, 0.f, 0.f);
	m_Mesh->SetRelativeRotationY(180.f);

	m_Animation = new CAnimation;
	m_Mesh->SetAnimation(m_Animation);
	m_Animation->Init();

	m_Animation->AddAnimationSequence("PlayerIdle");

	CInput::GetInst()->AddKeyCallback("MoveFront", Key_Type::KT_Push, this, &CPlayerTemp::MoveFront);
	CInput::GetInst()->AddKeyCallback("MoveBack", Key_Type::KT_Push, this, &CPlayerTemp::MoveBack);
	CInput::GetInst()->AddKeyCallback("RotationY", Key_Type::KT_Push, this, &CPlayerTemp::RotationY);
	CInput::GetInst()->AddKeyCallback("RotationYInv", Key_Type::KT_Push, this, &CPlayerTemp::RotationYInv);

	for (int i = 0; i < m_Mesh->GetMaterialCount(); ++i)
	{
		m_Mesh->GetMaterial(i)->SetReceiveDecal(false);
	}

	return true;
}

void CPlayerTemp::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CPlayerTemp::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CPlayerTemp::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CPlayerTemp::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CPlayerTemp* CPlayerTemp::Clone()
{
	return new CPlayerTemp(*this);
}

void CPlayerTemp::MoveFront(float Time)
{
	AddRelativePos(GetAxis(AXIS_Z) * 3.f * Time);
}

void CPlayerTemp::MoveBack(float Time)
{
	AddRelativePos(GetAxis(AXIS_Z) * -3.f * Time);
}

void CPlayerTemp::RotationY(float Time)
{
	AddRelativeRotationY(-180.f * Time);
}

void CPlayerTemp::RotationYInv(float Time)
{
	AddRelativeRotationY(180.f * Time);
}
