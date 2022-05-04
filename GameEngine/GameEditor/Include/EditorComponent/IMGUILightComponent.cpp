#include "../pch.h"
#include "IMGUILightComponent.h"
#include "IMGUICollapsingHeader.h"
#include "IMGUIText.h"
#include "IMGUITextInput.h"
#include "IMGUISameLine.h"
#include "IMGUICheckBox.h"
#include "IMGUIRadioButton.h"
#include "IMGUIDrag.h"
CIMGUILightComponent::CIMGUILightComponent():
	m_LightTypeRadioBtn(nullptr),
	m_InputDistance(nullptr),
	m_InputDiffuseR(nullptr),
	m_InputDiffuseG(nullptr),
	m_InputDiffuseB(nullptr),
	m_InputDiffuseA(nullptr),
	m_InputAmbientR(nullptr),
	m_InputAmbientG(nullptr),
	m_InputAmbientB(nullptr),
	m_InputAmbientA(nullptr),
	m_InputSpecularR(nullptr),
	m_InputSpecularG(nullptr),
	m_InputSpecularB(nullptr),
	m_InputSpecularA(nullptr)
{
}

CIMGUILightComponent::~CIMGUILightComponent()
{
}

void CIMGUILightComponent::ComponentUpdateInfo(CSceneComponent* Component)
{
	m_Component = (CLightComponent*)Component;
}
bool CIMGUILightComponent::Init()
{
	CIMGUIWidgetComponent::Init();
	CIMGUIText* Text;
	CIMGUISameLine* SameLine;

	m_Header = m_Owner->AddWidget<CIMGUICollapsingHeader>("Light");

	m_LightTypeRadioBtn = AddComponentWidget<CIMGUIRadioButton>("LightType");
	m_LightTypeRadioBtn->AddItem("Dir");
	m_LightTypeRadioBtn->AddItem("Point");
	m_LightTypeRadioBtn->AddItem("Spot");
	m_LightTypeRadioBtn->SetSelectCallback(this, &CIMGUILightComponent::LightTypeRadiobtnListCallback);

#pragma region Position

	Text = AddComponentWidget<CIMGUIText>("Text_Distance");
	Text->SetText("Distance");

	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputDistance = AddComponentWidget<CIMGUIDrag>("##Input_Distance", 60.f, 20.f);
	m_InputDistance->SetNumberFloat(true);
	m_InputDistance->SetInputCallback<CIMGUILightComponent>(this, &CIMGUILightComponent::InputDistance);
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

#pragma region Rotation
	Text = AddComponentWidget<CIMGUIText>("Text_Rotation");
	Text->SetText("Diffuse");

	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputDiffuseR = AddComponentWidget<CIMGUIDrag>("##Input_DiffuseR", 60.f, 20.f);
	m_InputDiffuseR->SetNumberFloat(true);
	m_InputDiffuseR->SetInputCallback<CIMGUILightComponent>(this, &CIMGUILightComponent::InputDiffuseR);
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputDiffuseG = AddComponentWidget<CIMGUIDrag>("##Input_DiffuseG", 60.f, 20.f);
	m_InputDiffuseG->SetNumberFloat(true);
	m_InputDiffuseG->SetInputCallback<CIMGUILightComponent>(this, &CIMGUILightComponent::InputDiffuseG);
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputDiffuseB = AddComponentWidget<CIMGUIDrag>("##Input_DiffuseB", 60.f, 20.f);
	m_InputDiffuseB->SetNumberFloat(true);
	m_InputDiffuseB->SetInputCallback<CIMGUILightComponent>(this, &CIMGUILightComponent::InputDiffuseB);
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputDiffuseA = AddComponentWidget<CIMGUIDrag>("##Input_DiffuseA", 60.f, 20.f);
	m_InputDiffuseA->SetNumberFloat(true);
	m_InputDiffuseA->SetInputCallback<CIMGUILightComponent>(this, &CIMGUILightComponent::InputDiffuseA);
#pragma endregion

#pragma region Scale

	Text = AddComponentWidget<CIMGUIText>("Text_Scale");
	Text->SetText("Ambient");

	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputAmbientR = AddComponentWidget<CIMGUIDrag>("##Input_AmbientR", 60.f, 20.f);
	m_InputAmbientR->SetNumberFloat(true);
	m_InputAmbientR->SetInputCallback<CIMGUILightComponent>(this, &CIMGUILightComponent::InputAmbientR);
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputAmbientG = AddComponentWidget<CIMGUIDrag>("##Input_AmbientG", 60.f, 20.f);
	m_InputAmbientG->SetNumberFloat(true);
	m_InputAmbientG->SetInputCallback<CIMGUILightComponent>(this, &CIMGUILightComponent::InputAmbientG);
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputAmbientB = AddComponentWidget<CIMGUIDrag>("##Input_AmbientB", 60.f, 20.f);
	m_InputAmbientB->SetNumberFloat(true);
	m_InputAmbientB->SetInputCallback<CIMGUILightComponent>(this, &CIMGUILightComponent::InputAmbientB);
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputAmbientA = AddComponentWidget<CIMGUIDrag>("##Input_AmbientA", 60.f, 20.f);
	m_InputAmbientA->SetNumberFloat(true);
	m_InputAmbientA->SetInputCallback<CIMGUILightComponent>(this, &CIMGUILightComponent::InputAmbientA);

#pragma endregion

#pragma region Scale

	Text = AddComponentWidget<CIMGUIText>("Text_Scale");
	Text->SetText("Specular");

	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputSpecularR = AddComponentWidget<CIMGUIDrag>("##Input_SpecularR", 60.f, 20.f);
	m_InputSpecularR->SetNumberFloat(true);
	m_InputSpecularR->SetInputCallback<CIMGUILightComponent>(this, &CIMGUILightComponent::InputSpecularR);
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputSpecularG = AddComponentWidget<CIMGUIDrag>("##Input_SpecularG", 60.f, 20.f);
	m_InputSpecularG->SetNumberFloat(true);
	m_InputSpecularG->SetInputCallback<CIMGUILightComponent>(this, &CIMGUILightComponent::InputSpecularG);
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputSpecularB = AddComponentWidget<CIMGUIDrag>("##Input_SpecularB", 60.f, 20.f);
	m_InputSpecularB->SetNumberFloat(true);
	m_InputSpecularB->SetInputCallback<CIMGUILightComponent>(this, &CIMGUILightComponent::InputSpecularB);
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputSpecularA = AddComponentWidget<CIMGUIDrag>("##Input_SpecularA", 60.f, 20.f);
	m_InputSpecularA->SetNumberFloat(true);
	m_InputSpecularA->SetInputCallback<CIMGUILightComponent>(this, &CIMGUILightComponent::InputSpecularA);

#pragma endregion

	m_Header->WidgetPush(m_vecWidgetComponent);
	m_vecWidgetComponent.push_back(m_Header);

	return true;
}

void CIMGUILightComponent::Update(float DeltaTime)
{
	Vector4 Diffuse = m_Component->GetDiffuse();

	m_InputDiffuseR->SetFloat(Diffuse.x);
	m_InputDiffuseG->SetFloat(Diffuse.y);
	m_InputDiffuseB->SetFloat(Diffuse.z);
	m_InputDiffuseA->SetFloat(Diffuse.w);


	Vector4 Ambient = m_Component->GetAmbient();
	m_InputAmbientR->SetFloat(Ambient.x);
	m_InputAmbientG->SetFloat(Ambient.y);
	m_InputAmbientB->SetFloat(Ambient.z);
	m_InputAmbientA->SetFloat(Ambient.w);


	Vector4 Specular = m_Component->GetSpecular();

	m_InputSpecularR->SetFloat(Specular.x);
	m_InputSpecularG->SetFloat(Specular.x);
	m_InputSpecularB->SetFloat(Specular.x);
	m_InputSpecularA->SetFloat(Specular.x);

}

void CIMGUILightComponent::LightTypeRadiobtnListCallback(int SelectIndex, const char* Item)
{
	m_Component->SetLightType((Light_Type)SelectIndex);
}

void CIMGUILightComponent::InputDistance()
{
	float x = m_InputDistance->GetValueFloat();
	m_Component->SetDistance(x);
}

void CIMGUILightComponent::InputDiffuseR()
{
	float f = m_InputDiffuseR->GetValueFloat();

	Vector4 vec4 =m_Component->GetDiffuse();
	vec4.x = f;
	
	m_Component->SetDiffuse(vec4);
}

void CIMGUILightComponent::InputDiffuseG()
{
	float f = m_InputDiffuseR->GetValueFloat();

	Vector4 vec4 = m_Component->GetDiffuse();
	vec4.y = f;

	m_Component->SetDiffuse(vec4);
}


void CIMGUILightComponent::InputDiffuseB()
{
	float f = m_InputDiffuseR->GetValueFloat();

	Vector4 vec4 = m_Component->GetDiffuse();
	vec4.z = f;

	m_Component->SetDiffuse(vec4);
}

void CIMGUILightComponent::InputDiffuseA()
{
	float f = m_InputDiffuseR->GetValueFloat();

	Vector4 vec4 = m_Component->GetDiffuse();
	vec4.w = f;

	m_Component->SetDiffuse(vec4);
}

void CIMGUILightComponent::InputAmbientR()
{
	float f = m_InputDiffuseR->GetValueFloat();

	Vector4 vec4 = m_Component->GetAmbient();
	vec4.x = f;

	m_Component->SetAmbient(vec4);
}

void CIMGUILightComponent::InputAmbientG()
{
	float f = m_InputDiffuseR->GetValueFloat();

	Vector4 vec4 = m_Component->GetAmbient();
	vec4.y = f;

	m_Component->SetAmbient(vec4);
}

void CIMGUILightComponent::InputAmbientB()
{
	float f = m_InputDiffuseR->GetValueFloat();

	Vector4 vec4 = m_Component->GetAmbient();
	vec4.z = f;

	m_Component->SetAmbient(vec4);
}

void CIMGUILightComponent::InputAmbientA()
{
	float f = m_InputDiffuseR->GetValueFloat();

	Vector4 vec4 = m_Component->GetAmbient();
	vec4.w = f;

	m_Component->SetAmbient(vec4);
}


void CIMGUILightComponent::InputSpecularR()
{
	float f = m_InputDiffuseR->GetValueFloat();

	Vector4 vec4 = m_Component->GetSpecular();
	vec4.w = f;

	m_Component->SetSpecular(vec4);
}

void CIMGUILightComponent::InputSpecularG()
{
	float f = m_InputDiffuseR->GetValueFloat();

	Vector4 vec4 = m_Component->GetSpecular();
	vec4.y = f;

	m_Component->SetSpecular(vec4);
}

void CIMGUILightComponent::InputSpecularB()
{
	float f = m_InputDiffuseR->GetValueFloat();

	Vector4 vec4 = m_Component->GetSpecular();
	vec4.z = f;

	m_Component->SetSpecular(vec4);
}

void CIMGUILightComponent::InputSpecularA()
{
	float f = m_InputDiffuseR->GetValueFloat();

	Vector4 vec4 = m_Component->GetSpecular();
	vec4.w = f;

	m_Component->SetSpecular(vec4);
}
