#include "../pch.h"
#include "IMGUICameraMoveComponent.h"
#include "IMGUICollapsingHeader.h"
#include "IMGUIText.h"
#include "IMGUITextInput.h"
#include "IMGUISameLine.h"
#include "IMGUICheckBox.h"
#include "IMGUIListBox.h"
#include "IMGUIButton.h"
#include "IMGUIComboBox.h"
#include "IMGUIManager.h"
#include "IMGUIDrag.h"
#include "../EditorWindow/ObjectWindow.h"
#include "Scene/Scene.h"
#include "Scene/CameraManager.h"
#include "Scene/SceneManager.h"

CIMGUICameraMoveComponent::CIMGUICameraMoveComponent():
	m_MoveList(nullptr),
	m_MoveName(nullptr),
	m_NextName(nullptr),
	m_EndTimeInput(nullptr),
	m_StartLengthInput(nullptr),
	m_StartPosYInput(nullptr),
	m_EndPosYInput(nullptr),
	m_NextMoveCheckBox(nullptr),
	m_InputStartRotX(nullptr),
	m_InputStartRotY(nullptr),
	m_InputStartRotZ(nullptr),
	m_InputEndRotX(nullptr),
	m_InputEndRotY(nullptr),
	m_InputEndRotZ(nullptr),
	m_StartRotButton(nullptr),
	m_EndRotButton(nullptr),
	m_CreateMoveButton(nullptr),
	m_TargetName(nullptr),
	m_Target(nullptr)
{
}

CIMGUICameraMoveComponent::~CIMGUICameraMoveComponent()
{
}

void CIMGUICameraMoveComponent::UpdateInfo(CGameObject* Object)
{
	CCameraMoveObject* Obj = (CCameraMoveObject*)Object;
	m_Object = Obj;
	if (!m_Object)
	{
		return;
	}
}

bool CIMGUICameraMoveComponent::Init()
{
	CIMGUIWidgetComponent::Init();
	CIMGUIText* Text;
	CIMGUISameLine* SameLine;

	m_Header = m_Owner->AddWidget<CIMGUICollapsingHeader>("CameraMove");


	m_MoveList = AddComponentWidget<CIMGUIListBox>("ObjectListBox", 300.f, 100.f);
	m_MoveList->SetBorder(false);
	m_MoveList->SetSelectCallback<CIMGUICameraMoveComponent>(this, &CIMGUICameraMoveComponent::MoveObjectCallback);

	Text = AddComponentWidget<CIMGUIText>("NextMoveCheckBoxText");
	Text->SetText("NextMove");
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");
	m_NextMoveCheckBox = AddComponentWidget<CIMGUICheckBox>("##NextMoveCheckBox", 100.f, 20.f);

	Text = AddComponentWidget<CIMGUIText>("MoveNameText");
	Text->SetText("MoveName");
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");
	m_MoveName = AddComponentWidget<CIMGUITextInput>("##MoveName", 100.f, 20.f);

	Text = AddComponentWidget<CIMGUIText>("NextNameText");
	Text->SetText("NextName");
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");
	m_NextName = AddComponentWidget<CIMGUITextInput>("##NextName", 100.f, 20.f);


	Text = AddComponentWidget<CIMGUIText>("EndTimeInputText");
	Text->SetText("EndTimeInput");
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");
	m_EndTimeInput = AddComponentWidget<CIMGUITextInput>("##EndTimeInput", 100.f, 20.f);
	m_EndTimeInput->SetNumberFloat(true);


	Text = AddComponentWidget<CIMGUIText>("LengthText");
	Text->SetText("Length");
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");
	m_StartLengthInput = AddComponentWidget<CIMGUITextInput>("##StartLengthInput", 100.f, 20.f);
	m_StartLengthInput->SetNumberFloat(true);
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");
	m_EndLengthInput = AddComponentWidget<CIMGUITextInput>("##EndLengthInput", 100.f, 20.f);
	m_EndLengthInput->SetNumberFloat(true);


	Text = AddComponentWidget<CIMGUIText>("PosY_Text");
	Text->SetText("PosY");
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");
	m_StartPosYInput = AddComponentWidget<CIMGUITextInput>("##StartPosYInput", 100.f, 20.f);
	m_StartPosYInput->SetNumberFloat(true);
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");
	m_EndPosYInput = AddComponentWidget<CIMGUITextInput>("##EndPosYInput", 100.f, 20.f);
	m_EndPosYInput->SetNumberFloat(true);

	Text = AddComponentWidget<CIMGUIText>("Text_Position");
	Text->SetText("Position");

	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputStartRotX = AddComponentWidget<CIMGUIDrag>("##InputStartRotX", 60.f, 20.f);
	m_InputStartRotX->SetNumberFloat(true);
	m_InputStartRotX->SetInputCallback<CIMGUICameraMoveComponent>(this, &CIMGUICameraMoveComponent::StartRotX);
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputStartRotY = AddComponentWidget<CIMGUIDrag>("##InputStartRotY", 60.f, 20.f);
	m_InputStartRotY->SetNumberFloat(true);
	m_InputStartRotY->SetInputCallback<CIMGUICameraMoveComponent>(this, &CIMGUICameraMoveComponent::StartRotY);
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputStartRotZ = AddComponentWidget<CIMGUIDrag>("##InputStartRotZ", 60.f, 20.f);
	m_InputStartRotZ->SetNumberFloat(true);
	m_InputStartRotZ->SetInputCallback<CIMGUICameraMoveComponent>(this, &CIMGUICameraMoveComponent::StartRotZ);

	Text = AddComponentWidget<CIMGUIText>("Text_Position");
	Text->SetText("Position");

	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputEndRotX = AddComponentWidget<CIMGUIDrag>("##InputEndRotX", 60.f, 20.f);
	m_InputEndRotX->SetNumberFloat(true);
	m_InputEndRotX->SetInputCallback<CIMGUICameraMoveComponent>(this, &CIMGUICameraMoveComponent::EndRotX);
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputEndRotY = AddComponentWidget<CIMGUIDrag>("##InputEndRotY", 60.f, 20.f);
	m_InputEndRotY->SetNumberFloat(true);
	m_InputEndRotY->SetInputCallback<CIMGUICameraMoveComponent>(this, &CIMGUICameraMoveComponent::EndRotY);
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputEndRotZ = AddComponentWidget<CIMGUIDrag>("##InputEndRotZ", 60.f, 20.f);
	m_InputEndRotZ->SetNumberFloat(true);
	m_InputEndRotZ->SetInputCallback<CIMGUICameraMoveComponent>(this, &CIMGUICameraMoveComponent::EndRotZ);



	m_StartRotButton = AddComponentWidget<CIMGUIButton>("StartRotButton", 100.f, 30.f);
	m_StartRotButton->SetClickCallback< CIMGUICameraMoveComponent>(this, &CIMGUICameraMoveComponent::StartRotBtnCallback);
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");
	m_EndRotButton = AddComponentWidget<CIMGUIButton>("EndRotButton", 100.f, 30.f);
	m_EndRotButton->SetClickCallback< CIMGUICameraMoveComponent>(this, &CIMGUICameraMoveComponent::EndRotBtnCallback);

	m_CreateMoveButton = AddComponentWidget<CIMGUIButton>("CreateMoveButton", 100.f, 30.f);
	m_CreateMoveButton->SetClickCallback< CIMGUICameraMoveComponent>(this, &CIMGUICameraMoveComponent::CreateMoveBtnCallback);

	Text = AddComponentWidget<CIMGUIText>("TargetName");
	Text->SetText("TargetName");
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");
	m_TargetName = AddComponentWidget<CIMGUITextInput>("##TargetName", 100.f, 20.f);

	m_Header->WidgetPush(m_vecWidgetComponent);
	m_vecWidgetComponent.push_back(m_Header);

	return true;
}

void CIMGUICameraMoveComponent::Update(float DeltaTime)
{
	m_MoveList->Clear();
	std::unordered_map<std::string, CameraMoveInfo*>& CameraMovemap = m_Object->GetMapMoveInfo();
	auto iter = CameraMovemap.begin();
	auto iterEnd = CameraMovemap.end();
	for (; iter != iterEnd; ++iter)
	{
		m_MoveList->AddItem(iter->second->Name.c_str());
	}
}

void CIMGUICameraMoveComponent::StartRotBtnCallback()
{
	CCamera* Camera = CSceneManager::GetInst()->GetScene()->GetCameraManager()->GetCurrentCamera();
	m_StartRot = Camera->GetWorldRotation();
	m_InputStartRotX->SetFloat(m_StartRot.x);
	m_InputStartRotY->SetFloat(m_StartRot.y);
	m_InputStartRotZ->SetFloat(m_StartRot.z);
}

void CIMGUICameraMoveComponent::EndRotBtnCallback()
{
	CCamera* Camera = CSceneManager::GetInst()->GetScene()->GetCameraManager()->GetCurrentCamera();
	m_EndRot = Camera->GetWorldRotation();
	m_InputEndRotX->SetFloat(m_EndRot.x);
	m_InputEndRotY->SetFloat(m_EndRot.y);
	m_InputEndRotZ->SetFloat(m_EndRot.z);
}

void CIMGUICameraMoveComponent::CreateMoveBtnCallback()
{
	CIMGUIText* Text = m_Owner->AddPopupWidget<CIMGUIText>("CreateComponent");
	Text->SetText("CreateComponent");

	CIMGUIComboBox* SelectTargetCombo = m_Owner->AddPopupWidget<CIMGUIComboBox>("##SelectTargetCombo", 100.f, 100.f);

	SelectTargetCombo->SetSelectCallback<CIMGUICameraMoveComponent>(this, &CIMGUICameraMoveComponent::SelectTargetComboCallback);
	CObjectWindow* ObjectWindow = (CObjectWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectWindow");

	std::vector<CSharedPtr<CGameObject>>& vecObject = ObjectWindow->GetAllObject();

	size_t Size = vecObject.size();
	for (int i = 0; i < Size; ++i)
	{
		SelectTargetCombo->AddItem(vecObject[i]->GetName().c_str());
	}

	CIMGUIButton* CreateObjButton = m_Owner->AddPopupWidget<CIMGUIButton>("»ý¼º");
	CreateObjButton->SetFont("DefaultFont");
	CreateObjButton->SetClickCallback<CIMGUICameraMoveComponent>(this, &CIMGUICameraMoveComponent::InputSelectTargetPopupButton);

	m_Owner->SetPopupTitle("Target");
	m_Owner->EnableModalPopup();
}

void CIMGUICameraMoveComponent::MoveObjectCallback(int SelectIndex, const char* Item)
{
	std::string SelectName = Item;
	CObjectWindow* ObjectWindow = (CObjectWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectWindow");
	CGameObject* Obj = ObjectWindow->FindObject(m_TargetName->GetTextMultibyte());
	if (Obj)
	{
		m_Object->StartCameraScene_FadeInOut(SelectName, Obj);
	}
	

}

void CIMGUICameraMoveComponent::SelectTargetComboCallback(int SelectIndex, const char* Item)
{
	CObjectWindow* ObjectWindow = (CObjectWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectWindow");
	CGameObject* Obj = ObjectWindow->FindObject(Item);
	if (Obj)
	{
		m_Target = Obj;
	}
}

void CIMGUICameraMoveComponent::InputSelectTargetPopupButton()
{
	if (!m_Target)
		return;
	bool NextMove = m_NextMoveCheckBox->GetCheck();
	std::string Name = m_MoveName->GetTextMultibyte();
	std::string NextName = m_NextName->GetTextMultibyte();
	float EndTime = m_EndTimeInput->GetValueFloat();
	float StartLength = m_StartLengthInput->GetValueFloat();
	float EndLength = m_EndLengthInput->GetValueFloat();
	float StartPosY = m_StartPosYInput->GetValueFloat();
	float EndPosY = m_EndPosYInput->GetValueFloat();

	m_Object->AddCameraMoveInfo(Name, NextName, EndTime, m_Target, m_EndRot, m_StartRot, StartPosY, EndPosY, StartLength,
		EndLength);

	m_Owner->ClosePopup();
}

void CIMGUICameraMoveComponent::StartRotX()
{
	float x = m_InputStartRotX->GetValueFloat();
	m_StartRot.x = x;
}

void CIMGUICameraMoveComponent::StartRotY()
{
	float x = m_InputStartRotY->GetValueFloat();
	m_StartRot.y = x;
}

void CIMGUICameraMoveComponent::StartRotZ()
{
	float x = m_InputStartRotZ->GetValueFloat();
	m_StartRot.z = x;
}

void CIMGUICameraMoveComponent::EndRotX()
{
	float x = m_InputEndRotX->GetValueFloat();
	m_EndRot.x = x;
}

void CIMGUICameraMoveComponent::EndRotY()
{
	float x = m_InputEndRotY->GetValueFloat();
	m_EndRot.y = x;
}

void CIMGUICameraMoveComponent::EndRotZ()
{
	float x = m_InputEndRotZ->GetValueFloat();
	m_EndRot.z = x;
}
