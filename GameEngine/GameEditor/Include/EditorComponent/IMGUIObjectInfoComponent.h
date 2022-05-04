#pragma once
#include "IMGUIWidgetComponent.h"
#include "GameObject.h"
class CIMGUIObjectInfoComponent :
	public CIMGUIWidgetComponent
{
public:
	CIMGUIObjectInfoComponent();
	virtual ~CIMGUIObjectInfoComponent();

private:
	class CIMGUITextInput* m_ObjectName;
	class CIMGUICheckBox* m_EnableCheckBox;
	CSharedPtr<CGameObject> m_Object;

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
	void InputObjectName();
	void EnableCheckBoxClick(bool Enable);
};
