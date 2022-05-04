#include "../pch.h"
#include "IMGUICurCameraComponent.h"
#include "IMGUISameLine.h"
#include "IMGUIText.h"
#include "IMGUIManager.h"
#include "IMGUIDrag.h"
#include "IMGUICollapsingHeader.h"
#include "Scene/SceneManager.h"
#include "Component/Camera.h"

CIMGUICurCameraComponent::CIMGUICurCameraComponent():
	m_InputPosX(nullptr),
	m_InputPosY(nullptr),
	m_InputPosZ(nullptr),
	m_InputRotX(nullptr),
	m_InputRotY(nullptr),
	m_InputRotZ(nullptr)
{
}

CIMGUICurCameraComponent::~CIMGUICurCameraComponent()
{
}

void CIMGUICurCameraComponent::SetPosition(const Vector3& Pos)
{
	m_InputPosX->SetFloat(Pos.x);
	m_InputPosY->SetFloat(Pos.y);
	m_InputPosZ->SetFloat(Pos.z);
	CCamera* Camera = CSceneManager::GetInst()->GetScene()->GetCameraManager()->GetCurrentCamera();
	if (Camera)
	{
		Camera->SetWorldPos(Pos);
	}
}
void CIMGUICurCameraComponent::SetRotation(const Vector3& Rotation)
{
	m_InputRotX->SetFloat(Rotation.x);
	m_InputRotY->SetFloat(Rotation.y);
	m_InputRotZ->SetFloat(Rotation.z);
	CCamera* Camera = CSceneManager::GetInst()->GetScene()->GetCameraManager()->GetCurrentCamera();
	if (Camera)
	{
		Camera->SetWorldRotation(Rotation);
	}
}

const Vector3 CIMGUICurCameraComponent::GetPosition()
{
	CCamera* Camera = CSceneManager::GetInst()->GetScene()->GetCameraManager()->GetCurrentCamera();
	return Camera->GetWorldPos();
}
const Vector3 CIMGUICurCameraComponent::GetRotation()
{
	CCamera* Camera = CSceneManager::GetInst()->GetScene()->GetCameraManager()->GetCurrentCamera();
	return Camera->GetRelativeRotation();
}
bool CIMGUICurCameraComponent::Init()
{

	CIMGUIWidgetComponent::Init();
	CIMGUIText* Text;
	CIMGUISameLine* SameLine;


	m_Header = m_Owner->AddWidget<CIMGUICollapsingHeader>("CurrentCamera");
#pragma region Position


	Text = AddComponentWidget<CIMGUIText>("Text_Title");
	Text->SetText("Transform");

	Text = AddComponentWidget<CIMGUIText>("Text_Position");
	Text->SetText("Position");

	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputPosX = AddComponentWidget<CIMGUIDrag>("##Camera_PosX", 60.f, 20.f);
	m_InputPosX->SetNumberFloat(true);
	m_InputPosX->SetInputCallback<CIMGUICurCameraComponent>(this, &CIMGUICurCameraComponent::InputPosX);
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputPosY = AddComponentWidget<CIMGUIDrag>("##Camera_PosY", 60.f, 20.f);
	m_InputPosY->SetNumberFloat(true);
	m_InputPosY->SetInputCallback<CIMGUICurCameraComponent>(this, &CIMGUICurCameraComponent::InputPosY);
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputPosZ = AddComponentWidget<CIMGUIDrag>("##Camera_PosZ", 60.f, 20.f);
	m_InputPosZ->SetNumberFloat(true);
	m_InputPosZ->SetInputCallback<CIMGUICurCameraComponent>(this, &CIMGUICurCameraComponent::InputPosZ);

#pragma endregion
#pragma region Rotation
	Text = AddComponentWidget<CIMGUIText>("Text_Rotation");
	Text->SetText("Rotation");

	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputRotX = AddComponentWidget<CIMGUIDrag>("##Camera_RotationX", 60.f, 20.f);
	m_InputRotX->SetNumberFloat(true);
	m_InputRotX->SetInputCallback<CIMGUICurCameraComponent>(this, &CIMGUICurCameraComponent::InputRotX);
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputRotY = AddComponentWidget<CIMGUIDrag>("##Camera_RotationY", 60.f, 20.f);
	m_InputRotY->SetNumberFloat(true);
	m_InputRotY->SetInputCallback<CIMGUICurCameraComponent>(this, &CIMGUICurCameraComponent::InputRotY);
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputRotZ = AddComponentWidget<CIMGUIDrag>("##Camera_RotationZ", 60.f, 20.f);
	m_InputRotZ->SetNumberFloat(true);
	m_InputRotZ->SetInputCallback<CIMGUICurCameraComponent>(this, &CIMGUICurCameraComponent::InputRotZ);


#pragma endregion

	m_Header->WidgetPush(m_vecWidgetComponent);
	m_vecWidgetComponent.push_back(m_Header);

	return true;
}

void CIMGUICurCameraComponent::Update(float DeltaTime)
{
	CCamera* Camera = CSceneManager::GetInst()->GetScene()->GetCameraManager()->GetCurrentCamera();
	SetPosition(Camera->GetWorldPos());
	SetRotation(Camera->GetWorldRotation());
}


void CIMGUICurCameraComponent::InputPosX()
{
	float x = m_InputPosX->GetValueFloat();
	CCamera* Camera = CSceneManager::GetInst()->GetScene()->GetCameraManager()->GetCurrentCamera();
	Vector3 Pos = Camera->GetWorldPos();
	Pos.x = x;
	Camera->SetWorldPos(Pos);
}

void CIMGUICurCameraComponent::InputPosY()
{
	float y = m_InputPosY->GetValueFloat();
	CCamera* Camera = CSceneManager::GetInst()->GetScene()->GetCameraManager()->GetCurrentCamera();
	Vector3 Pos = Camera->GetWorldPos();
	Pos.y = y;
	Camera->SetWorldPos(Pos);
}

void CIMGUICurCameraComponent::InputPosZ()
{
	float z = m_InputPosZ->GetValueFloat();
	CCamera* Camera = CSceneManager::GetInst()->GetScene()->GetCameraManager()->GetCurrentCamera();
	Vector3 Pos = Camera->GetWorldPos();
	Pos.z = z;
	Camera->SetWorldPos(Pos);
}

void CIMGUICurCameraComponent::InputRotX()
{
	float x = m_InputRotX->GetValueFloat();
	CCamera* Camera = CSceneManager::GetInst()->GetScene()->GetCameraManager()->GetCurrentCamera();
	Camera->SetRelativeRotationX(x);
}

void CIMGUICurCameraComponent::InputRotY()
{
	float y = m_InputRotY->GetValueFloat();
	CCamera* Camera = CSceneManager::GetInst()->GetScene()->GetCameraManager()->GetCurrentCamera();
	Camera->SetRelativeRotationY(y);
}

void CIMGUICurCameraComponent::InputRotZ()
{
	float z = m_InputRotZ->GetValueFloat();
	CCamera* Camera = CSceneManager::GetInst()->GetScene()->GetCameraManager()->GetCurrentCamera();
	Camera->SetRelativeRotationZ(z);
}
