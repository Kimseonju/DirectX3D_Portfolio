#pragma once
#include "IMGUIWidgetComponent.h"
//Transform
class CIMGUITransformComponent :
	public CIMGUIWidgetComponent
{
public:
	CIMGUITransformComponent();
	virtual ~CIMGUITransformComponent();

private:
	class CIMGUIDrag* m_InputPosX;
	class CIMGUIDrag* m_InputPosY;
	class CIMGUIDrag* m_InputPosZ;

	class CIMGUIDrag* m_InputRotX;
	class CIMGUIDrag* m_InputRotY;
	class CIMGUIDrag* m_InputRotZ;

	class CIMGUIDrag* m_InputScaleX;
	class CIMGUIDrag* m_InputScaleY;
	class CIMGUIDrag* m_InputScaleZ;

	class CIMGUIDrag* m_InputPivotX;
	class CIMGUIDrag* m_InputPivotY;
	class CIMGUIDrag* m_InputPivotZ;

	
	class CSceneComponent* m_Component;
public:
	void SetPosition(const Vector3& Pos);
	void SetRotation(const Vector3& Pos);
	void SetScale(const Vector3& Pos);
	void SetPivot(const Vector3& Pos);
	virtual void ComponentUpdateInfo(CSceneComponent* Component);
public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

public:
	void InputPosX();
	void InputPosY();
	void InputPosZ();

	void InputRotX();
	void InputRotY();
	void InputRotZ();

	void InputScaleX();
	void InputScaleY();
	void InputScaleZ();


	void InputPivotX();
	void InputPivotY();
	void InputPivotZ();
};
