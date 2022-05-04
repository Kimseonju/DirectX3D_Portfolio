#pragma once
#include "IMGUIWidgetComponent.h"
#include "GameObject.h"
#include "Object/BossSpawnObject.h"
class CIMGUIBossSpawnObjectComponent :
	public CIMGUIWidgetComponent
{
public:
	CIMGUIBossSpawnObjectComponent();
	virtual ~CIMGUIBossSpawnObjectComponent();

private:
	CSharedPtr<CBossSpawnObject> m_Object;

	class CIMGUIListBox* m_MonsterList;
	class CIMGUITextInput* m_MonsterName; 
	class CIMGUIDrag* m_InputTimer;

	class CIMGUIDrag* m_InputPosX;
	class CIMGUIDrag* m_InputPosY;
	class CIMGUIDrag* m_InputPosZ;

	class CIMGUIDrag* m_InputRotX;
	class CIMGUIDrag* m_InputRotY;
	class CIMGUIDrag* m_InputRotZ;

	class CIMGUIDrag* m_InputScaleX;
	class CIMGUIDrag* m_InputScaleY;
	class CIMGUIDrag* m_InputScaleZ;

	class CIMGUIButton* m_CreateMonsterButton;

	class CIMGUIButton* m_CreateMoveButton;
	CGameObject* m_Target;
	Vector3 m_StartRot;
	Vector3 m_EndRot;
public:
	void UpdateInfo(CGameObject* Object);
	bool IsObject() const
	{
		if (!m_Object)
			return false;
		return true;
	}
public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

public:
	void CreateMonsterSpawnBtnCallback();


	void MonsterSpawnObjectCallback(int SelectIndex, const char* Item);
};
