#include "LobbyScene.h"
#include "../StageManager.h"
#include "Scene/Scene.h"
#include "../Object/MainLandScape.h"
#include "../UI/UIManager.h"
#include "../Object/LobbyShip.h"
#include "Component/LightComponent.h"
#include "Component/SkyComponent.h"
#include "../Object/LobbyValkyrieSelectZone.h"
#include "../LobbyManager.h"
#include "../Object/LoadingStartObject.h"
#include "../UI/LoadingUI_Resource.h"
CLobbyScene::CLobbyScene()
{
	CLobbyManager::GetInst();
}

CLobbyScene::~CLobbyScene()
{
	CLobbyManager::DestroyInst();
}

bool CLobbyScene::Init()
{
	CStageManager::GetInst()->ResourceLoad(m_pScene);

	CGameObject* Sky = m_pScene->SpawnObject<CGameObject>("Sky");
	CSkyComponent* SkyComponent = Sky->CreateSceneComponent<CSkyComponent>("SkyComponent");

	Sky->SetRootComponent(SkyComponent);

	SkyComponent->SetRelativeScale(100000.f, 100000.f, 100000.f);


	CGameObject* GlobalLight = m_pScene->SpawnObject<CGameObject>("GlobalLight");
	CLightComponent* GlobalLightComponent = GlobalLight->CreateSceneComponent<CLightComponent>("GlobalLight");
	GlobalLight->SetRootComponent(GlobalLightComponent);
	GlobalLightComponent->SetWorldPos(162.f, 46.174f, 16.086f);
	GlobalLightComponent->SetWorldRotation(75.f, -86.45f, 0.f);


	if (!CStageManager::GetInst()->GetLoading())
	{
		CLoadingStartObject* LoadingStartObject = m_pScene->SpawnObject<CLoadingStartObject>("LoadingStartObject");
		LoadingStartObject->LobbyStartSound();
		LoadingStartObject->LoadingEndMark();
		CLobbyShip* LobbyShip = m_pScene->SpawnObject<CLobbyShip>("LobbyShip");
		LobbyShip->SetWorldPos(0.f, 1.f, 0.f);
		LobbyShip->Enable(false);
		CGameObject* CameraObject = m_pScene->SpawnObject<CGameObject>("CameraObject");
		CCamera* Camera = CameraObject->CreateSceneComponent<CCamera>("Camera");

		CameraObject->SetRootComponent(Camera);
		CameraObject->SetWorldPos(LoadingStartObject->GetCameraPos());
		//CameraObject->SetWorldPos(LoadingStartObject->GetCameraPos());
		m_pScene->GetCameraManager()->SetCurrentCamera(Camera);

		CLobbyValkyrieSelectZone* Zone = m_pScene->SpawnObject<CLobbyValkyrieSelectZone>("LobbyValkyrieSelectZone");
		Zone->SetWorldPos(100.f, 0.f, 100.f);

		CLobbyManager::GetInst()->SetLoadingStartObject(LoadingStartObject);
		CLobbyManager::GetInst()->SetShip(LobbyShip);
		CLobbyManager::GetInst()->SetValkyrieSelectZone(Zone);
	}
	else
	{
		CStageManager::GetInst()->BGMPlay("LobbyBG");
		CLobbyShip* LobbyShip = m_pScene->SpawnObject<CLobbyShip>("LobbyShip");
		LobbyShip->SetWorldPos(0.f, 1.f, 0.f);
		LobbyShip->Enable(true);
		m_CameraObject = m_pScene->SpawnObject<CGameObject>("CameraObject");
		CCamera* Camera = m_CameraObject->CreateSceneComponent<CCamera>("Camera");

		m_CameraObject->SetRootComponent(Camera);
		m_CameraObject->SetWorldPos(LobbyShip->GetLobbyCameraPos());
		//CameraObject->SetWorldPos(LoadingStartObject->GetCameraPos());
		m_pScene->GetCameraManager()->SetCurrentCamera(Camera);

		CLobbyValkyrieSelectZone* Zone = m_pScene->SpawnObject<CLobbyValkyrieSelectZone>("LobbyValkyrieSelectZone");
		Zone->SetWorldPos(100.f, 0.f, 100.f);

		CLobbyManager::GetInst()->SetShip(LobbyShip);
		CLobbyManager::GetInst()->SetValkyrieSelectZone(Zone);
	}
	return true;
}

void CLobbyScene::Start()
{
	if (!CStageManager::GetInst()->GetLoading())
	{
		CUIManager::GetInst()->Init(m_pScene);
		CStageManager::GetInst()->SetLoadingEnd();
		CLoadingUI_Resource* LoadingUI_Resource = (CLoadingUI_Resource*)CUIManager::GetInst()->FindWidgetWindow("LoadingUI_Resource");
		LoadingUI_Resource->Enable(true);
		LoadingUI_Resource->SetPercent(1.f);
	}
	else
	{
		CUIManager::GetInst()->Init(m_pScene);
		CUIManager::GetInst()->FindWidgetWindow("LobbyMainUI")->Enable(true);
		Vector3 CameraPos = CLobbyManager::GetInst()->GetLobbyShip()->GetLobbyCameraPos();
		m_CameraObject->SetWorldPos(CameraPos);
	}
}

void CLobbyScene::Update(float DeltaTime)
{
	if (GetAsyncKeyState(VK_NUMPAD4) & 0x8000)
	{
		m_CameraObject->AddWorldPos(0.f, 0.f, 10.f * DeltaTime);
	}
	if (GetAsyncKeyState(VK_NUMPAD6) & 0x8000)
	{
		m_CameraObject->AddWorldPos(0.f,0.f,-10.f * DeltaTime);
	}

	if (GetAsyncKeyState(VK_NUMPAD8) & 0x8000)
	{
		m_CameraObject->AddWorldPos(-10.f * DeltaTime, 0.f, 0.f);
	}

	if (GetAsyncKeyState(VK_NUMPAD2) & 0x8000)
	{
		m_CameraObject->AddWorldPos(10.f * DeltaTime, 0.f, 0.f);
	}
}


void CLobbyScene::SceneLoad()
{
	CStageManager::GetInst()->StartScene("test2.map", m_pScene);

}
