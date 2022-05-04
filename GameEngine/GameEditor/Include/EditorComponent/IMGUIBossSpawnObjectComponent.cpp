#include "../pch.h"
#include "IMGUIBossSpawnObjectComponent.h"
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

CIMGUIBossSpawnObjectComponent::CIMGUIBossSpawnObjectComponent()
{
}

CIMGUIBossSpawnObjectComponent::~CIMGUIBossSpawnObjectComponent()
{
}

void CIMGUIBossSpawnObjectComponent::UpdateInfo(CGameObject* Object)
{
	CBossSpawnObject* Obj = (CBossSpawnObject*)Object;
	m_Object = Obj;
	if (!m_Object)
	{
		return;
	}
}

bool CIMGUIBossSpawnObjectComponent::Init()
{
	CIMGUIWidgetComponent::Init();
	CIMGUIText* Text;
	CIMGUISameLine* SameLine;

	m_Header = m_Owner->AddWidget<CIMGUICollapsingHeader>("MonsterSpawn");


	m_MonsterList = AddComponentWidget<CIMGUIListBox>("ObjectListBox", 300.f, 100.f);
	m_MonsterList->SetBorder(false);
	m_MonsterList->SetSelectCallback<CIMGUIBossSpawnObjectComponent>(this, &CIMGUIBossSpawnObjectComponent::MonsterSpawnObjectCallback);

	Text = AddComponentWidget<CIMGUIText>("MonsterName");
	Text->SetText("MonsterName");
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");
	m_MonsterName = AddComponentWidget<CIMGUITextInput>("##MonsterName", 100.f, 20.f);

	Text = AddComponentWidget<CIMGUIText>("Text_Position");
	Text->SetText("SpawnTimer");
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");
	m_InputTimer = AddComponentWidget<CIMGUIDrag>("##InputTimer", 60.f, 20.f);
	m_InputTimer->SetNumberFloat(true);

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
	m_CreateMonsterButton->SetClickCallback< CIMGUIBossSpawnObjectComponent>(this, &CIMGUIBossSpawnObjectComponent::CreateMonsterSpawnBtnCallback);

	m_Header->WidgetPush(m_vecWidgetComponent);
	m_vecWidgetComponent.push_back(m_Header);

	return true;
}

void CIMGUIBossSpawnObjectComponent::Update(float DeltaTime)
{
	m_MonsterList->Clear();
	if (!m_Object)
	{
		Enable(false);
		return;
	}
		
	
	BossSpawnData* Data = m_Object->GetSpawnData();
	if (Data)
	{
		m_MonsterList->AddItem(Data->Name.c_str());
		m_Object->SetTimer(m_InputTimer->GetValueFloat());
	}
}

void CIMGUIBossSpawnObjectComponent::CreateMonsterSpawnBtnCallback()
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

	m_Object->SettingBoss(Name, Pos, Rot, Scale);
}

void CIMGUIBossSpawnObjectComponent::MonsterSpawnObjectCallback(int SelectIndex, const char* Item)
{
	BossSpawnData* Data = m_Object->GetSpawnData();

	m_MonsterName->SetText(Data->Name.c_str());
	m_InputPosX->SetFloat(Data->Pos.x);
	m_InputPosY->SetFloat(Data->Pos.y);
	m_InputPosZ->SetFloat(Data->Pos.z);
						  
	m_InputRotX->SetFloat(Data->Rot.x);
	m_InputRotY->SetFloat(Data->Rot.y);
	m_InputRotZ->SetFloat(Data->Rot.z);

	m_InputScaleX->SetFloat(Data->Scale.x);
	m_InputScaleY->SetFloat(Data->Scale.y);
	m_InputScaleZ->SetFloat(Data->Scale.z);

}

