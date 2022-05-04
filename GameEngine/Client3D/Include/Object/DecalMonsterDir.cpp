
#include "DecalMonsterDir.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Resource/Material.h"
#include "../PublicData.h"
#include "Player.h"
CDecalMonsterDir::CDecalMonsterDir()
{
}

CDecalMonsterDir::CDecalMonsterDir(const CDecalMonsterDir& obj) :
	CGameObject(obj)
{
	m_Decal = (CDecalComponent*)FindSceneComponent("Decal");
}

CDecalMonsterDir::~CDecalMonsterDir()
{
}

void CDecalMonsterDir::Start()
{
	CGameObject::Start();
}

bool CDecalMonsterDir::Init()
{
	CGameObject::Init();

	m_Decal = CreateSceneComponent<CDecalComponent>("Decal");

	SetRootComponent(m_Decal);

	CMaterial* Material = m_Decal->GetMaterial(0);

	//Material->SetTexture("DefaultDecal", "BloodDecal", TEXT("Decal/free-blood-texture_COLOR.png"));
	//Material->SetTexture("DefaultDecal", "BloodDecal", TEXT("HOS.jpg"));
	//Material->SetTexture("DefaultDecalNormal", "BloodDecalNormal", TEXT("Decal/free-blood-texture_NRM.png"));
	//Material->SetTexture("DefaultDecalSpecular", "BloodDecalSpecular", TEXT("Decal/free-blood-texture_SPEC.png"));

	Material->SetTexture("DefaultDecal", "BloodDecal", TEXT("Decal/Arrow.png"));
	m_Decal->SetWorldScale(1.f, 1.f, 1.f);
	//Material->SetTexture("DefaultDecalNormal", "BloodDecalNormal", TEXT("Decal/Decal_NRM.png"));
	//Material->SetTexture("DefaultDecalSpecular", "BloodDecalSpecular", TEXT("Decal/Decal_SPEC.png"));

	return true;
}

void CDecalMonsterDir::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	
	//m_Decal->AddRelativeRotationY(180.f * DeltaTime);
}

void CDecalMonsterDir::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CDecalMonsterDir::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CDecalMonsterDir::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CDecalMonsterDir* CDecalMonsterDir::Clone()
{
	return new CDecalMonsterDir(*this);
}
