
#include "SniperGrenade.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Resource/Material.h"
#include "../PublicData.h"
#include "Resource/BoneSocket.h"
#include "Player.h"
#include "ExplosionEffect.h"

CSniperGrenade::CSniperGrenade() :
    m_Setting(false),
    m_Up(false),
    m_Speed(1.0f),
    m_MinY(0.f),
    m_Check1(false),
    m_Move(true),
    m_Sound(false)
{
}

CSniperGrenade::CSniperGrenade(const CSniperGrenade& obj) : CAttackObject(obj)
{
}

CSniperGrenade::~CSniperGrenade()
{
}

void CSniperGrenade::Start()
{
    CAttackObject::Start();
}

bool CSniperGrenade::Init()
{
    CAttackObject::Init();
    
    m_Mesh->SetMesh("SpherePos");
    m_Mesh->AddMaterial("SniperBullet");
    m_Mesh->SetWorldScale(0.1f, 0.1f, 0.1f);
    m_Box->SetCollisionProfile("MonsterAttack");
    m_Sphere->SetCollisionProfile("MonsterAttack");
	m_Box->Enable(false);
    m_Sphere->Enable(false);
	m_Box->SetCollisionProfile("AttackObject");
	m_Sphere->SetCollisionProfile("MonsterAttack");
    SetDamage(30);
    SetDamageMax(50);
    return true;
}

void CSniperGrenade::Update(float DeltaTime)
{
    CAttackObject::Update(DeltaTime);
    if (!m_Setting)
    {
        m_Setting = true;
        m_Sphere->SetWorldScale(0.f, 0.f, 0.f);
        m_Mesh->AddWorldPos(0.f, 1.f, 0.f);
    }
    if (!m_Up)
    {
        m_Speed -= DeltaTime * 3.f;
        m_Mesh->AddRelativePos(GetAxis(AXIS_Y)  * m_Speed * 10.f * DeltaTime);
        if (0 >= m_Speed)
            m_Up = true;
    }
    else
    {
        if (m_Mesh->GetWorldPos().y <= m_MinY)
        {
     
              m_Sphere->Enable(true);
              static float CollSizeSpeed = 0.001f;

            if (!m_Check1)
            {
                if (!m_Sound)
                {
                    m_Sound = true;
                    m_pScene->GetResource()->FindSound3D("Sniper_GrenadeBoom2")->Play3D(m_Mesh->GetWorldPos());

                    {
                        CExplosionEffect* Effect = m_pScene->SpawnObject<CExplosionEffect>("Effect");
                        Effect->SetEffectType(ExplosionEffectType::Type_2);
                        Effect->SetWorldPos(m_Mesh->GetWorldPos());
                        Effect->SetEffectMultScale(2.f);
                    }
                }
                m_Move = false;
                CollSizeSpeed += DeltaTime * 3.f;
                m_Sphere->SetRadius(CollSizeSpeed * 1.5f);

                if (1.f <= CollSizeSpeed)
                {
                    m_Check1 = true;
                }
            }
            else
            {
                CollSizeSpeed -= DeltaTime * 3.f;
                m_Sphere->SetRadius(CollSizeSpeed * 1.5f);

                if (0.f >= CollSizeSpeed)
                {
                    this->Active(false);
                }
            }
           
        }
        else
        {
            m_Speed -= DeltaTime * 3.f;
            m_Mesh->AddRelativePos(GetAxis(AXIS_Y) * m_Speed * 10.f * DeltaTime);
        }
    }

    if (m_Move)
        m_Mesh->AddRelativePos(GetAxis(AXIS_Z) * -5.f * DeltaTime);
    //AddRelativePos(GetAxis(AXIS_Z) * (- 3 * DeltaTime));
    //AddRelativePos(GetAxis(AXIS_Y) * -500 * DeltaTime);

}

void CSniperGrenade::PostUpdate(float DeltaTime)
{
    CAttackObject::PostUpdate(DeltaTime);
}

void CSniperGrenade::Collision(float DeltaTime)
{
    CAttackObject::Collision(DeltaTime);
}

void CSniperGrenade::Render(float DeltaTime)
{
    CAttackObject::Render(DeltaTime);
}

CSniperGrenade* CSniperGrenade::Clone()
{
    return new CSniperGrenade(*this);
}


void CSniperGrenade::CollisionBegin(const HitResult& result, CCollider* Collider)
{
    if (result.DestCollider->GetProfile()->Name == "Player")
    {
        m_pScene->GetResource()->FindSound3D("Sniper_GrenadeBoom")->Play3D(m_Mesh->GetWorldPos());
        m_Sphere->Enable(false);
        m_Box->Enable(false);
        m_Mesh->Enable(false);
    }
}

void CSniperGrenade::CollisionMiddle(const HitResult& result, CCollider* Collider)
{
}

void CSniperGrenade::CollisionEnd(const HitResult& result, CCollider* Collider)
{
}