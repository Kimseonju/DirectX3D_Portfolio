#pragma once
#include "IMGUIWidgetComponent.h"
#include "GameObject.h"
class CIMGUIColliderBox3DComponent :
	public CIMGUIWidgetComponent
{
public:
	CIMGUIColliderBox3DComponent();
	virtual ~CIMGUIColliderBox3DComponent();

private:
	class CColliderBox3D* m_Component;
	class CIMGUIDrag* m_InputLengthX;
	class CIMGUIDrag* m_InputLengthY;
	class CIMGUIDrag* m_InputLengthZ;
public:
	virtual void ComponentUpdateInfo(CSceneComponent* Component);
public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

public:
	void InputLengthX();
	void InputLengthY();
	void InputLengthZ();

};
