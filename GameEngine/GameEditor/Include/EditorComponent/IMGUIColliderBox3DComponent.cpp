#include "../pch.h"
#include "IMGUIColliderBox3DComponent.h"
#include "IMGUICollapsingHeader.h"
#include "IMGUIText.h"
#include "IMGUISameLine.h"
#include "IMGUIDrag.h"

#include "Component/ColliderBox3D.h"
CIMGUIColliderBox3DComponent::CIMGUIColliderBox3DComponent():
	m_Component(nullptr),
	m_InputLengthX(nullptr),
	m_InputLengthY(nullptr),
	m_InputLengthZ(nullptr)
{
}

CIMGUIColliderBox3DComponent::~CIMGUIColliderBox3DComponent()
{
}

void CIMGUIColliderBox3DComponent::ComponentUpdateInfo(CSceneComponent* Component)
{
	m_Component = (CColliderBox3D*)Component;
	Box3DInfo Info = m_Component->GetInfo();

	m_InputLengthX->SetFloat(Info.Length[0]);
	m_InputLengthY->SetFloat(Info.Length[1]);
	m_InputLengthZ->SetFloat(Info.Length[2]);
}

bool CIMGUIColliderBox3DComponent::Init()
{
	CIMGUIWidgetComponent::Init();
	CIMGUIText* Text;
	CIMGUISameLine* SameLine;

	m_Header = m_Owner->AddWidget<CIMGUICollapsingHeader>("ColliderBox3DComponent");


	Text = AddComponentWidget<CIMGUIText>("InputLengthXText");
	Text->SetText("InputLengthX");
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");
	m_InputLengthX = AddComponentWidget<CIMGUIDrag>("##InputLengthX", 60.f, 20.f);
	m_InputLengthX->SetNumberFloat(true);
	m_InputLengthX->SetInputCallback<CIMGUIColliderBox3DComponent>(this, &CIMGUIColliderBox3DComponent::InputLengthX);


	Text = AddComponentWidget<CIMGUIText>("InputLengthYText");
	Text->SetText("InputLengthY");
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");
	m_InputLengthY = AddComponentWidget<CIMGUIDrag>("##InputLengthY", 60.f, 20.f);
	m_InputLengthY->SetNumberFloat(true);
	m_InputLengthY->SetInputCallback<CIMGUIColliderBox3DComponent>(this, &CIMGUIColliderBox3DComponent::InputLengthY);

	Text = AddComponentWidget<CIMGUIText>("InputLengthZText");
	Text->SetText("InputLengthZ");
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");
	m_InputLengthZ = AddComponentWidget<CIMGUIDrag>("##InputLengthZ", 60.f, 20.f);
	m_InputLengthZ->SetNumberFloat(true);
	m_InputLengthZ->SetInputCallback<CIMGUIColliderBox3DComponent>(this, &CIMGUIColliderBox3DComponent::InputLengthZ);

	m_Header->WidgetPush(m_vecWidgetComponent);
	m_vecWidgetComponent.push_back(m_Header);

	return true;
}

void CIMGUIColliderBox3DComponent::Update(float DeltaTime)
{
	if (m_Component)
	{
		Box3DInfo Info = m_Component->GetInfo();

		m_InputLengthX->SetFloat(Info.Length[0]);
		m_InputLengthY->SetFloat(Info.Length[1]);
		m_InputLengthZ->SetFloat(Info.Length[2]);
	}

}

void CIMGUIColliderBox3DComponent::InputLengthX()
{
	Box3DInfo Info = m_Component->GetInfo();
	
	m_Component->SetExtent(m_InputLengthX->GetValueFloat(), Info.Length[1], Info.Length[2]);
}

void CIMGUIColliderBox3DComponent::InputLengthY()
{
	Box3DInfo Info = m_Component->GetInfo();

	m_Component->SetExtent(Info.Length[0], m_InputLengthY->GetValueFloat(), Info.Length[2]);
}

void CIMGUIColliderBox3DComponent::InputLengthZ()
{
	Box3DInfo Info = m_Component->GetInfo();

	m_Component->SetExtent(Info.Length[0], Info.Length[1], m_InputLengthZ->GetValueFloat());
}
