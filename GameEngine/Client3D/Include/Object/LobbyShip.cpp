#include "LobbyShip.h"
#include "Resource/Animation.h"
#include "Resource/BoneSocket.h"
#include "Scene/SceneResource.h"
#include "Scene/Scene.h"
CLobbyShip::CLobbyShip():
	m_Animation(nullptr)
{
	m_ClientClassType = ClientClassType::LobbyShip;
}

CLobbyShip::CLobbyShip(const CLobbyShip& obj) :
	CClientObject(obj)
{
	m_Root = (CSceneComponent*)FindSceneComponent("Root");
	m_Ship = (CStaticMeshComponent*)FindSceneComponent("Ship");
	m_ShipControlRight = (CStaticMeshComponent*)FindSceneComponent("ShipControlRight");
	m_ShipControlLeft = (CStaticMeshComponent*)FindSceneComponent("ShipControlLeft");
	m_ShipControlCenter = (CStaticMeshComponent*)FindSceneComponent("ShipControlCenter");

	m_Mesh = (CAnimationMeshComponent*)FindSceneComponent("Mesh");
	m_WeaponMesh = (CStaticMeshComponent*)FindSceneComponent("WeaponMesh1");
	m_WeaponMesh2 = (CStaticMeshComponent*)FindSceneComponent("WeaponMesh2");
	m_Background = (CBillboardComponent*)FindSceneComponent("Background");
}

CLobbyShip::~CLobbyShip()
{
}

void CLobbyShip::Start()
{
	CClientObject::Start();
}

bool CLobbyShip::Init()
{
	if (!CClientObject::Init())
		return false;
	m_Root = CreateSceneComponent<CSceneComponent>("Root");
	m_Ship = CreateSceneComponent<CStaticMeshComponent>("Ship");
	m_ShipControlRight = CreateSceneComponent<CStaticMeshComponent>("ShipControlRight");
	m_ShipControlLeft = CreateSceneComponent<CStaticMeshComponent>("ShipControlLeft");
	m_ShipControlCenter = CreateSceneComponent<CStaticMeshComponent>("ShipControlCenter");

	m_Mesh = CreateSceneComponent<CAnimationMeshComponent>("Mesh");
	m_WeaponMesh = CreateSceneComponent<CStaticMeshComponent>("WeaponMesh1");
	m_WeaponMesh2 = CreateSceneComponent<CStaticMeshComponent>("WeaponMesh2");
	m_LobbyCameraPos = CreateSceneComponent<CSceneComponent>("LobbyCameraPos");
	m_Background = CreateSceneComponent<CBillboardComponent>("Background");

	SetRootComponent(m_Root);
	m_Root->AddChild(m_Ship);
	m_Root->AddChild(m_ShipControlRight);
	m_Root->AddChild(m_ShipControlLeft);
	m_Root->AddChild(m_ShipControlCenter);
	m_Root->AddChild(m_LobbyCameraPos);
	m_Root->AddChild(m_Background);
	m_Root->AddChild(m_Mesh);

	m_Mesh->SetInheritRotX(true);
	m_Root->SetWorldRotation(-90.f, 0.f, 0.f);
	m_Root->SetWorldPos(0.f, 0.f, 0.f);
	m_Ship->SetWorldPos(0.f, 0.f, 0.4f);
	m_ShipControlLeft->SetWorldPos(-2.377f, -1.194f, 7.372f);
	m_ShipControlRight->SetWorldPos(-1.663f,-1.116f,7.428f);
	m_ShipControlCenter->SetWorldPos(-2.f, -1.1f, 7.754f);
	m_Mesh->SetWorldPos(-0.423f, -0.394f, 2.406f);
	m_Mesh->SetWorldRotation(-90.f, -17.568f, -0.438f);
	m_LobbyCameraPos->SetWorldPos(0.f, 1.083f, 1.318f);
	m_Ship->SetMesh("WarShip");
	m_ShipControlRight->SetMesh("WarShip_ControlRight");
	m_ShipControlLeft->SetMesh("WarShip_ControlLeft");
	m_ShipControlCenter->SetMesh("WarShip_ControlCenter");



	m_Ship->SetNotLight();
	m_ShipControlRight->SetNotLight();
	m_ShipControlLeft->SetNotLight();
	m_ShipControlCenter->SetNotLight();
	m_Mesh->SetNotLight();
	m_WeaponMesh->SetNotLight();
	m_WeaponMesh2->SetNotLight();

	m_Animation = new CAnimation;
	m_Mesh->SetAnimation(m_Animation);
	m_Animation->Init();
	m_Mesh->SetWorldScale(1.f, 1.f, 1.f);
	m_Mesh->SetMesh("KianaMesh");
	m_Mesh->SetAllEmissiveColor(Vector3(0.6f, 0.6f, 0.6f));
	m_Animation->SetRootBoneIndex("Bip001 Pelvis");
	//Socket
	CSkeleton* Skel = m_Animation->GetSkeleton();
#pragma region Weapon
	Skel->AddSocket("Bip001 Prop1", "RightGun");
	CBoneSocket* RightGunSocket = Skel->GetSocket("RightGun");
	RightGunSocket->SetOffset(-0.000319f, 0.000428f, -0.009618f);
	RightGunSocket->SetOffsetRotation(-179.987701f, -3.559177f, 179.604233f);

	m_WeaponMesh->SetMesh("KianaRightPistol");
	m_WeaponMesh->SetWorldScale(1.f, 1.f, 1.f);
	m_Mesh->AddChild(m_WeaponMesh, "RightGun");

	Skel->AddSocket("Bip001 Prop2", "LeftGun");
	CBoneSocket* LeftGunSocket = Skel->GetSocket("LeftGun");
	LeftGunSocket->SetOffset(0.000588f, -0.001253f, 0.009635f);
	LeftGunSocket->SetOffsetRotation(0.015346f, -3.546651f, 179.504333f);

	m_WeaponMesh2->SetMesh("KianaLeftPistol");
	m_WeaponMesh2->SetWorldScale(1.f, 1.f, 1.f);

	m_Mesh->AddChild(m_WeaponMesh2, "LeftGun");
#pragma endregion

	//Anim
	{
		m_Animation->AddAnimationSequence("Avatar_Kiana_C1_StandBy", 1.f);

	}

	m_Background->SetRelativePos(-1.233f, -26.024f, 20.f);
	m_Background->SetRelativeScale(100.f, 100.f, 1.f);

	CMaterial* Mtrl = m_pScene->GetResource()->FindMaterial("LobbyBackGround");
	CMesh*   BackGroundMesh = m_Background->GetMesh();
	m_Background->AddMaterial(Mtrl);


	return true;
}

void CLobbyShip::Update(float DeltaTime)
{
	CClientObject::Update(DeltaTime);
}

void CLobbyShip::PostUpdate(float DeltaTime)
{
	CClientObject::PostUpdate(DeltaTime);
}

void CLobbyShip::Collision(float DeltaTime)
{
	CClientObject::Collision(DeltaTime);
}

void CLobbyShip::PrevRender(float DeltaTime)
{
	CClientObject::PrevRender(DeltaTime);
}

void CLobbyShip::Render(float DeltaTime)
{
	CClientObject::Render(DeltaTime);
}

CLobbyShip* CLobbyShip::Clone()
{
	return new CLobbyShip(*this);
}
