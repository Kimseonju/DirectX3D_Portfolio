#pragma once
#include "IMGUIWidgetComponent.h"
//Transform
class CIMGUIGizmoComponent :
	public CIMGUIWidgetComponent
{
public:
	CIMGUIGizmoComponent();
	virtual ~CIMGUIGizmoComponent();

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
	class CIMGUIRadioButton* m_GizmoOperation;
	class CIMGUIGizmo* m_Gizmo;
public:
	class CSceneComponent* GetComponent()
	{
		return m_Component;
	}
	void SetGizmo(class CIMGUIGizmo* Gizmo)
	{
		m_Gizmo = Gizmo;
	}

	void SetPosition(const Vector3& Pos);
	void SetRotation(const Vector3& Rotation);
	void SetScale(const Vector3& Scale);
	void SetPivot(const Vector3& Pos);
	void SetComponent(class CSceneComponent* Component);

	const Vector3 GetPosition();
	const Vector3 GetRotation();
	const Vector3 GetScale();
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
public:

	void GizmoOperationListCallback(int SelectIndex, const char* Item);
};
