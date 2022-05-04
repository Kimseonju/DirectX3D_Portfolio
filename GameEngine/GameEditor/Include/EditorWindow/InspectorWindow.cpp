#include "../pch.h"
#include "InspectorWindow.h"
#include "../EditorComponent/IMGUIObjectInfoComponent.h"
#include "../EditorComponent/IMGUITransformComponent.h"
#include "../EditorComponent/IMGUICameraComponent.h"
#include "../EditorComponent/IMGUIAnimationMeshComponent.h"
#include "../EditorComponent/IMGUIStaticMeshComponent.h"
#include "../EditorComponent/IMGUIColliderBox3DComponent.h"
#include "../EditorComponent/IMGUIColliderSphereComponent.h"
#include "../EditorComponent/IMGUIBillboardComponent.h"
#include "../EditorComponent/IMGUILightComponent.h"
#include "../EditorComponent/IMGUISkyComponent.h"
#include "../EditorComponent/IMGUICameraMoveComponent.h"
#include "../EditorComponent/IMGUIMonsterSpawnObjectComponent.h"
#include "../EditorComponent/IMGUIColliderSpawnObjectComponent.h"
#include "../EditorComponent/IMGUIBossSpawnObjectComponent.h"
CInspectorWindow::CInspectorWindow():
	m_Object(nullptr),
	m_CameraMoveObject(nullptr),
	m_MonsterSpawnObject(nullptr),
	m_ColliderSpawnObject(nullptr),
	m_BossSpawnObject(nullptr)
{
}

CInspectorWindow::~CInspectorWindow()
{
	auto iter = m_IMGUIComponent.begin();
	auto iterEnd = m_IMGUIComponent.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->second);
	}
	m_IMGUIComponent.clear();
	SAFE_DELETE(m_Object);
	SAFE_DELETE(m_CameraMoveObject);
	SAFE_DELETE(m_MonsterSpawnObject);
	SAFE_DELETE(m_ColliderSpawnObject);
	SAFE_DELETE(m_BossSpawnObject);
}

bool CInspectorWindow::Init()
{
	CreateComponent();

	AllComponentClose();


	return true;
}

void CInspectorWindow::Update(float DeltaTime)
{
	CIMGUIWindow::Update(DeltaTime);
	auto iter = m_IMGUIComponent.begin();
	auto iterEnd = m_IMGUIComponent.end();

	for (; iter != iterEnd; ++iter)
	{
		if (iter->second->IsEnable())
		{
			iter->second->Update(DeltaTime);
		}
	}
	//if (m_Transform->IsEnable())
	//{
	//	m_Transform->Update(DeltaTime);
	//}
	//
	if (m_Object->IsEnable())
	{
		m_Object->Update(DeltaTime);
	}
	if (m_CameraMoveObject->IsEnable())
	{
		m_CameraMoveObject->Update(DeltaTime);
	}

	if (m_MonsterSpawnObject->IsEnable())
	{
		m_MonsterSpawnObject->Update(DeltaTime);
	}

	if (m_ColliderSpawnObject->IsEnable())
	{
		m_ColliderSpawnObject->Update(DeltaTime);
	}

	if (m_BossSpawnObject->IsEnable())
	{
		
		m_BossSpawnObject->Update(DeltaTime);
	}
	//
	//if (m_AnimationMesh->IsEnable())
	//{
	//	m_AnimationMesh->Update(DeltaTime);
	//}
}

void CInspectorWindow::ObjectUpdateInfo(CGameObject* Obj)
{
	m_Object->UpdateInfo(Obj);
	m_Object->Enable(true);
}

void CInspectorWindow::CameraMoveUpdateInfo(CGameObject* Obj)
{
	m_CameraMoveObject->UpdateInfo(Obj);
	m_CameraMoveObject->Enable(true);
}

void CInspectorWindow::MonsterSpawnUpdateInfo(CGameObject* Obj)
{
	m_MonsterSpawnObject->UpdateInfo(Obj);
	m_MonsterSpawnObject->Enable(true);
}

void CInspectorWindow::ColliderSpawnUpdateInfo(CGameObject* Obj)
{
	m_ColliderSpawnObject->UpdateInfo(Obj);
	m_ColliderSpawnObject->Enable(true);
}

void CInspectorWindow::BossSpawnUpdateInfo(CGameObject* Obj)
{
	m_BossSpawnObject->UpdateInfo(Obj);
	m_BossSpawnObject->Enable(true);
}

void CInspectorWindow::ComponentUpdateInfo(const std::string& Name, CSceneComponent* Component)
{
	CIMGUIWidgetComponent* IMGUIComponent = m_IMGUIComponent.find(Name)->second;

	if (IMGUIComponent)
	{
		IMGUIComponent->ComponentUpdateInfo(Component);
		IMGUIComponent->Enable(true);
	}
}

void CInspectorWindow::CreateComponent()
{
	m_Object = new CIMGUIObjectInfoComponent;
	m_Object->SetOwner(this);
	m_Object->Init();

	m_CameraMoveObject = new CIMGUICameraMoveComponent;
	m_CameraMoveObject->SetOwner(this);
	m_CameraMoveObject->Init();

	m_MonsterSpawnObject = new CIMGUIMonsterSpawnObjectComponent;
	m_MonsterSpawnObject->SetOwner(this);
	m_MonsterSpawnObject->Init();

	m_ColliderSpawnObject = new CIMGUIColliderSpawnObjectComponent;
	m_ColliderSpawnObject->SetOwner(this);
	m_ColliderSpawnObject->Init();

	m_BossSpawnObject = new CIMGUIBossSpawnObjectComponent;
	m_BossSpawnObject->SetOwner(this);
	m_BossSpawnObject->Init();

	CIMGUIWidgetComponent* _Transform = new CIMGUITransformComponent;
	_Transform->SetOwner(this);
	_Transform->Init();
	m_IMGUIComponent.insert(std::make_pair("Transform", _Transform));

	CIMGUICameraComponent* _Camera = new CIMGUICameraComponent;
	_Camera->SetOwner(this);
	_Camera->Init();
	m_IMGUIComponent.insert(std::make_pair("Camera", _Camera));


	CIMGUIStaticMeshComponent* _StaticMesh = new CIMGUIStaticMeshComponent;
	_StaticMesh->SetOwner(this);
	_StaticMesh->Init();
	m_IMGUIComponent.insert(std::make_pair("StaticMesh", _StaticMesh));

	CIMGUIAnimationMeshComponent* _AnimationMesh = new CIMGUIAnimationMeshComponent;
	_AnimationMesh->SetOwner(this);
	_AnimationMesh->Init();
	m_IMGUIComponent.insert(std::make_pair("AnimationMesh", _AnimationMesh));

	CIMGUIColliderBox3DComponent* _ColliderBox3D = new CIMGUIColliderBox3DComponent;
	_ColliderBox3D->SetOwner(this);
	_ColliderBox3D->Init();
	m_IMGUIComponent.insert(std::make_pair("ColliderBox3D", _ColliderBox3D));


	CIMGUIColliderSphereComponent* _ColliderSphere = new CIMGUIColliderSphereComponent;
	_ColliderSphere->SetOwner(this);
	_ColliderSphere->Init();
	m_IMGUIComponent.insert(std::make_pair("ColliderSphere", _ColliderSphere));


	CIMGUIBillboardComponent* _Billboard = new CIMGUIBillboardComponent;
	_Billboard->SetOwner(this);
	_Billboard->Init();
	m_IMGUIComponent.insert(std::make_pair("Billboard", _Billboard));


	CIMGUILightComponent* _Light = new CIMGUILightComponent;
	_Light->SetOwner(this);
	_Light->Init();
	m_IMGUIComponent.insert(std::make_pair("Light", _Light));


	CIMGUISkyComponent* _Sky = new CIMGUISkyComponent;
	_Sky->SetOwner(this);
	_Sky->Init();
	m_IMGUIComponent.insert(std::make_pair("Sky", _Sky));

	//CIMGUICameraMoveComponent* _Sky = new CIMGUISkyComponent;
	//_Sky->SetOwner(this);
	//_Sky->Init();
	//m_IMGUIComponent.insert(std::make_pair("Sky", _Sky));
}



void CInspectorWindow::AllComponentClose()
{
	m_Object->Enable(false);
	m_CameraMoveObject->Enable(false);
	m_MonsterSpawnObject->Enable(false);
	m_ColliderSpawnObject->Enable(false);
	m_BossSpawnObject->Enable(false);
	auto iter = m_IMGUIComponent.begin();
	auto iterEnd = m_IMGUIComponent.end();

	for (; iter != iterEnd; ++iter)
	{
		iter->second->Enable(false);
	}
}

