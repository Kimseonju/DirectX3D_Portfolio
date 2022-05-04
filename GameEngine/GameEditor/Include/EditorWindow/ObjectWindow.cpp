#include "../pch.h"
#include "ObjectWindow.h"
#include "IMGUIButton.h"
#include "IMGUISameLine.h"
#include "IMGUIText.h"
#include "IMGUIListBox.h"
#include "GameObject.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "DetailWindow.h"
#include "IMGUITextInput.h"
#include "IMGUIComboBox.h"
#include "IMGUIManager.h"
#include "InspectorWindow.h"
#include "PrefabWindow.h"
#include <Scene/Scene.h>
#include <Scene/SceneCollision.h>
#include <Scene/SceneManager.h>
#include "Component/Collider.h"
#include "ComponentWindow.h"

#include "Global.h"

#include "Object/KianaPlayer.h"
#include "Object/SakuraPlayer.h"
#include "Object/Sniper.h"
#include "Object/AxeSoldier.h"
#include "Object/Wendy.h"
#include "object/LoadingStartObject.h"

#include "Custom/CollisionRay.h"
#include "ToolWindow.h"
#include "../EditorTool/IMGUIGizmo.h"
#include "../GlobalValue.h"
#include "Object/ClientObject.h"
#include "Object/LobbyShip.h"
#include "Object/CameraMoveObject.h"
#include "Object/ColliderSpawnObject.h"
#include "Object/MonsterSpawnObject.h"
#include "Object/BossSpawnObject.h"
#include "Object/MapCollision.h"
#include "Object/LobbyValkyrieSelectZone.h"
#include "Input.h"

CObjectWindow::CObjectWindow() :
	m_CreateObjectCount(0),
	m_CreateClassIndex(-1),
	m_CreateClient3DPrefab(false),
	m_CloneObjectCount(0),
	m_ObjListBox(nullptr),
	m_NameInput(nullptr),
	m_SelectObjectIndex(-1),
	m_PrefabWindow(nullptr),
	m_ComponentWindow(nullptr),
	m_Gizmo(nullptr),
	m_Scene(nullptr)
{
}

CObjectWindow::~CObjectWindow()
{
}



bool CObjectWindow::Init()
{
#pragma region Window

	m_Scene = CSceneManager::GetInst()->GetScene();
#pragma endregion

#pragma region ObjectWindow

	m_ObjListBox = AddWidget<CIMGUIListBox>("ObjectListBox", 300.f, 100.f);
	m_ObjListBox->SetBorder(false);
	m_ObjListBox->SetSelectCallback<CObjectWindow>(this, &CObjectWindow::ObjectListCallback);


	CIMGUIButton* CreateObjButton = AddWidget<CIMGUIButton>("오브젝트생성", 100.f, 30.f);
	CreateObjButton->SetFont("DefaultFont");
	CreateObjButton->SetClickCallback<CObjectWindow>(this, &CObjectWindow::CreateObjectButtonClick);

	CIMGUISameLine* SameLine = AddWidget<CIMGUISameLine>("SameLine");

	CreateObjButton = AddWidget<CIMGUIButton>("오브젝트삭제", 100.f, 30.f);
	CreateObjButton->SetFont("DefaultFont");
	CreateObjButton->SetClickCallback<CObjectWindow>(this, &CObjectWindow::DeleteObjectButtonClick);

	CIMGUIButton* Prefab = AddWidget<CIMGUIButton>("AddPrefab", 100.f, 30.f);
	Prefab->SetFont("DefaultFont");
	Prefab->SetClickCallback<CObjectWindow>(this, &CObjectWindow::AddPrefab);

#pragma endregion

#pragma region Gizmo

	m_Gizmo = AddWidget<CIMGUIGizmo>("Gizmo", 100.f, 30.f);
	m_Gizmo->GizmoStart(m_Scene);
	CToolWindow* ToolWindow = (CToolWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ToolWindow");
	m_Gizmo->SetGizmoComponent(ToolWindow->GetGizmoComponent());
#pragma endregion

	return true;
}

void CObjectWindow::Update(float DeltaTime)
{
	CIMGUIWindow::Update(DeltaTime);

	if (!m_CreateClient3DPrefab)
	{
		if (CreateClient3DPrefab())
		{
			m_CreateClient3DPrefab = true;
		}
	}
	m_ObjListBox->Clear();
	for (size_t i = 0; i < m_VecObject.size(); i++)
	{
		m_ObjListBox->AddItem(m_VecObject[i]->GetName().c_str());
	}
}


CGameObject* CObjectWindow::FindObject(const std::string& Name)
{
	auto iter = m_VecObject.begin();
	auto iterEnd = m_VecObject.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->GetName() == Name)
			return (*iter);
	}
	return nullptr;
}

void CObjectWindow::ObjectListCallback(int SelectIndex, const char* Item)
{
	m_SelectObjectIndex = SelectIndex;
	std::string SelectName = Item;

	m_SelectObject = m_VecObject[m_SelectObjectIndex];

	SetIMGUIWindowEvent();
}


void CObjectWindow::CreateObjectButtonClick()
{
	CScene* Scene = CSceneManager::GetInst()->GetScene();

	char	ObjName[256] = {};

	sprintf_s(ObjName, "GameObject_%d", m_CreateObjectCount);

	++m_CreateObjectCount;

	CGameObject* Obj = Scene->SpawnObject<CGameObject>(ObjName);
	m_VecObject.push_back(Obj);
}

void CObjectWindow::DeleteObjectButtonClick()
{
	size_t Size = m_VecObject.size();
	auto iter = m_VecObject.begin();
	auto iterEnd = m_VecObject.end();
	for (; iter != iterEnd; ++iter)
	{
		if ((*iter) == m_SelectObject)
		{
			m_VecObject.erase(iter);
			m_SelectObject->Active(false);
			m_SelectObject = nullptr;
			break;
		}
	}
	DeleteIMGUIWindowEvent();
}

void CObjectWindow::DeleteAllObject()
{
	size_t Size = m_VecObject.size();
	auto iter = m_VecObject.begin();
	auto iterEnd = m_VecObject.end();
	for (; iter != iterEnd; ++iter)
	{
		(*iter)->Active(false);

	}

	m_SelectObject = nullptr;
	m_VecObject.clear();

	DeleteIMGUIWindowEvent();
}

void CObjectWindow::SaveAllObject(FILE* pFile)
{
	size_t Size = m_VecObject.size();
	fwrite(&Size, sizeof(size_t), 1, pFile);
	auto iter = m_VecObject.begin();
	auto iterEnd = m_VecObject.end();
	for (; iter != iterEnd; ++iter)
	{
		//타입 읽어와서 클래스타입이라면 클래스 형변환 시킨 후 타입 읽기
		Object_Type ObjectType = (*iter)->GetObjectType();
		fwrite(&ObjectType, sizeof(Object_Type), 1, pFile);
		if (ObjectType == Object_Type::Client)
		{
			//클라이언트에서 제작된 오브젝트
			CClientObject* Object = (CClientObject*)(*iter).Get();
			ClientClassType ClassType = Object->GetClientClassType();
			fwrite(&ClassType, sizeof(ClientClassType), 1, pFile);
		}
		(*iter)->Save(pFile);
	}

}


void CObjectWindow::LoadAllObject(FILE* pFile)
{
	DeleteAllObject();
	size_t Size;
	fread(&Size, sizeof(size_t), 1, pFile);
	for (size_t i = 0; i < Size; i++)
	{
		CGameObject* Obj = nullptr;
		Object_Type ObjectType = Object_Type::Engine;
		fread(&ObjectType, sizeof(Object_Type), 1, pFile);
		if (ObjectType == Object_Type::Client)
		{
			ClientClassType ClassType = ClientClassType::Default;
			fread(&ClassType, sizeof(ClientClassType), 1, pFile);
			switch (ClassType)
			{
			case ClientClassType::Default:
			{
				Obj = m_Scene->SpawnObject<CClientObject>("Obj");
				break;
			}
			case ClientClassType::Kiana:
			{
				Obj = m_Scene->SpawnObject<CKianaPlayer>("Kiana");
				break;
			}
			case ClientClassType::Sakura:
			{
				Obj = m_Scene->SpawnObject<CSakuraPlayer>("Sakura");
				break;
			}
			case ClientClassType::Sniper:
			{
				CSniper* Sniper = m_Scene->SpawnObject<CSniper>("Sniper");
				Sniper->IsFSMPlay(false);
				Obj = Sniper;
				break;
			}
			case ClientClassType::Axe:
			{
				CAxeSoldier* Axe = m_Scene->SpawnObject<CAxeSoldier>("Axe");
				Axe->IsFSMPlay(false);
				Obj = Axe;
				break;
			}

			case ClientClassType::LoadingStartObject:
			{
				Obj = m_Scene->SpawnObject<CLoadingStartObject>("LoadingStartObject");
				break;
			}
			case ClientClassType::BossSpawnObject:
			{
				Obj = m_Scene->SpawnObject<CBossSpawnObject>("BossSpawnObject");
				break;
			}
			case ClientClassType::ColliderSpawnObject:
			{
				Obj = m_Scene->SpawnObject<CColliderSpawnObject>("ColliderSpawnObject");
				break;
			}
			case ClientClassType::MonsterSpawnObject:
			{
				Obj = m_Scene->SpawnObject<CMonsterSpawnObject>("MonsterSpawnObject");
				break;
			}
			case ClientClassType::MapCollision:
			{
				Obj = m_Scene->SpawnObject<CMapCollision>("MapCollision");
				break;
			}
			}
		}
		else
		{
			Obj = m_Scene->SpawnObject<CGameObject>("Obj");
		}
		Obj->SetObjectType(ObjectType);
		Obj->Load(pFile);
		m_VecObject.push_back(Obj);

	}
}


void CObjectWindow::AddPrefab()
{
	if (!m_SelectObject)
	{
		return;
	}
	m_PrefabWindow->AddPrefab(m_SelectObject);
}

bool CObjectWindow::CreateClient3DPrefab()
{
	if (!m_PrefabWindow)
	{
		m_PrefabWindow = (CPrefabWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("PrefabWindow");
		return false;
	}

	CKianaPlayer* Kiana = m_Scene->SpawnObject<CKianaPlayer>("Kiana");
	m_PrefabWindow->AddPrefab(Kiana);
	Kiana->Active(false);

	CSakuraPlayer* Sakura = m_Scene->SpawnObject<CSakuraPlayer>("Sakura");
	m_PrefabWindow->AddPrefab(Sakura);
	Sakura->Active(false);

	CSniper* Sniper = m_Scene->SpawnObject<CSniper>("Sniper");
	Sniper->IsFSMPlay(false);
	m_PrefabWindow->AddPrefab(Sniper);
	Sniper->Active(false);

	CAxeSoldier* AxeSoldier = m_Scene->SpawnObject<CAxeSoldier>("AxeSoldier");
	AxeSoldier->IsFSMPlay(false);
	m_PrefabWindow->AddPrefab(AxeSoldier);
	AxeSoldier->Active(false);


	CWendy* Wendy = m_Scene->SpawnObject<CWendy>("Wendy");
	Wendy->IsFSMPlay(false);
	m_PrefabWindow->AddPrefab(Wendy);
	Wendy->Active(false);

	CLoadingStartObject* LoadingStartObject = m_Scene->SpawnObject<CLoadingStartObject>("LoadingStartObject");
	m_PrefabWindow->AddPrefab(LoadingStartObject);
	LoadingStartObject->Active(false);


	CLobbyShip* LobbyShip = m_Scene->SpawnObject<CLobbyShip>("LobbyShip");
	m_PrefabWindow->AddPrefab(LobbyShip);
	LobbyShip->Active(false);


	CCameraMoveObject* CameraMoveObject = m_Scene->SpawnObject<CCameraMoveObject>("CameraMoveObject");
	m_PrefabWindow->AddPrefab(CameraMoveObject);
	CameraMoveObject->Active(false);

	CColliderSpawnObject* ColliderSpawnObject = m_Scene->SpawnObject<CColliderSpawnObject>("ColliderSpawnObject");
	m_PrefabWindow->AddPrefab(ColliderSpawnObject);
	ColliderSpawnObject->Active(false);

	CMonsterSpawnObject* MonsterSpawnObject = m_Scene->SpawnObject<CMonsterSpawnObject>("MonsterSpawnObject");
	m_PrefabWindow->AddPrefab(MonsterSpawnObject);
	MonsterSpawnObject->Active(false);

	CBossSpawnObject* BossSpawnObject = m_Scene->SpawnObject<CBossSpawnObject>("BossSpawnObject");
	m_PrefabWindow->AddPrefab(BossSpawnObject);
	BossSpawnObject->Active(false);

	CMapCollision* MapCollision = m_Scene->SpawnObject<CMapCollision>("MapCollision");
	m_PrefabWindow->AddPrefab(MapCollision);
	MapCollision->Active(false);

	CLobbyValkyrieSelectZone* LobbyValkyrieSelectZone = m_Scene->SpawnObject<CLobbyValkyrieSelectZone>("LobbyValkyrieSelectZone");
	m_PrefabWindow->AddPrefab(LobbyValkyrieSelectZone);
	LobbyValkyrieSelectZone->Active(false);

	return true;
}

void CObjectWindow::ClickWorldObject()
{
	//월드상태
	if (CGlobalValue::MouseState == Mouse_State::World)
	{
		HitResult HitObj;
		//선택된 빈공간 클릭
		bool check = false;

		CCollider* Col = m_Scene->GetCollisionManager()->GetMouseCollisionCollider();
		if (nullptr == Col)
		{
			return;
		}
		if (!Col->IsActive() || m_Gizmo->IsUsing())
		{
			return;
		}

		CGameObject* ColObj = Col->GetOwner();
		size_t Size = m_VecObject.size();
		for (size_t i = 0; i < Size; ++i)
		{
			if (m_VecObject[i] == ColObj)
			{
				m_SelectObjectIndex = (int)i;
				m_SelectObject = ColObj;
				check = true;
			}
		}
		if (check)
		{
			SetIMGUIWindowEvent();
		}
	}
	//프리팹상태
	else if(CGlobalValue::MouseState == Mouse_State::Prefab)
	{
		CGameObject* Object=m_PrefabWindow->GetSelectObject();
		CClientObject* Obj = dynamic_cast<CClientObject*>(Object);
		if (Obj)
		{
			switch (Obj->GetClientClassType())
			{
			case ClientClassType::Kiana:
			{
				Obj = m_Scene->SpawnObject<CKianaPlayer>("Kiana");
				break;
			}
			case ClientClassType::Sakura:
			{
				Obj = m_Scene->SpawnObject<CSakuraPlayer>("Sakura");
				break;
			}
			case ClientClassType::Sniper:
			{
				CSniper* Sniper = m_Scene->SpawnObject<CSniper>("Sniper");
				Sniper->IsFSMPlay(false);
				Obj = Sniper;
				break;
			}
			case ClientClassType::Axe:
			{
				CAxeSoldier* Axe = m_Scene->SpawnObject<CAxeSoldier>("Axe");
				Axe->IsFSMPlay(false);
				Obj = Axe;
				break;
			}

			case ClientClassType::LoadingStartObject:
			{
				Obj = m_Scene->SpawnObject<CLoadingStartObject>("LoadingStartObject");
				break;
			}
			case ClientClassType::BossSpawnObject:
			{
				Obj = m_Scene->SpawnObject<CBossSpawnObject>("BossSpawnObject");
				break;
			}
			case ClientClassType::ColliderSpawnObject:
			{
				Obj = m_Scene->SpawnObject<CColliderSpawnObject>("ColliderSpawnObject");
				break;
			}
			case ClientClassType::MonsterSpawnObject:
			{
				Obj = m_Scene->SpawnObject<CMonsterSpawnObject>("MonsterSpawnObject");
				break;
			}
			case ClientClassType::MapCollision:
			{
				Obj = m_Scene->SpawnObject<CMapCollision>("MapCollision");
				break;
			}

			case ClientClassType::CameraMoveObject:
			{
				Obj = m_Scene->SpawnObject<CCameraMoveObject>("CameraMoveObject");
				break;
			}
			case ClientClassType::LobbyShip:
			{
				Obj = m_Scene->SpawnObject<CLobbyShip>("LobbyShip");
				break;
			}
			case ClientClassType::LobbyValkyieSelectZone:
			{
				Obj = m_Scene->SpawnObject<CLobbyValkyrieSelectZone>("LobbyValkyrieSelectZone");
				break;
			}
			case ClientClassType::Wendy:
			{
				Obj = m_Scene->SpawnObject<CWendy>("Wendy");
				break;
			}
			}

			//CGameObject* Obj = m_Scene->CloneObject2(Object);
			//프리팹 버그수정일단 미루기..ㅠㅠ
			std::string str = Obj->GetName();
			str += std::to_string(m_CloneObjectCount);
			Obj->SetName(str);
			Ray ray=CInput::GetInst()->GetRay();
			
			CCamera* Camera=m_Scene->GetCameraManager()->GetCurrentCamera();
			
			Vector3 Pos = Camera->GetWorldPos();
			Pos.y = 0.f;
			//Pos+=ray.Dir * 20.f;
			Obj->SetWorldPos(Pos);
			m_CloneObjectCount++;
			AddObject(Obj);

		}
		//프리팹은 한번 넣어주고 다시 월드로 전환
		//일단 기능구현우선
		CGlobalValue::MouseState = Mouse_State::World;
	}
}


void CObjectWindow::SetPosX(float x)
{
	if (!m_ComponentWindow->GetSelectComponent())
		return;

	Vector3	Pos = m_ComponentWindow->GetSelectComponent()->GetRelativePos();
	Pos.x = x;

	m_ComponentWindow->GetSelectComponent()->SetWorldPos(Pos);
}

void CObjectWindow::SetPosY(float y)
{
	if (!m_ComponentWindow->GetSelectComponent())
		return;

	Vector3	Pos = m_ComponentWindow->GetSelectComponent()->GetRelativePos();
	Pos.y = y;

	m_ComponentWindow->GetSelectComponent()->SetWorldPos(Pos);
}

void CObjectWindow::SetPosZ(float z)
{
	if (!m_ComponentWindow->GetSelectComponent())
		return;

	Vector3	Pos = m_ComponentWindow->GetSelectComponent()->GetRelativePos();
	Pos.z = z;

	m_ComponentWindow->GetSelectComponent()->SetWorldPos(Pos);
}

void CObjectWindow::SetRotX(float x)
{
	if (!m_ComponentWindow->GetSelectComponent())
		return;

	
	Vector3	Rot = m_ComponentWindow->GetSelectComponent()->GetRelativeRotation();
	Rot.x = x;

	m_ComponentWindow->GetSelectComponent()->SetWorldRotation(Rot);
}

void CObjectWindow::SetRotY(float y)
{
	if (!m_ComponentWindow->GetSelectComponent())
		return;

	Vector3	Rot = m_ComponentWindow->GetSelectComponent()->GetRelativeRotation();
	Rot.y = y;

	m_ComponentWindow->GetSelectComponent()->SetWorldRotation(Rot);
}

void CObjectWindow::SetRotZ(float z)
{
	if (!m_ComponentWindow->GetSelectComponent())
		return;

	Vector3	Rot = m_ComponentWindow->GetSelectComponent()->GetRelativeRotation();
	Rot.z = z;

	m_ComponentWindow->GetSelectComponent()->SetWorldRotation(Rot);
}

void CObjectWindow::SetScaleX(float x)
{
	if (!m_ComponentWindow->GetSelectComponent())
		return;

	Vector3	Scale = m_ComponentWindow->GetSelectComponent()->GetRelativeScale();
	Scale.x = x;

	m_ComponentWindow->GetSelectComponent()->SetWorldScale(Scale);
}

void CObjectWindow::SetScaleY(float y)
{
	if (!m_ComponentWindow->GetSelectComponent())
		return;

	Vector3	Scale = m_ComponentWindow->GetSelectComponent()->GetRelativeScale();
	Scale.y = y;

	m_ComponentWindow->GetSelectComponent()->SetWorldScale(Scale);
}

void CObjectWindow::SetScaleZ(float z)
{
	if (!m_ComponentWindow->GetSelectComponent())
		return;

	Vector3	Scale = m_ComponentWindow->GetSelectComponent()->GetRelativeScale();
	Scale.z = z;

	m_ComponentWindow->GetSelectComponent()->SetWorldScale(Scale);
}

void CObjectWindow::SetPivotX(float x)
{
	if (!m_ComponentWindow->GetSelectComponent())
		return;

	Vector3	Scale = m_ComponentWindow->GetSelectComponent()->GetPivot();
	Scale.x = x;

	m_ComponentWindow->GetSelectComponent()->SetPivot(Scale);
}

void CObjectWindow::SetPivotY(float y)
{
	if (!m_ComponentWindow->GetSelectComponent())
		return;

	Vector3	Scale = m_ComponentWindow->GetSelectComponent()->GetPivot();
	Scale.y = y;

	m_ComponentWindow->GetSelectComponent()->SetPivot(Scale);
}

void CObjectWindow::SetPivotZ(float z)
{
	if (!m_ComponentWindow->GetSelectComponent())
		return;

	Vector3	Scale = m_ComponentWindow->GetSelectComponent()->GetPivot();
	Scale.z = z;

	m_ComponentWindow->GetSelectComponent()->SetPivot(Scale);
}

void CObjectWindow::SetIMGUIWindowEvent()
{
	if (!m_ComponentWindow)
	{
		m_ComponentWindow = (CComponentWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ComponentWindow");
	}
	m_ComponentWindow->SetSelectComponent(nullptr);

	// 가지고 있는 컴포넌트의 이름을 얻어온다.
	std::vector<std::string>	vecName;
	m_SelectObject->GetComponentName(vecName);

	m_ComponentWindow->Clear();
	size_t	Size = vecName.size();
	for (size_t i = 0; i < Size; ++i)
	{
		m_ComponentWindow->AddItem(vecName[i].c_str());
	}

	CInspectorWindow* InspectorWindow = (CInspectorWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("InspectorWindow");
	InspectorWindow->AllComponentClose();

	CSceneComponent* Component = m_SelectObject->FindSceneComponent(vecName[0]);
	InspectorWindow->ComponentUpdateInfo("Transform", Component);
	InspectorWindow->ObjectUpdateInfo(m_SelectObject);


	CToolWindow* ToolWindow = (CToolWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ToolWindow");
	ToolWindow->GizmoComponentUpdate(Component);
}

void CObjectWindow::DeleteIMGUIWindowEvent()
{
	m_ComponentWindow->Clear();
	CInspectorWindow* InspectorWindow = (CInspectorWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("InspectorWindow");
	InspectorWindow->ObjectUpdateInfo(nullptr);
	InspectorWindow->AllComponentClose();

	CToolWindow* ToolWindow = (CToolWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ToolWindow");
	ToolWindow->GizmoComponentUpdate(nullptr);
}
