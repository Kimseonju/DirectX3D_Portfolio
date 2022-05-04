#include "../pch.h"
#include "IMGUIStaticMeshComponent.h"
#include "IMGUICollapsingHeader.h"
#include "IMGUIText.h"
#include "IMGUITextInput.h"
#include "IMGUISameLine.h"
#include "IMGUICheckBox.h"
#include "IMGUIButton.h"
#include "IMGUIFileDialogWidget.h"
#include "Component/StaticMeshComponent.h"
#include "Scene/SceneManager.h"
CIMGUIStaticMeshComponent::CIMGUIStaticMeshComponent():
	m_MeshName(nullptr),
	m_Component(nullptr),
	m_SelectMeshButton(nullptr),
	m_MeshLightResetButton(nullptr),
	m_FileDialog(nullptr)
{
}

CIMGUIStaticMeshComponent::~CIMGUIStaticMeshComponent()
{
}

void CIMGUIStaticMeshComponent::ComponentUpdateInfo(CSceneComponent* _Component)
{
	
	CStaticMeshComponent* Component = (CStaticMeshComponent *)_Component;
	m_Component = Component;
	CMesh* Mesh= m_Component->GetMesh();
	if(Mesh)
		m_MeshName->SetText(Mesh->GetName().c_str());

}

bool CIMGUIStaticMeshComponent::Init()
{
	CIMGUIWidgetComponent::Init();
	CIMGUIText* Text;
	CIMGUISameLine* SameLine;

	m_Header = m_Owner->AddWidget<CIMGUICollapsingHeader>("StaticMesh");

#pragma region Name
	Text = AddComponentWidget<CIMGUIText>("StaticMeshName1");
	Text->SetText("Name");
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_MeshName = AddComponentWidget<CIMGUIText>("##StaticMeshName2", 100.f, 20.f);
#pragma endregion

	m_SelectMeshButton = AddComponentWidget<CIMGUIButton>("SelectMeshButton", 100.f, 20.f);
	
	m_SelectMeshButton->SetClickCallback(this, &CIMGUIStaticMeshComponent::SelectMeshButtonCallback);


	m_MeshLightResetButton = AddComponentWidget<CIMGUIButton>("MeshLightResetButton", 100.f, 20.f);

	m_MeshLightResetButton->SetClickCallback(this, &CIMGUIStaticMeshComponent::MeshLightResetCallback);

	m_Header->WidgetPush(m_vecWidgetComponent);
	m_vecWidgetComponent.push_back(m_Header);

	return true;
}

void CIMGUIStaticMeshComponent::Update(float DeltaTime)
{
	CMesh* Mesh = m_Component->GetMesh();
	if (Mesh)
		m_MeshName->SetText(Mesh->GetName().c_str());
}

void CIMGUIStaticMeshComponent::MeshLightResetCallback()
{
	CMesh* Mesh = m_Component->GetMesh();
	if (Mesh)
		Mesh->AllLightMaterialReset();
}

void CIMGUIStaticMeshComponent::SelectMeshButtonCallback()
{
	if (m_FileDialog)
		return;
	m_FileDialog = m_Owner->AddWidget<CIMGUIFileDialogWidget>("IMGUIFileDialogWidget");
	m_FileDialog->FileDialogSetting("SelectMesh", "Choose File", ".msh", "../Bin/Mesh", Vector2(300.f, 200.f));
	m_FileDialog->SetClickCallback(this, &CIMGUIStaticMeshComponent::PopupSelectMeshCallback);
}

void CIMGUIStaticMeshComponent::PopupSelectMeshCallback(std::string FileName)
{
	CScene* Scene = CSceneManager::GetInst()->GetScene();
	CMesh* Mesh= Scene->GetResource()->FindMesh(FileName);
	

	if (!Mesh)
	{
		std::string FullPathName = m_FileDialog->GetFilePathName();
		Scene->GetResource()->LoadMeshFullPathMultibyte(Mesh_Type::StaticMesh, FileName, FullPathName.c_str());
	}
	m_Component->SetMesh(FileName);

	m_Owner->DeleteWidget(m_FileDialog);
	m_FileDialog = nullptr;
}
