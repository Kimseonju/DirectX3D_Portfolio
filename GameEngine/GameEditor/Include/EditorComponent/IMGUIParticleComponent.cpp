#include "../pch.h"
#include "IMGUIParticleComponent.h"
#include "IMGUICollapsingHeader.h"
#include "IMGUIText.h"
#include "IMGUISameLine.h"
CIMGUIParticleComponent::CIMGUIParticleComponent()
{
}

CIMGUIParticleComponent::~CIMGUIParticleComponent()
{
}

void CIMGUIParticleComponent::UpdateInfo(CGameObject* Object)
{
	Enable(true);
}

bool CIMGUIParticleComponent::Init()
{
	CIMGUIWidgetComponent::Init();
	CIMGUIText* Text;
	CIMGUISameLine* SameLine;

	m_Header = m_Owner->AddWidget<CIMGUICollapsingHeader>("ObjectInfo");




	Text = m_Owner->AddWidget<CIMGUIText>("##Title");
	Text->SetText("ObjectInfo");
	m_vecWidgetComponent.push_back(Text);

#pragma region Name
	Text = m_Owner->AddWidget<CIMGUIText>("##ObjectName1");
	Text->SetText("ObjectName");
	m_vecWidgetComponent.push_back(Text);
	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidgetComponent.push_back(SameLine);


#pragma endregion


	m_Header->WidgetPush(m_vecWidgetComponent);
	m_vecWidgetComponent.push_back(m_Header);
	return true;
}

void CIMGUIParticleComponent::Update(float DeltaTime)
{
}
