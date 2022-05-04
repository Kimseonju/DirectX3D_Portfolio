#include "Effect.h"
#include "Scene/Scene.h"

CEffect::CEffect()
{

}

CEffect::CEffect(const CEffect& obj)
{
	m_Root = (CSceneComponent*)FindSceneComponent("Root");
	m_Mesh = (CStaticMeshComponent*)FindSceneComponent("Mesh");
	m_Camera = (CCamera*)FindSceneComponent("Camera");
	m_Arm = (CSpringArm3D*)FindSceneComponent("Arm");
	m_Body = (CColliderSphere*)FindSceneComponent("Body");

}

CEffect::~CEffect()
{

}

void CEffect::Start()
{
	CGameObject::Start();
}

bool CEffect::Init()
{
	CGameObject::Init();

	LoadMeshEffectResource();

	m_Root = CreateSceneComponent<CSceneComponent>("Root");
	m_Mesh = CreateSceneComponent<CStaticMeshComponent>("Mesh");

	// 이펙트 테스트용 카메라이므로 사용할때는 주석처리 or 삭제
	m_Camera = CreateSceneComponent<CCamera>("Camera");
	m_Arm = CreateSceneComponent<CSpringArm3D>("Arm");

	m_Body = CreateSceneComponent<CColliderSphere>("Body");
	m_Mesh->SetRender3DType(Render_Type_3D::RT3D_Particle);

	SetRootComponent(m_Root);
	m_Root->AddChild(m_Body);
	m_Body->AddChild(m_Mesh);
	m_Mesh->AddChild(m_Arm);
	m_Arm->AddChild(m_Camera);

	m_Body->SetInheritRotY(true);
	m_Body->SetDebugRender(false);
	m_Mesh->SetInheritRotY(true);

	m_Camera->SetInheritRotX(true);
	m_Camera->SetInheritRotY(true);
	m_Camera->SetInheritRotZ(true);

	m_Arm->SetInheritRotY(false);
	m_Arm->SetRelativeRotationX(10.f);
	m_Arm->SetRelativeRotationY(180.f);
	m_Arm->SetLength(5.f);
	m_Arm->SetOffset(0.f, 1.f, 0.f);

	m_Mesh->SetMesh("eff_Fire");
	m_Mesh->SetWorldScale(1.f, 1.f, 1.f);
	m_Mesh->SetRelativeRotationY(70.f);
	m_Mesh->SetWorldPos(0.f, 0.f, 0.f);

	// 이펙트 세부 설정 예시
	m_Mesh->GetMaterial(0)->SetTransparency(true);
	m_Mesh->GetMaterial(0)->SetFlowEnable(true);
	m_Mesh->GetMaterial(0)->SetFlowDirection(2);
	m_Mesh->GetMaterial(0)->SetFlowSpeedX(0.5f);
	//m_Mesh->GetMaterial(0)->SetFlowSpeedX(0.6f);

	// 이펙트 색상 설정
	//m_Mesh->GetMaterial(0)->SetBaseColor(Vector4(0.5f, 0.f, 0.f, 0.5f));
	//m_Mesh->GetMaterial(0)->SetEmissiveColor(Vector4(0.1f, 0.5f, 0.2f, 0.9f));
	//m_Mesh->GetMaterial(0)->SetAmbientColor(Vector4(0.5f, 0.f, 0.f, 0.5f));

	return true;
}

void CEffect::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CEffect::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CEffect::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CEffect::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CEffect* CEffect::Clone()
{
	return new CEffect(*this);

}

void CEffect::LoadMeshEffectResource()
{
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "eff_Attack", "Effect/eff_Attack.msh");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "eff_Tornado", "Effect/eff_Tornado.msh");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "eff_Projectile", "Effect/eff_Projectile.msh");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "eff_Sphere", "Effect/eff_Sphere.msh");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "eff_Fire", "Effect/eff_Fire.msh");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "eff_Ring", "Effect/eff_Ring.msh");

}
