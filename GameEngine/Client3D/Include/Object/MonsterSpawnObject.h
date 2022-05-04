#pragma once

#include "Component/AnimationMeshComponent.h"
#include "Component/ColliderSphere.h"
#include "Component/ColliderBox3D.h"
#include "ClientObject.h"
#include "Monster.h"
#include "Sniper.h"
#include "Wendy.h"
#include "AxeSoldier.h"

struct MonsterSpawnData
{
    std::string     Name;
    Vector3         Pos;
    Vector3         Rot;
    Vector3         Scale;
    ClientClassType Type;
    MonsterSpawnData() : Name(""), Pos(Vector3::Zero), Rot(Vector3::Zero), Scale(Vector3::Zero), Type(ClientClassType::Default)
    {

    }
    ~MonsterSpawnData()
    {

    }
};

class CMonsterSpawnObject : public CClientObject
{
    friend class CScene;

protected:
    CMonsterSpawnObject();
    CMonsterSpawnObject(const CMonsterSpawnObject& obj);
    virtual ~CMonsterSpawnObject();

protected:
    CSharedPtr<CSceneComponent> m_Root;
    CSharedPtr<CColliderBox3D> m_SpawnZone;

    bool  m_SpawnMonster;
    float m_SpawnTotalTime;
    bool  m_TimeSpawn;
    int   m_SpawnNumber;

    std::vector<CMonster*>    m_LivingMonsters;
    std::vector<MonsterSpawnData*>        m_WaitingMonsters;
public:
    void SetTimer(float SpawnTime)
    {m_SpawnTotalTime = SpawnTime;}
    void IsTimeSpawn(bool Enable)
    {m_TimeSpawn = Enable;}


	std::vector<MonsterSpawnData*>& GetSpawnData()
	{
		return m_WaitingMonsters;
	}

	float GetTimer()
	{
		return m_SpawnTotalTime;
	}
    int GetLivingMonsterCount()
    {return (int)m_LivingMonsters.size();}
    int GetWaitingMonsterCount()
    {return (int)m_WaitingMonsters.size();}
public:
    void CollisionCallBack(const HitResult& result, CCollider* Collider);
    void SettingMonster(const std::string& MonsterClass, const Vector3& Pos = Vector3::Zero, const Vector3& Rot = Vector3::Zero, const Vector3& Scale=Vector3::One,
        ClientClassType Type=ClientClassType::Default);
public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Collision(float DeltaTime);
    virtual void Render(float DeltaTime);
	virtual CMonsterSpawnObject* Clone();
public:
	virtual void Save(FILE* pFile);
	virtual void Load(FILE* pFile);
};