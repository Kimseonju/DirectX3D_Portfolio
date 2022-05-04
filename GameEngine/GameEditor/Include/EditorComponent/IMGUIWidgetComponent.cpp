#include "../pch.h"
#include "IMGUIWidgetComponent.h"
#include "IMGUIWidget.h"
#include <IMGUICollapsingHeader.h>
CIMGUIWidgetComponent::CIMGUIWidgetComponent():
	m_Owner(nullptr),
	m_Enable(false),
	m_Header(nullptr)
{
}

CIMGUIWidgetComponent::~CIMGUIWidgetComponent()
{
}

bool CIMGUIWidgetComponent::Init()
{

	return true;
}

void CIMGUIWidgetComponent::Update(float DeltaTime)
{
}

void CIMGUIWidgetComponent::Enable(bool Enable)
{
	size_t Size = m_vecWidgetComponent.size();
	for (size_t i = 0; i < Size; i++)
	{
		m_vecWidgetComponent[i]->Enable(Enable);
	}
	m_Enable = Enable;
}

void CIMGUIWidgetComponent::ComponentUpdateInfo(CSceneComponent* Component)
{
}
