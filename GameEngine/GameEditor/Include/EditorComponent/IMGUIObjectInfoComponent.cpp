#include "../pch.h"
#include "IMGUIObjectInfoComponent.h"
#include "IMGUICollapsingHeader.h"
#include "IMGUIText.h"
#include "IMGUITextInput.h"
#include "IMGUISameLine.h"
#include "IMGUICheckBox.h"
CIMGUIObjectInfoComponent::CIMGUIObjectInfoComponent():
	m_ObjectName(nullptr),
	m_EnableCheckBox(nullptr)
{
}

CIMGUIObjectInfoComponent::~CIMGUIObjectInfoComponent()
{
}

void CIMGUIObjectInfoComponent::UpdateInfo(CGameObject* Object)
{
	m_Object = Object;
	if (!m_Object)
	{
		return;
	}
	m_ObjectName->SetText(m_Object->GetName().c_str());
	m_EnableCheckBox->SetCheck(m_Object->IsEnable());
}

bool CIMGUIObjectInfoComponent::Init()
{
	CIMGUIWidgetComponent::Init();
	CIMGUIText* Text;
	CIMGUISameLine* SameLine;

	m_Header = m_Owner->AddWidget<CIMGUICollapsingHeader>("ObjectInfo");




	Text = AddComponentWidget<CIMGUIText>("##Title");
	Text->SetText("Info");

#pragma region Name
	Text = AddComponentWidget<CIMGUIText>("ObjectName1");
	Text->SetText("Name");
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_ObjectName = AddComponentWidget<CIMGUITextInput>("##ObjectName", 100.f, 20.f);
	m_ObjectName->SetInputCallback<CIMGUIObjectInfoComponent>(this, &CIMGUIObjectInfoComponent::InputObjectName);
	m_ObjectName->AddFlag(ImGuiInputTextFlags_EnterReturnsTrue);

#pragma endregion

	m_EnableCheckBox = AddComponentWidget<CIMGUICheckBox>("Enable", 300.f, 20.f);
	m_EnableCheckBox->SetCheckCallback<CIMGUIObjectInfoComponent>(this, &CIMGUIObjectInfoComponent::EnableCheckBoxClick);

	m_Header->WidgetPush(m_vecWidgetComponent);
	m_vecWidgetComponent.push_back(m_Header);

	return true;
}

void CIMGUIObjectInfoComponent::Update(float DeltaTime)
{
}

void CIMGUIObjectInfoComponent::InputObjectName()
{
	m_Object->SetName(m_ObjectName->GetTextMultibyte());
}

void CIMGUIObjectInfoComponent::EnableCheckBoxClick(bool Enable)
{
	m_Object->Enable(Enable);
}
