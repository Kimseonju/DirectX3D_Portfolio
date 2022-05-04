#include "StageScene1.h"
#include "../StageManager.h"
#include "Scene/Scene.h"
#include "../Object/MainLandScape.h"
#include "Component/LightComponent.h"
#include "../Object/DecalMonsterDir.h"
CStageScene1::CStageScene1()
{
}

CStageScene1::~CStageScene1()
{
}

bool CStageScene1::Init()
{
	if (!CStageScene::Init())
		return false;

	//CMainLandScape* LandScape = m_pScene->SpawnObject<CMainLandScape>("LandScape");

	//CDecalMonsterDir* LandScape1 = m_pScene->SpawnObject<CDecalMonsterDir>("LandSc1ape");
	//CDecalMonsterDir* LandScap2e = m_pScene->SpawnObject<CDecalMonsterDir>("LandSc23ape");
	//CDecalMonsterDir* LandScape3 = m_pScene->SpawnObject<CDecalMonsterDir>("LandSc3ape");
	//CDecalMonsterDir* LandSca4pe = m_pScene->SpawnObject<CDecalMonsterDir>("LandS4cape");
	return true;
}

void CStageScene1::Start()
{
	CStageScene::Start();
}

void CStageScene1::SelectPlayers(const std::string& Name1, const std::string& Name2, const std::string& Name3)
{
	CStageScene::SelectPlayers(Name1, Name2, Name3);
}

void CStageScene1::CreatePlayer(const std::string& Name, int Index)
{
	CStageScene::CreatePlayer(Name, Index);
}

void CStageScene1::SceneLoad()
{
	CStageManager::GetInst()->StartScene("StageScene1.map", m_pScene);
	SelectPlayers("Kiana", "Sakura");
	CStageManager::GetInst()->BGMPlay("Stage1BG");
}
