#include "StageScene2.h"
#include "../StageManager.h"
#include "Scene/Scene.h"
#include "../Object/MainLandScape.h"
#include "Component/LightComponent.h"
#include "../Object/DecalMonsterDir.h"
CStageScene2::CStageScene2()
{
}

CStageScene2::~CStageScene2()
{
}

bool CStageScene2::Init()
{
	if (!CStageScene::Init())
		return false;

	//CMainLandScape* LandScape = m_pScene->SpawnObject<CMainLandScape>("LandScape");

	return true;
}

void CStageScene2::Start()
{
	CStageScene::Start();
}

void CStageScene2::SelectPlayers(const std::string& Name1, const std::string& Name2, const std::string& Name3)
{
	CStageScene::SelectPlayers(Name1, Name2, Name3);
}

void CStageScene2::CreatePlayer(const std::string& Name, int Index)
{
	CStageScene::CreatePlayer(Name, Index);
}

void CStageScene2::SceneLoad()
{
	CStageManager::GetInst()->StartScene("StageScene2.map", m_pScene);
	SelectPlayers("Kiana", "Sakura");
	CStageManager::GetInst()->BGMPlay("Stage2BG");
}
