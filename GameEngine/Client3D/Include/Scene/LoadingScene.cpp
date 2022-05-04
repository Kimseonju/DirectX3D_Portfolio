#include "LoadingScene.h"
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
#include "LoadingThread.h"
#include "ThreadManager.h"
#include "../UI/LoadingUI_Resource.h"
CLoadingScene::CLoadingScene():
	m_LoadingEnd(false),
	m_Thread(nullptr)
{
}

CLoadingScene::~CLoadingScene()
{
}

bool CLoadingScene::Init()
{
	CStageManager::GetInst()->LoadingBeforeResourceLoad(m_pScene);

	CGameObject* Sky = m_pScene->SpawnObject<CGameObject>("Sky");
	CSkyComponent* SkyComponent = Sky->CreateSceneComponent<CSkyComponent>("SkyComponent");
	Sky->SetRootComponent(SkyComponent);
	SkyComponent->SetRelativeScale(100000.f, 100000.f, 100000.f);


	CGameObject* GlobalLight = m_pScene->SpawnObject<CGameObject>("GlobalLight");
	CLightComponent* GlobalLightComponent = GlobalLight->CreateSceneComponent<CLightComponent>("GlobalLight");
	GlobalLight->SetRootComponent(GlobalLightComponent);
	GlobalLightComponent->SetWorldPos(162.f, 46.174f, 16.086f);
	GlobalLightComponent->SetWorldRotation(75.f, -86.45f, 0.f);

	CLoadingStartObject* LoadingStartObject = m_pScene->SpawnObject<CLoadingStartObject>("LoadingStartObject");
	LoadingStartObject->LoadingStartSound();

	CGameObject* CameraObject = m_pScene->SpawnObject<CGameObject>("CameraObject");
	CCamera* Camera = CameraObject->CreateSceneComponent<CCamera>("Camera");
	CameraObject->SetRootComponent(Camera);
	CameraObject->SetWorldPos(LoadingStartObject->GetCameraPos());
	m_pScene->GetCameraManager()->SetCurrentCamera(Camera);

	CUIManager::GetInst()->Init(m_pScene);
	CUIManager::GetInst()->FindWidgetWindow("LoadingUI_Resource")->Enable(true);


	m_Thread = CThreadManager::GetInst()->CreateThread<CLoadingThread>("LoadingThread");
	m_Thread->SetLoop(false);
	m_Thread->Start();
	return true;
}

void CLoadingScene::Start()
{
}

void CLoadingScene::Update(float DeltaTime)
{
	if (!m_LoadingEnd)
	{

		CLoadingUI_Resource* LoadingUI_Resource = (CLoadingUI_Resource*)CUIManager::GetInst()->FindWidgetWindow("LoadingUI_Resource");
		LoadingUI_Resource->SetPercent(m_Thread->GetPersent());
	}
	if (m_Thread->GetPersent() >= 0.99999f)
	{
		m_LoadingEnd = true;
		CUIManager::GetInst()->DestroyInst();
		m_Thread->NextScene();
	}
		
}

void CLoadingScene::PostUpdate(float DeltaTime)
{
}
