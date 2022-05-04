
#include "AttackObject.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Resource/Material.h"

CAttackObject::CAttackObject() : 
    m_Damage(5), 
    m_DamageMax(10),
    m_MonsterAttack(true)
{
}

CAttackObject::CAttackObject(const CAttackObject& obj) : CClientObject(obj)
{
    m_Root = (CSceneComponent*)FindSceneComponent("Root");
    m_Mesh = (CStaticMeshComponent*)FindSceneComponent("Mesh");
    m_Box = (CColliderBox3D*)FindSceneComponent("Box");
    m_Sphere = (CColliderSphere*)FindSceneComponent("Sphere");
}

CAttackObject::~CAttackObject()
{
}

void CAttackObject::CollisionBegin(const HitResult& result, CCollider* Collider)
{
}

void CAttackObject::CollisionMiddle(const HitResult& result, CCollider* Collider)
{
}

void CAttackObject::CollisionEnd(const HitResult& result, CCollider* Collider)
{
}

void CAttackObject::Start()
{
    CClientObject::Start();
}

bool CAttackObject::Init()
{
    CClientObject::Init();

    m_Root = CreateSceneComponent<CSceneComponent>("Root");
    m_Mesh = CreateSceneComponent<CStaticMeshComponent>("Mesh");
    m_Sphere = CreateSceneComponent<CColliderSphere>("Sphere");
    m_Box = CreateSceneComponent<CColliderBox3D>("Box3D");

    SetRootComponent(m_Root);
    m_Root->AddChild(m_Mesh);
    m_Mesh->AddChild(m_Box);
    m_Mesh->AddChild(m_Sphere);
    m_Box->SetWorldScale(Vector3::Zero);
    m_Sphere->SetWorldScale(Vector3::Zero);
    m_Box->SetCollisionProfile("AttackObject");
    m_Sphere->SetCollisionProfile("AttackObject");
    m_Mesh->SetInheritRotX(true);
    m_Mesh->SetInheritRotY(true);
    m_Mesh->SetInheritRotZ(true);
    m_Box->SetInheritRotX(true);
    m_Box->SetInheritRotY(true);
    m_Box->SetInheritRotZ(true);

    m_Sphere->AddCollisionCallbackFunction(Collision_State::Begin, this, &CAttackObject::CollisionBegin);
    m_Sphere->AddCollisionCallbackFunction(Collision_State::End, this, &CAttackObject::CollisionEnd);
    m_Sphere->AddCollisionCallbackFunction(Collision_State::Middle, this, &CAttackObject::CollisionMiddle);
    m_Box->AddCollisionCallbackFunction(Collision_State::Begin, this, &CAttackObject::CollisionBegin);
    m_Box->AddCollisionCallbackFunction(Collision_State::End, this, &CAttackObject::CollisionEnd);
    m_Box->AddCollisionCallbackFunction(Collision_State::Middle, this, &CAttackObject::CollisionMiddle);
    //SetLifeTime(1.f);
    return true;
}

void CAttackObject::Update(float DeltaTime)
{
    CClientObject::Update(DeltaTime);
}

void CAttackObject::PostUpdate(float DeltaTime)
{
    CClientObject::PostUpdate(DeltaTime);
}

void CAttackObject::Collision(float DeltaTime)
{
    CClientObject::Collision(DeltaTime);
}

void CAttackObject::Render(float DeltaTime)
{
    CClientObject::Render(DeltaTime);
}

CAttackObject* CAttackObject::Clone()
{
    return new CAttackObject(*this);
}

void CAttackObject::SetBox3DLength(float x, float y, float z)
{
    m_Box->SetExtent(x, y, z);
}

void CAttackObject::SetMatrixPos(const Matrix& mat)
{
    Matrix mmat;
    mmat = mmat.GetXMMatrixDecompose(mat);
    m_Root->SetWorldPos(Vector3(mmat[0][0], mmat[0][1], mmat[0][2]));
}

int CAttackObject::GetDamage()
{
    return GetRandom(m_Damage, m_DamageMax);
}
