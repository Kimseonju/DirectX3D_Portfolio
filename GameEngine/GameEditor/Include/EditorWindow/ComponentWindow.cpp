#include "../pch.h"
#include "ComponentWindow.h"
#include "InspectorWindow.h"
#include "ObjectWindow.h"
#include "ToolWindow.h"

#include "IMGUIListBox.h"
#include "IMGUIManager.h"
#include "IMGUIText.h"
#include "IMGUISameLine.h"
#include "IMGUIComboBox.h"
#include "IMGUIButton.h"

#include "IMGUIListBox.h"
#include "Component/SceneComponent.h"
#include "IMGUITextInput.h"

#include "Component/AnimationMeshComponent.h"
#include "Component/StaticMeshComponent.h"
#include "Component/BillboardComponent.h"
#include "Component/DecalComponent.h"
#include "Component/ColliderBox3D.h"
#include "Component/ColliderSphere.h"
#include "Component/Camera.h"
#include "Component/ParticleSystemComponent.h"
#include "Component/SpringArm3D.h"
#include "Component/LightComponent.h"
#include "Component/SkyComponent.h"
#include "Object/CameraMoveObject.h"
#include "Object/MonsterSpawnObject.h"
#include "Object/ColliderSpawnObject.h"
#include "Object/BossSpawnObject.h"
CComponentWindow::CComponentWindow():
	m_SelectComponent(nullptr),
	m_CreateComponentIndex(-1),
	m_ComponentListBox(nullptr),
	m_NameInput(nullptr),
	m_SelectComponentIndex(-1),
	m_ObjectWindow(nullptr)
{
}

CComponentWindow::~CComponentWindow()
{

}

bool CComponentWindow::Init()
{
	m_ComponentListBox = AddWidget<CIMGUIListBox>("ComponentListBox", 300.f, 100.f);
	m_ComponentListBox->SetBorder(false);
	m_ComponentListBox->SetSelectCallback<CComponentWindow>(this, &CComponentWindow::ComponentListCallback);


	m_ObjectWindow = (CObjectWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectWindow");

	CIMGUIButton* CreateObjButton = AddWidget<CIMGUIButton>("컴포넌트생성", 100.f, 30.f);

	CreateObjButton->SetFont("DefaultFont");

	CreateObjButton->SetClickCallback<CComponentWindow>(this, &CComponentWindow::CreateComponentButtonClick);
	return true;
}

void CComponentWindow::Update(float DeltaTime)
{
	CIMGUIWindow::Update(DeltaTime);
}

void CComponentWindow::ComponentListCallback(int SelectIndex, const char* Item)
{
	m_SelectComponentIndex = SelectIndex;
	CGameObject* Obj=m_ObjectWindow->GetSelectObject();
	if (Obj)
	{
		m_SelectComponent =Obj->FindSceneComponent(Item);

		CInspectorWindow* InspectorWindow = (CInspectorWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("InspectorWindow");
		InspectorWindow->AllComponentClose();

		ComponentUpdateInfo(m_SelectComponent);
	}
}

void CComponentWindow::ComponentUpdateInfo(CSceneComponent* Component)
{
	CInspectorWindow* InspectorWindow = (CInspectorWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("InspectorWindow");
	InspectorWindow->AllComponentClose();

	CToolWindow* ToolWindow = (CToolWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ToolWindow");
	ToolWindow->GizmoComponentUpdate(Component);

	SceneComponent_Type Type = Component->GetSceneComponentType();
	Component_Class_Type ClassType = Component->GetComponent_Class_Type();
	InspectorWindow->ObjectUpdateInfo(Component->GetOwner());
#pragma region ObjectComponent

	CCameraMoveObject* CameraMoveObject = dynamic_cast<CCameraMoveObject*>(Component->GetOwner());
	if (CameraMoveObject)
	{
		InspectorWindow->CameraMoveUpdateInfo(CameraMoveObject);
	}

	CMonsterSpawnObject* MonsterSpawnObject = dynamic_cast<CMonsterSpawnObject*>(Component->GetOwner());
	if (MonsterSpawnObject)
	{
		InspectorWindow->MonsterSpawnUpdateInfo(MonsterSpawnObject);
	}

	CColliderSpawnObject* ColliderSpawnObject = dynamic_cast<CColliderSpawnObject*>(Component->GetOwner());
	if (ColliderSpawnObject)
	{
		InspectorWindow->ColliderSpawnUpdateInfo(ColliderSpawnObject);
	}


	CBossSpawnObject* BossSpawnObject = dynamic_cast<CBossSpawnObject*>(Component->GetOwner());
	if (BossSpawnObject)
	{
		InspectorWindow->BossSpawnUpdateInfo(BossSpawnObject);
	}
#pragma endregion


	//Component_Class_Type ClassType = Compoonent->GetComponentClassType();
	switch (ClassType)
	{
	case Component_Class_Type::Default:
	{
		InspectorWindow->ComponentUpdateInfo("Transform", Component);
		break;
	}
	case Component_Class_Type::Camera:
	{
		InspectorWindow->ComponentUpdateInfo("Transform", Component);
		//CCamera* CameraComponent = (CCamera*)Component;
		//InspectorWindow->CameraUpdate(CameraComponent);
		break;
	}
	case Component_Class_Type::SpringArm:
	{
		InspectorWindow->ComponentUpdateInfo("Transform", Component);
		break;
	}
	case Component_Class_Type::ParticleSystem:
	{
		InspectorWindow->ComponentUpdateInfo("Transform", Component);
		break;
	}
	case Component_Class_Type::AnimationMesh:
	{
		InspectorWindow->ComponentUpdateInfo("Transform", Component);
		InspectorWindow->ComponentUpdateInfo("AnimationMesh", Component);
		break;
	}
	case Component_Class_Type::StaticMesh:
	{
		InspectorWindow->ComponentUpdateInfo("Transform", Component);
		InspectorWindow->ComponentUpdateInfo("StaticMesh", Component);
		break;
	}
	case Component_Class_Type::ColliderBox3D:
	{
		InspectorWindow->ComponentUpdateInfo("Transform", Component);
		InspectorWindow->ComponentUpdateInfo("ColliderBox3D", Component);
		break;
	}
	case Component_Class_Type::ColliderSphere:
	{
		InspectorWindow->ComponentUpdateInfo("Transform", Component);
		InspectorWindow->ComponentUpdateInfo("ColliderSphere", Component);
		break;
	}
	case Component_Class_Type::Billboard:
	{
		InspectorWindow->ComponentUpdateInfo("Transform", Component);
		InspectorWindow->ComponentUpdateInfo("Billboard", Component);
		break;
	}
	case Component_Class_Type::Decal:
	{
		InspectorWindow->ComponentUpdateInfo("Transform", Component);
		break;
	}

	case Component_Class_Type::Light:
	{
		InspectorWindow->ComponentUpdateInfo("Transform", Component);
		InspectorWindow->ComponentUpdateInfo("Light", Component);
		break;
	}
	case Component_Class_Type::Sky:
	{
		InspectorWindow->ComponentUpdateInfo("Transform", Component);
		InspectorWindow->ComponentUpdateInfo("Sky", Component);

		break;
	}
	case Component_Class_Type::End:
		break;
	}
}

void CComponentWindow::ComponentComboCallback(int SelectIndex, const char* Item)
{
	if (!m_ObjectWindow->GetSelectObject())
		return;

	m_CreateComponentIndex = SelectIndex;
	m_CreateCmponentName = Item;
}

void CComponentWindow::CreateComponentButtonClick()
{
	if (!m_ObjectWindow->GetSelectObject())
		return;
	// 이름을 지정하기 위한 Popup 창을 열어준다.
	CIMGUIText* Text = AddPopupWidget<CIMGUIText>("CreateComponent");
	Text->SetText("CreateComponent");

	CIMGUIComboBox* ComponentCombo = AddPopupWidget<CIMGUIComboBox>("##ComponentCombo", 100.f, 100.f);

	ComponentCombo->SetSelectCallback<CComponentWindow>(this, &CComponentWindow::ComponentComboCallback);

	ComponentCombo->AddItem("Default");
	ComponentCombo->AddItem("Camera");
	ComponentCombo->AddItem("SpringArm");
	ComponentCombo->AddItem("ParticleSystem");
	ComponentCombo->AddItem("AnimationMesh");
	ComponentCombo->AddItem("StaticMesh");
	ComponentCombo->AddItem("ColliderBox3D");
	ComponentCombo->AddItem("ColliderSphere");
	ComponentCombo->AddItem("Billboard");
	ComponentCombo->AddItem("Decal");
	ComponentCombo->AddItem("Light");
	ComponentCombo->AddItem("Sky");

	CIMGUIButton* CreateObjButton = AddPopupWidget<CIMGUIButton>("생성");
	CreateObjButton->SetFont("DefaultFont");
	CreateObjButton->SetClickCallback<CComponentWindow>(this, &CComponentWindow::InputComponentPopupButton);

	m_CreateComponentIndex = -1;
	SetPopupTitle("Component");
	EnableModalPopup();
}

void CComponentWindow::InputComponentPopupButton()
{
	if (!m_ObjectWindow->GetSelectObject())
		return;
	if (m_CreateComponentIndex == -1)
		return;
	CSceneComponent* NewComponent = nullptr;

	const char* Name = m_CreateCmponentName.c_str();

	CInspectorWindow* InspectorWindow = (CInspectorWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("InspectorWindow");
	switch ((Component_Class_Type)m_CreateComponentIndex)
	{
	case Component_Class_Type::Default:
		NewComponent = m_ObjectWindow->GetSelectObject()->CreateSceneComponent<CSceneComponent>(Name);
		break;
	case Component_Class_Type::Camera:
		NewComponent = m_ObjectWindow->GetSelectObject()->CreateSceneComponent<CCamera>(Name);
		break;
	case Component_Class_Type::SpringArm:
		NewComponent = m_ObjectWindow->GetSelectObject()->CreateSceneComponent<CSpringArm3D>(Name);
		break;
	case Component_Class_Type::ParticleSystem:
		NewComponent = m_ObjectWindow->GetSelectObject()->CreateSceneComponent<CParticleSystemComponent>(Name);
		break;
	case Component_Class_Type::AnimationMesh:
		NewComponent = m_ObjectWindow->GetSelectObject()->CreateSceneComponent<CAnimationMeshComponent>(Name);
		break;
	case Component_Class_Type::StaticMesh:
		NewComponent = m_ObjectWindow->GetSelectObject()->CreateSceneComponent<CStaticMeshComponent>(Name);
		break;
	case Component_Class_Type::ColliderBox3D:
		NewComponent = m_ObjectWindow->GetSelectObject()->CreateSceneComponent<CColliderBox3D>(Name);
		break;
	case Component_Class_Type::ColliderSphere:
		NewComponent = m_ObjectWindow->GetSelectObject()->CreateSceneComponent<CColliderSphere>(Name);
		break;
	case Component_Class_Type::Billboard:
		NewComponent = m_ObjectWindow->GetSelectObject()->CreateSceneComponent<CBillboardComponent>(Name);
		break;
	case Component_Class_Type::Decal:
		NewComponent = m_ObjectWindow->GetSelectObject()->CreateSceneComponent<CDecalComponent>(Name);
		break;
	case Component_Class_Type::Light:
		NewComponent = m_ObjectWindow->GetSelectObject()->CreateSceneComponent<CLightComponent>(Name);
		break;
	case Component_Class_Type::Sky:
		NewComponent = m_ObjectWindow->GetSelectObject()->CreateSceneComponent<CSkyComponent>(Name);
		break;
	}

	m_ComponentListBox->AddItem(NewComponent->GetName().c_str());
	if (m_ObjectWindow->GetSelectObject()->GetRootComponent()->GetName() == "DefaultRoot")
	{
		m_ObjectWindow->GetSelectObject()->SetRootComponent(NewComponent);
		SetSelectComponent(NewComponent);

		std::vector<std::string>	vecName;

		m_ObjectWindow->GetSelectObject()->GetComponentName(vecName);

		m_ComponentListBox->Clear();

		size_t	Size = vecName.size();


		for (size_t i = 0; i < vecName.size(); ++i)
		{
			AddItem(vecName[i].c_str());
		}

		CInspectorWindow* InspectorWindow = (CInspectorWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("InspectorWindow");
		InspectorWindow->AllComponentClose();
		ComponentUpdateInfo(NewComponent);


	}
	else
	{
		m_ObjectWindow->GetSelectObject()->GetRootComponent()->AddChild(NewComponent);
	}

	NewComponent->SetRelativePos(10.f, 20.f, 30.f);

	ClosePopup();
}

void CComponentWindow::CloseComponentPopupButton()
{
	ClosePopup();
}

void CComponentWindow::Clear()
{
	m_ComponentListBox->Clear();
}

void CComponentWindow::AddItem(const char* Item)
{
	m_ComponentListBox->AddItem(Item);
}
