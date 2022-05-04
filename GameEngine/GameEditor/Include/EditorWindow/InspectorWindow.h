#pragma once
#include "IMGUIWindow.h"
#include "GameEngine.h"
class CInspectorWindow :
	public CIMGUIWindow
{
public:
	CInspectorWindow();
	virtual ~CInspectorWindow();

private:
	std::map<std::string, class CIMGUIWidgetComponent*> m_IMGUIComponent;
	class CIMGUIObjectInfoComponent* m_Object;
	class CIMGUICameraMoveComponent* m_CameraMoveObject;
	class CIMGUIMonsterSpawnObjectComponent* m_MonsterSpawnObject;
	class CIMGUIColliderSpawnObjectComponent* m_ColliderSpawnObject;
	class CIMGUIBossSpawnObjectComponent* m_BossSpawnObject;
public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	void ObjectUpdateInfo(class CGameObject* Obj);
	void CameraMoveUpdateInfo(class CGameObject* Obj);
	void MonsterSpawnUpdateInfo(class CGameObject* Obj);
	void ColliderSpawnUpdateInfo(class CGameObject* Obj);
	void BossSpawnUpdateInfo(class CGameObject* Obj);
	void ComponentUpdateInfo(const std::string& Name, class CSceneComponent* Component);


	void CreateComponent();

	void AllComponentClose();
	
};
