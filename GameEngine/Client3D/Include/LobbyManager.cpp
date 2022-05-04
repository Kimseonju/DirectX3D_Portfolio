#include "LobbyManager.h"
#include "Object/LobbyShip.h"
#include "Object/LobbyValkyrieSelectZone.h"
DEFINITION_SINGLE(CLobbyManager);

CLobbyManager::CLobbyManager():
	m_LoadingStartObject(nullptr),
	m_SelectZone(nullptr),
	m_Ship(nullptr)
{
}
CLobbyManager::~CLobbyManager()
{
}

Vector3 CLobbyManager::GetSelectCameraPos()
{
	if (!m_SelectZone)
		return Vector3::Zero;

	return m_SelectZone->GetCameraPos();
}

Vector3 CLobbyManager::GetShipCameraPos()
{
	if (!m_Ship)
		return Vector3::Zero;

	return m_Ship->GetLobbyCameraPos();
}

void CLobbyManager::ChangeValkyrieSelect(const std::string& Name)
{
	if(m_SelectZone)
		m_SelectZone->ChangeValkrie(Name);
}
