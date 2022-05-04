#pragma once

#include "Component/AnimationMeshComponent.h"
#include "Component/ColliderSphere.h"
#include "Component/ColliderBox3D.h"
#include "ClientObject.h"
#include "Monster.h"
#include "Sniper.h"
#include "Wendy.h"
#include "AxeSoldier.h"

struct BossSpawnData
{
	std::string     Name;
	Vector3         Pos;
	Vector3         Rot;
	Vector3         Scale;

    BossSpawnData() : Name(""), Pos(Vector3::Zero), Rot(Vector3::Zero), Scale(Vector3::Zero)
    {

    }
    ~BossSpawnData()
    {

    }
};

class CBossSpawnObject : public CClientObject
{
    friend class CScene;

protected:
    CBossSpawnObject();
    CBossSpawnObject(const CBossSpawnObject& obj);
    virtual ~CBossSpawnObject();

protected:
    CSharedPtr<CSceneComponent> m_Root;
    CSharedPtr<CColliderBox3D> m_SpawnZone;
    CSound* m_WarningSound;
	bool  m_SpawnBoss;
	float m_SpawnTotalTime;
	float m_SpawnTime;

    CMonster*    m_LivingBoss;
    BossSpawnData*        m_WaitingBoss;
public:
    void SetTimer(float SpawnTime)
    {
        m_SpawnTotalTime = SpawnTime;
    }

    BossSpawnData* GetSpawnData() const
	{
		return m_WaitingBoss;
	}

	float GetTimer()
	{
		return m_SpawnTotalTime;
	}
public:
    void CollisionCallBack(const HitResult& result, CCollider* Collider);
    void SettingBoss(const std::string& BossClass, const Vector3& Pos = Vector3::Zero, const Vector3& Rot = Vector3::Zero, const Vector3& Scale = Vector3::One);
public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Collision(float DeltaTime);
    virtual void Render(float DeltaTime);
    virtual CBossSpawnObject* Clone();
public:
	void Save(FILE* pFile);
	void Load(FILE* pFile);
};