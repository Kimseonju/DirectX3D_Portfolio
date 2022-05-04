#pragma once
#include "IMGUIWidgetComponent.h"
#include "GameObject.h"
#include "Object/CameraMoveObject.h"
class CIMGUICameraMoveComponent :
	public CIMGUIWidgetComponent
{
public:
	CIMGUICameraMoveComponent();
	virtual ~CIMGUICameraMoveComponent();

private:
	CSharedPtr<CCameraMoveObject> m_Object;

	class CIMGUIListBox* m_MoveList;
	class CIMGUITextInput* m_MoveName;
	class CIMGUITextInput* m_NextName;
	class CIMGUITextInput* m_EndTimeInput;
	class CIMGUITextInput* m_StartLengthInput;
	class CIMGUITextInput* m_EndLengthInput;

	class CIMGUITextInput* m_StartPosYInput;
	class CIMGUITextInput* m_EndPosYInput;
	class CIMGUICheckBox* m_NextMoveCheckBox;

	class CIMGUIDrag* m_InputStartRotX;
	class CIMGUIDrag* m_InputStartRotY;
	class CIMGUIDrag* m_InputStartRotZ;

	class CIMGUIDrag* m_InputEndRotX;
	class CIMGUIDrag* m_InputEndRotY;
	class CIMGUIDrag* m_InputEndRotZ;

	class CIMGUIButton* m_StartRotButton;
	class CIMGUIButton* m_EndRotButton;

	class CIMGUIButton* m_CreateMoveButton;

	class CIMGUITextInput* m_TargetName;
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

	void StartRotBtnCallback();
	void EndRotBtnCallback();
	void CreateMoveBtnCallback();


	void MoveObjectCallback(int SelectIndex, const char* Item);
	void SelectTargetComboCallback(int SelectIndex, const char* Item);
	void InputSelectTargetPopupButton();

	void StartRotX();
	void StartRotY();
	void StartRotZ();

	void EndRotX();
	void EndRotY();
	void EndRotZ();
};
