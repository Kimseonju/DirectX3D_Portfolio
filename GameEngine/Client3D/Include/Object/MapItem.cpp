#include "MapItem.h"

CMapItem::CMapItem():
	m_Target(nullptr)
{
}

CMapItem::CMapItem(const CMapItem& obj) :
	CClientObject(obj)
{
	m_Root = (CSceneComponent*)FindSceneComponent("Root");
	m_Mesh = (CStaticMeshComponent*)FindSceneComponent("Mesh");
	m_Body = (CColliderBox3D*)FindSceneComponent("Body");
}

CMapItem::~CMapItem()
{
}

void CMapItem::Start()
{
	CClientObject::Start();
}

bool CMapItem::Init()
{
	if (!CClientObject::Init())
		return false;

	m_Root = CreateSceneComponent<CSceneComponent>("Root");
	m_Mesh = CreateSceneComponent<CStaticMeshComponent>("Mesh");
	m_Body = CreateSceneComponent<CColliderBox3D>("Body");


	SetRootComponent(m_Root);

	m_Root->AddChild(m_Body);
	m_Body->SetExtent(0.2f, 0.2f, 0.2f);
	m_Body->SetCollisionProfile("MapItem");
	m_Body->AddChild(m_Mesh);

	m_Mesh->SetWorldScale(1.f, 1.f, 1.f);
	m_Mesh->SetWorldPos(0.f, 0.f, 0.f);
	m_Mesh->SetRelativeRotation(-90.f, 0.f, 0.f);


	m_Body->AddCollisionCallbackFunction<CMapItem>(Collision_State::Begin, this,
		&CMapItem::CollisionBegin);
	return true;
}

void CMapItem::Update(float DeltaTime)
{
	CClientObject::Update(DeltaTime);
	//범위 안에 있으면 플레이어에게 날라간다
	if (!m_Target)
	{
		CClientObject* Player = CPublicData::GetInst()->GetCurPlayer();
		Vector3 Dir= Player->GetWorldPos() - GetWorldPos();
		float Length = Dir.Length();
		if (Length > 1.f)
		{
			m_Target = Player;
		}
	}
	else
	{
		//플레이어 바뀌더라도 날라가게 추가
		m_Target = CPublicData::GetInst()->GetCurPlayer();
		Vector3 Dir = m_Target->GetWorldPos() - GetWorldPos();
		Dir.Normalize();

		AddWorldPos(Dir * 1.f * DeltaTime);
	}
}

void CMapItem::PostUpdate(float DeltaTime)
{
	CClientObject::PostUpdate(DeltaTime);
}

void CMapItem::Collision(float DeltaTime)
{
	CClientObject::Collision(DeltaTime);
}

void CMapItem::PrevRender(float DeltaTime)
{
	CClientObject::PrevRender(DeltaTime);
}

void CMapItem::Render(float DeltaTime)
{
	CClientObject::Render(DeltaTime);
}

CMapItem* CMapItem::Clone()
{
	return new CMapItem(*this);
}

void CMapItem::CollisionBegin(const HitResult& result, CCollider* Collider)
{
	Active(false);
}
