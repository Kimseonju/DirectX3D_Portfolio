
#include "ColliderSpawnObject.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Resource/Material.h"
#include "MapCollision.h"
#include "../StageManager.h"
#include "Engine.h"
CColliderSpawnObject::CColliderSpawnObject() : m_SpawnCollider(false), m_SpawnTotalTime(0.f),
m_SpawnNumber(0)
{
	m_ClientClassType = ClientClassType::ColliderSpawnObject;
}

CColliderSpawnObject::CColliderSpawnObject(const CColliderSpawnObject& obj) : CClientObject(obj)
{
	m_SpawnZone = (CColliderBox3D*)FindSceneComponent("SpawnZone");
}

CColliderSpawnObject::~CColliderSpawnObject()
{
	auto iter = m_WaitingColliders.begin();
	auto iterEnd = m_WaitingColliders.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE((*iter));
	}
	m_WaitingColliders.clear();
}


void CColliderSpawnObject::Active(bool bActive)
{
	CClientObject::Active(bActive);

	if (m_SpawnCollider)
	{
		for (size_t i = 0; i < m_LivingColliders.size(); ++i)
		{
			m_LivingColliders[i]->Active(bActive);
		}
	}
}

void CColliderSpawnObject::Start()
{
	CGameObject::Start();
	if (CEngine::GetInst()->IsEditor())
		return;
	auto Data = m_WaitingColliders.begin();
	auto DataEnd = m_WaitingColliders.end();
	int i = 0;
	std::string str = "MapCollider_Monster";
	for (; Data != DataEnd; Data++)
	{
		CMapCollision* Collision = m_pScene->SpawnObject<CMapCollision>(str + std::to_string(i));
		Collision->SetWorldPos((*Data)->Pos);
		Collision->SetWorldRotation((*Data)->Rot);
		Vector3 length = (*Data)->Scale / 2.f;
		Collision->SetLength(length.x, length.y, length.z);
		Collision->SetWorldScale((*Data)->Scale);
		Collision->Enable(false);
		m_LivingColliders.push_back(Collision);
		i++;
	}

	auto iter = m_WaitingColliders.begin();
	auto iterEnd = m_WaitingColliders.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE((*iter));
	}
	m_WaitingColliders.clear();

}

bool CColliderSpawnObject::Init()
{
	CGameObject::Init();
	m_Root = CreateSceneComponent<CSceneComponent>("Root");
	m_SpawnZone = CreateSceneComponent<CColliderBox3D>("SpawnZone");

	SetRootComponent(m_Root);
	m_Root->AddChild(m_SpawnZone);

	m_SpawnZone->SetCollisionProfile("SpawnZone");
	m_SpawnZone->SetWorldPos(1.f, 1.f, 1.f);
	m_Root->SetRelativePos(5.f, 0.f, 5.f);

	m_SpawnZone->AddCollisionCallbackFunction<CColliderSpawnObject>(Collision_State::Begin, this, &CColliderSpawnObject::CollisionCallBack);
	return true;
}

void CColliderSpawnObject::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	if (CEngine::GetInst()->IsEditor())
		return;

	if (m_SpawnCollider)
	{
		m_SpawnTotalTime -= DeltaTime;
		if (0 >= m_SpawnTotalTime)
		{
			for (size_t i = 0; i < m_LivingColliders.size(); ++i)
			{
				m_LivingColliders[i]->Enable(true);
			}
		}
		CStageManager::GetInst()->SetColliderSpawnObject(this);
	}

	auto Data = m_WaitingColliders.begin();
	auto DataEnd = m_WaitingColliders.end();
	int i = 0;
	std::string str = "MapCollider_Monster";
	for (; Data != DataEnd; Data++)
	{
		CMapCollision* Collision = m_pScene->SpawnObject<CMapCollision>(str + std::to_string(i));
		Collision->SetWorldPos((*Data)->Pos);
		Collision->SetWorldRotation((*Data)->Rot);
		Collision->SetWorldScale((*Data)->Scale);
		Collision->Enable(false);
		m_LivingColliders.push_back(Collision);
		i++;
	}

	auto iter = m_WaitingColliders.begin();
	auto iterEnd = m_WaitingColliders.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE((*iter));
	}
	m_WaitingColliders.clear();
}

void CColliderSpawnObject::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CColliderSpawnObject::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CColliderSpawnObject::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

void CColliderSpawnObject::CollisionCallBack(const HitResult& result, CCollider* Collider)
{
	if ("Body" == result.DestCollider->GetName())
	{
		m_SpawnCollider = true;
		m_SpawnZone->Enable(false);
	}
}

void CColliderSpawnObject::SettingCollider(const Vector3& Pos, const Vector3& Rot, const Vector3& Scale)
{
	ColliderSpawnData* Data = new ColliderSpawnData;
	Data->Pos = Pos;
	Data->Rot = Rot;
	Data->Scale = Scale;

	m_WaitingColliders.push_back(Data);
}


CColliderSpawnObject* CColliderSpawnObject::Clone()
{
	return new CColliderSpawnObject(*this);
}


void CColliderSpawnObject::Save(FILE* pFile)
{
	CClientObject::Save(pFile);
	size_t Size = m_WaitingColliders.size();

	fwrite(&Size, sizeof(size_t), 1, pFile);
	for (size_t i = 0; i < Size; ++i)
	{

		fwrite(&m_WaitingColliders[i]->Pos, sizeof(Vector3), 1, pFile);
		fwrite(&m_WaitingColliders[i]->Rot, sizeof(Vector3), 1, pFile);
		fwrite(&m_WaitingColliders[i]->Scale, sizeof(Vector3), 1, pFile);
	}
	fwrite(&m_SpawnCollider, sizeof(bool), 1, pFile);
	fwrite(&m_SpawnTotalTime, sizeof(float), 1, pFile);
	fwrite(&m_SpawnNumber, sizeof(int), 1, pFile);
}

void CColliderSpawnObject::Load(FILE* pFile)
{
	CClientObject::Load(pFile);
	size_t Size = 0;
	fread(&Size, sizeof(size_t), 1, pFile);
	for (size_t i = 0; i < Size; ++i)
	{
	
		Vector3 Pos = Vector3::Zero;
		Vector3 Rot = Vector3::Zero;
		Vector3 Scale = Vector3::Zero;
		fread(&Pos, sizeof(Vector3), 1, pFile);
		fread(&Rot, sizeof(Vector3), 1, pFile);
		fread(&Scale, sizeof(Vector3), 1, pFile);
		SettingCollider(Pos, Rot, Scale);
	}
	fread(&m_SpawnCollider, sizeof(bool), 1, pFile);
	fread(&m_SpawnTotalTime, sizeof(float), 1, pFile);
	fread(&m_SpawnNumber, sizeof(int), 1, pFile);
}
