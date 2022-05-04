#include "../pch.h"
#include "IMGUIColliderSphereComponent.h"
#include "IMGUICollapsingHeader.h"
#include "IMGUIText.h"
#include "IMGUISameLine.h"
#include "IMGUIDrag.h"

#include "Component/ColliderSphere.h"
CIMGUIColliderSphereComponent::CIMGUIColliderSphereComponent():
	m_Component(nullptr),
	m_InputRadius(nullptr)
{
}

CIMGUIColliderSphereComponent::~CIMGUIColliderSphereComponent()
{
}

void CIMGUIColliderSphereComponent::ComponentUpdateInfo(CSceneComponent* Component)
{
	m_Component = (CColliderSphere*)Component;
	SphereInfo Info = m_Component->GetInfo();
	m_InputRadius->SetFloat(Info.Radius);
}

bool CIMGUIColliderSphereComponent::Init()
{
	CIMGUIWidgetComponent::Init();
	CIMGUIText* Text;
	CIMGUISameLine* SameLine;

	m_Header = m_Owner->AddWidget<CIMGUICollapsingHeader>("ColliderSphere");


	Text = AddComponentWidget<CIMGUIText>("Radius");
	Text->SetText("Radius");

	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");
	m_InputRadius = AddComponentWidget<CIMGUIDrag>("##InputRadius", 60.f, 20.f);
	m_InputRadius->SetNumberFloat(true);
	m_InputRadius->SetInputCallback<CIMGUIColliderSphereComponent>(this, &CIMGUIColliderSphereComponent::InputRadius);

	m_Header->WidgetPush(m_vecWidgetComponent);
	m_vecWidgetComponent.push_back(m_Header);

	return true;
}

void CIMGUIColliderSphereComponent::Update(float DeltaTime)
{
	if (m_Component)
	{
		m_InputRadius->SetFloat(m_Component->GetInfo().Radius);
	}
}

void CIMGUIColliderSphereComponent::InputRadius()
{
	m_Component->SetRadius(m_InputRadius->GetValueFloat());
}
