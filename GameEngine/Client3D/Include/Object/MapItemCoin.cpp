#include "MapItemCoin.h"

CMapItemCoin::CMapItemCoin() 
{
	m_Type = MapItemType::Coin;
}

CMapItemCoin::CMapItemCoin(const CMapItemCoin& obj) :
	CMapItem(obj)
{
}

CMapItemCoin::~CMapItemCoin()
{
}

void CMapItemCoin::Start()
{
	CMapItem::Start();
}

bool CMapItemCoin::Init()
{
	if (!CMapItem::Init())
		return false;

	//m_Mesh->SetMesh();
	return true;
}

void CMapItemCoin::Update(float DeltaTime)
{
	CMapItem::Update(DeltaTime);
}

void CMapItemCoin::PostUpdate(float DeltaTime)
{
	CMapItem::PostUpdate(DeltaTime);
}

void CMapItemCoin::Collision(float DeltaTime)
{
	CMapItem::Collision(DeltaTime);
}

void CMapItemCoin::PrevRender(float DeltaTime)
{
	CMapItem::PrevRender(DeltaTime);
}

void CMapItemCoin::Render(float DeltaTime)
{
	CMapItem::Render(DeltaTime);
}

CMapItemCoin* CMapItemCoin::Clone()
{
	return new CMapItemCoin(*this);
}
