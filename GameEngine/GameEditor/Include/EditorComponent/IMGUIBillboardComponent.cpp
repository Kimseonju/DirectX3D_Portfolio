#include "../pch.h"
#include "IMGUIBillboardComponent.h"
#include "IMGUICollapsingHeader.h"
#include "IMGUIText.h"
#include "IMGUITextInput.h"
#include "IMGUISameLine.h"
#include "IMGUICheckBox.h"
#include "IMGUIButton.h"
#include "IMGUIFileDialogWidget.h"
#include "COmponent/BillboardComponent.h"
CIMGUIBillboardComponent::CIMGUIBillboardComponent()
{
}

CIMGUIBillboardComponent::~CIMGUIBillboardComponent()
{
}

void CIMGUIBillboardComponent::UpdateInfo(CSceneComponent* _Component)
{

	CBillboardComponent* Component = (CBillboardComponent*)_Component;
	m_Material =Component->GetMaterial(0);
	std::string Name = m_Material->GetName();
	m_MaterialName->SetText(Name.c_str());

	const MaterialTextureInfo* Info = m_Material->GetMaterialTextureInfo();
	m_TextureName->SetText(Info->pTexture->GetName().c_str());
}

bool CIMGUIBillboardComponent::Init()
{
	CIMGUIWidgetComponent::Init();
	CIMGUIText* Text;
	CIMGUISameLine* SameLine;

	m_Header = m_Owner->AddWidget<CIMGUICollapsingHeader>("Billboard");

#pragma region Name
	Text = AddComponentWidget<CIMGUIText>("MaterialName", 100.f, 20.f);
	Text->SetText("Name");
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_MaterialName = AddComponentWidget<CIMGUIText>("##MaterialName", 100.f, 20.f);
#pragma endregion

	//const MaterialTextureInfo* Info = m_Material->GetMaterialTextureInfo();
	
	Text = AddComponentWidget<CIMGUIText>("MaterialName", 100.f,20.f);
	Text->SetText("Name");
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");
	m_TextureName = AddComponentWidget<CIMGUIText>("##TextureName", 100.f, 20.f);
	//m_TextureName->SetText(Info->pTexture->GetName().c_str());
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");
	m_TextureChangeButton = AddComponentWidget<CIMGUIButton>("##TextureChangeButton", 100.f, 20.f);
	m_TextureChangeButton->SetText("TextureChange");
	m_TextureChangeButton->SetClickCallback(this, &CIMGUIBillboardComponent::ButtonTextureChangeCallback);


	m_Header->WidgetPush(m_vecWidgetComponent);
	m_vecWidgetComponent.push_back(m_Header);

	return true;
}

void CIMGUIBillboardComponent::Update(float DeltaTime)
{

}


void CIMGUIBillboardComponent::ButtonTextureChangeCallback()
{
	if (m_FileDialog)
		return;
	m_FileDialog = m_Owner->AddWidget<CIMGUIFileDialogWidget>("IMGUIFileDialogWidget");
	m_FileDialog->FileDialogSetting("TextureSelect", "Choose File", ".png,.jpg,.jpeg,.tga", "../Bin/Mesh", Vector2(300.f, 200.f));
	m_FileDialog->SetClickCallback(this, &CIMGUIBillboardComponent::FileDialogWidget_TextureChangeCallback);
}

void CIMGUIBillboardComponent::FileDialogWidget_TextureChangeCallback(std::string FileName)
{
	std::string FilePath = m_FileDialog->GetFilePath();

	std::basic_string<TCHAR> converted(FilePath.begin(), FilePath.end());
	const TCHAR* tchar = converted.c_str();

	m_Material->SetTextureFullPath(0, FileName, tchar);

	m_Owner->DeleteWidget(m_FileDialog);
	m_FileDialog = nullptr;

}
