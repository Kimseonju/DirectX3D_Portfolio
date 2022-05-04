#include "../pch.h"
#include "DetailWindow.h"
#include "IMGUITextInput.h"
#include "IMGUIText.h"
#include "IMGUISameLine.h"


#include "IMGUIManager.h"
#include "ObjectWindow.h"

CDetailWindow::CDetailWindow():
	m_InputPosX(nullptr),
	m_InputPosY(nullptr),
	m_InputPosZ(nullptr),
	m_InputRotX(nullptr),
	m_InputRotY(nullptr),
	m_InputRotZ(nullptr),
	m_InputScaleX(nullptr),
	m_InputScaleY(nullptr),
	m_InputScaleZ(nullptr),
	m_InputPivotX(nullptr),
	m_InputPivotY(nullptr),
	m_InputPivotZ(nullptr)
{
}

CDetailWindow::~CDetailWindow()
{
}

void CDetailWindow::SetPosition(const Vector3& Pos)
{
	m_InputPosX->SetFloat(Pos.x);
	m_InputPosY->SetFloat(Pos.y);
	m_InputPosZ->SetFloat(Pos.z);
}
void CDetailWindow::SetRotation(const Vector3& Pos)
{
	m_InputRotX->SetFloat(Pos.x);
	m_InputRotY->SetFloat(Pos.y);
	m_InputRotZ->SetFloat(Pos.z);
}
void CDetailWindow::SetScale(const Vector3& Pos)
{
	m_InputScaleX->SetFloat(Pos.x);
	m_InputScaleY->SetFloat(Pos.y);
	m_InputScaleZ->SetFloat(Pos.z);
}
void CDetailWindow::SetPivot(const Vector3& Pos)
{
	m_InputPivotX->SetFloat(Pos.x);
	m_InputPivotY->SetFloat(Pos.y);
	m_InputPivotZ->SetFloat(Pos.z);
}
bool CDetailWindow::Init()
{
	CIMGUIText* Text = AddWidget<CIMGUIText>("À§Ä¡");
	Text->SetFont("DefaultFont");

#pragma region Position


	CIMGUIText* Label = AddWidget<CIMGUIText>("Label_Title", 100.f, 20.f);
	Label->SetText("Transform");

	Label = AddWidget<CIMGUIText>("Label_Position", 100.f, 20.f);
	Label->SetText("Position");
	CIMGUISameLine* SameLine = AddWidget<CIMGUISameLine>("SameLine");

	m_InputPosX = AddWidget<CIMGUITextInput>("##Input_PosX", 100.f, 20.f);
	m_InputPosX->SetNumberFloat(true);
	m_InputPosX->SetInputCallback<CDetailWindow>(this, &CDetailWindow::InputPosX);
	SameLine = AddWidget<CIMGUISameLine>("SameLine");

	m_InputPosY = AddWidget<CIMGUITextInput>("##Input_PosY", 100.f, 20.f);
	m_InputPosY->SetNumberFloat(true);
	m_InputPosY->SetInputCallback<CDetailWindow>(this, &CDetailWindow::InputPosY);
	SameLine = AddWidget<CIMGUISameLine>("SameLine");

	m_InputPosZ = AddWidget<CIMGUITextInput>("##Input_PosZ", 100.f, 20.f);
	m_InputPosZ->SetNumberFloat(true);
	m_InputPosZ->SetInputCallback<CDetailWindow>(this, &CDetailWindow::InputPosZ);


	m_InputPosX->AddFlag(ImGuiInputTextFlags_EnterReturnsTrue);
	m_InputPosY->AddFlag(ImGuiInputTextFlags_EnterReturnsTrue);
	m_InputPosZ->AddFlag(ImGuiInputTextFlags_EnterReturnsTrue);
#pragma endregion
#pragma region Rotation
	Label = AddWidget<CIMGUIText>("Label_Rotation", 100.f, 20.f);
	Label->SetText("Rotation");
	SameLine = AddWidget<CIMGUISameLine>("SameLine");

	m_InputRotX = AddWidget<CIMGUITextInput>("##Input_RotationX", 100.f, 20.f);
	m_InputRotX->SetNumberFloat(true);
	m_InputRotX->SetInputCallback<CDetailWindow>(this, &CDetailWindow::InputRotX);
	SameLine = AddWidget<CIMGUISameLine>("SameLine");

	m_InputRotY = AddWidget<CIMGUITextInput>("##Input_RotationY", 100.f, 20.f);
	m_InputRotY->SetNumberFloat(true);
	m_InputRotY->SetInputCallback<CDetailWindow>(this, &CDetailWindow::InputRotY);
	SameLine = AddWidget<CIMGUISameLine>("SameLine");

	m_InputRotZ = AddWidget<CIMGUITextInput>("##Input_RotationZ", 100.f, 20.f);
	m_InputRotZ->SetNumberFloat(true);
	m_InputRotZ->SetInputCallback<CDetailWindow>(this, &CDetailWindow::InputRotZ);


	m_InputRotX->AddFlag(ImGuiInputTextFlags_EnterReturnsTrue);
	m_InputRotY->AddFlag(ImGuiInputTextFlags_EnterReturnsTrue);
	m_InputRotZ->AddFlag(ImGuiInputTextFlags_EnterReturnsTrue);
#pragma endregion

#pragma region Scale

	Label = AddWidget<CIMGUIText>("Label_Scale", 100.f, 20.f);
	Label->SetText("Scale");
	SameLine->SetSize(20.f, 20.f);
	SameLine = AddWidget<CIMGUISameLine>("SameLine");

	m_InputScaleX = AddWidget<CIMGUITextInput>("##Input_ScaleX", 100.f, 20.f);
	m_InputScaleX->SetNumberFloat(true);
	m_InputScaleX->SetInputCallback<CDetailWindow>(this, &CDetailWindow::InputScaleX);
	SameLine = AddWidget<CIMGUISameLine>("SameLine");

	m_InputScaleY = AddWidget<CIMGUITextInput>("##Input_ScaleY", 100.f, 20.f);
	m_InputScaleY->SetNumberFloat(true);
	m_InputScaleY->SetInputCallback<CDetailWindow>(this, &CDetailWindow::InputScaleY);
	SameLine = AddWidget<CIMGUISameLine>("SameLine");

	m_InputScaleZ = AddWidget<CIMGUITextInput>("##Input_ScaleZ", 100.f, 20.f);
	m_InputScaleZ->SetNumberFloat(true);
	m_InputScaleZ->SetInputCallback<CDetailWindow>(this, &CDetailWindow::InputScaleZ);


	m_InputScaleX->AddFlag(ImGuiInputTextFlags_EnterReturnsTrue);
	m_InputScaleY->AddFlag(ImGuiInputTextFlags_EnterReturnsTrue);
	m_InputScaleZ->AddFlag(ImGuiInputTextFlags_EnterReturnsTrue);

#pragma endregion

#pragma region Pivot


	Label = AddWidget<CIMGUIText>("Label_Pivot", 100.f, 20.f);
	Label->SetText("Pivot");
	SameLine->SetSize(20.f, 20.f);
	SameLine = AddWidget<CIMGUISameLine>("SameLine");

	m_InputPivotX = AddWidget<CIMGUITextInput>("##Input_PivotX", 100.f, 20.f);
	m_InputPivotX->SetNumberFloat(true);
	m_InputPivotX->SetInputCallback<CDetailWindow>(this, &CDetailWindow::InputScaleX);
	SameLine = AddWidget<CIMGUISameLine>("SameLine");

	m_InputPivotY = AddWidget<CIMGUITextInput>("##Input_PivotY", 100.f, 20.f);
	m_InputPivotY->SetNumberFloat(true);
	m_InputPivotY->SetInputCallback<CDetailWindow>(this, &CDetailWindow::InputScaleY);
	SameLine = AddWidget<CIMGUISameLine>("SameLine");

	m_InputPivotZ = AddWidget<CIMGUITextInput>("##Input_PivotZ", 100.f, 20.f);
	m_InputPivotZ->SetNumberFloat(true);
	m_InputPivotZ->SetInputCallback<CDetailWindow>(this, &CDetailWindow::InputScaleZ);
	SameLine = AddWidget<CIMGUISameLine>("SameLine");


	m_InputPivotX->AddFlag(ImGuiInputTextFlags_EnterReturnsTrue);
	m_InputPivotY->AddFlag(ImGuiInputTextFlags_EnterReturnsTrue);
	m_InputPivotZ->AddFlag(ImGuiInputTextFlags_EnterReturnsTrue);

#pragma endregion





	return true;
}

void CDetailWindow::Update(float DeltaTime)
{
	CIMGUIWindow::Update(DeltaTime);
}


void CDetailWindow::InputPosX()
{
	float x = m_InputPosX->GetValueFloat();

	CObjectWindow* Window = (CObjectWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectWindow");

	Window->SetPosX(x);
}

void CDetailWindow::InputPosY()
{
	float y = m_InputPosY->GetValueFloat();

	CObjectWindow* Window = (CObjectWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectWindow");

	Window->SetPosY(y);
}

void CDetailWindow::InputPosZ()
{
	float z = m_InputPosZ->GetValueFloat();

	CObjectWindow* Window = (CObjectWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectWindow");

	Window->SetPosZ(z);
}

void CDetailWindow::InputRotX()
{
	float x = m_InputRotX->GetValueFloat();

	CObjectWindow* Window = (CObjectWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectWindow");

	Window->SetRotX(x);
}

void CDetailWindow::InputRotY()
{
	float y = m_InputRotX->GetValueFloat();

	CObjectWindow* Window = (CObjectWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectWindow");

	Window->SetRotY(y);
}

void CDetailWindow::InputRotZ()
{
	float z = m_InputRotX->GetValueFloat();

	CObjectWindow* Window = (CObjectWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectWindow");

	Window->SetRotZ(z);
}

void CDetailWindow::InputScaleX()
{
	float x = m_InputScaleX->GetValueFloat();

	CObjectWindow* Window = (CObjectWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectWindow");

	Window->SetScaleX(x);
}

void CDetailWindow::InputScaleY()
{
	float y = m_InputScaleY->GetValueFloat();

	CObjectWindow* Window = (CObjectWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectWindow");

	Window->SetScaleY(y);
}

void CDetailWindow::InputScaleZ()
{
	float z = m_InputScaleZ->GetValueFloat();

	CObjectWindow* Window = (CObjectWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectWindow");

	Window->SetScaleZ(z);
}

void CDetailWindow::InputPivotX()
{
	float z = m_InputPivotX->GetValueFloat();

	CObjectWindow* Window = (CObjectWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectWindow");

	Window->SetPivotX(z);
}

void CDetailWindow::InputPivotY()
{
	float y = m_InputPivotY->GetValueFloat();

	CObjectWindow* Window = (CObjectWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectWindow");

	Window->SetPivotY(y);
}

void CDetailWindow::InputPivotZ()
{
	float z = m_InputPivotZ->GetValueFloat();

	CObjectWindow* Window = (CObjectWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectWindow");

	Window->SetPivotZ(z);
}
