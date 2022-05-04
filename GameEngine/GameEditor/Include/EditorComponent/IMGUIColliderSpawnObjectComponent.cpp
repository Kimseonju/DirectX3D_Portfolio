#include "../pch.h"
#include "IMGUIColliderSpawnObjectComponent.h"
#include "IMGUICollapsingHeader.h"
#include "IMGUIText.h"
#include "IMGUITextInput.h"
#include "IMGUISameLine.h"
#include "IMGUICheckBox.h"
#include "IMGUIListBox.h"
#include "IMGUIButton.h"
#include "IMGUIComboBox.h"
#include "IMGUIManager.h"
#include "IMGUIDrag.h"
#include "../EditorWindow/ObjectWindow.h"
#include "Scene/Scene.h"
#include "Scene/CameraManager.h"
#include "Scene/SceneManager.h"

CIMGUIColliderSpawnObjectComponent::CIMGUIColliderSpawnObjectComponent():
	m_InputPosX(nullptr),
	m_InputPosY(nullptr),
	m_InputPosZ(nullptr),
	m_InputRotX(nullptr),
	m_InputRotY(nullptr),
	m_InputRotZ(nullptr),
	m_InputScaleX(nullptr),
	m_InputScaleY(nullptr),
	m_InputScaleZ(nullptr),
	m_MonsterList(nullptr),
	m_MonsterName(nullptr),
	m_CreateMonsterButton(nullptr),
	m_CreateMoveButton(nullptr),
	m_Target(nullptr)
{
}

CIMGUIColliderSpawnObjectComponent::~CIMGUIColliderSpawnObjectComponent()
{
}

void CIMGUIColliderSpawnObjectComponent::UpdateInfo(CGameObject* Object)
{
	CColliderSpawnObject* Obj = (CColliderSpawnObject*)Object;
	m_Object = Obj;
	if (!m_Object)
	{
		return;
	}
}

bool CIMGUIColliderSpawnObjectComponent::Init()
{
	CIMGUIWidgetComponent::Init();
	CIMGUIText* Text;
	CIMGUISameLine* SameLine;

	m_Header = m_Owner->AddWidget<CIMGUICollapsingHeader>("ColliderSpawn");


	m_MonsterList = AddComponentWidget<CIMGUIListBox>("ObjectListBox", 300.f, 100.f);
	m_MonsterList->SetBorder(false);
	m_MonsterList->SetSelectCallback<CIMGUIColliderSpawnObjectComponent>(this, &CIMGUIColliderSpawnObjectComponent::MonsterSpawnObjectCallback);

	Text = AddComponentWidget<CIMGUIText>("MonsterName");
	Text->SetText("MonsterName");
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");
	m_MonsterName = AddComponentWidget<CIMGUITextInput>("##MonsterName", 100.f, 20.f);

	Text = AddComponentWidget<CIMGUIText>("Text_Position");
	Text->SetText("Position");
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");
	m_InputPosX = AddComponentWidget<CIMGUIDrag>("##InputPosX", 60.f, 20.f);
	m_InputPosX->SetNumberFloat(true);
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputPosY = AddComponentWidget<CIMGUIDrag>("##InputPosY", 60.f, 20.f);
	m_InputPosY->SetNumberFloat(true);
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputPosZ = AddComponentWidget<CIMGUIDrag>("##m_InputPosZ", 60.f, 20.f);
	m_InputPosZ->SetNumberFloat(true);




	Text = AddComponentWidget<CIMGUIText>("Text_Rot");
	Text->SetText("Rot");
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputRotX = AddComponentWidget<CIMGUIDrag>("##InputRotX", 60.f, 20.f);
	m_InputRotX->SetNumberFloat(true);
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputRotY = AddComponentWidget<CIMGUIDrag>("##InputRotY", 60.f, 20.f);
	m_InputRotY->SetNumberFloat(true);
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputRotZ = AddComponentWidget<CIMGUIDrag>("##InputRotZ", 60.f, 20.f);
	m_InputRotZ->SetNumberFloat(true);


	Text = AddComponentWidget<CIMGUIText>("Text_Rot");
	Text->SetText("Scale");
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputScaleX = AddComponentWidget<CIMGUIDrag>("##InputScaleX", 60.f, 20.f);
	m_InputScaleX->SetNumberFloat(true);
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputScaleY = AddComponentWidget<CIMGUIDrag>("##InputScaleY", 60.f, 20.f);
	m_InputScaleY->SetNumberFloat(true);
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_InputScaleZ = AddComponentWidget<CIMGUIDrag>("##InputScaleZ", 60.f, 20.f);
	m_InputScaleZ->SetNumberFloat(true);


	m_CreateMonsterButton = AddComponentWidget<CIMGUIButton>("CreateMonster", 100.f, 30.f);
	m_CreateMonsterButton->SetClickCallback< CIMGUIColliderSpawnObjectComponent>(this, &CIMGUIColliderSpawnObjectComponent::CreateMonsterSpawnBtnCallback);

	m_Header->WidgetPush(m_vecWidgetComponent);
	m_vecWidgetComponent.push_back(m_Header);

	return true;
}

void CIMGUIColliderSpawnObjectComponent::Update(float DeltaTime)
{
	m_MonsterList->Clear();
	std::vector<ColliderSpawnData*>& vec = m_Object->GetSpawnData();
	for (size_t i = 0; i < vec.size(); ++i)
	{
		m_MonsterList->AddItem(std::to_string(i).c_str());
	}
}

void CIMGUIColliderSpawnObjectComponent::CreateMonsterSpawnBtnCallback()
{
	Vector3 Pos;
	Vector3 Rot;
	Vector3 Scale;
	std::string Name = "";
	Name = m_MonsterName->GetTextMultibyte();
	Pos.x = m_InputPosX->GetValueFloat();
	Pos.y = m_InputPosY->GetValueFloat();
	Pos.z = m_InputPosZ->GetValueFloat();

	Rot.x = m_InputRotX->GetValueFloat();
	Rot.y = m_InputRotY->GetValueFloat();
	Rot.z = m_InputRotZ->GetValueFloat();

	Scale.x = m_InputScaleX->GetValueFloat();
	Scale.y = m_InputScaleY->GetValueFloat();
	Scale.z = m_InputScaleZ->GetValueFloat();

	m_Object->SettingCollider(Pos, Rot, Scale);
}

void CIMGUIColliderSpawnObjectComponent::MonsterSpawnObjectCallback(int SelectIndex, const char* Item)
{
	std::vector<ColliderSpawnData*>& vec = m_Object->GetSpawnData();

	m_InputPosX->SetFloat(vec[SelectIndex]->Pos.x);
	m_InputPosY->SetFloat(vec[SelectIndex]->Pos.y);
	m_InputPosZ->SetFloat(vec[SelectIndex]->Pos.z);

	m_InputRotX->SetFloat(vec[SelectIndex]->Rot.x);
	m_InputRotY->SetFloat(vec[SelectIndex]->Rot.y);
	m_InputRotZ->SetFloat(vec[SelectIndex]->Rot.z);

	m_InputScaleX->SetFloat(vec[SelectIndex]->Scale.x);
	m_InputScaleY->SetFloat(vec[SelectIndex]->Scale.y);
	m_InputScaleZ->SetFloat(vec[SelectIndex]->Scale.z);

}

