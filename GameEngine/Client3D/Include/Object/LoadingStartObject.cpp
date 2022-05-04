#include "LoadingStartObject.h"
#include "Resource/Animation.h"
#include "../Scene/LobbyScene.h"
#include "Scene/SceneManager.h"
#include "../LobbyManager.h"
#include "../UI/UIManager.h"
#include "LobbyShip.h"
#include "../StageManager.h"
CLoadingStartObject::CLoadingStartObject()
{
	m_ObjectType = Object_Type::Client;
	m_ClientClassType = ClientClassType::LoadingStartObject;
	m_State = LoadingStartObjectState::Loading;
	m_OpenDoorPause = 1.f;
	m_Sound = nullptr;
	m_SoundChange = false;
}

CLoadingStartObject::CLoadingStartObject(const CLoadingStartObject& obj) :
	CClientObject(obj)
{
	m_Root = (CSceneComponent*)FindSceneComponent("Root");
	m_Pillar = (CStaticMeshComponent*)FindSceneComponent("Pillar");
	m_DoorUp = (CStaticMeshComponent*)FindSceneComponent("DoorUp");
	m_DoorDown = (CStaticMeshComponent*)FindSceneComponent("DoorDown");
	m_DoorDownMove = (CStaticMeshComponent*)FindSceneComponent("DoorDownMove");
	m_Elevator = (CStaticMeshComponent*)FindSceneComponent("Elevator");
	m_GroundIn = (CStaticMeshComponent*)FindSceneComponent("GroundIn");
	m_LoadingMark = (CStaticMeshComponent*)FindSceneComponent("LoadingMark");
	//m_Camera = (CCamera*)FindSceneComponent("LoadingObjectCamera");
	m_CameraPos = (CSceneComponent*)FindSceneComponent("CameraPos");
	m_DoorMain = (CStaticMeshComponent*)FindSceneComponent("DoorMain");
}

CLoadingStartObject::~CLoadingStartObject()
{
}

void CLoadingStartObject::Start()
{
	CClientObject::Start();
}

bool CLoadingStartObject::Init()
{
	if (!CClientObject::Init())
		return false;
	m_Root = CreateSceneComponent<CSceneComponent>("Root");
	m_Pillar = CreateSceneComponent<CStaticMeshComponent>("Pillar");
	m_DoorUp = CreateSceneComponent<CStaticMeshComponent>("DoorUp");
	m_DoorDown = CreateSceneComponent<CStaticMeshComponent>("DoorDown");
	m_DoorDownMove = CreateSceneComponent<CStaticMeshComponent>("DoorDownMove");
	m_Elevator = CreateSceneComponent<CStaticMeshComponent>("Elevator");
	m_GroundIn = CreateSceneComponent<CStaticMeshComponent>("GroundIn");
	m_DoorMain = CreateSceneComponent<CStaticMeshComponent>("DoorMain");
	m_LoadingMark = CreateSceneComponent<CStaticMeshComponent>("LoadingMark");
	//m_Camera = CreateSceneComponent<CCamera>("LoadingObjectCamera");
	m_CameraPos = CreateSceneComponent<CSceneComponent>("CameraPos");
	

	m_Pillar->SetInheritRotX(true);
	m_DoorDown->SetInheritRotX(true);
	m_DoorDownMove->SetInheritRotX(true);
	m_DoorUp->SetInheritRotX(true);
	m_DoorDown->SetInheritRotX(true);
	m_Elevator->SetInheritRotX(true);
	m_GroundIn->SetInheritRotX(true);
	m_DoorMain->SetInheritRotX(true);
	m_LoadingMark->SetInheritRotX(true);


	m_Pillar->SetInheritRotX(true);
	m_Pillar->SetNotLight();
	m_DoorDown->SetNotLight();
	m_DoorDownMove->SetNotLight();
	m_DoorUp->SetNotLight();
	m_Elevator->SetNotLight();
	m_GroundIn->SetNotLight();
	m_DoorMain->SetNotLight();
	m_LoadingMark->SetNotLight();


	SetRootComponent(m_Root);
	m_Root->SetWorldRotation(-90.f, 0.f, 0.f);
	m_Root->AddChild(m_Pillar);
	m_Root->AddChild(m_DoorDownMove);
	m_Root->AddChild(m_DoorUp);
	m_Root->AddChild(m_DoorDown);
	m_Root->AddChild(m_Elevator);
	m_Root->AddChild(m_GroundIn);
	m_Root->AddChild(m_DoorMain);
	m_Root->AddChild(m_LoadingMark);
	m_Root->AddChild(m_CameraPos);
	m_Root->SetInheritRotX(true);
	//m_Arm->AddChild(m_Camera);
	m_Pillar->SetMesh("Pillar");
	m_DoorUp->SetMesh("DoorUp");
	m_DoorDown->SetMesh("DoorDown");
	m_DoorDownMove->SetMesh("DoorDownMove");
	m_Elevator->SetMesh("Elevator");
	m_GroundIn->SetMesh("GroundIn");
	m_DoorMain->SetMesh("DoorMain");
	m_LoadingMark->SetMesh("LoadingMark");

	m_Pillar->GetMesh()->AllLightMaterialReset();
	m_DoorUp->GetMesh()->AllLightMaterialReset();
	m_DoorDown->GetMesh()->AllLightMaterialReset();
	m_DoorDownMove->GetMesh()->AllLightMaterialReset();
	m_Elevator->GetMesh()->AllLightMaterialReset();
	m_GroundIn->GetMesh()->AllLightMaterialReset();
	m_DoorMain->GetMesh()->AllLightMaterialReset();
	m_LoadingMark->GetMesh()->AllLightMaterialReset();

	m_DoorUp->SetAllTransparency(true, false);
	m_DoorDown->SetAllTransparency(true, false);
	m_DoorMain->SetAllTransparency(true, false);

	m_Pillar->SetRelativeRotationX(90.f);
	m_Pillar->SetWorldPos(-0.126f, 2.736f, 1.329f);
	m_DoorDownMove->SetWorldPos(0.f, 6.2f, 0.598f);
	m_Elevator->SetWorldPos(0.f, -3.95f, -12.1f);
	m_GroundIn->SetWorldPos(-0.064f, 0.224f, 0.f);
	m_DoorUp->SetWorldPos(-0.239f, 11.9f, 0.562f);
	m_DoorDown->SetWorldPos(0.052f, 10.9f, 0.457f);
	//m_DoorUp->SetWorldPos(-0.239f, 2.426f, 0.562f);
	//m_DoorDown->SetWorldPos(0.052f, 1.422f, 0.457f);
	m_DoorMain->SetWorldPos(-0.125f, 0.339f, 0.065f);
	m_LoadingMark->SetWorldPos(-0.059f, 0.228f, -0.134f);
	m_LoadingMark->SetWorldRotation(2.564f, 0.f, 0.f);
	m_CameraPos->SetWorldPos(0.f, 2.083f, -1.204f);

		
	return true;
}

void CLoadingStartObject::Update(float DeltaTime)
{
	CClientObject::Update(DeltaTime);
	if (m_Sound)
	{
		if (!m_Sound->IsPlay())
		{
			if (m_Sound->GetName() == "LoadingSound0")
			{
				m_Sound = m_pScene->GetResource()->FindSound2D("LoadingSound1");
				m_Sound->Play();
			}
		}
	}
	m_Pillar->AddWorldPos(0.f, -1.6f * DeltaTime, 0.f);
	Vector3 PillarPos = m_Pillar->GetWorldPos();
	if (PillarPos.y < -10.f)
	{
		PillarPos.y += 10.f;
		m_Pillar->SetWorldPos(PillarPos);
	}
	m_Elevator->AddWorldPos(0.f, -0.8f * DeltaTime, 0.f);
	Vector3 ElevatorPos = m_Elevator->GetWorldPos();
	if (ElevatorPos.y < -10.f)
	{
		ElevatorPos.y += 10.f;
		m_Elevator->SetWorldPos(ElevatorPos);
	}

	switch (m_State)
	{	
	case LoadingStartObjectState::LoadEnd_GoLobbyShip:
	{
		m_DoorDownMove->AddWorldPos(0.f, -4.8f * DeltaTime, 0.f);
		Vector3 DoorDownMovePos = m_DoorDownMove->GetWorldPos();
		m_DoorUp->AddWorldPos(0.f, -4.8f * DeltaTime, 0.f);
		m_DoorDown->AddWorldPos(0.f, -4.8f * DeltaTime, 0.f);
		if (DoorDownMovePos.y < 3.2f)
		{
			m_State = LoadingStartObjectState::GoLobbyShipEnd_SeeLobbyShip;
			m_SoundChange = true;
		}
		break;
	}
		
	case LoadingStartObjectState::GoLobbyShipEnd_SeeLobbyShip:
	{
		if (m_SoundChange)
		{
			m_SoundChange = false;
			m_Sound->Stop();
			m_Sound = m_pScene->GetResource()->FindSound2D("LoadingSound2_GoShip");
			m_Sound->Play();
		}
		m_Pillar->Enable(false);
		m_Elevator->Enable(false);
		CLobbyManager::GetInst()->GetLobbyShip()->Enable(true);
		//로비보이게하기
		m_DoorDownMove->AddWorldPos(0.f, -4.8f * DeltaTime, 0.f);
		m_DoorUp->AddWorldPos(0.f, -4.8f * DeltaTime, 0.f);
		m_DoorDown->AddWorldPos(0.f, -4.8f * DeltaTime, 0.f);
		Vector3 DoorUpPos = m_DoorUp->GetWorldPos();
		Vector3 DoorDownPos = m_DoorDown->GetWorldPos();
		if (DoorUpPos.y < 2.426f)
		{
			DoorUpPos.y = 2.426f;
			m_DoorUp->SetWorldPos(DoorUpPos);
			m_State = LoadingStartObjectState::SeeLobbyShipEnd_OpenDoor;
			m_SoundChange = true;

			//움직임완료
		}
		if (DoorDownPos.y < 1.422f)
		{
			DoorDownPos.y = 1.422f;
			m_DoorDown->SetWorldPos(DoorDownPos);
			m_State = LoadingStartObjectState::SeeLobbyShipEnd_OpenDoor;
			m_SoundChange = true;
		}
		break;
	}

	case LoadingStartObjectState::SeeLobbyShipEnd_OpenDoor:
	{
		m_OpenDoorPause -= DeltaTime;

		if (m_SoundChange)
		{
			m_SoundChange = false;
			m_Sound->Stop();
			m_Sound = m_pScene->GetResource()->FindSound2D("LoadingSound3_OpenDoor");
			m_Sound->Play();
		}

		if (m_OpenDoorPause < 0.f)
		{
			m_DoorMain->AddWorldPos(-3.2f * DeltaTime, 0.f, 0.f);
			m_DoorDown->AddWorldPos(0.f, -3.2f * DeltaTime, 0.f);
			m_DoorUp->AddWorldPos(0.f, 3.2f * DeltaTime, 0.f);
		}
		Vector3 DoorMainPos = m_DoorMain->GetWorldPos();
		if (DoorMainPos.x < -3.7f)
		{

			m_State = LoadingStartObjectState::OpenDoorEnd_InLobbyShip;
			m_SoundChange = true;
		}
		break;
	}
	case LoadingStartObjectState::OpenDoorEnd_InLobbyShip:
	{
		if (m_SoundChange)
		{
			m_SoundChange = false;
			m_Sound->Stop();
			m_Sound = m_pScene->GetResource()->FindSound2D("LoadingSound4_Captain");
			m_Sound->Play();
		}
		Vector3 CameraPos=CLobbyManager::GetInst()->GetLobbyShip()->GetLobbyCameraPos();
		CCamera* Camera = m_pScene->GetCameraManager()->GetCurrentCamera();
		if (0.002f > (Camera->GetWorldPos()- CameraPos).Length())
		{
			//완료 UI등장 그리고 Enable(false)
			Camera->SetWorldPos(CameraPos);
			CUIManager::GetInst()->FindWidgetWindow("LobbyMainUI")->Enable(true);
			CStageManager::GetInst()->BGMPlay("LobbyBG");
			Enable(false);
		}
		CameraPos=Vector3::Lerp3D(Camera->GetWorldPos(), CameraPos, DeltaTime*3.f);
		//이동은 z으로만 이동함
		Camera->SetWorldPos(CameraPos);
		
		break;
	}
		
	}
	
}

void CLoadingStartObject::PostUpdate(float DeltaTime)
{
	CClientObject::PostUpdate(DeltaTime);
}

void CLoadingStartObject::Collision(float DeltaTime)
{
	CClientObject::Collision(DeltaTime);
}

void CLoadingStartObject::PrevRender(float DeltaTime)
{
	CClientObject::PrevRender(DeltaTime);
}

void CLoadingStartObject::Render(float DeltaTime)
{
	CClientObject::Render(DeltaTime);
}

CLoadingStartObject* CLoadingStartObject::Clone()
{
	return new CLoadingStartObject(*this);
}

void CLoadingStartObject::LoadingEndMark()
{
	m_LoadingMark->GetMaterial(0)->SetTexture(0, "Elevator_Display03", TEXT("Scene/LoadingScene/LoadingMark.fbm/Elevator_Display03.tga"), MESH_PATH);
}

void CLoadingStartObject::GoShipStart()
{
	m_State = LoadingStartObjectState::LoadEnd_GoLobbyShip;
}

Vector3 CLoadingStartObject::GetCameraPos()
{
	return m_CameraPos->GetWorldPos();
}

void CLoadingStartObject::LoadingStartSound()
{
	m_Sound = m_pScene->GetResource()->FindSound2D("LoadingSound0");
	m_Sound->Play();
}

void CLoadingStartObject::LobbyStartSound()
{
	m_Sound = m_pScene->GetResource()->FindSound2D("LoadingSound1");
	m_Sound->Play();
}
