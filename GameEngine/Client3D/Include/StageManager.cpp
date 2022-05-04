#include "StageManager.h"
#include "PublicData.h"
#include "PathManager.h"
#include "Scene/Scene.h"
#include "Object/AxeSoldier.h"
#include "Object/Sniper.h"
#include "Object/Wendy.h"
#include "Resource/ResourceManager.h"
#include "UI/UIManager.h"
#include "UI/PlayerHitComboUI.h"
#include "Object/Player.h"
#include "PublicData.h"
#include "Object/KianaPlayer.h"
#include "object/SakuraPlayer.h"
#include "Scene/SceneManager.h"
#include "Scene/LobbyScene.h"
#include "Scene/CameraManager.h"
#include "Object/DecalMonsterDir.h"
#include "Resource/Sound.h"
#include "Object/BossSpawnObject.h"
#include "Object/ColliderSpawnObject.h"
#include "Object/MonsterSpawnObject.h"
#include "Object/MapCollision.h"
#include "Input.h"
#include "DataTable/PlayerDataTable.h"
#include "Scene/LoadingThread.h"
DEFINITION_SINGLE(CStageManager)

CStageManager::CStageManager() :
	m_Clear(false),
	m_Stage(false),
	m_PlayBGMSound(nullptr),
	m_ClearTimer(0.f),
	m_BossSpawnTimer(0.f),
	m_HitCombo(0),
	m_HitTimer(0),
	m_PlayTime(0.f),
	m_WorldSpeedTime(1.f),
	m_HitComboMax(0),
	m_MapMeshComponentDarkness(false),
	m_MeshColor(1.f),
	m_LoadThread(nullptr),
	m_Loading(false),
	m_Fail(false),
	m_BossSpawn(false),
	m_pScene(nullptr),
	m_ClearOrder(0),
	m_WorldSpeed(1.f),
	m_LoadingResource(false)
{
}
CStageManager::~CStageManager()
{

}

void CStageManager::StartScene(const char* SceneName, CScene* Scene)
{
	m_SceneName = SceneName;
	m_Stage = true;
	m_pScene = Scene;
	m_Clear = false;
	m_Fail = false;
	m_ClearOrder = 0;
	m_PlayTime = 0.f;
	m_MapMeshComponentDarkness = false;
	//플레이어가 타겟팅한 몬스터

	SceneClear();

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

	m_PlayerMainCamera = m_pScene->SpawnObject<CPlayerMainCamera>("PlayerMainCamera");
	m_pScene->GetCameraManager()->SetCurrentCamera(m_PlayerMainCamera->GetCamera());
	m_CameraCut = m_pScene->SpawnObject<CCameraMoveObject>("CameraMoveObject");
	fclose(pFile);
	CPublicData::GetInst()->GetPlayerDataTable()->StageStart();
}

void CStageManager::StoryStart()
{
	if ("Stage1" == m_SceneName)
	{
		CWidgetWindow* Widget = CUIManager::GetInst()->FindWidgetWindow("Stage1StroyUI");
		if (Widget == nullptr)
		{
			BGMPlay("Stage1BG");
			return;
		}
		Widget->Enable(true);
	}
	else if ("Stage2" == m_SceneName)
	{
		CWidgetWindow* Widget = CUIManager::GetInst()->FindWidgetWindow("Stage1StroyUI");
		if (Widget == nullptr)
		{
			BGMPlay("Stage2BG");
			return;
		}
		Widget->Enable(true);
	}
}

CMonster* CStageManager::GetMonsterTarget(const Vector3& vec)
{
	size_t Size = m_SpawnMonsters.size();
	CMonster* Target = nullptr;
	float Length = 10.f;
	for (size_t i = 0; i < Size; ++i)
	{
		
		if (m_SpawnMonsters[i]->IsEnable()&& m_SpawnMonsters[i]->GetHp()>0)
		{
			float Len = (vec - m_SpawnMonsters[i]->GetWorldPos()).Length();
			if (Length >= Len)
			{
				Length = Len;
				Target = m_SpawnMonsters[i];
			}
		}
	}
	if (m_BossMonster)
	{
		if (m_BossMonster->IsEnable())
		{
			float Len = (vec - m_BossMonster->GetWorldPos()).Length();
			if (Length >= Len)
			{
				Length = Len;
				Target = m_BossMonster;
			}
		}
	}
	return Target;
}


void CStageManager::Update(float DeltaTime)
{
	if (!m_Stage)
	{

		return;
	}
	if (!m_Fail && !m_Clear)
	{
		m_PlayTime += DeltaTime;
	}
	m_WorldSpeedTime -= DeltaTime;
	if (m_WorldSpeedTime <= 0)
	{
		m_WorldSpeed = 1.f;
		m_WorldSpeedTime = 0.f;
		if (m_DarknessTimeCheck)
		{
			m_DarknessTimeCheck = false;
			CStageManager::GetInst()->SetMapMeshDarkness(false);
		}
	}
	if (m_SpawnMonsters.size() == 0 && m_BossMonster == nullptr)
	{
		m_Clear = true;
	}
	if (m_SpawnMonsters.size() != 0 || m_BossMonster)
	{
		m_Clear = false;
		m_ClearTimer = 0.f;
	}
	if (m_Fail)
	{
		//Fail UI 나타나고 Main Scene으로 이동
		m_PlayTime = 0.f;
	}
	if (m_MapMeshComponentDarkness)
	{
		m_MeshColor -= DeltaTime;
		if (m_MeshColor < 0.4f)
		{
			m_MeshColor = 0.4f;
		}
		m_MapMeshComponent->SetAllColor(m_MeshColor);
	}
	else
	{
		m_MeshColor += DeltaTime;
		if (m_MeshColor >1.f)
		{
			m_MeshColor = 1.f;
		}
		m_MapMeshComponent->SetAllColor(m_MeshColor);
	}
	if (m_Clear)
	{
		m_ClearTimer += DeltaTime;
		if (m_ClearTimer >= 5.f)
		{
			if (m_ClearOrder == 0)
			{
				m_CameraCut->StartCameraScene_FadeInOutWhite("SakuraVictory1", CPublicData::GetInst()->GetCurPlayer(), false, 5.f);
				BGMPlay("StageClear");
				m_ClearOrder++;
			}
			else if (m_ClearOrder == 1)
			{
				//카메라움직임이 완전히 종료가되었다면 이쪽으로
				if (m_CameraCut->IsEnd())
				{
					m_ClearTimer = 0.f;
					m_Clear = false;
					m_Stage = false;
					CInput::GetInst()->ClearCallback();
					CUIManager::GetInst()->FindWidgetWindow("GameClearUI")->Enable(false);
					
					CSceneManager::GetInst()->SetSceneMode<CLobbyScene>();
					m_PlayTime = 0.f;
				}
			}
		}	
	}
	{

		auto iter = m_SpawnMonsters.begin();
		auto iterEnd = m_SpawnMonsters.end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->IsActive())
			{
				iter = m_SpawnMonsters.erase(iter);
				iterEnd = m_SpawnMonsters.end();
				continue;
			}
			iter++;
		}
		if (m_BossMonster)
		{
			if (!m_BossMonster->IsActive())
				m_BossMonster = nullptr;
		}
	}
	int MonsterEnableCount=0;
	{
		auto iter = m_SpawnMonsters.begin();
		auto iterEnd = m_SpawnMonsters.end();

		for (; iter != iterEnd; iter++)
		{
			if ((*iter)->IsEnable())
			{
				MonsterEnableCount++;
			}
		}
		// 현재 등장한 몬스터가 없다.
		if (MonsterEnableCount == 0)
		{
			if (m_ColliderSpawnObject)
			{
				m_ColliderSpawnObject->Active(false);
				m_ColliderSpawnObject = nullptr;
			}
		}
	}
	
	size_t Size = m_SpawnMonsters.size();
	size_t i = 0;
	//for (; i < Size; ++i)
	//{
	//	if (!m_SpawnMonsters[i]->IsEnable())
	//		continue;
	//	if (nullptr == m_MonsterDir[i])
	//	{
	//
	//		m_MonsterDir[i] = m_pScene->SpawnObject<CDecalMonsterDir>("MonsterDir");
	//	}
	//
	//	m_MonsterDir[i]->SetWorldPos(CPublicData::GetInst()->GetCurPlayer()->GetWorldPos());
	//
	//	Vector3	Dir = m_SpawnMonsters[i]->GetWorldPos() - m_MonsterDir[i]->GetWorldPos();
	//	Dir.y = 0.f;
	//	Dir.Normalize();
	//	Vector3 v1 = Dir;
	//	Vector3 v2 = Vector3(0, 0, -1);
	//	v1.Normalize();
	//	v2.Normalize();
	//	float   Dot = v1.Dot(v2);
	//	float Angle = RadianToDegree(acosf(Dot));
	//	m_MonsterDir[i]->SetWorldRotationY(Angle-180.f);
	//	m_MonsterDir[i]->Enable(true);
	//}
	Size = m_MonsterDir.size();
	for (; i < Size; ++i)
	{
		if(m_MonsterDir[i])
			m_MonsterDir[i]->Enable(false);
	}

	m_HitTimer -= DeltaTime;
	if (m_HitTimer <= 0.f)
	{
		m_HitTimer = 0.f;
		CPlayerHitComboUI* ComboUI = (CPlayerHitComboUI*)CUIManager::GetInst()->FindWidgetWindow("PlayerHitComboUI");
		ComboUI->Enable(false);
		if (m_HitComboMax < m_HitCombo)
		{
			m_HitComboMax = m_HitCombo;
		}
		m_HitCombo = 0;
	}
}

void CStageManager::SceneLoad(FILE* pFile)
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
			case ClientClassType::Default:
			{
				Obj = m_pScene->SpawnObject<CClientObject>("Obj");
				break;
			}
			case ClientClassType::Kiana:
			{
				Obj = m_pScene->SpawnObject<CGameObject>("Kiana");
				break;
			}
			case ClientClassType::Sakura:
			{
				Obj = m_pScene->SpawnObject<CGameObject>("Sniper");
				break;
			}
			case ClientClassType::Sniper:
			{
				Obj = m_pScene->SpawnObject<CSniper>("Sniper");
				break;
			}
			case ClientClassType::Wendy:
			{
				Obj = m_pScene->SpawnObject<CWendy>("Wendy");
				break;
			}
			case ClientClassType::BossSpawnObject:
			{
				Obj = m_pScene->SpawnObject<CBossSpawnObject>("BossSpawnObject");
				break;
			}

			case ClientClassType::ColliderSpawnObject:
			{
				Obj = m_pScene->SpawnObject<CColliderSpawnObject>("ColliderSpawnObject");
				break;
			}
			case ClientClassType::MonsterSpawnObject:
			{
				Obj = m_pScene->SpawnObject<CMonsterSpawnObject>("MonsterSpawnObject");
				break;
			}
			case ClientClassType::MapCollision:
			{
				Obj = m_pScene->SpawnObject<CMapCollision>("MapCollision");
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

		//몬스터를 상속받고있다면 몬스터임 그외에는 건물 충돌체 등등..
		CMonster* Mon = dynamic_cast<CMonster*>(Obj);
		if (Mon)
		{
			m_SpawnMonsters.push_back(Mon);
		}

		if (Obj->GetName() == "PlayerSpawn")
		{
			m_PlayerSpawnPoint = Obj;
			m_PlayerSpawnPoint->Enable(false);
		}
		if (Obj->GetName() == "MapMesh")
		{
			m_MapMeshComponent= (CStaticMeshComponent*)Obj->FindSceneComponent("StaticMesh");
		}
	}
}

void CStageManager::ProjectResourceLoading()
{
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "Map2", "/Scene/StageScene1/Map2.msh");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "Map3", "/Scene/StageScene1/Map3.msh");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "MapColX", "/Scene/StageScene1/MapColX.msh");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "WarShip", "/Scene/LobbyScene/WarShip.msh");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "WarShip_ControlRight", "/Scene/LobbyScene/WarShip_ControlRight.msh");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "WarShip_ControlLeft", "/Scene/LobbyScene/WarShip_ControlLeft.msh");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "WarShip_ControlCenter", "/Scene/LobbyScene/WarShip_ControlCenter.msh");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "DoorUp", "/Scene/LoadingScene/DoorUp.msh");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "DoorDown", "/Scene/LoadingScene/DoorDown.msh");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "DoorDownMove", "/Scene/LoadingScene/DoorDownMove.msh");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "Door", "/Scene/LoadingScene/Door.msh");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "Pillar", "/Scene/LoadingScene/Pillar.msh");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "Elevator", "/Scene/LoadingScene/Elevator.msh");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "GroundIn", "/Scene/LoadingScene/GroundIn.msh");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "DoorMain", "/Scene/LoadingScene/DoorMain.msh");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "LoadingMark", "/Scene/LoadingScene/LoadingMark.msh");
	if(m_LoadThread)
		m_LoadThread->SetLoadingCount(3);
	CMesh* pMesh = m_pScene->GetResource()->FindMesh("Map2");
	pMesh->AllLightMaterialReset();
	pMesh = m_pScene->GetResource()->FindMesh("Map3");
	pMesh->AllLightMaterialReset();
	pMesh->GetMaterialSlot(0)->AddTexture("Stage_AirIsland_Tex_Hyperion_LowPolyLight", TEXT("Scene/StageScene1/Map3.fbm/Stage_AirIsland_Tex_Hyperion_LowPolyLight.png"), "MeshPath");
	pMesh->GetMaterialSlot(0)->SetTextureLink("Stage_AirIsland_Tex_Hyperion_LowPolyLight", Texture_Link::NormalTexture);

	pMesh = m_pScene->GetResource()->FindMesh("MapColX");
	pMesh->AllLightMaterialReset();
	for (int i = 0; i < pMesh->GetMaterialSlots()->size(); ++i)
	{
		pMesh->GetMaterialSlot(i)->SetReceiveDecal(true);
	}
	pMesh = m_pScene->GetResource()->FindMesh("WarShip");
	pMesh->AllLightMaterialReset();
	pMesh = m_pScene->GetResource()->FindMesh("WarShip_ControlRight");
	pMesh->AllLightMaterialReset();
	pMesh = m_pScene->GetResource()->FindMesh("WarShip_ControlLeft");
	pMesh->AllLightMaterialReset();
	pMesh = m_pScene->GetResource()->FindMesh("WarShip_ControlCenter");
	pMesh->AllLightMaterialReset();
	pMesh = m_pScene->GetResource()->FindMesh("DoorUp");
	pMesh->AllLightMaterialReset();
	pMesh = m_pScene->GetResource()->FindMesh("DoorDown");
	pMesh->AllLightMaterialReset();
	pMesh = m_pScene->GetResource()->FindMesh("DoorDownMove");
	pMesh->AllLightMaterialReset();
	pMesh = m_pScene->GetResource()->FindMesh("Door");
	pMesh->AllLightMaterialReset();
	pMesh = m_pScene->GetResource()->FindMesh("Pillar");
	pMesh->AllLightMaterialReset();
	pMesh = m_pScene->GetResource()->FindMesh("GroundIn");
	pMesh->AllLightMaterialReset();
	pMesh = m_pScene->GetResource()->FindMesh("DoorMain");
	pMesh->AllLightMaterialReset();
	pMesh = m_pScene->GetResource()->FindMesh("LoadingMark");
	pMesh->AllLightMaterialReset();
	if (m_LoadThread)
		m_LoadThread->SetLoadingCount(4);
#pragma region KianaResource
	{
		//m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "KianaMesh", "Player/Avatar_Sakura_C1_YS_Run.fbx");
		m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "KianaMesh", "Player/Kiana/Kiana_2.msh");
		m_pScene->GetResource()->SetAnimationMeshSkeleton("KianaMesh", "SKianaSkeleton", TEXT("Player/Kiana/Kiana_2.bne"));
		CMesh* pMesh = m_pScene->GetResource()->FindMesh("KianaMesh");
		pMesh->AllLightMaterialReset();
		pMesh->AllShadowEnable(false);
		pMesh->GetMaterialSlot(1)->AddTexture("Avatar_Kiana_C1_Texture_Body_LightMap_Common12367", TEXT("Player/Kiana/Kiana_2.fbm/Avatar_Kiana_C1_Texture_Body_LightMap_Common12367.png"), "MeshPath");
		pMesh->GetMaterialSlot(1)->SetTextureLink("Avatar_Kiana_C1_Texture_Body_LightMap_Common12367", Texture_Link::NormalTexture);
		pMesh->GetMaterialSlot(2)->AddTexture("Avatar_Kiana_C1_Texture_Body_LightMap_Common12367", TEXT("Player/Kiana/Kiana_2.fbm/Avatar_Kiana_C1_Texture_Body_LightMap_Common12367.png"), "MeshPath");
		pMesh->GetMaterialSlot(2)->SetTextureLink("Avatar_Kiana_C1_Texture_Body_LightMap_Common12367", Texture_Link::NormalTexture);
		pMesh->GetMaterialSlot(3)->AddTexture("Avatar_Kiana_C1_Texture_Body_LightMap_Common12367", TEXT("Player/Kiana/Kiana_2.fbm/Avatar_Kiana_C1_Texture_Body_LightMap_Common12367.png"), "MeshPath");
		pMesh->GetMaterialSlot(3)->SetTextureLink("Avatar_Kiana_C1_Texture_Body_LightMap_Common12367", Texture_Link::NormalTexture);
		//
		pMesh->GetMaterialSlot(4)->AddTexture("Avatar_Kiana_C1_Texture_Face_LightMap_Common4", TEXT("Player/Kiana/Kiana_2.fbm/Avatar_Kiana_C1_Texture_Face_LightMap_Common4.png"), "MeshPath");
		pMesh->GetMaterialSlot(4)->SetTextureLink("Avatar_Kiana_C1_Texture_Face_LightMap_Common4", Texture_Link::NormalTexture);
		pMesh->GetMaterialSlot(5)->AddTexture("Avatar_Kiana_C1_Texture_Hair_LightMap_Common5", TEXT("Player/Kiana/Kiana_2.fbm/Avatar_Kiana_C1_Texture_Hair_LightMap_Common5.png"), "MeshPath");
		pMesh->GetMaterialSlot(5)->SetTextureLink("Avatar_Kiana_C1_Texture_Hair_LightMap_Common5", Texture_Link::NormalTexture);
		
		pMesh->GetMaterialSlot(6)->AddTexture("Avatar_Kiana_C1_Texture_Body_LightMap_Common12367", TEXT("Player/Kiana/Kiana_2.fbm/Avatar_Kiana_C1_Texture_Body_LightMap_Common12367.png"), "MeshPath");
		pMesh->GetMaterialSlot(6)->SetTextureLink("Avatar_Kiana_C1_Texture_Body_LightMap_Common12367", Texture_Link::NormalTexture);
		pMesh->GetMaterialSlot(7)->AddTexture("Avatar_Kiana_C1_Texture_Body_LightMap_Common12367", TEXT("Player/Kiana/Kiana_2.fbm/Avatar_Kiana_C1_Texture_Body_LightMap_Common12367.png"), "MeshPath");
		pMesh->GetMaterialSlot(7)->SetTextureLink("Avatar_Kiana_C1_Texture_Body_LightMap_Common12367", Texture_Link::NormalTexture);
		//키아나
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_Ultra_Artifact", TEXT("Player/Kiana/Avatar_Kiana_C1_Ultra_Artifact.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_Branch_03_Artifact", TEXT("Player/Kiana/Avatar_Kiana_C1_Branch_03_Artifact.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_Skill_Ultra", TEXT("Player/Kiana/Avatar_Kiana_C1_Skill_Ultra.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_EvadeForward_Artifact", TEXT("Player/Kiana/Avatar_Kiana_C1_EvadeForward_Artifact.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_Branch_02_Artifact", TEXT("Player/Kiana/Avatar_Kiana_C1_Branch_02_Artifact.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_EvadeBackward_Artifact", TEXT("Player/Kiana/Avatar_Kiana_C1_EvadeBackward_Artifact.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_Branch_01_Artifact", TEXT("Player/Kiana/Avatar_Kiana_C1_Branch_01_Artifact.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_Branch_01_Loop", TEXT("Player/Kiana/Avatar_Kiana_C1_Branch_01_Loop.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_Attack_QTE_Gun_Low", TEXT("Player/Kiana/Avatar_Kiana_C1_Attack_QTE_Gun_Low.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_HolyFireSlash", TEXT("Player/Kiana/Avatar_Kiana_C1_HolyFireSlash.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_QTE_Artifact", TEXT("Player/Kiana/Avatar_Kiana_C1_QTE_Artifact.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_Appear", TEXT("Player/Kiana/Avatar_Kiana_C1_Appear.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_Attack_Gun_04_02", TEXT("Player/Kiana/Avatar_Kiana_C1_Attack_Gun_04_02.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_Cyclone_Low", TEXT("Player/Kiana/Avatar_Kiana_C1_Cyclone_Low.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_SpecialStun_AS_Artifact", TEXT("Player/Kiana/Avatar_Kiana_C1_SpecialStun_AS_Artifact.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_Failure_01", TEXT("Player/Kiana/Avatar_Kiana_C1_Failure_01.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_Failure_01_", TEXT("Player/Kiana/Avatar_Kiana_C1_Failure_01_.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_Weapon_Hammer", TEXT("Player/Kiana/Avatar_Kiana_C1_Weapon_Hammer.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_Attack_Gun_03", TEXT("Player/Kiana/Avatar_Kiana_C1_Attack_Gun_03.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_Idle_03", TEXT("Player/Kiana/Avatar_Kiana_C1_Idle_03.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_SpecialStun_BS_Artifact", TEXT("Player/Kiana/Avatar_Kiana_C1_SpecialStun_BS_Artifact.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_Attack_04_Artifact", TEXT("Player/Kiana/Avatar_Kiana_C1_Attack_04_Artifact.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_Attack_03_Artifact", TEXT("Player/Kiana/Avatar_Kiana_C1_Attack_03_Artifact.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_Attack_Gun_04_01", TEXT("Player/Kiana/Avatar_Kiana_C1_Attack_Gun_04_01.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_Idle_02", TEXT("Player/Kiana/Avatar_Kiana_C1_Idle_02.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_EvadeBackward_fix", TEXT("Player/Kiana/Avatar_Kiana_C1_EvadeBackward_fix.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_Die", TEXT("Player/Kiana/Avatar_Kiana_C1_Die.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_Victory_01", TEXT("Player/Kiana/Avatar_Kiana_C1_Victory_01.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_SixShot", TEXT("Player/Kiana/Avatar_Kiana_C1_SixShot.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_Attack_Gun_01", TEXT("Player/Kiana/Avatar_Kiana_C1_Attack_Gun_01.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_EvadeForward", TEXT("Player/Kiana/Avatar_Kiana_C1_EvadeForward.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_Idle_01", TEXT("Player/Kiana/Avatar_Kiana_C1_Idle_01.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_DualShot", TEXT("Player/Kiana/Avatar_Kiana_C1_DualShot.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_Victory_Idle", TEXT("Player/Kiana/Avatar_Kiana_C1_Victory_Idle.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_Attack_Gun_02", TEXT("Player/Kiana/Avatar_Kiana_C1_Attack_Gun_02.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_Attack_02_Artifact", TEXT("Player/Kiana/Avatar_Kiana_C1_Attack_02_Artifact.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_QuantumEvade", TEXT("Player/Kiana/Avatar_Kiana_C1_QuantumEvade.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_Sakura", TEXT("Player/Kiana/Avatar_Kiana_C1_Sakura.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_Hit_H", TEXT("Player/Kiana/Avatar_Kiana_C1_Hit_H.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_Victory_01_Artifact", TEXT("Player/Kiana/Avatar_Kiana_C1_Victory_01_Artifact.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_Cyclone_AS", TEXT("Player/Kiana/Avatar_Kiana_C1_Cyclone_AS.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_Weapon_SkyShot", TEXT("Player/Kiana/Avatar_Kiana_C1_Weapon_SkyShot.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_SpecialStun_Artifact", TEXT("Player/Kiana/Avatar_Kiana_C1_SpecialStun_Artifact.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_RunStopRight", TEXT("Player/Kiana/Avatar_Kiana_C1_RunStopRight.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_Hit_L", TEXT("Player/Kiana/Avatar_Kiana_C1_Hit_L.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_SwitchIn", TEXT("Player/Kiana/Avatar_Kiana_C1_SwitchIn.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_RunBS_fix", TEXT("Player/Kiana/Avatar_Kiana_C1_RunBS_fix.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_Weapon_SpecialShot", TEXT("Player/Kiana/Avatar_Kiana_C1_Weapon_SpecialShot.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_Stun", TEXT("Player/Kiana/Avatar_Kiana_C1_Stun.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_SwitchOut", TEXT("Player/Kiana/Avatar_Kiana_C1_SwitchOut.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_ElectroMelee", TEXT("Player/Kiana/Avatar_Kiana_C1_ElectroMelee.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_RobotMelee", TEXT("Player/Kiana/Avatar_Kiana_C1_RobotMelee.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_StandBy", TEXT("Player/Kiana/Avatar_Kiana_C1_StandBy.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_Cyclone_Repeat", TEXT("Player/Kiana/Avatar_Kiana_C1_Cyclone_Repeat.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_RunStopLeft", TEXT("Player/Kiana/Avatar_Kiana_C1_RunStopLeft.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_Cyclone_BS", TEXT("Player/Kiana/Avatar_Kiana_C1_Cyclone_BS.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_FastRun", TEXT("Player/Kiana/Avatar_Kiana_C1_FastRun.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_UI_TurnAround", TEXT("Player/Kiana/Avatar_Kiana_C1_UI_TurnAround.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_RunBS", TEXT("Player/Kiana/Avatar_Kiana_C1_RunBS.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_Failure_01_Idle", TEXT("Player/Kiana/Avatar_Kiana_C1_Failure_01_Idle.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_UI_StandBy_Back", TEXT("Player/Kiana/Avatar_Kiana_C1_UI_StandBy_Back.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_UI_StandBy_No_Weapon", TEXT("Player/Kiana/Avatar_Kiana_C1_UI_StandBy_No_Weapon.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_Victory_Idle_Artifact", TEXT("Player/Kiana/Avatar_Kiana_C1_Victory_Idle_Artifact.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Kiana_C1_Run", TEXT("Player/Kiana/Avatar_Kiana_C1_Run.sqc"), MESH_PATH);
		

		//공격콤보 Notify로 다음콤보 되게 ON하기
		//이동입력안받으면 바로 Idle재생되게해야함
		//

		m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "KianaLeftPistol", "Player/Kiana/KianaLeftPistol.msh");
		m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "KianaRightPistol", "Player/Kiana/KianaRightPistol.msh");

		pMesh = m_pScene->GetResource()->FindMesh("KianaLeftPistol");
		pMesh->AllLightMaterialReset();
		pMesh = m_pScene->GetResource()->FindMesh("KianaRightPistol");
		pMesh->AllLightMaterialReset();
	}

	if (m_LoadThread)
		m_LoadThread->SetLoadingCount(5);
#pragma endregion
#pragma region SakuraResource

	{
		//m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "Avatar_Sakura_C1_YS_Run", "Player/Sakura/Avatar_Sakura_C1_YS_Run.fbx");
		m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "SakuraMesh", "Player/Sakura/Sakura_2.msh");
		m_pScene->GetResource()->SetAnimationMeshSkeleton("SakuraMesh", "SakuraSkeleton", TEXT("Player/Sakura/Sakura_2.bne"));
		CMesh* pMesh = m_pScene->GetResource()->FindMesh("SakuraMesh");
		pMesh->AllLightMaterialReset();
		pMesh->AllShadowEnable(false);
		
	pMesh->GetMaterialSlot(2)->AddTexture("Avatar_Yae_sakura_C1_Texture_Body_LightMap234589", TEXT("Player/Sakura/Sakura_2.fbm/Avatar_Yae_sakura_C1_Texture_Body_LightMap234589.tga"), "MeshPath");
	pMesh->GetMaterialSlot(2)->SetTextureLink("Avatar_Yae_sakura_C1_Texture_Body_LightMap234589", Texture_Link::NormalTexture);
	pMesh->GetMaterialSlot(3)->AddTexture("Avatar_Yae_sakura_C1_Texture_Body_LightMap234589", TEXT("Player/Sakura/Sakura_2.fbm/Avatar_Yae_sakura_C1_Texture_Body_LightMap234589.tga"), "MeshPath");
	pMesh->GetMaterialSlot(3)->SetTextureLink("Avatar_Yae_sakura_C1_Texture_Body_LightMap234589", Texture_Link::NormalTexture);
	pMesh->GetMaterialSlot(4)->AddTexture("Avatar_Yae_sakura_C1_Texture_Body_LightMap234589", TEXT("Player/Sakura/Sakura_2.fbm/Avatar_Yae_sakura_C1_Texture_Body_LightMap234589.tga"), "MeshPath");
	pMesh->GetMaterialSlot(4)->SetTextureLink("Avatar_Yae_sakura_C1_Texture_Body_LightMap234589", Texture_Link::NormalTexture);
	pMesh->GetMaterialSlot(5)->AddTexture("Avatar_Yae_sakura_C1_Texture_Body_LightMap234589", TEXT("Player/Sakura/Sakura_2.fbm/Avatar_Yae_sakura_C1_Texture_Body_LightMap234589.tga"), "MeshPath");
	pMesh->GetMaterialSlot(5)->SetTextureLink("Avatar_Yae_sakura_C1_Texture_Body_LightMap234589", Texture_Link::NormalTexture);
	pMesh->GetMaterialSlot(6)->AddTexture("Avatar_Yae_sakura_C0_Texture_Face_LightMap6", TEXT("Player/Sakura/Sakura_2.fbm/Avatar_Yae_sakura_C0_Texture_Face_LightMap6.tga"), "MeshPath");
	pMesh->GetMaterialSlot(6)->SetTextureLink("Avatar_Yae_sakura_C0_Texture_Face_LightMap6", Texture_Link::NormalTexture);
	pMesh->GetMaterialSlot(7)->AddTexture("Avatar_Yae_sakura_C0_Texture_Hair_LightMap7", TEXT("Player/Sakura/Sakura_2.fbm/Avatar_Yae_sakura_C0_Texture_Hair_LightMap7.tga"), "MeshPath");
	pMesh->GetMaterialSlot(7)->SetTextureLink("Avatar_Yae_sakura_C0_Texture_Hair_LightMap7", Texture_Link::NormalTexture);
	pMesh->GetMaterialSlot(8)->AddTexture("Avatar_Yae_sakura_C1_Texture_Body_LightMap234589", TEXT("Player/Sakura/Sakura_2.fbm/Avatar_Yae_sakura_C1_Texture_Body_LightMap234589.tga"), "MeshPath");
	pMesh->GetMaterialSlot(8)->SetTextureLink("Avatar_Yae_sakura_C1_Texture_Body_LightMap234589", Texture_Link::NormalTexture);
	pMesh->GetMaterialSlot(9)->AddTexture("Avatar_Yae_sakura_C1_Texture_Body_LightMap234589", TEXT("Player/Sakura/Sakura_2.fbm/Avatar_Yae_sakura_C1_Texture_Body_LightMap234589.tga"), "MeshPath");
	pMesh->GetMaterialSlot(9)->SetTextureLink("Avatar_Yae_sakura_C1_Texture_Body_LightMap234589", Texture_Link::NormalTexture);
	m_pScene->GetResource()->LoadAnimationSequence("Sakura_Appear", TEXT("Character/Sakura_Appear.sqc"), MESH_PATH);
	m_pScene->GetResource()->LoadAnimationSequence("Sakura_Idle", TEXT("Character/Avatar_Yae_Sakura_Ani_Attack_01_StandBy.sqc"), MESH_PATH);

	if (m_LoadThread)
		m_LoadThread->SetLoadingCount(6);
		//등장씬
		//m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "Avatar_Sakura_C1_YS_Appear", "Player/Sakura/Avatar_Sakura_C1_YS_Appear.fbx");
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Sakura_C1_YS_Appear", TEXT("Player/Sakura/Avatar_Yae_Sakura_Ani_Appear.sqc"), MESH_PATH);

		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Sakura_C1_YS1", TEXT("Player/Sakura/Avatar_Sakura_C1_YS1.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Yae_Sakura_Ani_Idle", TEXT("Player/Sakura/Avatar_Yae_Sakura_Ani_Idle.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Yae_Sakura_Ani_Attack_01_Combat", TEXT("Player/Sakura/Avatar_Yae_Sakura_Ani_Attack_01_Combat.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Yae_Sakura_Ani_Attack_01_StandBy", TEXT("Player/Sakura/Avatar_Yae_Sakura_Ani_Attack_01_StandBy.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Yae_Sakura_Ani_Attack_02", TEXT("Player/Sakura/Avatar_Yae_Sakura_Ani_Attack_02.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Yae_Sakura_Ani_Attack_03", TEXT("Player/Sakura/Avatar_Yae_Sakura_Ani_Attack_03.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Yae_Sakura_Ani_Attack_04", TEXT("Player/Sakura/Avatar_Yae_Sakura_Ani_Attack_04.sqc"), MESH_PATH); //üũ
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Yae_Sakura_Ani_Attack_05", TEXT("Player/Sakura/Avatar_Yae_Sakura_Ani_Attack_05.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Yae_Sakura_Ani_Charge_01_C3Ult", TEXT("Player/Sakura/Avatar_Yae_Sakura_Ani_Charge_01_C3Ult.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Yae_Sakura_Ani_Charge_01_Quick", TEXT("Player/Sakura/Avatar_Yae_Sakura_Ani_Charge_01_Quick.sqc"), MESH_PATH);
		//공격대기모드 일정시간지나면 CombatTo로
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Yae_Sakura_Ani_Combat", TEXT("Player/Sakura/Avatar_Yae_Sakura_Ani_Combat.sqc"), MESH_PATH);
		//Idle가기전 완료되면 Idle로 이동
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Yae_Sakura_Ani_CombatToStandBy", TEXT("Player/Sakura/Avatar_Yae_Sakura_Ani_CombatToStandBy.sqc"), MESH_PATH);

		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Yae_Sakura_Ani_Idle", TEXT("Player/Sakura/Avatar_Yae_Sakura_Ani_Idle.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Yae_Sakura_Ani_Run", TEXT("Player/Sakura/Avatar_Yae_Sakura_Ani_Run.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Yae_sakura_Ani_Die", TEXT("Player/Sakura/Avatar_Yae_sakura_Ani_Die.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Yae_Sakura_Ani_Failure_01", TEXT("Player/Sakura/Avatar_Yae_Sakura_Ani_Failure_01.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Yae_Sakura_Ani_Failure_Loop", TEXT("Player/Sakura/Avatar_Yae_Sakura_Ani_Failure_Loop.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Yae_Sakura_Ani_Hit_H", TEXT("Player/Sakura/Avatar_Yae_Sakura_Ani_Hit_H.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Yae_Sakura_Ani_Hit_L", TEXT("Player/Sakura/Avatar_Yae_Sakura_Ani_Hit_L.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Yae_Sakura_Ani_Idle", TEXT("Player/Sakura/Avatar_Yae_Sakura_Ani_Idle.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Yae_Sakura_Ani_Run", TEXT("Player/Sakura/Avatar_Yae_Sakura_Ani_Run.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Yae_Sakura_Ani_RunBS", TEXT("Player/Sakura/Avatar_Yae_Sakura_Ani_RunBS.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Yae_Sakura_Ani_RunStopLeft", TEXT("Player/Sakura/Avatar_Yae_Sakura_Ani_RunStopLeft.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Yae_Sakura_Ani_RunStopRight", TEXT("Player/Sakura/Avatar_Yae_Sakura_Ani_RunStopRight.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Yae_Sakura_Ani_Skill_01", TEXT("Player/Sakura/Avatar_Yae_Sakura_Ani_Skill_01.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Yae_sakura_Ani_Skill_Ultra_01", TEXT("Player/Sakura/Avatar_Yae_sakura_Ani_Skill_Ultra_01.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Yae_sakura_Ani_Stun", TEXT("Player/Sakura/Avatar_Yae_sakura_Ani_Stun.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Yae_Sakura_Ani_SwitchIn", TEXT("Player/Sakura/Avatar_Yae_Sakura_Ani_SwitchIn.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Yae_Sakura_Ani_SwitchRole", TEXT("Player/Sakura/Avatar_Yae_Sakura_Ani_SwitchRole.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Yae_Sakura_Ani_UI_StandBy", TEXT("Player/Sakura/Avatar_Yae_Sakura_Ani_UI_StandBy.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Yae_Sakura_Ani_UI_StandBy_Back", TEXT("Player/Sakura/Avatar_Yae_Sakura_Ani_UI_StandBy_Back.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Yae_sakura_Ani_Weapon_CastDown", TEXT("Player/Sakura/Avatar_Yae_sakura_Ani_Weapon_CastDown.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Yae_sakura_Ani_Weapon_CircleCut", TEXT("Player/Sakura/Avatar_Yae_sakura_Ani_Weapon_CircleCut.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Yae_sakura_Ani_Weapon_GroundField", TEXT("Player/Sakura/Avatar_Yae_sakura_Ani_Weapon_GroundField.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Yae_sakura_Ani_Weapon_QuantumDash", TEXT("Player/Sakura/Avatar_Yae_sakura_Ani_Weapon_QuantumDash.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Yae_sakura_Ani_Weapon_SpaceTear", TEXT("Player/Sakura/Avatar_Yae_sakura_Ani_Weapon_SpaceTear.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Yae_sakura_Ani_Weapon_SprintCut", TEXT("Player/Sakura/Avatar_Yae_sakura_Ani_Weapon_SprintCut.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Yae_sakura_Ani_Weapon_Whirl", TEXT("Player/Sakura/Avatar_Yae_sakura_Ani_Weapon_Whirl.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Yae_sakura_Ani_win", TEXT("Player/Sakura/Avatar_Yae_sakura_Ani_win.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Yae_sakura_Ani_win_idle", TEXT("Player/Sakura/Avatar_Yae_sakura_Ani_win_idle.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Yae_Sakura_EvadeBackward", TEXT("Player/Sakura/Avatar_Yae_Sakura_EvadeBackward.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Yae_Sakura_EvadeForward", TEXT("Player/Sakura/Avatar_Yae_Sakura_EvadeForward.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Avatar_Yae_Sakura_Stun_A", TEXT("Player/Sakura/Avatar_Yae_Sakura_Stun_A.sqc"), MESH_PATH);

		//공격콤보 Notify로 다음콤보 되게 ON하기
		//이동입력안받으면 바로 Idle재생되게해야함
		//

		m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "Katana_1", "Player/Sakura/Weapon_Katana_M2_17_3.msh");
		pMesh = m_pScene->GetResource()->FindMesh("Katana_1");
		pMesh->AllLightMaterialReset();

	}

	if (m_LoadThread)
		m_LoadThread->SetLoadingCount(7);
#pragma endregion
#pragma region AxeSoldierResource

	if (!CPublicData::GetInst()->Axe_ResourceCheck)
	{
		CPublicData::GetInst()->Axe_ResourceCheck = true;
		m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "AxesoldierMesh", "Monster/Axe/DG_070.msh");
		m_pScene->GetResource()->SetAnimationMeshSkeleton("AxesoldierMesh", "AxesoldierSkeleton", TEXT("Monster/Axe/DG_070.bne"));
		CMesh* pMesh1 = m_pScene->GetResource()->FindMesh("AxesoldierMesh");
		pMesh1->AllLightMaterialReset();
		pMesh1->AllShadowEnable(false);

		m_pScene->GetResource()->LoadAnimationSequence("AxeSoldier_Idle", TEXT("Monster/Axe/Animation/DG_070_Ani_Bron.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("AxeSoldier_NAttack", TEXT("Monster/Axe/Animation/DG_010_Ani_Attack_1.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("AxeSoldier_FAttack_1", TEXT("Monster/Axe/Animation/DG_010_Ani_Attack_2.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("AxeSoldier_FAttack_2", TEXT("Monster/Axe/Animation/DG_010_Ani_Attack_2_1.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("AxeSoldier_TAttack", TEXT("Monster/Axe/Animation/DG_070_Ani_Attack_3.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("AxeSoldier_RAttack", TEXT("Monster/Axe/Animation/DG_070_Ani_Attack_3_1.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("AxeSoldier_Hit", TEXT("Monster/Axe/Animation/DG_010_Ani_Hit_Back.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("AxeSoldier_Hit_HFly", TEXT("Monster/Axe/Animation/DG_010_Ani_Hit_Throw.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("AxeSoldier_Hit_LFly", TEXT("Monster/Axe/Animation/DG_010_Ani_Hit_Throw_Low.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("AxeSoldier_FlyToKnockBack", TEXT("Monster/Axe/Animation/DG_010_Ani_KnockDown.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("AxeSoldier_StandUp", TEXT("Monster/Axe/Animation/DG_010_Ani_StandUp.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("AxeSoldier_StandBy", TEXT("Monster/Axe/Animation/DG_010_Ani_StandBy.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("AxeSoldier_Stun", TEXT("Monster/Axe/Animation/DG_010_Ani_Stun.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("AxeSoldier_HThrow_1", TEXT("Monster/Axe/Animation/DG_010_Ani_Throw_01.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("AxeSoldier_LThrow_1", TEXT("Monster/Axe/Animation/DG_010_Ani_Throw_02.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("AxeSoldier_KnockBack", TEXT("Monster/Axe/Animation/DG_010_Ani_Throw_Blow.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("AxeSoldier_Run", TEXT("Monster/Axe/Animation/Monster_DG_070_Run.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("AxeSoldier_Run+", TEXT("Monster/Axe/Animation/Monster_DG_070_Run.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("AxeSoldier_BWalk", TEXT("Monster/Axe/Animation/DG_010_Ani_Walk_B.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("AxeSoldier_LWalk", TEXT("Monster/Axe/Animation/DG_010_Ani_Walk_L.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("AxeSoldier_RWalk", TEXT("Monster/Axe/Animation/DG_010_Ani_Walk_R.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("AxeSoldier_NDie", TEXT("Monster/Axe/Animation/DG_070_Ani_Die.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("AxeSoldier_BDie", TEXT("Monster/Axe/Animation/DG_070_Ani_Die_Back.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("AxeSoldier_FDie", TEXT("Monster/Axe/Animation/DG_070_Ani_Die_Fly.sqc"), MESH_PATH);
	}
#pragma endregion
	if (m_LoadThread)
		m_LoadThread->SetLoadingCount(8);
#pragma region SniperResource

	if (!CPublicData::GetInst()->Sniper_ResourceCheck)
	{
		CPublicData::GetInst()->Sniper_ResourceCheck = true;
		m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "SniperMesh", "Monster/Sniper/DG_080.msh");
		m_pScene->GetResource()->SetAnimationMeshSkeleton("SniperMesh", "SniperSkeleton", TEXT("Monster/Sniper/DG_080.bne"));
		CMesh* pMesh1 = m_pScene->GetResource()->FindMesh("SniperMesh");
		pMesh1->AllLightMaterialReset();
		pMesh1->AllShadowEnable(false);

		//m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "SnasdiperMesh", "Monster/Sniper/Animation/DG_080.fbx");
		m_pScene->GetResource()->LoadAnimationSequence("Sniper_Idle", TEXT("Monster/Sniper/Animation/DG_080_Ani_StandBy.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Sniper_Run", TEXT("Monster/Sniper/Animation/DG_080_Ani_Run.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Sniper_Run+", TEXT("Monster/Sniper/Animation/DG_080_Ani_Run.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Sniper_Backward", TEXT("Monster/Sniper/Animation/DG_080_Ani_Walk_Backward.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Sniper_NAttack", TEXT("Monster/Sniper/Animation/DG_080_Ani_Attack_1.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Sniper_GAttack", TEXT("Monster/Sniper/Animation/DG_080_Ani_Attack_1_Throw_Grenade.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Sniper_RAttack", TEXT("Monster/Sniper/Animation/DG_080_Ani_Attack_2_Rush.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Sniper_FAttack", TEXT("Monster/Sniper/Animation/DG_080_Ani_Attack_4_1.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Sniper_AttToIdle", TEXT("Monster/Sniper/Animation/DG_080_Ani_Born.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Sniper_Stun", TEXT("Monster/Sniper/Animation/DG_080_Ani_Stun.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Sniper_HHit", TEXT("Monster/Sniper/Animation/DG_080_Ani_Hit_H.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Sniper_LHit", TEXT("Monster/Sniper/Animation/DG_080_Ani_Hit_L.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Sniper_HFly", TEXT("Monster/Sniper/Animation/DG_080_Ani_Hit_Throw.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Sniper_LFly", TEXT("Monster/Sniper/Animation/DG_080_Ani_Hit_Throw_Low.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Sniper_FlyToKnockDown", TEXT("Monster/Sniper/Animation/DG_080_Ani_KnockDown.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Sniper_StandUp", TEXT("Monster/Sniper/Animation/DG_080_Ani_StandUP.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Sniper_HFlyALL", TEXT("Monster/Sniper/Animation/DG_080_Ani_Throw_01.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Sniper_HFlyToStand", TEXT("Monster/Sniper/Animation/DG_080_Ani_Throw_02.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Sniper_Die", TEXT("Monster/Sniper/Animation/DG_080_Ani_Die.sqc"), MESH_PATH);
		//m_pScene->GetResource()->LoadAnimationSequence("4", TEXT("Monster/Sniper/Animation/DG_080_Ani_Appear.sqc"), MESH_PATH);
		//m_pScene->GetResource()->LoadAnimationSequence("6", TEXT("Monster/Sniper/Animation/DG_080_Ani_Attack_1_Throw.sqc"), MESH_PATH);
		//m_pScene->GetResource()->LoadAnimationSequence("7", TEXT("Monster/Sniper/Animation/DG_080_Ani_Attack_1_Throw_2.sqc"), MESH_PATH);
		//m_pScene->GetResource()->LoadAnimationSequence("10", TEXT("Monster/Sniper/Animation/DG_080_Ani_Attack_3.sqc"), MESH_PATH);
		//m_pScene->GetResource()->LoadAnimationSequence("11", TEXT("Monster/Sniper/Animation/DG_080_Ani_Attack_3_2.sqc"), MESH_PATH);
		//m_pScene->GetResource()->LoadAnimationSequence("12", TEXT("Monster/Sniper/Animation/DG_080_Ani_Attack_3_H.sqc"), MESH_PATH);
		//m_pScene->GetResource()->LoadAnimationSequence("14", TEXT("Monster/Sniper/Animation/DG_080_Ani_Attack_UAV.sqc"), MESH_PATH);
		//m_pScene->GetResource()->LoadAnimationSequence("15", TEXT("Monster/Sniper/Animation/DG_080_Ani_Blow.sqc"), MESH_PATH);
		//m_pScene->GetResource()->LoadAnimationSequence("18", TEXT("Monster/Sniper/Animation/DG_080_Ani_Die_Back.sqc"), MESH_PATH);
		//m_pScene->GetResource()->LoadAnimationSequence("19", TEXT("Monster/Sniper/Animation/DG_080_Ani_Die_Fly.sqc"), MESH_PATH);
		//m_pScene->GetResource()->LoadAnimationSequence("20", TEXT("Monster/Sniper/Animation/DG_080_Ani_Hit_Back.sqc"), MESH_PATH);
		//m_pScene->GetResource()->LoadAnimationSequence("21", TEXT("Monster/Sniper/Animation/DG_080_Ani_Hit_Front.sqc"), MESH_PATH);
		//m_pScene->GetResource()->LoadAnimationSequence("22", TEXT("Monster/Sniper/Animation/DG_080_Ani_Hit_Front_L.sqc"), MESH_PATH);
		//m_pScene->GetResource()->LoadAnimationSequence("24", TEXT("Monster/Sniper/Animation/DG_080_Ani_Hit_H_Early.sqc"), MESH_PATH);
		//m_pScene->GetResource()->LoadAnimationSequence("26", TEXT("Monster/Sniper/Animation/DG_080_Ani_Hit_L_Early.sqc"), MESH_PATH);
		//m_pScene->GetResource()->LoadAnimationSequence("27", TEXT("Monster/Sniper/Animation/DG_080_Ani_Hit_Shake.sqc"), MESH_PATH);
	}
#pragma endregion
	if (m_LoadThread)
		m_LoadThread->SetLoadingCount(9);
#pragma region WendyResource

	if (!CPublicData::GetInst()->Wendy_ResourceCheck)
	{
		//	// ?醫딅빍筌롫뗄???fbx ??疫?
		//{
		//	for (int i = 1; i <= 32; i++)
		//	{
		//		std::string Name = {};
		//		Name = "Monster/Wendy/Animation/00 (";
		//		Name += std::to_string(i);
		//		Name += ")/Animator/Boss_020/Boss_020.fbx";
		//		m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, Name+"AxesoldierMesh", Name.c_str());
		//	}
		//}
		{
			CPublicData::GetInst()->Wendy_ResourceCheck = true;
			m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "WendyMesh", "Monster/Wendy/Boss_020.msh");
			m_pScene->GetResource()->SetAnimationMeshSkeleton("WendyMesh", "WendySkeleton", TEXT("Monster/Wendy/Boss_020.bne"));
			CMesh* pMesh1 = m_pScene->GetResource()->FindMesh("WendyMesh");
			pMesh1->AllLightMaterialReset();
			pMesh1->AllShadowEnable(false);
			pMesh1->GetMaterialSlot(0)->AddTexture("Boss_020_Body_Lightmap", TEXT("Monster/Wendy/Boss_020_Body_Lightmap.png"), "MeshPath");
			pMesh1->GetMaterialSlot(0)->SetTextureLink("Boss_020_Body_Lightmap", Texture_Link::NormalTexture);
			pMesh1->GetMaterialSlot(0)->AddTexture("Boss_020_Body_Lightmap", TEXT("Monster/Wendy/Boss_020_Body_Lightmap.png"), "MeshPath");
			pMesh1->GetMaterialSlot(0)->SetTextureLink("Boss_020_Body_Lightmap", Texture_Link::NormalTexture);
			pMesh1->GetMaterialSlot(1)->AddTexture("Boss_020_Body_Lightmap", TEXT("Monster/Wendy/Boss_020_Body_Lightmap.png"), "MeshPath");
			pMesh1->GetMaterialSlot(1)->SetTextureLink("Boss_020_Body_Lightmap", Texture_Link::NormalTexture);
			pMesh1->GetMaterialSlot(2)->AddTexture("Boss_020_Body_Lightmap", TEXT("Monster/Wendy/Boss_020_Body_Lightmap.png"), "MeshPath");
			pMesh1->GetMaterialSlot(2)->SetTextureLink("Boss_020_Body_Lightmap", Texture_Link::NormalTexture);
			pMesh1->GetMaterialSlot(3)->AddTexture("Boss_020_Body_Lightmap", TEXT("Monster/Wendy/Boss_020_Body_Lightmap.png"), "MeshPath");
			pMesh1->GetMaterialSlot(3)->SetTextureLink("Boss_020_Body_Lightmap", Texture_Link::NormalTexture);
			pMesh1->GetMaterialSlot(4)->AddTexture("Boss_020_Body_Lightmap", TEXT("Monster/Wendy/Boss_020_Body_Lightmap.png"), "MeshPath");
			pMesh1->GetMaterialSlot(4)->SetTextureLink("Boss_020_Body_Lightmap", Texture_Link::NormalTexture);
			pMesh1->GetMaterialSlot(5)->AddTexture("Boss_020_Face_Lightmap", TEXT("Monster/Wendy/Boss_020_Face_Lightmap.png"), "MeshPath");
			pMesh1->GetMaterialSlot(5)->SetTextureLink("Boss_020_Face_Lightmap", Texture_Link::NormalTexture);
			pMesh1->GetMaterialSlot(6)->AddTexture("Boss_020_Hair_Lightmap", TEXT("Monster/Wendy/Boss_020_Hair_Lightmap.png"), "MeshPath");
			pMesh1->GetMaterialSlot(6)->SetTextureLink("Boss_020_Hair_Lightmap", Texture_Link::NormalTexture);

		}

		m_pScene->GetResource()->LoadAnimationSequence("Wendy_Idle", TEXT("Monster/Wendy/Animation/Boss_020_Ani_StandBy.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Boss_020_Ani_StandBy", TEXT("Monster/Wendy/Animation/Boss_020_Ani_StandBy.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Wendy_Run", TEXT("Monster/Wendy/Animation/Boss_020_Ani_Run.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Wendy_RunStart", TEXT("Monster/Wendy/Animation/BOSS_020_Ani_RunStart.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Wendy_GlideBack", TEXT("Monster/Wendy/Animation/BOSS_020_Ani_GlideBack.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Wendy_GlideLeft", TEXT("Monster/Wendy/Animation/BOSS_020_Ani_GlideLeft.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Wendy_GlideRight", TEXT("Monster/Wendy/Animation/BOSS_020_Ani_GlideRight.sqc"), MESH_PATH);

		m_pScene->GetResource()->LoadAnimationSequence("Wendy_AirShoot", TEXT("Monster/Wendy/Animation/Boss_020_Ani_Attack_Blast01.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Wendy_AirHole", TEXT("Monster/Wendy/Animation/Boss_020_Ani_Attack_Blast02.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Wendy_Brandish_1", TEXT("Monster/Wendy/Animation/Boss_020_Ani_Attack_Shoot01.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Wendy_LongAttack", TEXT("Monster/Wendy/Animation/Boss_020_Ani_Attack_Shoot02.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Wendy_Brandish", TEXT("Monster/Wendy/Animation/Boss_020_Ani_Attack01.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Wendy_Born", TEXT("Monster/Wendy/Animation/Boss_020_Ani_Born.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Boss_020_Ani_Born", TEXT("Monster/Wendy/Animation/Boss_020_Ani_Born.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Wendy_Storm", TEXT("Monster/Wendy/Animation/Boss_020_Ani_Born.sqc"), MESH_PATH);

		m_pScene->GetResource()->LoadAnimationSequence("Wendy_Die", TEXT("Monster/Wendy/Animation/Boss_020_Ani_Die.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Wendy_StunEnd", TEXT("Monster/Wendy/Animation/Boss_020_Ani_HeavyHit_End.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("Wendy_StunStart", TEXT("Monster/Wendy/Animation/Boss_020_Ani_HeavyHit_Start.sqc"), MESH_PATH);

		m_pScene->GetResource()->LoadAnimationSequence("1", TEXT("Monster/Wendy/Animation/Boss_020_Ani_ActivateRampage.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("4", TEXT("Monster/Wendy/Animation/Boss_020_Ani_Attack_Blast03.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("5", TEXT("Monster/Wendy/Animation/Boss_020_Ani_Attack_ForceRecover.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("6", TEXT("Monster/Wendy/Animation/Boss_020_Ani_Attack_Recover.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("9", TEXT("Monster/Wendy/Animation/Boss_020_Ani_Attack_Shoot03.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("10", TEXT("Monster/Wendy/Animation/Boss_020_Ani_Attack_Shoot04.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("11", TEXT("Monster/Wendy/Animation/Boss_020_Ani_Attack_Shoot05.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("12", TEXT("Monster/Wendy/Animation/Boss_020_Ani_Attack_Shoot05_Start.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("13", TEXT("Monster/Wendy/Animation/Boss_020_Ani_Attack_Storm.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("16", TEXT("Monster/Wendy/Animation/Boss_020_Ani_CollapseRampage.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("23", TEXT("Monster/Wendy/Animation/Boss_020_Ani_Hit_H.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("24", TEXT("Monster/Wendy/Animation/Boss_020_Ani_Hit_L.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("25", TEXT("Monster/Wendy/Animation/Boss_020_Ani_Rampage.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("29", TEXT("Monster/Wendy/Animation/Boss_020_Ani_Vanish.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("30", TEXT("Monster/Wendy/Animation/Boss_020_Ani_Weak_End.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("31", TEXT("Monster/Wendy/Animation/Boss_020_Ani_Weak_Loop.sqc"), MESH_PATH);
		m_pScene->GetResource()->LoadAnimationSequence("32", TEXT("Monster/Wendy/Animation/Boss_020_Ani_Weak_Start.sqc"), MESH_PATH);



		m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "WendyAirShootMesh", "Monster/Wendy/AttackFBX/Wendy_AirShoot.msh");
		m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "AirStarMesh", "Monster/Wendy/AttackFBX/AirStar.msh");
		m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "AirBullet", "Monster/Wendy/AttackFBX/AirBullet.msh");
		m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "Tornado_001", "Effect/Tornado/Tornado_001.msh");
		m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "Tornado_002", "Effect/Tornado/Tornado_002.msh");
		m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "Tornado_003", "Effect/Tornado/Tornado_003.msh");
		m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "Tornado_004", "Effect/Tornado/Tornado_004.msh");
		m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "Tornado_005", "Effect/Tornado/Tornado_005.msh");
		m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "Tornado_006", "Effect/Tornado/Tornado_006.msh");
		m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "Tornado_007", "Effect/Tornado/Tornado_007.msh");
		CMesh* pMesh1 = m_pScene->GetResource()->FindMesh("AirBullet");
		pMesh1->AllLightMaterialReset();
		CMesh* pMesh2 = m_pScene->GetResource()->FindMesh("AirStarMesh");
		pMesh2->AllLightMaterialReset();
	}
	if (m_LoadThread)
		m_LoadThread->SetLoadingCount(10);
#pragma endregion
}

bool CStageManager::CreateMaterial()
{
	{
		m_pScene->GetResource()->CreateMaterial("MainLandScape");

		CMaterial* Mtrl = m_pScene->GetResource()->FindMaterial("MainLandScape");

		Mtrl->AddTexture("MainLandScapeDefault", TEXT("LandScape/Terrain_Pebbles_01.dds"));
		Mtrl->SetTextureLink("MainLandScapeDefault", Texture_Link::BaseTexture);

		Mtrl->AddTexture("MainLandScapeDefaultNormal", TEXT("LandScape/Terrain_Pebbles_01_NRM.bmp"));
		Mtrl->SetTextureLink("MainLandScapeDefaultNormal", Texture_Link::NormalTexture);

		Mtrl->AddTexture("MainLandScapeDefaultSpecular", TEXT("LandScape/Terrain_Pebbles_01_SPEC.bmp"));
		Mtrl->SetTextureLink("MainLandScapeDefaultSpecular", Texture_Link::SpecularTexture);

		std::vector<const TCHAR*>	vecAlbedo;
		std::vector<const TCHAR*>	vecNormal;
		std::vector<const TCHAR*>	vecSpecular;
		std::vector<const TCHAR*>	vecAlpha;

		TCHAR* FileName = new TCHAR[MAX_PATH];
		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);
		lstrcpy(FileName, TEXT("LandScape/BD_Terrain_Cliff05.dds"));
		vecAlbedo.push_back(FileName);

		FileName = new TCHAR[MAX_PATH];
		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);
		lstrcpy(FileName, TEXT("LandScape/BD_Terrain_Cave_01.dds"));
		vecAlbedo.push_back(FileName);

		FileName = new TCHAR[MAX_PATH];
		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);
		lstrcpy(FileName, TEXT("LandScape/ROCK_01+MOSS_COLOR.png"));
		vecAlbedo.push_back(FileName);

		FileName = new TCHAR[MAX_PATH];
		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);
		lstrcpy(FileName, TEXT("LandScape/Terrain_Cliff_15_Large.dds"));
		vecAlbedo.push_back(FileName);

		Mtrl->AddTextureArray("MainLandScapeAlbedo", vecAlbedo);
		Mtrl->SetTextureLink("MainLandScapeAlbedo", Texture_Link::CustomTexture);
		Mtrl->SetTextureRegister("MainLandScapeAlbedo", 30);

		FileName = new TCHAR[MAX_PATH];
		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);
		lstrcpy(FileName, TEXT("LandScape/BD_Terrain_Cliff05_NRM.bmp"));
		vecNormal.push_back(FileName);

		FileName = new TCHAR[MAX_PATH];
		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);
		lstrcpy(FileName, TEXT("LandScape/BD_Terrain_Cave_01_NRM.bmp"));
		vecNormal.push_back(FileName);

		FileName = new TCHAR[MAX_PATH];
		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);
		lstrcpy(FileName, TEXT("LandScape/ROCK_01+MOSS_NRM.png"));
		vecNormal.push_back(FileName);

		FileName = new TCHAR[MAX_PATH];
		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);
		lstrcpy(FileName, TEXT("LandScape/Terrain_Cliff_15_Large_NRM.bmp"));
		vecNormal.push_back(FileName);

		Mtrl->AddTextureArray("MainLandScapeNormal", vecNormal);
		Mtrl->SetTextureLink("MainLandScapeNormal", Texture_Link::CustomTexture);
		Mtrl->SetTextureRegister("MainLandScapeNormal", 31);

		FileName = new TCHAR[MAX_PATH];
		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);
		lstrcpy(FileName, TEXT("LandScape/BD_Terrain_Cliff05_SPEC.bmp"));
		vecSpecular.push_back(FileName);

		FileName = new TCHAR[MAX_PATH];
		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);
		lstrcpy(FileName, TEXT("LandScape/BD_Terrain_Cave_01_SPEC.bmp"));
		vecSpecular.push_back(FileName);

		FileName = new TCHAR[MAX_PATH];
		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);
		lstrcpy(FileName, TEXT("LandScape/ROCK_01+MOSS_SPEC.png"));
		vecSpecular.push_back(FileName);

		FileName = new TCHAR[MAX_PATH];
		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);
		lstrcpy(FileName, TEXT("LandScape/Terrain_Cliff_15_Large_SPEC.bmp"));
		vecSpecular.push_back(FileName);

		Mtrl->AddTextureArray("MainLandScapeSpecular", vecSpecular);
		Mtrl->SetTextureLink("MainLandScapeSpecular", Texture_Link::CustomTexture);
		Mtrl->SetTextureRegister("MainLandScapeSpecular", 32);

		FileName = new TCHAR[MAX_PATH];
		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);
		lstrcpy(FileName, TEXT("LandScape/RoadAlpha.bmp"));
		vecAlpha.push_back(FileName);

		FileName = new TCHAR[MAX_PATH];
		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);
		lstrcpy(FileName, TEXT("LandScape/SandBaseAlpha.bmp"));
		vecAlpha.push_back(FileName);

		FileName = new TCHAR[MAX_PATH];
		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);
		lstrcpy(FileName, TEXT("LandScape/WaterBaseAlpha.bmp"));
		vecAlpha.push_back(FileName);

		FileName = new TCHAR[MAX_PATH];
		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);
		lstrcpy(FileName, TEXT("LandScape/StonAlpha.bmp"));
		vecAlpha.push_back(FileName);

		Mtrl->AddTextureArray("MainLandScapeAlpha", vecAlpha);
		Mtrl->SetTextureLink("MainLandScapeAlpha", Texture_Link::CustomTexture);
		Mtrl->SetTextureRegister("MainLandScapeAlpha", 33);


		Mtrl->SetSpecularPower(2.f);
		Mtrl->SetAmbientColor(1.f, 1.f, 1.f, 1.f);

		Mtrl->SetShader("LandScapeShader");

		size_t	Size = vecAlbedo.size();

		for (size_t i = 0; i < Size; ++i)
		{
			SAFE_DELETE_ARRAY(vecAlbedo[i]);
			SAFE_DELETE_ARRAY(vecNormal[i]);
			SAFE_DELETE_ARRAY(vecSpecular[i]);
			SAFE_DELETE_ARRAY(vecAlpha[i]);
		}
	}

	// Monster
	{
		// SniperBullet
		{
			m_pScene->GetResource()->CreateMaterial("SniperBullet");
			CMaterial* Mtrl = m_pScene->GetResource()->FindMaterial("SniperBullet");

			Mtrl->AddTexture("SniperBulletTexture", TEXT("DefaultPaperBurn1.png"));
			Mtrl->SetTextureLink("SniperBulletTexture", Texture_Link::BaseTexture);
		}
		// Wendy_AirShootMaterial
		{
			m_pScene->GetResource()->CreateMaterial("Wendy_AirShootMaterial");
			CMaterial* Mtrl = m_pScene->GetResource()->FindMaterial("Wendy_AirShootMaterial");

			Mtrl->AddTexture("Wendy_AirShootTexture", TEXT("Monster/Wendy_AirShoot.png"));
			Mtrl->SetTextureLink("Wendy_AirShootTexture", Texture_Link::BaseTexture);
		}
		// Wendy_Brandish
		{
			m_pScene->GetResource()->CreateMaterial("Wendy_Brandish");
			CMaterial* Mtrl = m_pScene->GetResource()->FindMaterial("Wendy_Brandish");

			Mtrl->AddTexture("Wendy_BrandishTexture", TEXT("Monster/wing Gas.png"));
			Mtrl->SetTextureLink("Wendy_BrandishTexture", Texture_Link::BaseTexture);
			Mtrl->SetShader("BillboardShader");
		}
		// Wendy_Brandish
		{
			m_pScene->GetResource()->CreateMaterial("Axe_RAttack");
			CMaterial* Mtrl = m_pScene->GetResource()->FindMaterial("Axe_RAttack");

			Mtrl->AddTexture("Axe_RAttackTexture", TEXT("Monster/wing Gas_B.png"));
			Mtrl->SetTextureLink("Axe_RAttackTexture", Texture_Link::BaseTexture);
			Mtrl->SetShader("BillboardShader");
		}
		// BlackCircle
		{
			m_pScene->GetResource()->CreateMaterial("BlackCircle");
			CMaterial* Mtrl = m_pScene->GetResource()->FindMaterial("BlackCircle");

			Mtrl->AddTexture("BlackCircleTexture", TEXT("Monster/Decal/Black Circle.png"));
			Mtrl->SetTextureLink("BlackCircleTexture", Texture_Link::BaseTexture);
		}
		// BlackSmoke
		{
			m_pScene->GetResource()->CreateMaterial("BlackSmoke");
			CMaterial* Mtrl = m_pScene->GetResource()->FindMaterial("BlackSmoke");

			Mtrl->AddTexture("BlackSmokeTexture", TEXT("Monster/Effect/fx_snowfield_fog03_2.png"));
			Mtrl->SetTextureLink("BlackSmokeTexture", Texture_Link::BaseTexture);
			Mtrl->DistortionEnable(true);
		}
		// AirStarTrail
		{
			m_pScene->GetResource()->CreateMaterial("AirStarTrail_G");
			CMaterial* Mtrl1 = m_pScene->GetResource()->FindMaterial("AirStarTrail_G");

			Mtrl1->AddTexture("AirStarTrail_GTexture", TEXT("Monster/Wendy_AirShoot.png"));
			Mtrl1->SetTextureLink("AirStarTrail_GTexture", Texture_Link::BaseTexture);
			Mtrl1->DistortionEnable(true);
			Mtrl1->SetShader("TrailShader");

			m_pScene->GetResource()->CreateMaterial("AirStarTrail_W");
			CMaterial* Mtrl = m_pScene->GetResource()->FindMaterial("AirStarTrail_W");

			Mtrl->AddTexture("AirStarTrail_WTexture", TEXT("Monster/Wendy_AirShoot_W.png"));
			Mtrl->SetTextureLink("AirStarTrail_WTexture", Texture_Link::BaseTexture);
			Mtrl->DistortionEnable(true);
			Mtrl->SetShader("TrailShader");
		}
		// Tornado
		{
			{
				m_pScene->GetResource()->CreateMaterial("Tornado");
				CMaterial* Mtrl = m_pScene->GetResource()->FindMaterial("Tornado");

				Mtrl->AddTexture("TornadoTexture", TEXT("Monster/Tornado/Tornado_1.png"));
				Mtrl->SetTextureLink("TornadoTexture", Texture_Link::BaseTexture);
			}

			{
				m_pScene->GetResource()->CreateMaterial("Tornado_00");
				CMaterial* Mtrl = m_pScene->GetResource()->FindMaterial("Tornado_00");

				Mtrl->AddTexture("Tornado00Texture", TEXT("Monster/Effect/CircleRing_01.png"));
				Mtrl->SetTextureLink("Tornado01Texture", Texture_Link::BaseTexture);

				Mtrl->SetShader("BillboardShader");
			}
			{
				m_pScene->GetResource()->CreateMaterial("Tornado_01");
				CMaterial* Mtrl = m_pScene->GetResource()->FindMaterial("Tornado_01");

				Mtrl->AddTexture("Tornado01Texture", TEXT("Monster/Effect/Slash_01.png"));
				Mtrl->SetTextureLink("Tornado01Texture", Texture_Link::BaseTexture);

				Mtrl->SetShader("BillboardShader");
			}
			{
				m_pScene->GetResource()->CreateMaterial("Tornado_02");
				CMaterial* Mtrl = m_pScene->GetResource()->FindMaterial("Tornado_02");

				Mtrl->AddTexture("Tornado02Texture", TEXT("Monster/Effect/Swirl_1.png"));
				Mtrl->SetTextureLink("Tornado02Texture", Texture_Link::BaseTexture);

				Mtrl->SetShader("BillboardShader");
			}
			{
				m_pScene->GetResource()->CreateMaterial("Tornado_03");
				CMaterial* Mtrl = m_pScene->GetResource()->FindMaterial("Tornado_03");

				Mtrl->AddTexture("Tornado03Texture", TEXT("Monster/Effect/mangci5-new.png"));
				Mtrl->SetTextureLink("Tornado03Texture", Texture_Link::BaseTexture);

				Mtrl->SetShader("BillboardShader");
			}
		}
		//AirHole
		{
			{
				m_pScene->GetResource()->CreateMaterial("AirHole_Wind");
				CMaterial* Mtrl = m_pScene->GetResource()->FindMaterial("AirHole_Wind");

				Mtrl->AddTexture("AirHole_Wind", TEXT("Monster/Decal/Windcir_01.png"));
				Mtrl->SetTextureLink("AirHole_Wind", Texture_Link::BaseTexture);
				Mtrl->DistortionEnable(true);
			}
			{
				m_pScene->GetResource()->CreateMaterial("AirHole_Wind_Black");
				CMaterial* Mtrl = m_pScene->GetResource()->FindMaterial("AirHole_Wind_Black");

				Mtrl->AddTexture("AirHole_Wind_BlackTexture", TEXT("Monster/Decal/Windcir_01_Black.png"));
				Mtrl->SetTextureLink("AirHole_Wind_BlackTexture", Texture_Link::BaseTexture);
				Mtrl->DistortionEnable(true);
			}

			{
				m_pScene->GetResource()->CreateMaterial("AirHole_Circle_1");
				CMaterial* Mtrl = m_pScene->GetResource()->FindMaterial("AirHole_Circle_1");

				Mtrl->AddTexture("AirHole_Circle_1", TEXT("Monster/Effect/Swirl_1.png"));
				Mtrl->SetTextureLink("AirHole_Circle_1", Texture_Link::BaseTexture);
				Mtrl->DistortionEnable(true);
			}
			{
				m_pScene->GetResource()->CreateMaterial("AirHole_Circle_2");
				CMaterial* Mtrl = m_pScene->GetResource()->FindMaterial("AirHole_Circle_2");

				Mtrl->AddTexture("AirHole_Circle_2", TEXT("Monster/Effect/mangci5-new.png"));
				Mtrl->SetTextureLink("AirHole_Circle_2", Texture_Link::BaseTexture);
				Mtrl->DistortionEnable(true);
			}
		}
	}

	{}
	{
		{
			m_pScene->GetResource()->CreateMaterial("LobbyValkyrieSelectZoneBG");
			CMaterial* Mtrl = m_pScene->GetResource()->FindMaterial("LobbyValkyrieSelectZoneBG");
			Mtrl->AddTexture("BgPicSchool07", TEXT("UI/Character Select/BgPicSchool07.png"));
			Mtrl->SetTextureLink("BgPicSchool07", Texture_Link::BaseTexture);
			Mtrl->SetShader("BillboardShader");
		}
		{
			m_pScene->GetResource()->CreateMaterial("KianaFire");
			CMaterial* Mtrl = m_pScene->GetResource()->FindMaterial("KianaFire");
			Mtrl->SetShader("BillboardShader");
		}
		{
			m_pScene->GetResource()->CreateMaterial("PlayerHitEffect");
			CMaterial* Mtrl = m_pScene->GetResource()->FindMaterial("PlayerHitEffect");
			Mtrl->SetShader("BillboardShader");
		}
		{
			m_pScene->GetResource()->CreateMaterial("KianaFire");
			CMaterial* Mtrl = m_pScene->GetResource()->FindMaterial("KianaFire");
			Mtrl->AddTexture("Blast_3", TEXT("Effect/Blast_3.png"));
			Mtrl->SetTextureLink("Blast_3", Texture_Link::BaseTexture);
			Mtrl->SetShader("BillboardShader");
		}
		{
			m_pScene->GetResource()->CreateMaterial("LobbyBackGround");
			CMaterial* Mtrl = m_pScene->GetResource()->FindMaterial("LobbyBackGround");
			Mtrl->SetShader("BillboardShader");

			Mtrl->AddTexture("LobbyBackGround", TEXT("Scene/LobbyScene/Background_01/Background_01.tga"), "MeshPath");
			Mtrl->SetTextureLink("LobbyBackGround", Texture_Link::BaseTexture);
			Mtrl->SetShader("BillboardShader");
		}
		{
			m_pScene->GetResource()->CreateMaterial("SakuraTrail");
			CMaterial* Mtrl = m_pScene->GetResource()->FindMaterial("SakuraTrail");
			Mtrl->SetOpacity(1.f);

			Mtrl->SetTransparency(true, true);
			Mtrl->AddTexture("AlphaTrail", TEXT("Effect/AlphaTrail.png"));
			Mtrl->SetTextureLink("AlphaTrail", Texture_Link::BaseTexture);
			Mtrl->DistortionEnable(true);
			Mtrl->SetShader("TrailShader");
		}
		{
			m_pScene->GetResource()->CreateMaterial("SakuraChargeTrail");
			CMaterial* Mtrl = m_pScene->GetResource()->FindMaterial("SakuraChargeTrail");
			Mtrl->SetOpacity(1.f);

			Mtrl->SetTransparency(true, true);
			Mtrl->AddTexture("Mei_Dodge_Line_3", TEXT("Effect/Mei_Dodge_Line_3.png"));
			Mtrl->SetTextureLink("Mei_Dodge_Line_3", Texture_Link::BaseTexture);
			Mtrl->DistortionEnable(true);
			Mtrl->SetShader("TrailShader");
		}
		{
			m_pScene->GetResource()->CreateMaterial("TornadoTrail");
			CMaterial* Mtrl = m_pScene->GetResource()->FindMaterial("TornadoTrail");
			Mtrl->SetOpacity(0.5f);
			Mtrl->SetTransparency(true, true);
			Mtrl->AddTexture("Tornado_1", TEXT("Effect/Tornado_1.png"));
			Mtrl->SetTextureLink("Tornado_1", Texture_Link::BaseTexture);
			Mtrl->SetShader("TrailShader");
		}
		{
			m_pScene->GetResource()->CreateMaterial("BillboardTarget");
			CMaterial* Mtrl = m_pScene->GetResource()->FindMaterial("BillboardTarget");
			Mtrl->AddTexture("B2785713", TEXT("UI/In Game/B2785713.png"));
			Mtrl->SetTextureLink("B2785713", Texture_Link::BaseTexture);
			Mtrl->SetShader("BillboardShader");
		}
		{
			m_pScene->GetResource()->CreateMaterial("CurrentMark");
			CMaterial* Mtrl = m_pScene->GetResource()->FindMaterial("CurrentMark");
			Mtrl->AddTexture("CurrentMark", TEXT("UI/In Game/CurrentMark.png"));
			Mtrl->SetTextureLink("CurrentMark", Texture_Link::BaseTexture);
			Mtrl->SetShader("BillboardShader");
		}

	}


	CreateParticle();
	return true;
}

bool CStageManager::CreateSound()
{
	CResourceManager::GetInst()->CreateSoundChannelGroup("BGM");
	CResourceManager::GetInst()->CreateSoundChannelGroup("UISound");
	CResourceManager::GetInst()->CreateSoundChannelGroup("Effect");
	CResourceManager::GetInst()->CreateSoundChannelGroup("PlayerEffect");
	CResourceManager::GetInst()->CreateSoundChannelGroup("Player");
	CResourceManager::GetInst()->CreateSoundChannelGroup("PlayerCV");
	CResourceManager::GetInst()->CreateSoundChannelGroup("PlayerNotStop");
	CResourceManager::GetInst()->CreateSoundChannelGroup("Sniper");
	CResourceManager::GetInst()->CreateSoundChannelGroup("Axe");
	CResourceManager::GetInst()->CreateSoundChannelGroup("Wendy");

	CResourceManager::GetInst()->FindSoundChannelGroup("BGM")->setVolume(0.3f);
	CResourceManager::GetInst()->FindSoundChannelGroup("PlayerCV")->setVolume(1.5f);
	CResourceManager::GetInst()->FindSoundChannelGroup("PlayerEffect")->setVolume(0.7f);
	CResourceManager::GetInst()->FindSoundChannelGroup("UISound")->setVolume(0.5f);
#pragma region BGM

	m_pScene->GetResource()->LoadSound("BGM", true, "Stage1BG", "BG/Stage1BG.mp3");
	m_pScene->GetResource()->LoadSound("BGM", true, "Stage2BG", "BG/Stage2BG.mp3");
	m_pScene->GetResource()->LoadSound("BGM", true, "LobbyBG", "BG/LobbyBG.mp3");
	m_pScene->GetResource()->LoadSound("BGM", true, "StageSelectBG", "BG/StageSelectBG.mp3");
	m_pScene->GetResource()->LoadSound("BGM", false, "StageClear", "BG/StageClear.mp3");
	m_pScene->GetResource()->LoadSound("BGM", true, "StageFail", "BG/StageFail.mp3");
	m_pScene->GetResource()->LoadSound("BGM", true, "ShopBG", "BG/ShopBG.mp3");
	m_BGMSound.push_back(m_pScene->GetResource()->FindSound2D("Stage1BG"));
	m_BGMSound.push_back(m_pScene->GetResource()->FindSound2D("Stage2BG"));
	m_BGMSound.push_back(m_pScene->GetResource()->FindSound2D("LobbyBG"));
	m_BGMSound.push_back(m_pScene->GetResource()->FindSound2D("StageSelectBG"));
	m_BGMSound.push_back(m_pScene->GetResource()->FindSound2D("StageClear"));
	m_BGMSound.push_back(m_pScene->GetResource()->FindSound2D("StageFail"));
	m_BGMSound.push_back(m_pScene->GetResource()->FindSound2D("ShopBG"));

	m_pScene->GetResource()->LoadSound("BGM", false, "LoadingSound0", "LoadingSound0.wav");
	m_pScene->GetResource()->LoadSound("BGM", true, "LoadingSound1", "LoadingSound1.wav");
	m_pScene->GetResource()->LoadSound("BGM", false, "LoadingSound2_GoShip", "LoadingSound2_GoShip.wav");
	m_pScene->GetResource()->LoadSound("BGM", false, "LoadingSound3_OpenDoor", "LoadingSound3_OpenDoor.wav");
	m_pScene->GetResource()->LoadSound("BGM", false, "LoadingSound4_Captain", "LoadingSound4_Captain.wav");
#pragma region UISOund

	m_pScene->GetResource()->LoadSound("UISound", false, "ButtonClick", "UI/ButtonClick.wav");
	m_pScene->GetResource()->LoadSound("UISound", false, "PopUpIn", "UI/PopUpIn.wav");
	m_pScene->GetResource()->LoadSound("UISound", false, "PopUpOut", "UI/PopUpOut.wav");
	m_pScene->GetResource()->LoadSound("UISound", false, "ShopResult", "UI/ShopResult.wav");
	m_pScene->GetResource()->LoadSound("UISound", false, "Upgrade", "UI/Upgrade.wav");
#pragma endregion

#pragma region Effect
	m_pScene->GetResource()->LoadSound("Effect", false, "Warning_Loop", "Effect/Warning_Loop.wav");
	m_pScene->GetResource()->LoadSound("Effect", false, "PerpectEvade", "Effect/PerpectEvade.wav");

#pragma endregion

#pragma endregion

#pragma region Monster

#pragma region SniperSound
	{
		m_pScene->GetResource()->LoadSound("Sniper", false, "HumanStep_1", "Monster/NormalMonster/Step_Sound_1.mp3");
		m_pScene->GetResource()->LoadSound("Sniper", false, "HumanStep_2", "Monster/NormalMonster/Step_Sound_2.mp3");
		m_pScene->GetResource()->LoadSound("Sniper", false, "HumanStep_3", "Monster/NormalMonster/Step_Sound_3.mp3");
		m_pScene->GetResource()->LoadSound("Sniper", false, "HumanStep_4", "Monster/NormalMonster/Step_Sound_4.mp3");



		m_pScene->GetResource()->LoadSound("Sniper", false, "Sniper_GunShoot", "Monster/NormalMonster/GunShoot_Sound.mp3");
		m_pScene->GetResource()->LoadSound("Sniper", false, "Sniper_GunHit", "Monster/NormalMonster/SniperBilletHit.mp3");
		m_pScene->GetResource()->LoadSound("Sniper", false, "Sniper_GunSet", "Monster/NormalMonster/GunSet_Sound.mp3");
		m_pScene->GetResource()->LoadSound("Sniper", false, "Sniper_RAttack", "Monster/NormalMonster/SniperRAttack.mp3");
		m_pScene->GetResource()->LoadSound("Sniper", false, "Sniper_JumpBack", "Monster/NormalMonster/JumpBack_Sound.mp3");
		m_pScene->GetResource()->LoadSound("Sniper", false, "Sniper_SetGrenade", "Monster/NormalMonster/SetGrenade_Sound.mp3");
		m_pScene->GetResource()->LoadSound("Sniper", false, "Sniper_ShootGrenade", "Monster/NormalMonster/ShootGrenade_Sound.mp3");
		m_pScene->GetResource()->LoadSound("Sniper", false, "Sniper_GrenadeBoom", "Monster/NormalMonster/SniperBoom.mp3");
		m_pScene->GetResource()->LoadSound("Sniper", false, "Sniper_GrenadeBoom2", "Monster/NormalMonster/SniperBoom2.mp3");
		m_pScene->GetResource()->LoadSound("Sniper", false, "Sniper_GrenadeBoom3", "Monster/NormalMonster/SniperBoom3.mp3");
		m_pScene->GetResource()->LoadSound("Sniper", false, "Sniper_JumpTurn", "Monster/NormalMonster/JumpTurn_Sound.mp3");
		m_pScene->GetResource()->FindSoundChannelGroup("Sniper")->setVolume(1.f);
	}
#pragma endregion
#pragma region AxeSoldierSound
	{
		m_pScene->GetResource()->LoadSound("Axe", false, "Axe_HumanStep_1", "Monster/NormalMonster/Step_Sound_1.mp3");
		m_pScene->GetResource()->LoadSound("Axe", false, "Axe_HumanStep_2", "Monster/NormalMonster/Step_Sound_2.mp3");
		m_pScene->GetResource()->LoadSound("Axe", false, "Axe_HumanStep_3", "Monster/NormalMonster/Step_Sound_3.mp3");
		m_pScene->GetResource()->LoadSound("Axe", false, "Axe_HumanStep_4", "Monster/NormalMonster/Step_Sound_4.mp3");
		m_pScene->GetResource()->LoadSound("Axe", false, "Axe_HumanStep_1_Short", "Monster/NormalMonster/Step_Sound_1_Short.mp3");

		m_pScene->GetResource()->LoadSound("Axe", false, "AxeAttack_0", "Monster/NormalMonster/AxeAttack_Sound_0.mp3");
		m_pScene->GetResource()->LoadSound("Axe", false, "AxeAttack_1", "Monster/NormalMonster/AxeAttack_Sound_1.mp3");
		m_pScene->GetResource()->LoadSound("Axe", false, "AxeAttack_2", "Monster/NormalMonster/AxeAttack_Sound_2.mp3");
		m_pScene->GetResource()->LoadSound("Axe", false, "AxeAttack_3", "Monster/NormalMonster/AxeAttack_Sound_3.mp3");
		m_pScene->GetResource()->LoadSound("Axe", false, "AxeAttack_4", "Monster/NormalMonster/AxeAttack_Sound_4.mp3");

		m_pScene->GetResource()->LoadSound("Axe", false, "Axe_Dash_1", "Monster/NormalMonster/AxeDash_Sound_1.mp3");
		m_pScene->GetResource()->LoadSound("Axe", false, "Axe_Dash_2", "Monster/NormalMonster/AxeDash_Sound_2.mp3");
		//m_pScene->GetResource()->LoadSound("Sniper", false, "Sniper_GunHit", "Monster/NormalMonster/GunHit_Sound.mp3");
		//m_pScene->GetResource()->LoadSound("Sniper", false, "Sniper_GunSet", "Monster/NormalMonster/GunSet_Sound.mp3");
		//m_pScene->GetResource()->LoadSound("Sniper", false, "Sniper_RAttack", "Monster/NormalMonster/SniperRAttack.mp3");
		//m_pScene->GetResource()->LoadSound("Sniper", false, "Sniper_JumpBack", "Monster/NormalMonster/JumpBack_Sound.mp3");
		//m_pScene->GetResource()->LoadSound("Sniper", false, "Sniper_SetGrenade", "Monster/NormalMonster/SetGrenade_Sound.mp3");
		//m_pScene->GetResource()->LoadSound("Sniper", false, "Sniper_ShootGrenade", "Monster/NormalMonster/ShootGrenade_Sound.mp3");
		//m_pScene->GetResource()->LoadSound("Sniper", false, "Sniper_JumpTurn", "Monster/NormalMonster/JumpTurn_Sound.mp3");
		m_pScene->GetResource()->FindSoundChannelGroup("Axe")->setVolume(1.f);
	}
#pragma endregion
#pragma region Wendy
	{
		m_pScene->GetResource()->LoadSound("Wendy", false, "Wendy_Born", "Monster/Wendy/Wendy_Born.mp3");
		m_pScene->GetResource()->LoadSound("Wendy", false, "Wendy_AirHole", "Monster/Wendy/Wendy_AirHole.mp3");
		m_pScene->GetResource()->LoadSound("Wendy", false, "Wendy_AirShoot", "Monster/Wendy/Wendy_AirShoot.mp3");
		m_pScene->GetResource()->LoadSound("Wendy", false, "Wendy_AirShoot_Boom", "Monster/Wendy/Wendy_AirShoot_Boom.mp3");
		m_pScene->GetResource()->LoadSound("Wendy", false, "Wendy_Trun", "Monster/Wendy/Wendy_Trun.mp3");
		m_pScene->GetResource()->LoadSound("Wendy", false, "Wendy_Brandish_1", "Monster/Wendy/Wendy_Brandish_1.mp3");
		m_pScene->GetResource()->LoadSound("Wendy", false, "Wendy_Brandish_2", "Monster/Wendy/Wendy_Brandish_2.mp3");
		m_pScene->GetResource()->LoadSound("Wendy", false, "Wendy_Brandish_Start", "Monster/Wendy/Wendy_Brandish_Start.mp3");
		m_pScene->GetResource()->LoadSound("Wendy", false, "Wendy_Brandish_Hit", "Monster/Wendy/Wendy_BrandishHit.mp3");

		m_pScene->GetResource()->LoadSound("Wendy", false, "AirStarBorn", "Monster/Wendy/AirStarBorn.mp3");
		m_pScene->GetResource()->LoadSound("Wendy", false, "AirStarShoot", "Monster/Wendy/AirStarShoot.mp3");
		m_pScene->GetResource()->LoadSound("Wendy", false, "AirStarBoom", "Monster/Wendy/AirStarBoom.mp3");

		m_pScene->GetResource()->LoadSound("Wendy", false, "Wendy_Glide_1", "Monster/Wendy/Wendy_Glide_1.mp3");
		m_pScene->GetResource()->LoadSound("Wendy", false, "Wendy_Glide_2", "Monster/Wendy/Wendy_Glide_2.mp3");

		m_pScene->GetResource()->LoadSound("Wendy", false, "Wendy_BulletShoot", "Monster/Wendy/AirBulletShoot.mp3");
		m_pScene->GetResource()->LoadSound("Wendy", false, "Wendy_AirBoom", "Monster/Wendy/Wendy_AirBoom.mp3");
		m_pScene->GetResource()->LoadSound("Wendy", false, "Wendy_AirHit", "Monster/Wendy/AirHit.mp3");
		m_pScene->GetResource()->LoadSound("Wendy", false, "Wendy_Tornado", "Monster/Wendy/Wendy_Tornado.mp3");


		m_pScene->GetResource()->FindSoundChannelGroup("Wendy")->setVolume(1.f);
	}
#pragma endregion
#pragma endregion

#pragma region PlayerShare
	m_pScene->GetResource()->LoadSound("PlayerEffect", false, "PlayerRunSound", "Player/PlayerRunSound.wav");


#pragma endregion
	m_pScene->GetResource()->LoadSound("PlayerEffect", false, "SakuraAttackHit", "Player/SakuraAttackHit.wav");
	m_pScene->GetResource()->LoadSound("Player", false, "AppearEffectSound", "Player/AppearEffectSound.mp3");
#pragma region SakuraSound
	m_pScene->GetResource()->LoadSound("Player", false, "SakuraAttackCombo1", "Player/Sakura/SakuraAttackCombo1.mp3");

	m_pScene->GetResource()->LoadSound("Player", false, "SakuraAttackCombo2", "Player/Sakura/SakuraAttackCombo2.mp3");
	m_pScene->GetResource()->LoadSound("Player", false, "SakuraAttackCombo3", "Player/Sakura/SakuraAttackCombo3.mp3");
	m_pScene->GetResource()->LoadSound("Player", false, "SakuraAttackCombo4", "Player/Sakura/SakuraAttackCombo4.mp3");
	m_pScene->GetResource()->LoadSound("PlayerNotStop", false, "SakuraAttackCombo5", "Player/Sakura/SakuraAttackCombo5.mp3");

	m_pScene->GetResource()->LoadSound("PlayerCV", false, "SakuraAttackCV1", "Player/Sakura/SakuraAttackCV1.mp3");
	m_pScene->GetResource()->LoadSound("PlayerCV", false, "SakuraAttackCV2", "Player/Sakura/SakuraAttackCV2.mp3");
	m_pScene->GetResource()->LoadSound("PlayerCV", false, "SakuraAttackCV3", "Player/Sakura/SakuraAttackCV3.mp3");
	m_pScene->GetResource()->LoadSound("PlayerCV", false, "SakuraAttackCV4", "Player/Sakura/SakuraAttackCV4.mp3");
	m_pScene->GetResource()->LoadSound("PlayerCV", false, "SakuraAttackCV5", "Player/Sakura/SakuraAttackCV5.mp3");
	m_pScene->GetResource()->LoadSound("PlayerCV", false, "SakuraAttackCV6", "Player/Sakura/SakuraAttackCV6.mp3");

	m_pScene->GetResource()->LoadSound("Player", false, "SakuraCombatToIdle", "Player/Sakura/SakuraCombatToIdle.mp3");
	m_pScene->GetResource()->LoadSound("Player", false, "SakuraUltraSkill", "Player/Sakura/SakuraUltraSkill.wav");
	m_pScene->GetResource()->LoadSound("PlayerCV", false, "SakuraUltraSkillCV", "Player/Sakura/SakuraUltraSkillCV.mp3");
	m_pScene->GetResource()->LoadSound("Player", false, "SakuraEvade", "Player/Sakura/SakuraEvade.mp3");
	m_pScene->GetResource()->LoadSound("PlayerNotStop", false, "SakuraAppearCV", "Player/Sakura/SakuraAppearCV.mp3");
#pragma endregion

#pragma region KianaSound

	m_pScene->GetResource()->LoadSound("PlayerEffect", false, "KianaAttackHit", "Player/KianaAttackHit.wav");
	m_pScene->GetResource()->LoadSound("Player", false, "KianaAttack1", "Player/Kiana/KianaAttack1.mp3");
	m_pScene->GetResource()->LoadSound("Player", false, "KianaAttack2", "Player/Kiana/KianaAttack2.mp3");
	m_pScene->GetResource()->LoadSound("Player", false, "KianaAttack3", "Player/Kiana/KianaAttack3.mp3");
	m_pScene->GetResource()->LoadSound("PlayerNotStop", false, "KianaAttack4_1", "Player/Kiana/KianaAttack4_1.mp3");
	m_pScene->GetResource()->LoadSound("PlayerNotStop", false, "KianaAttack4_2Charge", "Player/Kiana/KianaAttack4_2Charge.mp3");

	m_pScene->GetResource()->LoadSound("Player", false, "KianaAttackCharge", "Player/Kiana/KianaAttackCharge.mp3");
	m_pScene->GetResource()->LoadSound("PlayerCV", false, "KianaAttack1CV", "Player/Kiana/KianaAttack1CV.mp3");

	m_pScene->GetResource()->LoadSound("PlayerCV", false, "KianaAttack2CV", "Player/Kiana/KianaAttack1CV.mp3");
	m_pScene->GetResource()->LoadSound("PlayerCV", false, "KianaAttack3CV", "Player/Kiana/KianaAttack1CV.mp3");
	m_pScene->GetResource()->LoadSound("PlayerCV", false, "KianaAttack4_1CV", "Player/Kiana/KianaAttack1CV.mp3");
	m_pScene->GetResource()->LoadSound("PlayerCV", false, "KianaAttack4_2CV", "Player/Kiana/KianaAttack1CV.mp3");

	m_pScene->GetResource()->LoadSound("PlayerCV", false, "KianaHit1CV", "Player/Kiana/KianaHit1CVmp3");
	m_pScene->GetResource()->LoadSound("PlayerCV", false, "KianaHit2CV", "Player/Kiana/KianaHit2CV.mp3");

	m_pScene->GetResource()->LoadSound("Player", false, "KianaUltraSkill", "Player/Kiana/KianaUltraSkill.mp3");
	m_pScene->GetResource()->LoadSound("PlayerCV", false, "KianaUltraSkillCV", "Player/Kiana/KianaUltraSkillCV.mp3");
	m_pScene->GetResource()->LoadSound("Player", false, "KianaEvade", "Player/Kiana/KianaEvade.mp3");
	m_pScene->GetResource()->LoadSound("PlayerNotStop", false, "KianaAppearCV", "Player/Kiana/KianaAppearCV.mp3");
#pragma endregion


	m_pScene->GetResource()->CreateMaterial("Snow");
	m_pScene->GetResource()->AddMaterialTexture("Snow", "Snow", TEXT("Particle/Bubbles50px.png"));
	m_pScene->GetResource()->SetMaterialTransparency("Snow", true);
	return true;
}

bool CStageManager::CreateAnimation2D()
{
	
	m_pScene->GetResource()->CreateAnimationSequence2D("Hit_Small_04", 0.6f);
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Hit_Small_04", "Hit_Small_04", TEXT("Effect/Hit_Small_04.png"));
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			m_pScene->GetResource()->AddAnimationSequence2DFrame("Hit_Small_04",
				Vector2(j * 171.f, 256.f*i), Vector2((j + 1) * 171.f, 256.f*(i+1)));

		}
	}
	m_pScene->GetResource()->CreateAnimationSequence2D("Hit_Small_01", 0.6f);
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Hit_Small_01", "Hit_Small_01", TEXT("Effect/Hit_Small_01.png"));
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			m_pScene->GetResource()->AddAnimationSequence2DFrame("Hit_Small_01",
				Vector2(j * 171.f, 256.f * i), Vector2((j + 1) * 171.f, 256.f * (i + 1)));

		}
	}
	m_pScene->GetResource()->CreateAnimationSequence2D("Effect_Wave08", 0.5f, 0.5f);
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Effect_Wave08",
		"Effect_Wave08", TEXT("Effect/Effect_Wave08.png"));
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 1; j >=0; --j)
		{
			m_pScene->GetResource()->AddAnimationSequence2DFrame("Effect_Wave08",
				Vector2(i * 128.f, 128.f * j), Vector2((i + 1) * 128.f, 128.f * (j + 1)));

		}
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Wendy_AirBall");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Wendy_AirBall", "Wendy_AirBall", TEXT("Monster/Effect/Air_ball.png"));
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			m_pScene->GetResource()->AddAnimationSequence2DFrame("Wendy_AirBall", Vector2(j * 128.f, 256.f * i), Vector2((j + 1) * 128.f, 256.f * (i + 1)));
		}
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Black_Circle");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Black_Circle", "Black_Circle", TEXT("Monster/Effect/Swirl-BlackAll.png"));
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			m_pScene->GetResource()->AddAnimationSequence2DFrame("Black_Circle", Vector2(j * 128.f, 128.f * i), Vector2((j + 1) * 128.f, 128.f * (i + 1)));
		}
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Air_HitEffect");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Air_HitEffect", "Air_HitEffect", TEXT("Monster/Effect/Hit_Small_04.png"));
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			m_pScene->GetResource()->AddAnimationSequence2DFrame("Air_HitEffect", Vector2(j * 170.5f, 256.f * i), Vector2((j + 1) * 170.5f, 256.f* (i + 1)));
		}
	}
	m_pScene->GetResource()->AddAnimationSequence2DFrame("Air_HitEffect", Vector2(0.f, 0.f), Vector2(1.f, 1.f));

	m_pScene->GetResource()->CreateAnimationSequence2D("Tornado_Effect_1");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Tornado_Effect_1", "Tornado_Effect_1", TEXT("Monster/Effect_Wave08.png"));
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 2; j > 0; --j)
		{
			m_pScene->GetResource()->AddAnimationSequence2DFrame("Tornado_Effect_1", Vector2(j * 128.f, 128.f* i), Vector2((j + 1) * 128.f, 128.f * (i + 1)));
		}
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Tornado_Effect_2");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Tornado_Effect_2", "Tornado_Effect_2", TEXT("Monster/Effect_Wave09.png"));
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 2; j > 0; --j)
		{
			m_pScene->GetResource()->AddAnimationSequence2DFrame("Tornado_Effect_2", Vector2(j * 256.f, 256.f * i), Vector2((j + 1) * 256.f, 256.f * (i + 1)));
		}
	}


	m_pScene->GetResource()->CreateAnimationSequence2D("Explosion_01");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Explosion_01", "Explosion_01", TEXT("Monster/Effect/hit explosion4_new.png"));
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 7; j > 0; --j)
		{
			m_pScene->GetResource()->AddAnimationSequence2DFrame("Explosion_01", Vector2(j * 18.285f, 42.666f * i), Vector2((j + 1) * 18.285f, 42.666f * (i + 1)));
		}
	}
	m_pScene->GetResource()->CreateAnimationSequence2D("Explosion_02");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Explosion_02", "Explosion_02", TEXT("Monster/Effect/Explosion-B.png"));
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 5; j > 0; --j)
		{
			m_pScene->GetResource()->AddAnimationSequence2DFrame("Explosion_02", Vector2(j * 102.4f, 170.66f * i), Vector2((j + 1) * 102.4f, 170.66f * (i + 1)));
		}
	}
	m_pScene->GetResource()->CreateAnimationSequence2D("Explosion_03");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Explosion_03", "Explosion_03", TEXT("Monster/Effect/Fire diffusion path_2.png"));
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 3; j > 0; --j)
		{
			m_pScene->GetResource()->AddAnimationSequence2DFrame("Explosion_03", Vector2(j * 85.333f, 128.f * i), Vector2((j + 1) * 85.333f, 128.f * (i + 1)));
		}
	}
	m_pScene->GetResource()->CreateAnimationSequence2D("KnifeEffect");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("KnifeEffect", "KnifeEffect", TEXT("Monster/Hit/k-line01.png"));
	for (int i = 0; i < 6; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("KnifeEffect", Vector2(0.f, 85.33333333f * i), Vector2(512.f, 85.33333333f * (i + 1)));
	}
	return true;
}

bool CStageManager::CreateTexture2D()
{
	return true;
}

bool CStageManager::CreateParticle()
{
	// Dust
	{ 
		{
			m_pScene->GetResource()->CreateMaterial("Dust");
			CMaterial* Mtrl = m_pScene->GetResource()->FindMaterial("Dust");
			Mtrl->AddTexture("DustTexture", TEXT("Monster/Fx_Fire_02.png"));
			Mtrl->SetTextureLink("DustTexture", Texture_Link::BaseTexture);
			Mtrl->SetShader("BillboardShader");
		}
		CMaterial* Material = m_pScene->GetResource()->FindMaterial("Dust");

		m_pScene->GetResource()->CreateParticle("DustParticle");
		m_pScene->GetResource()->SetParticleMaterial("DustParticle", Material);
		m_pScene->GetResource()->SetParticleMaxParticleCount("DustParticle", 10);
		m_pScene->GetResource()->SetParticleStartColor("DustParticle", 1.f, 1.f, 1.f, 0.0f);
		m_pScene->GetResource()->SetParticleEndColor("DustParticle", 1.f, 1.f, 1.f, 0.8f);
		m_pScene->GetResource()->SetParticleStartScale("DustParticle", 0.1f, 0.1f, 0.1f);
		m_pScene->GetResource()->SetParticleEndScale("DustParticle", 0.5f, 0.5f, 0.5f);
		m_pScene->GetResource()->SetParticleLifeTimeMin("DustParticle", 0.5f);
		m_pScene->GetResource()->SetParticleLifeTimeMax("DustParticle", 1.0f);
		m_pScene->GetResource()->SetParticleRange("DustParticle", 0.f, 0.f, 0.f);
		m_pScene->GetResource()->SetParticleMinSpeed("DustParticle", 0.5f);
		m_pScene->GetResource()->SetParticleMaxSpeed("DustParticle", 1.f);
		m_pScene->GetResource()->SetParticleMoveEnable("DustParticle", true); 
		m_pScene->GetResource()->SetParticle2D("DustParticle", false);
		m_pScene->GetResource()->SetParticleMoveDir("DustParticle", 0.f, 0.f, 0.f);
		//m_pScene->GetResource()->SetParticleMoveAngle("DustParticle", 1.f, 0.f, 0.f);
	}

	return true;
}

void CStageManager::ResourceLoad(CScene* Scene)
{
	if (m_LoadingResource)
	{
		return;
	}
	if (m_pScene == Scene)
	{
		return;
	}
	m_pScene = Scene;
	ResourceLoad();
}

void CStageManager::ResourceLoad()
{
	if (m_LoadingResource)
	{
		return;
	}
	m_LoadingResource = true;
	CreateSound();
	if (m_LoadThread)
		m_LoadThread->SetLoadingCount(1);
	CreateMaterial();
	if (m_LoadThread)
		m_LoadThread->SetLoadingCount(2);
	ProjectResourceLoading();
	CreateAnimation2D();
	if (m_LoadThread)
		m_LoadThread->SetLoadingCount(11);
	CreateTexture2D();
	if (m_LoadThread)
		m_LoadThread->SetLoadingCount(12);
}

void CStageManager::LoadingBeforeResourceLoad(CScene* Scene)
{
	m_pScene = Scene;
	CreateMaterial();
	CreateSound();
	//m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "WarShip", "/Scene/LobbyScene/WarShip.fbx");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "Map2", "/Scene/StageScene1/Map2.msh");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "Map3", "/Scene/StageScene1/Map3.msh");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "MapColX", "/Scene/StageScene1/MapColX.msh");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "WarShip", "/Scene/LobbyScene/WarShip.msh");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "WarShip_ControlRight", "/Scene/LobbyScene/WarShip_ControlRight.msh");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "WarShip_ControlLeft", "/Scene/LobbyScene/WarShip_ControlLeft.msh");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "WarShip_ControlCenter", "/Scene/LobbyScene/WarShip_ControlCenter.msh");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "DoorUp", "/Scene/LoadingScene/DoorUp.msh");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "DoorDown", "/Scene/LoadingScene/DoorDown.msh");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "DoorDownMove", "/Scene/LoadingScene/DoorDownMove.msh");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "Door", "/Scene/LoadingScene/Door.msh");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "Pillar", "/Scene/LoadingScene/Pillar.msh");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "Elevator", "/Scene/LoadingScene/Elevator.msh");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "GroundIn", "/Scene/LoadingScene/GroundIn.msh");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "DoorMain", "/Scene/LoadingScene/DoorMain.msh");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "LoadingMark", "/Scene/LoadingScene/LoadingMark.msh");
	CMesh* pMesh = m_pScene->GetResource()->FindMesh("Map2");
	pMesh->AllLightMaterialReset();
	pMesh = m_pScene->GetResource()->FindMesh("Map3");
	pMesh->AllLightMaterialReset();
	pMesh->GetMaterialSlot(0)->AddTexture("Stage_AirIsland_Tex_Hyperion_LowPolyLight", TEXT("Scene/StageScene1/Map3.fbm/Stage_AirIsland_Tex_Hyperion_LowPolyLight.png"), "MeshPath");
	pMesh->GetMaterialSlot(0)->SetTextureLink("Stage_AirIsland_Tex_Hyperion_LowPolyLight", Texture_Link::NormalTexture);

	pMesh = m_pScene->GetResource()->FindMesh("MapColX");
	pMesh->AllLightMaterialReset();
	for (int i = 0; i < pMesh->GetMaterialSlots()->size(); ++i)
	{
		pMesh->GetMaterialSlot(i)->SetReceiveDecal(true);
	}

	pMesh = m_pScene->GetResource()->FindMesh("WarShip");
	pMesh->AllLightMaterialReset();
	pMesh = m_pScene->GetResource()->FindMesh("WarShip_ControlRight");
	pMesh->AllLightMaterialReset();
	pMesh = m_pScene->GetResource()->FindMesh("WarShip_ControlLeft");
	pMesh->AllLightMaterialReset();
	pMesh = m_pScene->GetResource()->FindMesh("WarShip_ControlCenter");
	pMesh->AllLightMaterialReset();
	pMesh = m_pScene->GetResource()->FindMesh("DoorUp");
	pMesh->AllLightMaterialReset();
	pMesh = m_pScene->GetResource()->FindMesh("DoorDown");
	pMesh->AllLightMaterialReset();
	pMesh = m_pScene->GetResource()->FindMesh("DoorDownMove");
	pMesh->AllLightMaterialReset();
	pMesh = m_pScene->GetResource()->FindMesh("Door");
	pMesh->AllLightMaterialReset();
	pMesh = m_pScene->GetResource()->FindMesh("Pillar");
	pMesh->AllLightMaterialReset();
	pMesh = m_pScene->GetResource()->FindMesh("GroundIn");
	pMesh->AllLightMaterialReset();
	pMesh = m_pScene->GetResource()->FindMesh("DoorMain");
	pMesh->AllLightMaterialReset();
	pMesh = m_pScene->GetResource()->FindMesh("LoadingMark");
	pMesh->AllLightMaterialReset();
}

void CStageManager::BGMPlay(const std::string& Name)
{
	auto iter = m_BGMSound.begin();
	auto iterEnd = m_BGMSound.end();
	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->GetName() == Name)
		{
			if (m_PlayBGMSound)
				m_PlayBGMSound->Stop();
			m_PlayBGMSound = (*iter);
			m_PlayBGMSound->Play();
		}
	}
}

void CStageManager::BGMStop()
{
	if (m_PlayBGMSound)
		m_PlayBGMSound->Stop();
}

void CStageManager::SceneClear()
{
	m_SpawnMonsters.clear();
	size_t Size = m_MonsterDir.size();
	for (size_t i = 0; i < Size; ++i)
	{
		if (m_MonsterDir[i])
		{
			m_MonsterDir[i]->Active(false);
		}
	}
	m_MonsterDir.clear();
	m_MonsterDir.resize(50);
	if (m_Target)
	{
		m_Target->Active(false);
	}
	if (m_CameraCut)
	{
		m_CameraCut->Active(false);
	}
	if (m_PlayerMainCamera)
	{
		m_PlayerMainCamera->Active(false);
	}
	if (m_MapMeshComponent)
	{
		m_MapMeshComponent->Active(false);
	}
	m_Target = nullptr;
	m_CameraCut = nullptr;
	m_PlayerSpawnPoint = nullptr;
	m_BossMonster = nullptr;
	m_ColliderSpawnObject = nullptr;
	m_PlayerMainCamera = nullptr;
	m_MapMeshComponent = nullptr;
}

void CStageManager::MonsterHit()
{
	m_HitCombo++;
	m_HitTimer= 5.f;

	CPlayerHitComboUI* ComboUI = (CPlayerHitComboUI*)CUIManager::GetInst()->FindWidgetWindow("PlayerHitComboUI");
	ComboUI->AddShake(Vector2(5.f, 5.f), 0.5f);
	ComboUI->SetCombo(m_HitCombo);
	ComboUI->Enable(true);
}


