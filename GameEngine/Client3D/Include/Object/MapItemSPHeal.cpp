#include "MapItemSPHeal.h"

CMapItemSPHeal::CMapItemSPHeal()
{
	m_Type = MapItemType::Coin;
}

CMapItemSPHeal::CMapItemSPHeal(const CMapItemSPHeal& obj) :
	CMapItem(obj)
{
}

CMapItemSPHeal::~CMapItemSPHeal()
{
}

void CMapItemSPHeal::Start()
{
	CMapItem::Start();
}

bool CMapItemSPHeal::Init()
{
	if (!CMapItem::Init())
		return false;

	//m_Mesh->SetMesh();
	return true;
}

void CMapItemSPHeal::Update(float DeltaTime)
{
	CMapItem::Update(DeltaTime);
}

void CMapItemSPHeal::PostUpdate(float DeltaTime)
{
	CMapItem::PostUpdate(DeltaTime);
}

void CMapItemSPHeal::Collision(float DeltaTime)
{
	CMapItem::Collision(DeltaTime);
}

void CMapItemSPHeal::PrevRender(float DeltaTime)
{
	CMapItem::PrevRender(DeltaTime);
}

void CMapItemSPHeal::Render(float DeltaTime)
{
	CMapItem::Render(DeltaTime);
}

CMapItemSPHeal* CMapItemSPHeal::Clone()
{
	return new CMapItemSPHeal(*this);
}
