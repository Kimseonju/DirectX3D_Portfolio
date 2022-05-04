
#include "SniperBillet.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Resource/Material.h"
#include "../PublicData.h"
#include "Resource/BoneSocket.h"
#include "Player.h"
#include "ExplosionEffect.h"

CSniperBullet::CSniperBullet() :
    m_Setting(false),
    m_Point(Vector3::Zero),
    m_PrevPos(Vector3::Zero),
    m_NAttack(true)
{
}

CSniperBullet::CSniperBullet(const CSniperBullet& obj) : CAttackObject(obj)
{
}

CSniperBullet::~CSniperBullet()
{
}

void CSniperBullet::CollisionBegin(const HitResult& result, CCollider* Collider)
{
    if (result.DestCollider->GetProfile()->Name == "Player")
    {
        m_Sphere->Enable(false);
        m_Box->Enable(false);
        m_Mesh->Enable(false);
        m_pScene->GetResource()->FindSound3D("Sniper_GunHit")->Play3D(m_Mesh->GetWorldPos());

        {
            CExplosionEffect* Effect = m_pScene->SpawnObject<CExplosionEffect>("Effect");
            Effect->SetEffectType(ExplosionEffectType::Type_1);
            Effect->SetWorldPos(m_Mesh->GetWorldPos());
            Effect->SetEffectMultScale(1.f);
        }
    }
}

void CSniperBullet::CollisionMiddle(const HitResult& result, CCollider* Collider)
{
}

void CSniperBullet::CollisionEnd(const HitResult& result, CCollider* Collider)
{
}

void CSniperBullet::Start()
{
    CAttackObject::Start();
}

bool CSniperBullet::Init()
{
    CAttackObject::Init();
    if (CPublicData::GetInst()->Bullet_ResourceCheck != true)
    {
        CPublicData::GetInst()->Bullet_ResourceCheck = true;
        m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "BulletMesh", "Monster/AttackObject/Bullet/Bullet.msh");
        CMesh* pMesh1 = m_pScene->GetResource()->FindMesh("BulletMesh");
        pMesh1->AllLightMaterialReset();
    }
    m_Mesh->SetMesh("BulletMesh");
    m_Mesh->SetWorldScale(1.f, 1.f, 1.f);

    SetDamage(10);
    SetDamageMax(20);
    m_Box->Enable(false);

    m_Sphere->Active(true);
    m_Box->SetCollisionProfile("MonsterAttack");
    m_Sphere->SetCollisionProfile("MonsterAttack");

    return true;
}

void CSniperBullet::Update(float DeltaTime)
{
    CAttackObject::Update(DeltaTime);

    if (!m_Setting)
    {
        m_Point = CPublicData::GetInst()->m_CurPlayer->GetWorldPos() - GetWorldPos();
        m_Setting = true;
        float Dir = CPublicData::GetInst()->DistanceToPlayer(GetWorldPos());
        m_Sphere->SetWorldRotation(GetWorldRotation());
        m_Sphere->SetRadius(0.1f);
        m_Mesh->AddWorldPos(0.f, 1.0f, 0.f);
        m_PrevPos = GetWorldPos();
    }
    else
    {
        if (m_NAttack)
            AddRelativePos(GetAxis(AXIS_Z) * -Sniper_BulletSpeed * DeltaTime);
        else
            AddRelativePos(GetAxis(AXIS_Z) * Sniper_BulletSpeed * DeltaTime);

        float Dir = m_PrevPos.Distance(GetWorldPos());
        if (Sniper_NAttack_Dir <= Dir)
        {
            this->Active(false);
        }
    }
}

void CSniperBullet::PostUpdate(float DeltaTime)
{
    CAttackObject::PostUpdate(DeltaTime);
}

void CSniperBullet::Collision(float DeltaTime)
{
    CAttackObject::Collision(DeltaTime);
}

void CSniperBullet::Render(float DeltaTime)
{
    CAttackObject::Render(DeltaTime);
}

CSniperBullet* CSniperBullet::Clone()
{
    return new CSniperBullet(*this);
}
