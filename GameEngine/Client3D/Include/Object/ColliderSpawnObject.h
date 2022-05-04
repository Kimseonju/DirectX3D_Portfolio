#pragma once

#include "Component/AnimationMeshComponent.h"
#include "Component/ColliderSphere.h"
#include "Component/ColliderBox3D.h"
#include "ClientObject.h"
#include "Sniper.h"
#include "Wendy.h"
#include "AxeSoldier.h"

struct ColliderSpawnData
{
	Vector3        Pos;
	Vector3        Rot;
	Vector3        Scale;

    ColliderSpawnData() : Pos(Vector3::Zero), Rot(Vector3::Zero), Scale(Vector3::Zero)
    {

    }
    ~ColliderSpawnData()
    {

    }
};

class CColliderSpawnObject : public CClientObject
{
    friend class CScene;

protected:
    CColliderSpawnObject();
    CColliderSpawnObject(const CColliderSpawnObject& obj);
    virtual ~CColliderSpawnObject();

protected:
    CSharedPtr<CSceneComponent> m_Root;
    CSharedPtr<CColliderBox3D> m_SpawnZone;

    bool  m_SpawnCollider;
    float m_SpawnTotalTime;
    int   m_SpawnNumber;
    
	std::vector<class CMapCollision*>        m_LivingColliders;
	std::vector<ColliderSpawnData*>        m_WaitingColliders;
public:
    void SetTimer(float SpawnTime)
    {
        m_SpawnTotalTime = SpawnTime;
    }
    float GetTimer()
    {
        return m_SpawnTotalTime;
    }
        
    int GetWaitingColliderCount()
    {
        return (int)m_WaitingColliders.size();
    }
    std::vector<ColliderSpawnData*>& GetSpawnData()
    {
        return m_WaitingColliders;
    }
public:
    void CollisionCallBack(const HitResult& result, CCollider* Collider);
    void SettingCollider(const Vector3& Pos = Vector3::Zero, const Vector3& Rot = Vector3::Zero, const Vector3& Scale = Vector3::One);

public:
    virtual void Active(bool bActive);
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Collision(float DeltaTime);
    virtual void Render(float DeltaTime);
	virtual CColliderSpawnObject* Clone();
public:
	virtual void Save(FILE* pFile);
	virtual void Load(FILE* pFile);
};