#include "../pch.h"
#include "IMGUICameraComponent.h"
#include "IMGUISameLine.h"
#include "IMGUIText.h"
#include "IMGUIManager.h"
#include <Component/Camera.h>
#include "IMGUICollapsingHeader.h"
CIMGUICameraComponent::CIMGUICameraComponent()
{
}

CIMGUICameraComponent::~CIMGUICameraComponent()
{
}

void CIMGUICameraComponent::UpdateInfo(CCamera* CCamera)
{
	m_Camera = CCamera;
	Camera_Type Type=m_Camera->GetCameraType();
	float Left = m_Camera->GetCameraLeft();
	float Bottom = m_Camera->GetCameraBottom();

	switch (Type)
	{
	case Camera_Type::Cam3D:
		m_CameraType->SetText("Cam3D");
		break;
	case Camera_Type::Cam2D:
		m_CameraType->SetText("Cam2D");
		break;
	case Camera_Type::CamUI:
		m_CameraType->SetText("CamUI");
		break;
	}

	Enable(true);

}

bool CIMGUICameraComponent::Init()
{
	CIMGUIWidgetComponent::Init();
	m_Header = AddComponentWidget<CIMGUICollapsingHeader>("Camera");
#pragma region Type

	CIMGUIText* Text = AddComponentWidget<CIMGUIText>("##Type");
	Text->SetText("Type");
	CIMGUISameLine* SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_CameraType = AddComponentWidget<CIMGUIText>("##CameraType", 300.f, 20.f);

#pragma endregion

#pragma region Info


	Text = AddComponentWidget<CIMGUIText>("##Zoom");
	Text->SetText("Zoom");
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	Text = AddComponentWidget<CIMGUIText>("##Left");
	Text->SetText("Left");
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");


	Text = AddComponentWidget<CIMGUIText>("##Bottom");
	Text->SetText("Bottom");
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

#pragma endregion

	m_Header->WidgetPush(m_vecWidgetComponent);
	m_vecWidgetComponent.push_back(m_Header);

	return true;
}

void CIMGUICameraComponent::Update(float DeltaTime)
{
}