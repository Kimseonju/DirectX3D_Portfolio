#include "PublicData.h"
#include "Object/Player.h"
#include "DataTable/PlayerDataTable.h"
#include "DataTable/ItemDataTable.h"
DEFINITION_SINGLE(CPublicData);

CPublicData::CPublicData():
	m_CurPlayer(nullptr),
	Axe_ResourceCheck(false),
	Sniper_ResourceCheck(false),
	Wendy_ResourceCheck(false),
	m_Crystal(10000),
	m_Gold(10000),
	Bullet_ResourceCheck(false)
{
	m_PlayerDataTable = new CPlayerDataTable;
	m_PlayerDataTable->Init();

	m_ItemDataTable = new CItemDataTable;
	m_ItemDataTable->Init();

}
CPublicData::~CPublicData()
{
	SAFE_DELETE(m_PlayerDataTable);
	SAFE_DELETE(m_ItemDataTable);
	m_mapPlayer.clear();
}

float CPublicData::DistanceToPlayer(Vector3 Target)
{
	if (m_CurPlayer)
	{
		return  m_CurPlayer->GetWorldPos().Distance(Target);
	}
	else
		return 0.f;
	
}

float CPublicData::AngleToPlayer(Vector3 Target)
{
	if (m_CurPlayer)
	{
		return  m_CurPlayer->GetWorldPos().Dot(Target);
	}
	else
		return 0.f;
}

Vector3 CPublicData::MoveToPlayer(Vector3 Target)
{
	return Vector3();
}

PlayerStatus* CPublicData::FindPlayerData(const std::string& Name)
{
	return m_PlayerDataTable->FindData(Name);
}

CPlayer* CPublicData::GetPlayer(int Index)
{
	auto iter = m_mapPlayer.find(Index);

	if (iter == m_mapPlayer.end())
	{
		return nullptr;
	}
	return iter->second;


}

CPlayer* CPublicData::GetNextPlayer()
{
	auto iter = m_mapPlayer.begin();
	auto iterEnd = m_mapPlayer.end();
	for (; iter != iterEnd; ++iter)
	{
		if (iter->second->GetStatus()->HP>0 && iter->second!=m_CurPlayer)
		{
			return iter->second;
		}
	}
	return nullptr;
}

