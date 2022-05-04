
#include "BossSpawnObject.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Resource/Material.h"
#include "../StageManager.h"
#include "Engine.h"
CBossSpawnObject::CBossSpawnObject() : m_SpawnBoss(false),  m_SpawnTotalTime(1.f),
	m_WarningSound(nullptr),
	m_SpawnTime(0.f),
	m_LivingBoss(nullptr),
	m_WaitingBoss(nullptr)

{
	m_ClientClassType = ClientClassType::BossSpawnObject;
}

CBossSpawnObject::CBossSpawnObject(const CBossSpawnObject& obj) : CClientObject(obj)
{
	m_SpawnZone = (CColliderBox3D*)FindSceneComponent("SpawnZone");
}

CBossSpawnObject::~CBossSpawnObject()
{
}


void CBossSpawnObject::Start()
{
	CGameObject::Start();

	if (CEngine::GetInst()->IsEditor())
		return;
	if (m_WaitingBoss)
	{
		std::string Name = "Wendy";
		CWendy* Boss = m_pScene->SpawnObject<CWendy>(Name);
		Boss->SetWorldPos(m_WaitingBoss->Pos);
		Boss->SetWorldRotation(m_WaitingBoss->Rot);
		Boss->SetWorldScale(m_WaitingBoss->Scale);
		Boss->Enable(false);
		m_LivingBoss = Boss;
		CStageManager::GetInst()->SetBoss(Boss);
		SAFE_DELETE(m_WaitingBoss);
	}
}

bool CBossSpawnObject::Init()
{
	CGameObject::Init();
	m_Root = CreateSceneComponent<CSceneComponent>("Root");
	m_SpawnZone = CreateSceneComponent<CColliderBox3D>("SpawnZone");

	SetRootComponent(m_Root);
	m_Root->AddChild(m_SpawnZone);

	m_SpawnZone->SetCollisionProfile("SpawnZone");
	m_SpawnZone->SetWorldPos(1.f, 1.f, 1.f);
	m_Root->SetRelativePos(5.f, 0.f, 5.f);
	m_WarningSound =m_pScene->GetResource()->FindSound2D("Warning_Loop");
	m_SpawnZone->AddCollisionCallbackFunction<CBossSpawnObject>(Collision_State::Begin, this, &CBossSpawnObject::CollisionCallBack);
	return true;
}

void CBossSpawnObject::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	if (CEngine::GetInst()->IsEditor())
		return;
	if (m_SpawnBoss)
	{
		m_SpawnTotalTime -= DeltaTime;
		if (!m_WarningSound->IsPlay())
		{
			m_WarningSound->Play();
		}
		if (m_SpawnTotalTime<0.f)
		{
			m_WarningSound->Stop();
			CStageManager::GetInst()->GetCameraCut()->StartCameraScene_FadeInOut("Wendy1", m_LivingBoss, true, 2.f);
			//스폰완료
			m_SpawnBoss = false;
		}
		
	}

	if (m_WaitingBoss)
	{
		std::string Name = "Wendy";
		CWendy* Boss = m_pScene->SpawnObject<CWendy>(Name);
		Boss->SetWorldPos(m_WaitingBoss->Pos);
		Boss->SetWorldRotation(m_WaitingBoss->Rot);
		Boss->SetWorldScale(m_WaitingBoss->Scale);
		Boss->Enable(false);
		m_LivingBoss = Boss;
		CStageManager::GetInst()->SetBoss(Boss);

		SAFE_DELETE(m_WaitingBoss);
	}
}


void CBossSpawnObject::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CBossSpawnObject::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CBossSpawnObject::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

void CBossSpawnObject::CollisionCallBack(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Name=="Player")
	{
		m_SpawnBoss = true;
		m_SpawnZone->Enable(false);
	}
}

void CBossSpawnObject::SettingBoss(const std::string& BossClass, const Vector3& Pos, const Vector3& Rot, const Vector3& Scale)
{
	if (BossClass == "Wendy")
	{
		BossSpawnData* Data = new BossSpawnData;
		Data->Name = "Wendy";
		Data->Pos = Pos;
		Data->Rot = Rot;
		Data->Scale = Scale;
		m_WaitingBoss = Data;
	}
}

CBossSpawnObject* CBossSpawnObject::Clone()
{
	return new CBossSpawnObject(*this);
}

void CBossSpawnObject::Save(FILE* pFile)
{
	CClientObject::Save(pFile);

	bool Enable = false;
	if (m_WaitingBoss)
	{
		Enable = true;
	}
	fwrite(&Enable, sizeof(bool), 1, pFile);

	if (Enable)
	{
		int Length = (int)strlen(m_WaitingBoss->Name.c_str());

		fwrite(&Length, sizeof(int), 1, pFile);
		fwrite(m_WaitingBoss->Name.c_str(), sizeof(char), Length, pFile);

		fwrite(&m_WaitingBoss->Pos, sizeof(Vector3), 1, pFile);
		fwrite(&m_WaitingBoss->Rot, sizeof(Vector3), 1, pFile);
		fwrite(&m_WaitingBoss->Scale, sizeof(Vector3), 1, pFile);
	}
	
	fwrite(&m_SpawnTotalTime, sizeof(float), 1, pFile);
}

void CBossSpawnObject::Load(FILE* pFile)
{
	CClientObject::Load(pFile);

	bool Enable = false;
	fread(&Enable, sizeof(bool), 1, pFile);
	if (Enable)
	{
		int Length = -1;
		fread(&Length, sizeof(int), 1, pFile);
		char	Name[256] = {};
		fread(Name, sizeof(char), Length, pFile);

		Vector3 Pos = Vector3::Zero;
		Vector3 Rot = Vector3::Zero;
		Vector3 Scale = Vector3::Zero;
		fread(&Pos, sizeof(Vector3), 1, pFile);
		fread(&Rot, sizeof(Vector3), 1, pFile);
		fread(&Scale, sizeof(Vector3), 1, pFile);
		SettingBoss(Name, Pos, Rot, Scale);
	}
	fread(&m_SpawnTotalTime, sizeof(float), 1, pFile);

}
