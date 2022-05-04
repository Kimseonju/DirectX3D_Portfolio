#include "../pch.h"
#include "IMGUISkyComponent.h"
#include "IMGUICollapsingHeader.h"
#include "IMGUIText.h"
#include "IMGUITextInput.h"
#include "IMGUISameLine.h"
#include "IMGUICheckBox.h"
#include "IMGUIButton.h"
#include "IMGUIFileDialogWidget.h"
#include "Component/SkyComponent.h"
#include "Scene/SceneManager.h"

CIMGUISkyComponent::CIMGUISkyComponent():
	m_TexName(nullptr),
	m_Component(nullptr),
	m_SelectTexBtn(nullptr),
	m_MeshLightResetButton(nullptr),
	m_FileDialog(nullptr)
{
}

CIMGUISkyComponent::~CIMGUISkyComponent()
{
}

void CIMGUISkyComponent::ComponentUpdateInfo(CSceneComponent* _Component)
{

	CSkyComponent* Component = (CSkyComponent*)_Component;
	m_Component = Component;
	CMesh* Mesh = m_Component->GetMesh();
	if (Mesh)
		m_TexName->SetText(Mesh->GetName().c_str());

}

bool CIMGUISkyComponent::Init()
{
	CIMGUIWidgetComponent::Init();
	CIMGUIText* Text;
	CIMGUISameLine* SameLine;

	m_Header = m_Owner->AddWidget<CIMGUICollapsingHeader>("Sky");

#pragma region Name
	Text = AddComponentWidget<CIMGUIText>("StaticMeshName1");
	Text->SetText("TexName");
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_TexName = AddComponentWidget<CIMGUIText>("##TexName", 100.f, 20.f);
#pragma endregion

	m_SelectTexBtn = AddComponentWidget<CIMGUIButton>("SelecTextureButton", 150, 20.f);
	m_SelectTexBtn->SetClickCallback(this, &CIMGUISkyComponent::SelectTexBtnCallback);

	m_Header->WidgetPush(m_vecWidgetComponent);
	m_vecWidgetComponent.push_back(m_Header);

	return true;
}

void CIMGUISkyComponent::Update(float DeltaTime)
{
	m_TexName->SetText(m_Component->GetMaterial(0)->GetMaterialTextureInfo(0)->Name.c_str());
}

void CIMGUISkyComponent::MeshLightResetCallback()
{
	CMesh* Mesh = m_Component->GetMesh();
	if (Mesh)
		Mesh->AllLightMaterialReset();
}

void CIMGUISkyComponent::SelectTexBtnCallback()
{
	if (m_FileDialog)
		return;
	m_FileDialog = m_Owner->AddWidget<CIMGUIFileDialogWidget>("IMGUIFileDialogWidget");
	m_FileDialog->FileDialogSetting("SelectTexture", "Choose File", ".dds,.tga,.png", "../Bin/Texture", Vector2(300.f, 200.f));
	m_FileDialog->SetClickCallback(this, &CIMGUISkyComponent::PopupSelectTexBtnCallback);
}

void CIMGUISkyComponent::PopupSelectTexBtnCallback(std::string FileName)
{
	CScene* Scene = CSceneManager::GetInst()->GetScene();

	std::string FullPathName = m_FileDialog->GetFilePathName();
	std::wstring WFullPathName;
	WFullPathName.assign(FullPathName.begin(), FullPathName.end());
	wprintf(WFullPathName.c_str());

	m_Component->SetSkyTextureFullPath(FileName, WFullPathName.c_str());

	m_Owner->DeleteWidget(m_FileDialog);
	m_FileDialog = nullptr;
}

