
#include "Monster.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Resource/Material.h"
#include "AttackObject.h"
#include "../UI/UIDamageText.h"
#include "HitEffect.h"
#include "KnifeEffect.h"
CMonster::CMonster() : m_Setting(false), m_Hp(30)
{
}

CMonster::CMonster(const CMonster& obj) : CClientObject(obj)
{
    m_Root = (CAnimationMeshComponent*)FindSceneComponent("Root");
    m_Body = (CColliderBox3D*)FindSceneComponent("Box3D");
    m_Mesh = (CAnimationMeshComponent*)FindSceneComponent("Mesh");
}

CMonster::~CMonster()
{
}

void CMonster::Start()
{
    CClientObject::Start();
}

bool CMonster::Init()
{
    CClientObject::Init();

    m_Root = CreateSceneComponent<CSceneComponent>("Root");
    m_Mesh = CreateSceneComponent<CAnimationMeshComponent>("Mesh");
    // m_Body = CreateSceneComponent<CColliderSphere>("Body");
    m_Body = CreateSceneComponent<CColliderBox3D>("Box3D");
    m_MapBody = CreateSceneComponent<CColliderBox3D>("MapCollision");
    
    SetRootComponent(m_Root);
    m_Root->AddChild(m_Mesh);
    m_Mesh->AddChild(m_Body);
    m_Body->AddRelativePos(0.f, 1.f, 0.f);
	m_Body->SetCollisionProfile("Monster");

	m_Body->AddCollisionCallbackFunction<CMonster>(Collision_State::Begin, this,&CMonster::CollisionBegin);
	m_Body->AddCollisionCallbackFunction<CMonster>(Collision_State::Middle, this,&CMonster::CollisionMiddle);
	m_Body->AddCollisionCallbackFunction<CMonster>(Collision_State::End, this,&CMonster::CollisionEnd);

    m_Body->AddChild(m_MapBody);
    m_MapBody->SetInheritPosZ(true);
    m_MapBody->SetInheritRotX(true);
    m_MapBody->SetInheritRotY(true);
    m_MapBody->SetInheritRotZ(true);
    m_MapBody->SetExtent(0.f, 0.f, 0.f);
    m_MapBody->SetCollisionProfile("MapCollision");

    m_MapBody->Enable(true);
    return true;
}

void CMonster::Update(float DeltaTime)
{
    //DeltaTime *= CStageManager::GetInst()->GetWorldSpeed();
    CClientObject::Update(DeltaTime);

}

void CMonster::PostUpdate(float DeltaTime)
{
    CClientObject::PostUpdate(DeltaTime);
}

void CMonster::Collision(float DeltaTime)
{
    CClientObject::Collision(DeltaTime);
}

void CMonster::Render(float DeltaTime)
{
    CClientObject::Render(DeltaTime);
}

CMonster* CMonster::Clone()
{
    return new CMonster(*this);
}

void CMonster::CollisionBegin(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Name == "PlayerAttack")
	{
        {
            CKnifeEffect* HitEffect = m_pScene->SpawnObject<CKnifeEffect>("HitEffect");
            Vector3	Dir = (GetWorldPos() + (GetWorldScale() * 0.5f));
            HitEffect->SetWorldPos(Dir);
        }
	}
}

void CMonster::CollisionMiddle(const HitResult& result, CCollider* Collider)
{
}

void CMonster::CollisionEnd(const HitResult& result, CCollider* Collider)
{
}

void CMonster::CreateHitDamage(int Damage)
{
    CUIDamageText * UIText=m_pScene->GetViewport()->AddWindow<CUIDamageText>("Damage");

    UIText->SetDamage(Damage);
    CCamera* Camera=m_pScene->GetCameraManager()->GetCurrentCamera();
    Vector2 UIPos=Camera->WorldToScreen(this->GetWorldPos());
    UIText->SetPos(UIPos);
}

void CMonster::CreateHitBillboard(const Vector3& Pos)
{
    CHitEffect* Effect = m_pScene->SpawnObject<CHitEffect>("HitEffect");
    Effect->SetWorldPos(Pos);
}
