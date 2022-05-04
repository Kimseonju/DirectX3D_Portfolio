#include "MapItemHeal.h"

CMapItemHeal::CMapItemHeal()
{
	m_Type = MapItemType::Heal;
}

CMapItemHeal::CMapItemHeal(const CMapItemHeal& obj) :
	CMapItem(obj)
{
}

CMapItemHeal::~CMapItemHeal()
{
}

void CMapItemHeal::Start()
{
	CMapItem::Start();
}

bool CMapItemHeal::Init()
{
	if (!CMapItem::Init())
		return false;

	//m_Mesh->SetMesh();
	return true;
}

void CMapItemHeal::Update(float DeltaTime)
{
	CMapItem::Update(DeltaTime);
}

void CMapItemHeal::PostUpdate(float DeltaTime)
{
	CMapItem::PostUpdate(DeltaTime);
}

void CMapItemHeal::Collision(float DeltaTime)
{
	CMapItem::Collision(DeltaTime);
}

void CMapItemHeal::PrevRender(float DeltaTime)
{
	CMapItem::PrevRender(DeltaTime);
}

void CMapItemHeal::Render(float DeltaTime)
{
	CMapItem::Render(DeltaTime);
}

CMapItemHeal* CMapItemHeal::Clone()
{
	return new CMapItemHeal(*this);
}
