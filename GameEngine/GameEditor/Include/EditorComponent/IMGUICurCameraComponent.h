#pragma once
#include "IMGUIWidgetComponent.h"
//Transform
class CIMGUICurCameraComponent :
	public CIMGUIWidgetComponent
{
public:
	CIMGUICurCameraComponent();
	virtual ~CIMGUICurCameraComponent();

private:
	class CIMGUIDrag* m_InputPosX;
	class CIMGUIDrag* m_InputPosY;
	class CIMGUIDrag* m_InputPosZ;

	class CIMGUIDrag* m_InputRotX;
	class CIMGUIDrag* m_InputRotY;
	class CIMGUIDrag* m_InputRotZ;
public:

	void SetPosition(const Vector3& Pos);
	void SetRotation(const Vector3& Rotation);

	const Vector3 GetPosition();
	const Vector3 GetRotation();
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
};
