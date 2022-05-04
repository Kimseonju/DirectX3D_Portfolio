#include "LoadingThread.h"
#include "LobbyScene.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "ThreadManager.h"
#include "Sync.h"
#include "../StageManager.h"
CLoadingThread::CLoadingThread()
	:m_LoadingMaxCount(12), 
	m_LoadingCount(0),
	nextScene(nullptr)
{
	CThreadManager::GetInst()->CreateCriticalSection("LoadingCritcal");
}

CLoadingThread::~CLoadingThread()
{
}

void CLoadingThread::Run()
{
	CStageManager::GetInst()->SetLoadThreading(this);
	CScene* Scene = CSceneManager::GetInst()->CreateScene();

	Scene->SetSceneMode<CLobbyScene>();
	nextScene = Scene;
}

void CLoadingThread::SetLoadingCount(int num)
{
	CRITICAL_SECTION* Cri = CThreadManager::GetInst()->FindCriticalSection("LoadingCritcal");
	CSync sync = CSync(Cri);

	m_LoadingCount = num;

}

int CLoadingThread::GetLoadingCount() const
{
	CRITICAL_SECTION* Cri = CThreadManager::GetInst()->FindCriticalSection("LoadingCritcal");
	CSync sync = CSync(Cri);

	return m_LoadingCount;
}

float CLoadingThread::GetPersent() const
{
	CRITICAL_SECTION* Cri = CThreadManager::GetInst()->FindCriticalSection("LoadingCritcal");
	CSync sync = CSync(Cri);

	return (float)m_LoadingCount / (float)m_LoadingMaxCount;
}

void CLoadingThread::NextScene()
{
	CStageManager::GetInst()->SetLoadThreading(nullptr);
	CSceneManager::GetInst()->SetNextScene(nextScene);
	DestroyThread();
}
