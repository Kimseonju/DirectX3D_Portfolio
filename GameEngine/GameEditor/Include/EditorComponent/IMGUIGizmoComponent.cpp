#include "../pch.h"
#include "IMGUIGizmoComponent.h"
#include "IMGUISameLine.h"
#include "IMGUIText.h"
#include "IMGUIManager.h"
#include "IMGUIDrag.h"
#include "IMGUICollapsingHeader.h"
#include "IMGUIRadioButton.h"
#include "../EditorTool/IMGUIGizmo.h"
#include "Component/SceneComponent.h"
CIMGUIGizmoComponent::CIMGUIGizmoComponent():
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
	m_InputPivotZ(nullptr),
	m_Component(nullptr),
	m_GizmoOperation(nullptr),
	m_Gizmo(nullptr)
{
}

CIMGUIGizmoComponent::~CIMGUIGizmoComponent()
{
}

void CIMGUIGizmoComponent::SetPosition(const Vector3& Pos)
{
	m_InputPosX->SetFloat(Pos.x);
	m_InputPosY->SetFloat(Pos.y);
	m_InputPosZ->SetFloat(Pos.z);
	if (m_Component)
	{
		m_Component->SetWorldPos(Pos);
	}
}
void CIMGUIGizmoComponent::SetRotation(const Vector3& Rotation)
{
	m_InputRotX->SetFloat(Rotation.x);
	m_InputRotY->SetFloat(Rotation.y);
	m_InputRotZ->SetFloat(Rotation.z);
	if (m_Component)
	{
		m_Component->SetRelativeRotation(Rotation);
	}
}
void CIMGUIGizmoComponent::SetScale(const Vector3& Scale)
{
	m_InputScaleX->SetFloat(Scale.x);
	m_InputScaleY->SetFloat(Scale.y);
	m_InputScaleZ->SetFloat(Scale.z);
	if (m_Component)
	{
		m_Component->SetRelativeScale(Scale);
	}
}
void CIMGUIGizmoComponent::SetPivot(const Vector3& Pivot)
{
	m_InputPivotX->SetFloat(Pivot.x);
	m_InputPivotY->SetFloat(Pivot.y);
	m_InputPivotZ->SetFloat(Pivot.z);
	if (m_Component)
	{
		m_Component->SetPivot(Pivot);
	}
}
void CIMGUIGizmoComponent::SetComponent(CSceneComponent* Component)
{
	m_Component = Component;
	if (nullptr == m_Component)
	{
		SetPosition(Vector3::Zero);
		SetRotation(Vector3::Zero);
		SetScale(Vector3::Zero);
		SetPivot(Vector3::Zero);
	}
	else
	{
		SetPosition(m_Component->GetWorldPos());
		SetRotation(m_Component->GetRelativeRotation());
		SetScale(m_Component->GetRelativeScale());
		SetPivot(m_Component->GetPivot());
	}

}
const Vector3 CIMGUIGizmoComponent::GetPosition()
{
	if (!m_Component)
		return Vector3::Zero;
	return m_Component->GetWorldPos();
}
const Vector3 CIMGUIGizmoComponent::GetRotation()
{
	if (!m_Component)
		return Vector3::Zero;
	return m_Component->GetRelativeRotation();
}
const Vector3 CIMGUIGizmoComponent::GetScale()
{
	if (!m_Component)
		return Vector3::Zero;
	return m_Component->GetRelativeScale();
}
bool CIMGUIGizmoComponent::Init()
{

	CIMGUIWidgetComponent::Init();
	CIMGUIText* Text;
	CIMGUISameLine* SameLine;


	m_Header = m_Owner->AddWidget<CIMGUICollapsingHeader>("Tool Gizmo");
#pragma region Position


	m_GizmoOperation = AddComponentWidget<CIMGUIRadioButton>("GizmoOperation");
	m_GizmoOperation->AddItem("Translate");
	m_GizmoOperation->AddItem("Rotate");
	m_GizmoOperation->AddItem("Scale");
	m_GizmoOperation->AddItem("Universal");
	m_GizmoOperation->SetSelectCallback(this, &CIMGUIGizmoComponent::GizmoOperationListCallback);
	Text = AddComponentWidget<CIMGUIText>("Text_Title");
	Text->SetText("Transform");

	Text = AddComponentWidget<CIMGUIText>("Text_Position");
	Text->SetText("Position");

	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputPosX = AddComponentWidget<CIMGUIDrag>("##Gizmo_PosX", 60.f, 20.f);
	m_InputPosX->SetNumberFloat(true);
	m_InputPosX->SetInputCallback<CIMGUIGizmoComponent>(this, &CIMGUIGizmoComponent::InputPosX);
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputPosY = AddComponentWidget<CIMGUIDrag>("##Gizmo_PosY", 60.f, 20.f);
	m_InputPosY->SetNumberFloat(true);
	m_InputPosY->SetInputCallback<CIMGUIGizmoComponent>(this, &CIMGUIGizmoComponent::InputPosY);
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputPosZ = AddComponentWidget<CIMGUIDrag>("##Gizmo_PosZ", 60.f, 20.f);
	m_InputPosZ->SetNumberFloat(true);
	m_InputPosZ->SetInputCallback<CIMGUIGizmoComponent>(this, &CIMGUIGizmoComponent::InputPosZ);

#pragma endregion
#pragma region Rotation
	Text = AddComponentWidget<CIMGUIText>("Text_Rotation");
	Text->SetText("Rotation");

	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputRotX = AddComponentWidget<CIMGUIDrag>("##Gizmo_RotationX", 60.f, 20.f);
	m_InputRotX->SetNumberFloat(true);
	m_InputRotX->SetInputCallback<CIMGUIGizmoComponent>(this, &CIMGUIGizmoComponent::InputRotX);
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputRotY = AddComponentWidget<CIMGUIDrag>("##Gizmo_RotationY", 60.f, 20.f);
	m_InputRotY->SetNumberFloat(true);
	m_InputRotY->SetInputCallback<CIMGUIGizmoComponent>(this, &CIMGUIGizmoComponent::InputRotY);
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputRotZ = AddComponentWidget<CIMGUIDrag>("##Gizmo_RotationZ", 60.f, 20.f);
	m_InputRotZ->SetNumberFloat(true);
	m_InputRotZ->SetInputCallback<CIMGUIGizmoComponent>(this, &CIMGUIGizmoComponent::InputRotZ);


#pragma endregion

#pragma region Scale

	Text = AddComponentWidget<CIMGUIText>("Text_Scale");
	Text->SetText("Scale");

	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputScaleX = AddComponentWidget<CIMGUIDrag>("##Gizmo_ScaleX", 60.f, 20.f);
	m_InputScaleX->SetNumberFloat(true);
	m_InputScaleX->SetInputCallback<CIMGUIGizmoComponent>(this, &CIMGUIGizmoComponent::InputScaleX);
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputScaleY = AddComponentWidget<CIMGUIDrag>("##Gizmo_ScaleY", 60.f, 20.f);
	m_InputScaleY->SetNumberFloat(true);
	m_InputScaleY->SetInputCallback<CIMGUIGizmoComponent>(this, &CIMGUIGizmoComponent::InputScaleY);
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputScaleZ = AddComponentWidget<CIMGUIDrag>("##Gizmo_ScaleZ", 60.f, 20.f);
	m_InputScaleZ->SetNumberFloat(true);
	m_InputScaleZ->SetInputCallback<CIMGUIGizmoComponent>(this, &CIMGUIGizmoComponent::InputScaleZ);



#pragma endregion

#pragma region Pivot


	Text = AddComponentWidget<CIMGUIText>("Text_Pivot");
	Text->SetText("Pivot");
	SameLine->SetSize(20.f, 20.f);

	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");
	m_InputPivotX = AddComponentWidget<CIMGUIDrag>("##Gizmo_PivotX", 100.f, 20.f);
	m_InputPivotX->SetNumberFloat(true);
	m_InputPivotX->SetInputCallback<CIMGUIGizmoComponent>(this, &CIMGUIGizmoComponent::InputPivotX);
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputPivotY = AddComponentWidget<CIMGUIDrag>("##Gizmo_PivotY", 100.f, 20.f);
	m_InputPivotY->SetNumberFloat(true);
	m_InputPivotY->SetInputCallback<CIMGUIGizmoComponent>(this, &CIMGUIGizmoComponent::InputPivotY);
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputPivotZ = AddComponentWidget<CIMGUIDrag>("##Gizmo_PivotZ", 100.f, 20.f);
	m_InputPivotZ->SetNumberFloat(true);
	m_InputPivotZ->SetInputCallback<CIMGUIGizmoComponent>(this, &CIMGUIGizmoComponent::InputPivotZ);

#pragma endregion


	m_Header->WidgetPush(m_vecWidgetComponent);
	m_vecWidgetComponent.push_back(m_Header);

	return true;
}

void CIMGUIGizmoComponent::Update(float DeltaTime)
{
	if (m_Component)
		SetComponent(m_Component);
}


void CIMGUIGizmoComponent::InputPosX()
{
	float x = m_InputPosX->GetValueFloat();

	Vector3 Pos = m_Component->GetWorldPos();
	Pos.x = x;
	m_Component->SetWorldPos(Pos);
}

void CIMGUIGizmoComponent::InputPosY()
{
	float y = m_InputPosY->GetValueFloat();

	Vector3 Pos = m_Component->GetWorldPos();
	Pos.y = y;
	m_Component->SetWorldPos(Pos);
}

void CIMGUIGizmoComponent::InputPosZ()
{
	float z = m_InputPosZ->GetValueFloat();

	Vector3 Pos = m_Component->GetWorldPos();
	Pos.z = z;
	m_Component->SetWorldPos(Pos);
}

void CIMGUIGizmoComponent::InputRotX()
{
	float x = m_InputRotX->GetValueFloat();

	m_Component->SetRelativeRotationX(x);
}

void CIMGUIGizmoComponent::InputRotY()
{
	float y = m_InputRotY->GetValueFloat();

	m_Component->SetRelativeRotationY(y);
}

void CIMGUIGizmoComponent::InputRotZ()
{
	float z = m_InputRotZ->GetValueFloat();

	m_Component->SetRelativeRotationZ(z);
}

void CIMGUIGizmoComponent::InputScaleX()
{
	float x = m_InputScaleX->GetValueFloat();

	Vector3 Scale = m_Component->GetRelativeScale();
	Scale.x = x;
	m_Component->SetRelativeScale(Scale);
}

void CIMGUIGizmoComponent::InputScaleY()
{
	float y = m_InputScaleY->GetValueFloat();

	Vector3 Scale = m_Component->GetRelativeScale();
	Scale.y = y;
	m_Component->SetRelativeScale(Scale);
}

void CIMGUIGizmoComponent::InputScaleZ()
{
	float z = m_InputScaleZ->GetValueFloat();

	Vector3 Scale = m_Component->GetRelativeScale();
	Scale.z = z;
	m_Component->SetRelativeScale(Scale);
}

void CIMGUIGizmoComponent::InputPivotX()
{
	float x = m_InputPivotX->GetValueFloat();

	Vector3 Pivot = m_Component->GetPivot();
	Pivot.x = x;
	m_Component->SetPivot(Pivot);
}

void CIMGUIGizmoComponent::InputPivotY()
{
	float y = m_InputPivotY->GetValueFloat();

	Vector3 Pivot = m_Component->GetPivot();
	Pivot.y = y;
	m_Component->SetPivot(Pivot);
}

void CIMGUIGizmoComponent::InputPivotZ()
{
	float z = m_InputPivotZ->GetValueFloat();

	Vector3 Pivot = m_Component->GetPivot();
	Pivot.z = z;
	m_Component->SetPivot(Pivot);
}

void CIMGUIGizmoComponent::GizmoOperationListCallback(int SelectIndex, const char* Item)
{
	m_Gizmo->SetCurrentGizmoOperation(SelectIndex);
}
