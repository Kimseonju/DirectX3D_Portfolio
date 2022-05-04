
#include "IMGUIRenderOptionComponent.h"
#include "IMGUISameLine.h"
#include "IMGUIText.h"
#include "IMGUIManager.h"
#include "IMGUIDrag.h"
#include "IMGUICollapsingHeader.h"
#include "IMGUICheckBox.h"
#include "Scene/SceneManager.h"
#include "Component/Camera.h"
#include "Render/RenderManager.h"
CIMGUIRenderOptionComponent::CIMGUIRenderOptionComponent():
	m_OutLine(nullptr),
	m_CelShader(nullptr),
	m_ToonShader(nullptr),
	m_FXAA(nullptr),
	m_RenderManager(nullptr)
{
}

CIMGUIRenderOptionComponent::~CIMGUIRenderOptionComponent()
{
}


bool CIMGUIRenderOptionComponent::Init()
{
	

	m_RenderManager = CRenderManager::GetInst();
	CIMGUIText* Text;
	CIMGUISameLine* SameLine;
	
	m_Header = m_Owner->AddWidget<CIMGUICollapsingHeader>("RenderOption");




	Text = AddComponentWidget<CIMGUIText>("##Title");
	Text->SetText("Info");

#pragma region Name
	Text = AddComponentWidget<CIMGUIText>("ObjectName1");
	Text->SetText("Name");
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	//m_ObjectName = AddComponentWidget<CIMGUITextInput>("##ObjectName", 100.f, 20.f);
	//m_ObjectName->SetInputCallback<CIMGUIObjectInfoComponent>(this, &CIMGUIObjectInfoComponent::InputObjectName);
	//m_ObjectName->AddFlag(ImGuiInputTextFlags_EnterReturnsTrue);

#pragma endregion

	m_OutLine = AddComponentWidget<CIMGUICheckBox>("OutLine", 300.f, 20.f);
	m_OutLine->SetCheckCallback<CIMGUIRenderOptionComponent>(this, &CIMGUIRenderOptionComponent::OutLineCheckBoxClick);
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_CelShader = AddComponentWidget<CIMGUICheckBox>("CelShader", 300.f, 20.f);
	m_CelShader->SetCheckCallback<CIMGUIRenderOptionComponent>(this, &CIMGUIRenderOptionComponent::CelShaderCheckBoxClick);

	m_ToonShader = AddComponentWidget<CIMGUICheckBox>("ToonShader", 300.f, 20.f);
	m_ToonShader->SetCheckCallback<CIMGUIRenderOptionComponent>(this, &CIMGUIRenderOptionComponent::ToonShaderCheckBoxClick);
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_FXAA = AddComponentWidget<CIMGUICheckBox>("FXAA", 300.f, 20.f);
	m_FXAA->SetCheckCallback<CIMGUIRenderOptionComponent>(this, &CIMGUIRenderOptionComponent::FXAACheckBoxClick);
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");
	m_Header->WidgetPush(m_vecWidgetComponent);
	m_vecWidgetComponent.push_back(m_Header);
	return true;
}

void CIMGUIRenderOptionComponent::Update(float DeltaTime)
{
	
}

void CIMGUIRenderOptionComponent::OutLineCheckBoxClick(bool Enable)
{
	m_RenderManager->SetOutLine(Enable);
}

void CIMGUIRenderOptionComponent::CelShaderCheckBoxClick(bool Enable)
{
	m_RenderManager->SetOutLine(Enable);
}

void CIMGUIRenderOptionComponent::ToonShaderCheckBoxClick(bool Enable)
{
	m_RenderManager->SetToonShader(Enable);
}

void CIMGUIRenderOptionComponent::FXAACheckBoxClick(bool Enable)
{
	m_RenderManager->SetFXAA(Enable);
}
