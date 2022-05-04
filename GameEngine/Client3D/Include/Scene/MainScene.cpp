#include "MainScene.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Render/RenderManager.h"
#include "Scene/Viewport.h"
#include "GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/AnimationMeshComponent.h"
#include "Component/LightComponent.h"
#include "Resource/ResourceManager.h"
#include "Component/BillboardComponent.h"

#include "../UI/UIManager.h"
#include "../Object/SakuraPlayer.h"
#include "../Object/KianaPlayer.h"
#include "../Animation/PlayerAnimation.h"
#include "../Object/Monster.h"
#include "../Object/DecalWind.h"
#include "../Object/MainLandScape.h"
#include "../Object/SakuraPlayer.h"
#include "../Object/AxeSoldier.h"
#include "../Object/Sniper.h"
#include "../Object/Wendy.h"
#include "../PublicData.h"
#include "../Object/MonsterSpawnObject.h"
#include "../Object/PlayerTemp.h"
#include "../Object/PlayerMainCamera.h"
#include "../Object/TestParticle.h"
#include "../Object/MapCollision.h"
#include "../Object/Effect.h"

#include "PathManager.h"
#include "../Object/LoadingStartObject.h"
#include "../Object/LobbyShip.h"
#include "../StageManager.h"
#include "../Object/Wendy_Storm.h"
#include "../Object/ColliderSpawnObject.h"
#include "../Object/BossSpawnObject.h"
#include "../Object/HitEffect.h"
#include "../Object/Wendy_AirBallEffect.h"
#include "../Object/Wendy_AirBullet.h"
#include "../Object/Wendy_AirHitEffect.h"
#include "../Object/Wendy_AirHoleEffect.h"
#include "../Object/TornadoEffect.h"
#include "../Object/Wendy_AirStar.h"
#include "../Object/TornadoTrailObject.h"
#include "../Object/Wendy_Brandish.h"
#include "../Object/Wendy_Shoot.h"
#include "../Object/ExplosionEffect.h"
#include "../Object/KnifeEffect.h"
CMainScene::CMainScene()
{
	//_CrtSetBreakAlloc(3008269);
}

CMainScene::~CMainScene()
{
}

bool CMainScene::Init()
{
	// 웬디 테스트 용 코드들

	CStageManager::GetInst()->ResourceLoad(m_pScene);
	{
		// 조명
		{
			// 전역조명 생성
			CGameObject* m_GlobalLight = m_pScene->SpawnObject<CGameObject>("GlobalLight", Vector3(0.f, 3.f, 0.f), Vector3(0.f, 0.f, 45.f));

			CLightComponent* m_GlobalLightComponent = m_GlobalLight->CreateSceneComponent<CLightComponent>("GlobalLight");

			m_GlobalLight->SetRootComponent(m_GlobalLightComponent);

			m_GlobalLightComponent->SetRelativeRotation(45.f, 90.f, 0.f);
			m_pScene->GetLightManager()->SetGlobalLightComponent(m_GlobalLightComponent);
			m_pScene->GetLightManager()->SetGlobalLight(m_GlobalLight);
		}
		// 플레이어
		{
			CPlayer* CKianaPlayer1 = m_pScene->SpawnObject<CKianaPlayer>("CKianaPlayer1");
			CPublicData::GetInst()->PlayerMapInsert(0, CKianaPlayer1);
			CPublicData::GetInst()->SetCurPlayer(CKianaPlayer1);
			CKianaPlayer1->SetRelativeRotationY(180.f);
			CPlayer* CSakuraPlayer1 = m_pScene->SpawnObject<CSakuraPlayer>("CSakuraPlayer1");
			CPublicData::GetInst()->PlayerMapInsert(1, CSakuraPlayer1);

			CPublicData::GetInst()->SetCurPlayer(CSakuraPlayer1);
			CKianaPlayer1->PlayerWait();

			CPlayerMainCamera* Camera = m_pScene->SpawnObject< CPlayerMainCamera>("PlayerMainCamera");
			Camera->SetLength(5.f);
			Camera->SetOffset(0.f, 4.f, 0.f);
		}
		// 몬스터
		{ 

			/*CColliderSpawnObject* SpawnObj = m_pScene->SpawnObject<CColliderSpawnObject>("obj");
			SpawnObj->SetWorldPos(2.f, 0.f, 2.f);
			SpawnObj->SettingCollider(Vector3(2.f, 0.f, 1.f));
			SpawnObj->SettingCollider(Vector3(-2.f, 0.f, 1.f));*/

			/*CSniper* Spawn = m_pScene->SpawnObject<CSniper>("obj");
			Spawn->SetWorldPos(2.f, 0.f, 2.f);*/

			//CColliderSpawnObject* SpawnObj = m_pScene->SpawnObject<CColliderSpawnObject>("obj");
			//SpawnObj->SetWorldPos(2.f, 0.f, 2.f);
			//SpawnObj->SettingCollider(Vector3(2.f, 0.f, 1.f));
			//SpawnObj->SettingCollider(Vector3(-2.f, 0.f, 1.f));
			
			/*CBossSpawnObject* Spawn = m_pScene->SpawnObject<CBossSpawnObject>("obj");
			Spawn->SetWorldPos(2.f, 0.f, 2.f);
			Spawn->SettingBoss("Wendy", Vector3(-2.f, 0.f, 1.f));*/

			/*CMonsterSpawnObject* Spawn = m_pScene->SpawnObject<CMonsterSpawnObject>("obj");
			Spawn->SetWorldPos(2.f, 0.f, 2.f);
			Spawn->SettingMonster("Sniper",Vector3(1.f, 0.f, 1.f));*/

			CWendy* Effect = m_pScene->SpawnObject<CWendy>("Effect");
			Effect->SetWorldPos(3.f, 0.f, 3.f);



			
			

			//KianaFire->SetMatrixPos(LeftGun->GetSocketMatrix());
			//KianaFire->SetWorldRotation(GetWorldRotation().y - 90.f, 0.f, 90.f);
		}
		// 랜드 스케이프 테스트
		{
			CMainLandScape* LandScape = m_pScene->SpawnObject<CMainLandScape>("LandScape");
		}
		//// CollisionTest
		//{
		//	CGameObject* pCollision = m_pScene->SpawnObject<CGameObject>("TestCollider1");

		//	CColliderBox3D* Box3D = pCollision->CreateSceneComponent<CColliderBox3D>("TestCollider1");

		//	pCollision->SetRootComponent(Box3D);
		//	Box3D->SetExtent(10.f,5.f,2.f);
		//	Box3D->SetCollisionProfile("MapCollision");
		//	pCollision->SetWorldPos(1.f, 0.f, -3.f);
		//	
		//}

		//{
		//	CGameObject* pCollision = m_pScene->SpawnObject<CGameObject>("TestCollider2");
		//	CColliderBox3D* Box3D = pCollision->CreateSceneComponent<CColliderBox3D>("TestCollider2");
		//	pCollision->SetRootComponent(Box3D);
		//	Box3D->SetExtent(1.f, 5.f, 9.f);
		//	Box3D->SetCollisionProfile("MapCollision");
		//	pCollision->SetWorldPos(10.f, 0.f, 3.f);

		//}
	}


	//Test code for Effect
	{
	/*	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "eff_Sphere", "Effect/eff_Sphere.msh");

		CMesh* pMesh = m_pScene->GetResource()->FindMesh("eff_Sphere");

		CEffect* pEffect = m_pScene->SpawnObject<CEffect>("eff_Sphere");
		pEffect->SetWorldPos(2.f, 2.f, 4.f);*/
	}
	return true;
}
void CMainScene::Start()
{
	CUIManager::GetInst()->Init(m_pScene);
	CUIManager::GetInst()->FindWidgetWindow("PlayerUI")->Enable(true);
}
void CMainScene::TestLoad(const char* SceneName)
{
	char    FullPath[MAX_PATH] = {};
	const PathInfo* Path = CPathManager::GetInst()->FindPath(MAP_PATH);
	if (Path)
		strcpy_s(FullPath, Path->pPathMultibyte);
	strcat_s(FullPath, SceneName);
	FILE* pFile = nullptr;
	fopen_s(&pFile, FullPath, "rb");
	if (!pFile)
		return;

	SceneLoad(pFile);

	fclose(pFile);
}
void CMainScene::SceneLoad(FILE* pFile)
{
	size_t Size;
	fread(&Size, sizeof(size_t), 1, pFile);
	for (size_t i = 0; i < Size; i++)
	{
		CGameObject* Obj = nullptr;
		Object_Type ObjectType = Object_Type::Engine;
		fread(&ObjectType, sizeof(Object_Type), 1, pFile);
		if (ObjectType == Object_Type::Client)
		{
			ClientClassType ClassType = ClientClassType::Default;
			fread(&ClassType, sizeof(ClientClassType), 1, pFile);
			switch (ClassType)
			{
			case ClientClassType::Sniper:
			{
				Obj = m_pScene->SpawnObject<CSniper>("Sniper");
				break;
			}
			case ClientClassType::Axe:
			{
				Obj = m_pScene->SpawnObject<CSniper>("Axe");
				break;
			}
			}
		}
		else
		{
			Obj = m_pScene->SpawnObject<CGameObject>("Obj");
		}
		Obj->SetObjectType(ObjectType);
		Obj->Load(pFile);

	}
}