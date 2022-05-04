#include "../pch.h"
#include "IMGUITransformComponent.h"
#include "IMGUIDrag.h"
#include "Component/SceneComponent.h"
#include "IMGUIText.h"
#include "IMGUISameLine.h"
#include "IMGUICollapsingHeader.h"
CIMGUITransformComponent::CIMGUITransformComponent():
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
	m_Component(nullptr)
{
}

CIMGUITransformComponent::~CIMGUITransformComponent()
{
}

void CIMGUITransformComponent::SetPosition(const Vector3& Pos)
{
	m_InputPosX->SetFloat(Pos.x);
	m_InputPosY->SetFloat(Pos.y);
	m_InputPosZ->SetFloat(Pos.z);
}
void CIMGUITransformComponent::SetRotation(const Vector3& Pos)
{
	m_InputRotX->SetFloat(Pos.x);
	m_InputRotY->SetFloat(Pos.y);
	m_InputRotZ->SetFloat(Pos.z);
}
void CIMGUITransformComponent::SetScale(const Vector3& Pos)
{
	m_InputScaleX->SetFloat(Pos.x);
	m_InputScaleY->SetFloat(Pos.y);
	m_InputScaleZ->SetFloat(Pos.z);
}
void CIMGUITransformComponent::SetPivot(const Vector3& Pos)
{
	m_InputPivotX->SetFloat(Pos.x);
	m_InputPivotY->SetFloat(Pos.y);
	m_InputPivotZ->SetFloat(Pos.z);
}
void CIMGUITransformComponent::ComponentUpdateInfo(CSceneComponent* Component)
{
	m_Component = Component;
	SetPosition(m_Component->GetWorldPos());
	SetRotation(m_Component->GetWorldRotation());
	SetScale(m_Component->GetWorldScale());
	SetPivot(m_Component->GetPivot());
}
bool CIMGUITransformComponent::Init()
{

	CIMGUIWidgetComponent::Init();
	CIMGUIText* Text;
	CIMGUISameLine* SameLine;
	m_Header = m_Owner->AddWidget<CIMGUICollapsingHeader>("Transform");
#pragma region Position


	Text = AddComponentWidget<CIMGUIText>("Text_Title");
	Text->SetText("Transform");

	Text = AddComponentWidget<CIMGUIText>("Text_Position");
	Text->SetText("Position");

	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputPosX = AddComponentWidget<CIMGUIDrag>("##Input_PosX", 60.f, 20.f);
	m_InputPosX->SetNumberFloat(true);
	m_InputPosX->SetInputCallback<CIMGUITransformComponent>(this, &CIMGUITransformComponent::InputPosX);
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputPosY = AddComponentWidget<CIMGUIDrag>("##Input_PosY", 60.f, 20.f);
	m_InputPosY->SetNumberFloat(true);
	m_InputPosY->SetInputCallback<CIMGUITransformComponent>(this, &CIMGUITransformComponent::InputPosY);
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputPosZ = AddComponentWidget<CIMGUIDrag>("##Input_PosZ", 60.f, 20.f);
	m_InputPosZ->SetNumberFloat(true);
	m_InputPosZ->SetInputCallback<CIMGUITransformComponent>(this, &CIMGUITransformComponent::InputPosZ);

#pragma endregion
#pragma region Rotation
	Text = AddComponentWidget<CIMGUIText>("Text_Rotation");
	Text->SetText("Rotation");

	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputRotX = AddComponentWidget<CIMGUIDrag>("##Input_RotationX", 60.f, 20.f);
	m_InputRotX->SetNumberFloat(true);
	m_InputRotX->SetInputCallback<CIMGUITransformComponent>(this, &CIMGUITransformComponent::InputRotX);
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputRotY = AddComponentWidget<CIMGUIDrag>("##Input_RotationY", 60.f, 20.f);
	m_InputRotY->SetNumberFloat(true);
	m_InputRotY->SetInputCallback<CIMGUITransformComponent>(this, &CIMGUITransformComponent::InputRotY);
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputRotZ = AddComponentWidget<CIMGUIDrag>("##Input_RotationZ", 60.f, 20.f);
	m_InputRotZ->SetNumberFloat(true);
	m_InputRotZ->SetInputCallback<CIMGUITransformComponent>(this, &CIMGUITransformComponent::InputRotZ);

#pragma endregion

#pragma region Scale

	Text = AddComponentWidget<CIMGUIText>("Text_Scale");
	Text->SetText("Scale");

	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputScaleX = AddComponentWidget<CIMGUIDrag>("##Input_ScaleX", 60.f, 20.f);
	m_InputScaleX->SetNumberFloat(true);
	m_InputScaleX->SetInputCallback<CIMGUITransformComponent>(this, &CIMGUITransformComponent::InputScaleX);
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputScaleY = AddComponentWidget<CIMGUIDrag>("##Input_ScaleY", 60.f, 20.f);
	m_InputScaleY->SetNumberFloat(true);
	m_InputScaleY->SetInputCallback<CIMGUITransformComponent>(this, &CIMGUITransformComponent::InputScaleY);
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputScaleZ = AddComponentWidget<CIMGUIDrag>("##Input_ScaleZ", 60.f, 20.f);
	m_InputScaleZ->SetNumberFloat(true);
	m_InputScaleZ->SetInputCallback<CIMGUITransformComponent>(this, &CIMGUITransformComponent::InputScaleZ);

#pragma endregion

#pragma region Pivot


	Text = AddComponentWidget<CIMGUIText>("Text_Pivot");
	Text->SetText("Pivot");
	SameLine->SetSize(20.f, 20.f);

	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");
	m_InputPivotX = AddComponentWidget<CIMGUIDrag>("##Input_PivotX", 100.f, 20.f);
	m_InputPivotX->SetNumberFloat(true);
	m_InputPivotX->SetInputCallback<CIMGUITransformComponent>(this, &CIMGUITransformComponent::InputPivotX);
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputPivotY = AddComponentWidget<CIMGUIDrag>("##Input_PivotY", 100.f, 20.f);
	m_InputPivotY->SetNumberFloat(true);
	m_InputPivotY->SetInputCallback<CIMGUITransformComponent>(this, &CIMGUITransformComponent::InputPivotY);
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputPivotZ = AddComponentWidget<CIMGUIDrag>("##Input_PivotZ", 100.f, 20.f);
	m_InputPivotZ->SetNumberFloat(true);
	m_InputPivotZ->SetInputCallback<CIMGUITransformComponent>(this, &CIMGUITransformComponent::InputPivotZ);

#pragma endregion


	m_Header->WidgetPush(m_vecWidgetComponent);
	m_vecWidgetComponent.push_back(m_Header);

	return true;
}

void CIMGUITransformComponent::Update(float DeltaTime)
{
	if(m_Component)
		ComponentUpdateInfo(m_Component);
}


void CIMGUITransformComponent::InputPosX()
{
	float x = m_InputPosX->GetValueFloat();

	Vector3 Pos=m_Component->GetWorldPos();
	Pos.x = x;
	m_Component->SetWorldPos(Pos);
}

void CIMGUITransformComponent::InputPosY()
{
	float y = m_InputPosY->GetValueFloat();

	Vector3 Pos = m_Component->GetWorldPos();
	Pos.y = y;
	m_Component->SetWorldPos(Pos);
}

void CIMGUITransformComponent::InputPosZ()
{
	float z = m_InputPosZ->GetValueFloat();

	Vector3 Pos = m_Component->GetWorldPos();
	Pos.z = z;
	m_Component->SetWorldPos(Pos);
}

void CIMGUITransformComponent::InputRotX()
{
	float x = m_InputRotX->GetValueFloat();

	m_Component->SetRelativeRotationX(x);
}

void CIMGUITransformComponent::InputRotY()
{
	float y = m_InputRotY->GetValueFloat();

	m_Component->SetRelativeRotationY(y);
}

void CIMGUITransformComponent::InputRotZ()
{
	float z = m_InputRotZ->GetValueFloat();

	m_Component->SetRelativeRotationZ(z);
}

void CIMGUITransformComponent::InputScaleX()
{
	float x = m_InputScaleX->GetValueFloat();

	Vector3 Scale = m_Component->GetRelativeScale();
	Scale.x =x;
	m_Component->SetRelativeScale(Scale);
}

void CIMGUITransformComponent::InputScaleY()
{
	float y = m_InputScaleY->GetValueFloat();

	Vector3 Scale = m_Component->GetRelativeScale();
	Scale.y = y;
	m_Component->SetRelativeScale(Scale);
}

void CIMGUITransformComponent::InputScaleZ()
{
	float z = m_InputScaleZ->GetValueFloat();

	Vector3 Scale = m_Component->GetRelativeScale();
	Scale.z =z;
	m_Component->SetRelativeScale(Scale);
}

void CIMGUITransformComponent::InputPivotX()
{
	float x = m_InputPivotX->GetValueFloat();

	Vector3 Pivot = m_Component->GetPivot();
	Pivot.x = x;
	m_Component->SetPivot(Pivot);
}

void CIMGUITransformComponent::InputPivotY()
{
	float y = m_InputPivotY->GetValueFloat();

	Vector3 Pivot = m_Component->GetPivot();
	Pivot.y = y;
	m_Component->SetPivot(Pivot);
}

void CIMGUITransformComponent::InputPivotZ()
{
	float z = m_InputPivotZ->GetValueFloat();

	Vector3 Pivot = m_Component->GetPivot();
	Pivot.z = z;
	m_Component->SetPivot(Pivot);
}
