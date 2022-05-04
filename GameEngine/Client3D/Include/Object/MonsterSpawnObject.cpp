
#include "MonsterSpawnObject.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Resource/Material.h"
#include "../StageManager.h"
#include "Engine.h"
CMonsterSpawnObject::CMonsterSpawnObject() : m_SpawnMonster(false), m_SpawnTotalTime(0.f), m_TimeSpawn(false),
m_SpawnNumber(0)
{
	m_ClientClassType = ClientClassType::MonsterSpawnObject;
}

CMonsterSpawnObject::CMonsterSpawnObject(const CMonsterSpawnObject& obj) : CClientObject(obj)
{
    m_SpawnZone = (CColliderBox3D*)FindSceneComponent("SpawnZone");
}

CMonsterSpawnObject::~CMonsterSpawnObject()
{
    auto iter = m_WaitingMonsters.begin();
    auto iterEnd = m_WaitingMonsters.end();

    for (; iter != iterEnd; ++iter)
    {
        SAFE_DELETE((*iter));
    }
    m_WaitingMonsters.clear();
}


void CMonsterSpawnObject::Start()
{
	CGameObject::Start();
	if (CEngine::GetInst()->IsEditor())
		return;
	auto Data = m_WaitingMonsters.begin();
	auto DataEnd = m_WaitingMonsters.end();
    int i = 0;
    for (; Data != DataEnd; ++Data)
    {
		CMonster* Monster = nullptr;
		switch ((*Data)->Type)
		{
		case ClientClassType::Axe:
		{
			std::string Name = "AxeSoldier" + std::to_string(i);
			Monster = m_pScene->SpawnObject<CAxeSoldier>(Name);
		}
			break;
		case ClientClassType::Sniper:
		{
			std::string Name = "Sniper" + std::to_string(i);
			Monster = m_pScene->SpawnObject<CSniper>(Name);
		}
			break;
		case ClientClassType::Wendy:
		{
			std::string Name = "Wendy" + std::to_string(i);
			Monster = m_pScene->SpawnObject<CWendy>(Name);
		}
			break;
		default:
			break;
		}

        if (Monster)
		{
            Monster->Enable(false);

			Monster->SetWorldPos((*Data)->Pos);
			Monster->SetWorldRotation((*Data)->Rot);
			Monster->SetWorldScale((*Data)->Scale);
			m_LivingMonsters.push_back(Monster);
            CStageManager::GetInst()->PushMonster(Monster);
        }
        i++;
    }
}

bool CMonsterSpawnObject::Init()
{
    CGameObject::Init();
    m_Root = CreateSceneComponent<CSceneComponent>("Root");
    m_SpawnZone = CreateSceneComponent<CColliderBox3D>("SpawnZone");

    SetRootComponent(m_Root);
    m_Root->AddChild(m_SpawnZone);

    m_SpawnZone->SetCollisionProfile("SpawnZone");
    m_SpawnZone->SetWorldPos(1.f, 1.f, 1.f);
    m_Root->SetRelativePos(5.f, 0.f, 5.f);

    m_SpawnZone->AddCollisionCallbackFunction<CMonsterSpawnObject>(Collision_State::Begin, this, &CMonsterSpawnObject::CollisionCallBack);
    return true;
}

void CMonsterSpawnObject::Update(float DeltaTime)
{
    CGameObject::Update(DeltaTime);

	if (CEngine::GetInst()->IsEditor())
		return;
    if (m_SpawnMonster)
    {
        m_SpawnTotalTime -= DeltaTime;
		//모든 몬스터에게 스폰할때 이쪽에 원이 점점커지게하기
        if (0 >= m_SpawnTotalTime)
        {
			for (size_t i = 0; i < m_LivingMonsters.size(); ++i)
			{
				m_LivingMonsters[i]->Enable(true);
			}
            
        }
    }
}

void CMonsterSpawnObject::PostUpdate(float DeltaTime)
{
    CGameObject::PostUpdate(DeltaTime);
}

void CMonsterSpawnObject::Collision(float DeltaTime)
{
    CGameObject::Collision(DeltaTime);
}

void CMonsterSpawnObject::Render(float DeltaTime)
{
    CGameObject::Render(DeltaTime);
}

void CMonsterSpawnObject::CollisionCallBack(const HitResult& result, CCollider* Collider)
{
    if ("Player" == result.DestCollider->GetProfile()->Name)
    {
        m_SpawnMonster = true;


    }
}

void CMonsterSpawnObject::SettingMonster(const std::string& MonsterClass, const Vector3& Pos, const Vector3& Rot, const Vector3& Scale, ClientClassType Type)
{
    if (Type == ClientClassType::Default)
    {
		if (MonsterClass == "Sniper")
		{
			MonsterSpawnData* Data = new MonsterSpawnData;
			Data->Name = "Sniper" + std::to_string(m_WaitingMonsters.size());
			Data->Type = ClientClassType::Sniper;
			Data->Pos = Pos;
			Data->Rot = Rot;
			Data->Scale = Scale;
			m_WaitingMonsters.push_back(Data);
		}
		else if (MonsterClass == "AxeSoldier")
		{
			MonsterSpawnData* Data = new MonsterSpawnData;
			Data->Name = "AxeSoldier" + std::to_string(m_WaitingMonsters.size());
			Data->Type = ClientClassType::Axe;
			Data->Pos = Pos;
			Data->Rot = Rot;
			Data->Scale = Scale;
			m_WaitingMonsters.push_back(Data);
		}
		else if (MonsterClass == "Wendy")
		{
			MonsterSpawnData* Data = new MonsterSpawnData;
			Data->Name = "Wendy" + std::to_string(m_WaitingMonsters.size());
			Data->Type = ClientClassType::Wendy;
			Data->Pos = Pos;
			Data->Rot = Rot;
			Data->Scale = Scale;
			m_WaitingMonsters.push_back(Data);
		}
    }
	else
	{
		switch (Type)
		{
		case ClientClassType::Axe:
		{
			MonsterSpawnData* Data = new MonsterSpawnData;
			Data->Name = "AxeSoldier" + std::to_string(m_WaitingMonsters.size());
			Data->Type = ClientClassType::Axe;
			Data->Pos = Pos;
			Data->Rot = Rot;
			Data->Scale = Scale;
			m_WaitingMonsters.push_back(Data);
		}
			break;
		case ClientClassType::Sniper:
		{
			MonsterSpawnData* Data = new MonsterSpawnData;
			Data->Name = "Sniper" + std::to_string(m_WaitingMonsters.size());
			Data->Type = ClientClassType::Sniper;
			Data->Pos = Pos;
			Data->Rot = Rot;
			Data->Scale = Scale;
			m_WaitingMonsters.push_back(Data);
		}
			break;
		default:
			break;
		}
	}
}

CMonsterSpawnObject* CMonsterSpawnObject::Clone()
{
    return new CMonsterSpawnObject(*this);
}

void CMonsterSpawnObject::Save(FILE* pFile)
{
    CClientObject::Save(pFile);
    size_t Size = m_WaitingMonsters.size();

	fwrite(&Size, sizeof(size_t), 1, pFile);
    for (size_t i = 0; i < Size; ++i)
	{
		int Length = (int)strlen(m_WaitingMonsters[i]->Name.c_str());

		fwrite(&Length, sizeof(int), 1, pFile);
		fwrite(m_WaitingMonsters[i]->Name.c_str(), sizeof(char), Length, pFile);
		fwrite(&m_WaitingMonsters[i]->Type, sizeof(ClientClassType), 1, pFile);

        fwrite(&m_WaitingMonsters[i]->Pos, sizeof(Vector3), 1, pFile);
        fwrite(&m_WaitingMonsters[i]->Rot, sizeof(Vector3), 1, pFile);
        fwrite(&m_WaitingMonsters[i]->Scale, sizeof(Vector3), 1, pFile);
    }
    fwrite(&m_SpawnMonster, sizeof(bool), 1, pFile);
	fwrite(&m_SpawnTotalTime, sizeof(float), 1, pFile);
	fwrite(&m_TimeSpawn, sizeof(bool), 1, pFile);
	fwrite(&m_SpawnNumber, sizeof(int), 1, pFile);
}

void CMonsterSpawnObject::Load(FILE* pFile)
{
	CClientObject::Load(pFile);
    size_t Size = 0;
	fread(&Size, sizeof(size_t), 1, pFile);
	for (size_t i = 0; i < Size; ++i)
	{
		int Length = -1;
		fread(&Length, sizeof(int), 1, pFile);
		char	Name[256] = {};
		fread(Name, sizeof(char), Length, pFile);
        Vector3 Pos = Vector3::Zero;
        Vector3 Rot = Vector3::Zero;
        Vector3 Scale = Vector3::Zero;
		ClientClassType Type = ClientClassType::Default;
        fread(&Type, sizeof(ClientClassType), 1, pFile);
		fread(&Pos, sizeof(Vector3), 1, pFile);
		fread(&Rot, sizeof(Vector3), 1, pFile);
		fread(&Scale, sizeof(Vector3), 1, pFile);
	
        SettingMonster(Name, Pos, Rot, Scale, Type);
	}
	fread(&m_SpawnMonster, sizeof(bool), 1, pFile);
	fread(&m_SpawnTotalTime, sizeof(float), 1, pFile);
	fread(&m_TimeSpawn, sizeof(bool), 1, pFile);
	fread(&m_SpawnNumber, sizeof(int), 1, pFile);
}
