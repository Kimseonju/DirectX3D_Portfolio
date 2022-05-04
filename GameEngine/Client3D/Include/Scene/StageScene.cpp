#include "StageScene.h"
#include "../StageManager.h"
#include "Scene/Scene.h"
#include "../Object/KianaPlayer.h"
#include "../Object/SakuraPlayer.h"
#include "../PublicData.h"
#include "../Object/PlayerMainCamera.h"
#include "../UI/UIManager.h"
CStageScene::CStageScene()
{
}

CStageScene::~CStageScene()
{
}

bool CStageScene::Init()
{
	SceneLoad();
	CUIManager::GetInst()->FindWidgetWindow("PlayerUI")->Enable(true);
	return true;
}

void CStageScene::Start()
{
}

void CStageScene::Update(float DeltaTime)
{
	CStageManager::GetInst()->Update(DeltaTime);
}

void CStageScene::PostUpdate(float DeltaTime)
{
}

void CStageScene::SelectPlayers(const std::string& Name1, const std::string& Name2, const std::string& Name3)
{
	CPublicData::GetInst()->PlayerMapClear();
	CreatePlayer(Name1, 0);
	CreatePlayer(Name2, 1);
	CreatePlayer(Name3, 2);
}

void CStageScene::CreatePlayer(const std::string& Name, int Index)
{
	CPlayer* Player = nullptr;
	if (Name == "Kiana")
	{
		Player = m_pScene->SpawnObject<CKianaPlayer>("Kiana");
	}
	else if (Name == "Sakura")
	{
		Player= m_pScene->SpawnObject<CSakuraPlayer>("Sakura");
		Player->PlayerWait();
	}

	if (Player)
	{
		CPublicData::GetInst()->PlayerMapInsert(Index, Player);
	}
	//첫번째 선택된 캐릭터(리더) 플레이어없으면 터지게 일부러 놔둠.
	if (Index == 0)
	{
		CPublicData::GetInst()->SetCurPlayer(Player);
		Player->SetWorldPos(CStageManager::GetInst()->GetPlayerSpawnPos());
		Player->SetWorldRotation(CStageManager::GetInst()->GetPlayerSpawnRotation());
		Player->StartAnimation();
	}
}

void CStageScene::SceneLoad()
{
	//CStageManager::GetInst()->StartScene("Scene1.map", m_pScene);
}
