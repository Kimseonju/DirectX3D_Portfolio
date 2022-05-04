#pragma once
#include "IMGUIWidgetComponent.h"
#include "GameObject.h"
class CIMGUIColliderSphereComponent :
	public CIMGUIWidgetComponent
{
public:
	CIMGUIColliderSphereComponent();
	virtual ~CIMGUIColliderSphereComponent();

private:
	class CColliderSphere* m_Component;
	class CIMGUIDrag* m_InputRadius;
public:
	virtual void ComponentUpdateInfo(CSceneComponent* Component);
public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

public:
	void InputRadius();
};
