#pragma once
#include "GameEngine.h"
#include "Global.h"
#include "Object/Player.h"
class CLobbyManager
{
private:
	class CLoadingStartObject* m_LoadingStartObject;
	class CLobbyValkyrieSelectZone* m_SelectZone;
	class CLobbyShip* m_Ship;
public:
	void SetLoadingStartObject(class CLoadingStartObject* LoadingStartObject)
	{
		m_LoadingStartObject = LoadingStartObject;
	}
	void SetShip(class CLobbyShip* Ship)
	{
		m_Ship = Ship;
	}
	void SetValkyrieSelectZone(class CLobbyValkyrieSelectZone* SelectZone)
	{
		m_SelectZone = SelectZone;
	}
	
	class CLoadingStartObject* GetLoadingStartObject()
	{
		return m_LoadingStartObject;
	}
	class CLobbyShip* GetLobbyShip()
	{
		return m_Ship;
	}
	class CLobbyValkyrieSelectZone* GetValkyrieSelectZone()
	{
		return m_SelectZone;
	}
	Vector3 GetSelectCameraPos();
	Vector3 GetShipCameraPos();

	void ChangeValkyrieSelect(const std::string& Name);
	DECLARE_SINGLE(CLobbyManager);
};
