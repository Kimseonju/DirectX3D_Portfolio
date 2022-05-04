#pragma once
#include "GameEngine.h"
#include "Object/Monster.h"
#include "Object/ColliderSpawnObject.h"
#include "Object/CameraMoveObject.h"
#include "Object/PlayerMainCamera.h"
class CStageManager
{
	std::vector<CSharedPtr<CMonster>> m_SpawnMonsters;
	//보스도 들고있어야하는데..
	CSharedPtr<CMonster> m_BossMonster;
	
	//바닥UI 적절한이름 추천해주세욤..
	std::vector<CSharedPtr<CGameObject>> m_MonsterDir;
	std::vector<class CSound*> m_BGMSound;
	class CLoadingThread* m_LoadThread;
	class CSound* m_PlayBGMSound;
	//플레이어가 타겟팅한 몬스터
	CSharedPtr<CGameObject> m_Target;
	CSharedPtr<CCameraMoveObject> m_CameraCut;
	CSharedPtr<CGameObject> m_PlayerSpawnPoint;
	CSharedPtr<CStaticMeshComponent> m_MapMeshComponent;
	CSharedPtr<CColliderSpawnObject> m_ColliderSpawnObject;
	CSharedPtr<CPlayerMainCamera> m_PlayerMainCamera;
	bool m_MapMeshComponentDarkness;
	bool m_Clear;
	bool m_Fail; 
	bool m_Stage;
	bool m_BossSpawn;
	float m_BossSpawnTimer;
	class CScene* m_pScene;
	float m_ClearTimer;
	int m_ClearOrder;
	std::string m_SceneName;
	int m_HitCombo;
	int m_HitComboMax;
	float m_HitTimer;
	float m_WorldSpeed;
	float m_WorldSpeedTime;
	float m_PlayTime;
	float m_MeshColor;
	bool m_Loading;
	bool m_LoadingResource;
	bool m_DarknessTimeCheck;
	//로비용 사운드 관리

public:

	void SetLoadingEnd()
	{
		m_Loading = true;
	}
	bool GetLoading()
	{
		return m_Loading;
	}
	void SetLoadThreading(class CLoadingThread* Thread)
	{
		m_LoadThread = Thread;
	}
	
	void SetMapMeshDarkness(bool Darkness)
	{
		m_MapMeshComponentDarkness = Darkness;
	}
	CStaticMeshComponent* GetMapMeshComponent()
	{
		return m_MapMeshComponent;
	}
	int GetHitComboMax()
	{
		return m_HitComboMax;
	}
	CCameraMoveObject* GetCameraCut()
	{
		return m_CameraCut;
	}
	float GetWorldSpeed()
	{
		return m_WorldSpeed;
	}
	void WorldSpeed(float Speed, float SpeedTime)
	{
		m_WorldSpeed = Speed;
		m_WorldSpeedTime = SpeedTime;
		if (SpeedTime > 0.f)
			m_DarknessTimeCheck = true;
	}
	float GetPlayTime()
	{
		return m_PlayTime;
	}
	void SetColliderSpawnObject(CColliderSpawnObject* Obj)
	{
		m_ColliderSpawnObject = Obj;
	}
	void StartScene(const char* SceneName, class CScene* Scene);
	void StoryStart();
	Vector3 GetPlayerSpawnPos() const
	{
		return m_PlayerSpawnPoint->GetWorldPos();
	}

	Vector3 GetPlayerSpawnRotation() const
	{
		return m_PlayerSpawnPoint->GetWorldRotation();
	}
	CMonster* GetMonsterTarget(const Vector3& vec);

	void PushMonster(CMonster* Monster)
	{
		m_SpawnMonsters.push_back(Monster);
	}
	void SetBoss(CMonster* Boss)
	{
		m_BossMonster = Boss;
	}
	void SetFail(bool _Fail)
	{
		m_Fail = _Fail;
	}
	bool IsFail()
	{
		return m_Fail;
	}

public:
	void Update(float DeltaTime);

private:
	void SceneLoad(FILE* pFile);
	void ProjectResourceLoading();
	bool CreateMaterial();
	bool CreateSound();
	bool CreateAnimation2D();
	bool CreateTexture2D();
	bool CreateParticle();
public:
	void ResourceLoad(CScene* Scene);
	void ResourceLoad();
	void LoadingBeforeResourceLoad(CScene* Scene);
public:
	void BGMPlay(const std::string& Name);
	void BGMStop();
public:
	void SceneClear();
	void MonsterHit();
	DECLARE_SINGLE(CStageManager);
};

