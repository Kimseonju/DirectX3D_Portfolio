#include "MapCollision.h"

CMapCollision::CMapCollision()
{
	m_ClientClassType = ClientClassType::MapCollision;
}

CMapCollision::CMapCollision(const CMapCollision& obj) :
	CClientObject(obj)
{
}

CMapCollision::~CMapCollision()
{
}

void CMapCollision::SetMatrixPos(const Matrix& mat)
{
	Matrix mmat;
	mmat = mmat.GetXMMatrixDecompose(mat);

	m_CollisionBox3D->SetWorldPos(Vector3(mmat[0][0], mmat[0][1], mmat[0][2]));
}

void CMapCollision::SetLength(float X, float Y, float Z)
{
	m_CollisionBox3D->SetExtent(X, Y, Z);
}

void CMapCollision::SetWorldScale(const Vector3& Scale)
{
	CClientObject::SetWorldScale(Scale);
	m_CollisionBox3D->SetWorldScale(Scale);
}

void CMapCollision::Enable(bool bEnable)
{
	CClientObject::Enable(bEnable);
	m_CollisionBox3D->Enable(bEnable);
}

void CMapCollision::Start()
{
	CClientObject::Start();
}

bool CMapCollision::Init()
{
	CClientObject::Init();
	m_CollisionBox3D = CreateSceneComponent<CColliderBox3D>("Box3D");
	SetRootComponent(m_CollisionBox3D);
	m_CollisionBox3D->SetTransformState(Transform_State::None);
	m_CollisionBox3D->SetCollisionProfile("CollisionBlock");



	m_CollisionBox3D->AddCollisionCallbackFunction<CMapCollision>(Collision_State::Begin, this,
		&CMapCollision::CollisionBegin);
	m_CollisionBox3D->AddCollisionCallbackFunction<CMapCollision>(Collision_State::Middle, this,
		&CMapCollision::CollisionMiddle);
	m_CollisionBox3D->AddCollisionCallbackFunction<CMapCollision>(Collision_State::End, this,
		&CMapCollision::CollisionEnd);
	return true;
}

void CMapCollision::Update(float DeltaTime)
{
	//m_CollisionBox3D->SetDebugRender(true);
	CClientObject::Update(DeltaTime);
}

void CMapCollision::PostUpdate(float DeltaTime)
{
	CClientObject::PostUpdate(DeltaTime);
}

void CMapCollision::Collision(float DeltaTime)
{
	CClientObject::Collision(DeltaTime);
}

void CMapCollision::Render(float DeltaTime)
{
	CClientObject::Render(DeltaTime);
}

CMapCollision* CMapCollision::Clone()
{
	return new CMapCollision(*this);
}

void CMapCollision::CollisionBegin(const HitResult& result, CCollider* Collider)
{
	Vector3 MovePos = result.DestObject->GetVelocity();

	result.DestObject->AddWorldPos(MovePos*-1.f);
}

void CMapCollision::CollisionMiddle(const HitResult& result, CCollider* Collider)
{
	Vector3 MovePos = result.DestObject->GetVelocity();

	result.DestObject->AddWorldPos(MovePos * -1.f);
}

void CMapCollision::CollisionEnd(const HitResult& result, CCollider* Collider)
{
}
