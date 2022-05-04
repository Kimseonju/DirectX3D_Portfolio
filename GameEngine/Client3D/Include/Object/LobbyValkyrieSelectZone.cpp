#include "LobbyValkyrieSelectZone.h"
#include "Resource/Animation.h"
#include "Resource/BoneSocket.h"
#include "Scene/SceneResource.h"
#include "Scene/Scene.h"
CLobbyValkyrieSelectZone::CLobbyValkyrieSelectZone()
{
	m_ClientClassType = ClientClassType::LobbyValkyieSelectZone;
}

CLobbyValkyrieSelectZone::CLobbyValkyrieSelectZone(const CLobbyValkyrieSelectZone& obj) :
	CClientObject(obj)
{
}

CLobbyValkyrieSelectZone::~CLobbyValkyrieSelectZone()
{
}

void CLobbyValkyrieSelectZone::Start()
{
	CClientObject::Start();
}

bool CLobbyValkyrieSelectZone::Init()
{
	if (!CClientObject::Init())
		return false;
	m_Root = CreateSceneComponent<CSceneComponent>("Root");
	m_CameraPos = CreateSceneComponent<CSceneComponent>("CameraPos");
	m_Background = CreateSceneComponent<CBillboardComponent>("Background");
	SetRootComponent(m_Root);

	m_Root->AddChild(m_CameraPos);
	m_Root->AddChild(m_Background);
	m_CameraPos->SetRelativePos(0.f, 1.5f, -0.7f);

	m_Background->SetRelativePos(-0.135f, 1.24f, 0.174f);
	m_Background->SetRelativeScale(5.85f, 4.0, 1.f);

	CMaterial* Mtrl = m_pScene->GetResource()->FindMaterial("LobbyValkyrieSelectZoneBG");
	CMesh* BackGroundMesh = m_Background->GetMesh();
	m_Background->AddMaterial(Mtrl);



	{
	#pragma region Kiana
		CAnimationMeshComponent* Mesh = CreateSceneComponent<CAnimationMeshComponent>("KianaSelectMesh");
		m_Root->AddChild(Mesh);

		CStaticMeshComponent* WeaponMesh = CreateSceneComponent<CStaticMeshComponent>("WeaponMesh_Kiana");
		CStaticMeshComponent* WeaponMesh2 = CreateSceneComponent<CStaticMeshComponent>("WeaponMesh_Kiana");

		Mesh->SetMesh("KianaMesh");
		Mesh->SetRelativeRotation(-90.f, 0.f, 0.f);

		CAnimation* Animation = new CAnimation;
		Animation->Init();
		Mesh->SetAnimation(Animation);

		Mesh->SetWorldScale(1.f, 1.f, 1.f);
		Animation->SetRootBoneIndex("Bip001 Pelvis");
		//Socket
		CSkeleton* Skel = Animation->GetSkeleton();
		#pragma region Weapon
			Skel->AddSocket("Bip001 Prop1", "RightGun");
		CBoneSocket* RightGunSocket = Skel->GetSocket("RightGun");
		RightGunSocket->SetOffset(-0.000319f, 0.000428f, -0.009618f);
		RightGunSocket->SetOffsetRotation(-179.987701f, -3.559177f, 179.604233f);

		WeaponMesh->SetMesh("KianaRightPistol");
		WeaponMesh->SetWorldScale(1.f, 1.f, 1.f);
		Mesh->AddChild(WeaponMesh, "RightGun");

		Skel->AddSocket("Bip001 Prop2", "LeftGun");
		CBoneSocket* LeftGunSocket = Skel->GetSocket("LeftGun");
		LeftGunSocket->SetOffset(0.000588f, -0.001253f, 0.009635f);
		LeftGunSocket->SetOffsetRotation(0.015346f, -3.546651f, 179.504333f);

		WeaponMesh2->SetMesh("KianaLeftPistol");
		WeaponMesh2->SetWorldScale(1.f, 1.f, 1.f);

		Mesh->AddChild(WeaponMesh2, "LeftGun");
		#pragma endregion

		Animation->AddAnimationSequence("Avatar_Kiana_C1_StandBy", 1.f, false);
		m_mapSelectMesh.insert(std::make_pair("Kiana", Mesh));
		Mesh->Enable(true);
		Mesh->SetAllEmissiveColor(Vector3(0.6f, 0.6f, 0.6f));
		Mesh->SetNotLight();
	#pragma endregion
	}
	{
#pragma region Sakura
		CAnimationMeshComponent* Mesh = CreateSceneComponent<CAnimationMeshComponent>("SakuraSelectMesh");
		CStaticMeshComponent* WeaponMesh = CreateSceneComponent<CStaticMeshComponent>("WeaponMesh_Sakura");
		Mesh->SetMesh("SakuraMesh");
		Mesh->SetRelativeRotation(-90.f, 0.f, 0.f);
		m_Root->AddChild(Mesh);
		CAnimation* Animation = new CAnimation;
		Animation->Init();
		Mesh->SetAnimation(Animation);

		Mesh->SetWorldScale(1.f, 1.f, 1.f);
		Animation->SetRootBoneIndex("Bip001 Pelvis");
		//Socket
#pragma region Weapon
		CSkeleton* Skel = Animation->GetSkeleton();
		Skel->AddSocket("Bip001 Prop1", "Weapon");
		CBoneSocket* WeaponSocket = Skel->GetSocket("Weapon");
		WeaponSocket->SetOffsetRotation(0.f, -10.f, 0.f);

		WeaponMesh->SetMesh("Katana_1");
		WeaponMesh->SetWorldScale(1.f, 1.f, 1.f);
		Mesh->AddChild(WeaponMesh, "Weapon");

#pragma endregion
		Animation->AddAnimationSequence("Avatar_Sakura_C1_YS1", 1.f, false);
		m_mapSelectMesh.insert(std::make_pair("Sakura", Mesh));
		Mesh->Enable(false);
		Mesh->SetAllEmissiveColor(Vector3(0.6f, 0.6f, 0.6f));
		Mesh->SetNotLight();
#pragma endregion


	}


	return true;
}

void CLobbyValkyrieSelectZone::Update(float DeltaTime)
{
	CClientObject::Update(DeltaTime);
}

void CLobbyValkyrieSelectZone::PostUpdate(float DeltaTime)
{
	CClientObject::PostUpdate(DeltaTime);
}

void CLobbyValkyrieSelectZone::Collision(float DeltaTime)
{
	CClientObject::Collision(DeltaTime);
}

void CLobbyValkyrieSelectZone::PrevRender(float DeltaTime)
{
	CClientObject::PrevRender(DeltaTime);
}

void CLobbyValkyrieSelectZone::Render(float DeltaTime)
{
	CClientObject::Render(DeltaTime);
}

CLobbyValkyrieSelectZone* CLobbyValkyrieSelectZone::Clone()
{
	return new CLobbyValkyrieSelectZone(*this);
}

void CLobbyValkyrieSelectZone::ChangeValkrie(const std::string& Name)
{
	auto iter = m_mapSelectMesh.find(Name);
	if (iter == m_mapSelectMesh.end())
		return;
	if(m_SelectMesh)
		m_SelectMesh->Enable(false);
	iter->second->Enable(true);
	m_SelectMesh = iter->second;
}

void CLobbyValkyrieSelectZone::Valkyrie_Info()
{
	auto iter = m_mapSelectMesh.begin();
	auto iterEnd = m_mapSelectMesh.end();

	for (; iter != iterEnd; ++iter)
	{
		iter->second->SetRelativePos(-0.55f, 0.f, -0.15f);
		iter->second->SetRelativeRotation(-90.f, -50.f, 0.f);
	}
}

void CLobbyValkyrieSelectZone::Valkyrie_Zone()
{
	auto iter = m_mapSelectMesh.begin();
	auto iterEnd = m_mapSelectMesh.end();

	for (; iter != iterEnd; ++iter)
	{
		iter->second->SetRelativePos(0.f, 0.f, -0.1f);
		iter->second->SetRelativeRotation(-90.f, 0.f, 0.f);
	}
}
