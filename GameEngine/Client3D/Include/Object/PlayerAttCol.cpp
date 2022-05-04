
#include "PlayerAttCol.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Resource/Material.h"
#include "../PublicData.h"
#include "Resource/BoneSocket.h"
#include "Player.h"
#include "HitEffect.h"

CPlayerAttCol::CPlayerAttCol():
    m_SoundPlay(false)
{
}

CPlayerAttCol::CPlayerAttCol(const CPlayerAttCol& obj) : CAttackObject(obj)
{
}

CPlayerAttCol::~CPlayerAttCol()
{
}

void CPlayerAttCol::Start()
{
    CAttackObject::Start();
}

bool CPlayerAttCol::Init()
{
    CAttackObject::Init();
    m_Sphere->Enable(false);
	m_Box->SetCollisionProfile("PlayerAttack");
    m_Sphere->SetCollisionProfile("PlayerAttack");

    SetLifeTime(0.5f);
    return true;
}

void CPlayerAttCol::Update(float DeltaTime)
{
    CAttackObject::Update(DeltaTime);

}

void CPlayerAttCol::PostUpdate(float DeltaTime)
{
    CAttackObject::PostUpdate(DeltaTime);
}

void CPlayerAttCol::Collision(float DeltaTime)
{
    CAttackObject::Collision(DeltaTime);
}

void CPlayerAttCol::Render(float DeltaTime)
{
    CAttackObject::Render(DeltaTime);
}

CPlayerAttCol* CPlayerAttCol::Clone()
{
    return new CPlayerAttCol(*this);
}

void CPlayerAttCol::CollisionBegin(const HitResult& result, CCollider* Collider)
{
    if (!m_SoundPlay)
    {
		if (m_Type == ClientClassType::Kiana)
		{
			m_pScene->GetResource()->FindSound3D("KianaAttackHit")->Play3D(GetWorldPos());
            m_SoundPlay = true;
			//CHitEffect* Effect = m_pScene->SpawnObject<CHitEffect>("Hit");
			//Effect->SetWorldPos(result.DestObject->GetWorldPos());
		}
		if (m_Type == ClientClassType::Sakura)
		{
			m_pScene->GetResource()->FindSound3D("SakuraAttackHit")->Play3D(GetWorldPos());
			m_SoundPlay = true;
			//CHitEffect* Effect = m_pScene->SpawnObject<CHitEffect>("Hit");
            //Effect->SetWorldPos(result.DestObject->GetWorldPos());
		}
    }
    
}

void CPlayerAttCol::CollisionMiddle(const HitResult& result, CCollider* Collider)
{
}

void CPlayerAttCol::CollisionEnd(const HitResult& result, CCollider* Collider)
{
}
