
#include "Axe_Weapon.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Resource/Material.h"
#include "../PublicData.h"
#include "Resource/BoneSocket.h"
#include "Player.h"
#include "KnifeEffect.h"
CAxeWeapon::CAxeWeapon() :
    m_Setting(false),
    m_AttackType(Axe_AttState::None),
    m_LifeTime(0.f),
    m_Monster(nullptr),
    m_TAttack2(false)
{
}

CAxeWeapon::CAxeWeapon(const CAxeWeapon& obj) : CAttackObject(obj)
{
}

CAxeWeapon::~CAxeWeapon()
{
}

void CAxeWeapon::CollisionBegin(const HitResult& result, CCollider* Collider)
{
    if (result.DestCollider->GetProfile()->Name == "Player")
    {
        m_pScene->GetResource()->FindSound3D("Sniper_GunHit")->Play3D(m_Monster->GetWorldPos());

        {
            CKnifeEffect* HitEffect = m_pScene->SpawnObject<CKnifeEffect>("HitEffect");
            Vector3	Dir = (result.DestObject->GetWorldPos() + (result.DestObject->GetWorldScale() * 0.5f));
            HitEffect->SetWorldPos(Dir);

            if (m_AttackType == Axe_AttState::FAttack1||
                m_AttackType == Axe_AttState::FAttack2||
                m_AttackType == Axe_AttState::TAttack||
                m_AttackType == Axe_AttState::RAttack)
            {
                HitEffect->SetAxeAtt();
            }
        }
    }
}

void CAxeWeapon::CollisionMiddle(const HitResult& result, CCollider* Collider)
{
}

void CAxeWeapon::CollisionEnd(const HitResult& result, CCollider* Collider)
{
}

void CAxeWeapon::Start()
{
    CAttackObject::Start();
}

bool CAxeWeapon::Init()
{
    CAttackObject::Init();
    
    SetDamage(1);
    SetDamageMax(2);
    m_Box->Enable(true);
    m_Sphere->Active(false);
    m_Box->SetCollisionProfile("MonsterAttack");
    m_Sphere->SetCollisionProfile("MonsterAttack");
    {
        m_Texture = CreateSceneComponent<CBillboardComponent>("BillboardComponent");
        m_Root->AddChild(m_Texture);
        m_Texture->SetInheritPosZ(true);
        m_Texture->SetInheritRotX(true);
        m_Texture->SetInheritRotY(true);
        m_Texture->SetInheritRotZ(true);
        m_Texture->AddMaterial("Axe_RAttack");
        m_Texture->SetBillboardEnable(false);
        m_Texture->SetWorldScale(Vector3::One * 2.f);
        m_Texture->GetMaterial(0)->SetTransparency(true);
        m_Texture->Enable(false);
    }
    return true;
}

void CAxeWeapon::Update(float DeltaTime)
{
    CAttackObject::Update(DeltaTime);

    if (!m_Setting)
    {
        m_Setting = true;

        switch (m_AttackType)
        {
        case Axe_AttState::NAttack:
        {
            SetDamage(10);
            SetDamageMax(20);
            m_LifeTime = 0.1f;
            m_Box->SetExtent(0.4f, 1.0f, 0.5f);
            SetWorldPos(m_Monster->GetWorldPos());
            SetWorldRotation(m_Monster->GetWorldRotation());
            AddRelativePos(GetAxis(AXIS_X) * 0.f);
            AddRelativePos(GetAxis(AXIS_Y) * 0.5f);
            AddRelativePos(GetAxis(AXIS_Z) * -0.5f);
        }
            break;
        case Axe_AttState::FAttack1:
        {
            SetDamage(20);
            SetDamageMax(40);
            m_LifeTime = 0.1f;
            m_Box->SetExtent(1.f, 0.4f, 0.5f);
            SetWorldPos(m_Monster->GetWorldPos());
            SetWorldRotation(m_Monster->GetWorldRotation());
            AddRelativePos(GetAxis(AXIS_X) * 0.f);
            AddRelativePos(GetAxis(AXIS_Y) * 1.0f);
            AddRelativePos(GetAxis(AXIS_Z) * -0.5f);
        }
            break;
        case Axe_AttState::FAttack2:
        {
            SetDamage(20);
            SetDamageMax(60);
            m_LifeTime = 0.1f;
            m_Box->SetExtent(0.8f, 1.0f, 0.5f);
            SetWorldPos(m_Monster->GetWorldPos());
            SetWorldRotation(m_Monster->GetWorldRotation());
            AddRelativePos(GetAxis(AXIS_X) * 0.f);
            AddRelativePos(GetAxis(AXIS_Y) * 0.6f);
            AddRelativePos(GetAxis(AXIS_Z) * -0.5f);
        }
            break;
        case Axe_AttState::TAttack:
        {
            if (m_TAttack2)
            {
                SetDamage(40);
                SetDamageMax(60);
                m_LifeTime = 0.1f;
                m_Box->SetExtent(0.4f, 1.0f, 0.5f);
                SetWorldPos(m_Monster->GetWorldPos());
                SetWorldRotation(m_Monster->GetWorldRotation());
                AddRelativePos(GetAxis(AXIS_X) * 0.f);
                AddRelativePos(GetAxis(AXIS_Y) * 0.5f);
                AddRelativePos(GetAxis(AXIS_Z) * -0.5f);
            }
            else
            {
                SetDamage(10);
                SetDamageMax(20);
                m_LifeTime = 1.f;
                m_Box->SetExtent(0.5f, 1.0f, 0.5f);
                SetWorldPos(m_Monster->GetWorldPos());
                SetWorldRotation(m_Monster->GetWorldRotation());
                AddRelativePos(GetAxis(AXIS_X) * 0.f);
                AddRelativePos(GetAxis(AXIS_Y) * 0.5f);
                AddRelativePos(GetAxis(AXIS_Z) * 0.f);
            }
        }
            break;
        case Axe_AttState::RAttack:
        {
            SetDamage(50);
            SetDamageMax(100);
            m_LifeTime = 3.0f;
            m_Box->SetExtent(1.f, 0.4f, 0.5f);
            SetWorldPos(m_Monster->GetWorldPos());
            SetWorldRotation(m_Monster->GetWorldRotation());
            AddRelativePos(GetAxis(AXIS_X) * 0.f);
            AddRelativePos(GetAxis(AXIS_Y) * 1.0f);
            AddRelativePos(GetAxis(AXIS_Z) * -0.5f);
            m_Texture->Enable(true);
            m_Texture->AddWorldRotationX(90.f);
            m_Texture->AddWorldRotationY(90.f);
        }
            break;
        }
    }
    else
    {
        m_LifeTime -= DeltaTime;
        //m_Texture->AddWorldRotationX(180.f * DeltaTime);
        switch (m_AttackType)
        {
        case Axe_AttState::NAttack:
        {


            if (0 >= m_LifeTime)
                this->Active(false);
        }
        break;
        case Axe_AttState::FAttack1:
        {


            if (0 >= m_LifeTime)
                this->Active(false);
        }
        break;
        case Axe_AttState::FAttack2:
        {


            if (0 >= m_LifeTime)
                this->Active(false);
        }
        break;
        case Axe_AttState::TAttack:
        {
            if (!m_TAttack2)
            {
                SetWorldPos(m_Monster->GetWorldPos());
                SetWorldRotation(m_Monster->GetWorldRotation());
                AddRelativePos(GetAxis(AXIS_Y) * 0.5f);
            }

            if (0 >= m_LifeTime)
                this->Active(false);
        }
        break;
        case Axe_AttState::RAttack:
        {

            AddRelativePos(GetAxis(AXIS_Z) *  10.f * -DeltaTime);

            if (0 >= m_LifeTime)
                this->Active(false);
        }
        break;
        }
    }
}

void CAxeWeapon::PostUpdate(float DeltaTime)
{
    CAttackObject::PostUpdate(DeltaTime);

    if (GetAsyncKeyState(VK_NUMPAD4)& 0x8000)
    {
        m_Box->AddWorldRotationX(10.f * DeltaTime);
    }
    if (GetAsyncKeyState(VK_NUMPAD5) & 0x8000)
    {
        m_Box->AddWorldRotationY(10.f * DeltaTime);
    }
    if (GetAsyncKeyState(VK_NUMPAD6) & 0x8000)
    {
        m_Box->AddWorldRotationZ(10.f * DeltaTime);
    }
    if (GetAsyncKeyState(VK_NUMPAD1) & 0x8000)
    {
        m_Box->AddWorldRotationX(-10.f * DeltaTime);
    }
    if (GetAsyncKeyState(VK_NUMPAD2) & 0x8000)
    {
        m_Box->AddWorldRotationY(-10.f * DeltaTime);
    }
    if (GetAsyncKeyState(VK_NUMPAD3) & 0x8000)
    {
        m_Box->AddWorldRotationZ(-10.f * DeltaTime);
    }

    Vector3 BosRot = m_Box->GetWorldRotation();
}

void CAxeWeapon::Collision(float DeltaTime)
{
    CAttackObject::Collision(DeltaTime);
}

void CAxeWeapon::Render(float DeltaTime)
{
    CAttackObject::Render(DeltaTime);
}

CAxeWeapon* CAxeWeapon::Clone()
{
    return new CAxeWeapon(*this);
}
