
#include "../pch.h"
#include "EditorScene.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "Scene/CameraManager.h"
#include "Component/Camera.h"
#include "IMGUIManager.h"
#include "Component/TileMapComponent.h"
#include <Scene/Scene.h>
#include <Resource/ResourceManager.h>
#include "Scene/SceneResource.h"
#include "Resource/ResourceManager.h"
#include "../GlobalValue.h"
#include "../EditorWIndow/ObjectWindow.h"
#include "../EditorWIndow/PrefabWindow.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include <Component/Camera.h>
#include <CollisionManager.h>

#include "PublicData.h"
#include "Object/DecalTest.h"
#include "Component/LightComponent.h"
#include "Object/MainLandScape.h"
#include "Component/BillboardComponent.h"
#include "StageManager.h"
#include "UI/UIManager.h"
#include "LobbyManager.h"
CEditorScene::CEditorScene() :
	m_CloneObjectCount(0),
	m_PrefabWindow(nullptr),
	m_ObjectWindow(nullptr)
{
}

CEditorScene::~CEditorScene()
{
	CPublicData::DestroyInst();
	CStageManager::GetInst()->DestroyInst();
	CUIManager::GetInst()->DestroyInst();
	CLobbyManager::GetInst()->DestroyInst();
}

bool CEditorScene::Init()
{
	CreateCollisionProfile();
	CStageManager::GetInst()->ResourceLoad(m_pScene);
	CUIManager::GetInst()->Init(m_pScene);


    CInput::GetInst()->CreateKey("EditorMoveFront", 'W');
    CInput::GetInst()->CreateKey("EditorMoveBack", 'S');
    CInput::GetInst()->CreateKey("EditorLeftMove", 'A');
    CInput::GetInst()->CreateKey("EditorRightMove", 'D');
    CInput::GetInst()->CreateKey("EditorMouseLButton", VK_LBUTTON);
	CInput::GetInst()->CreateKey("EditorMouseRButton", VK_RBUTTON);

    CInput::GetInst()->AddKeyCallback<CEditorScene>("EditorMoveFront", KT_Push, this, &CEditorScene::MoveFront);
    CInput::GetInst()->AddKeyCallback<CEditorScene>("EditorMoveBack", KT_Push, this, &CEditorScene::MoveBack);
    CInput::GetInst()->AddKeyCallback<CEditorScene>("EditorLeftMove", KT_Push, this, &CEditorScene::LeftMove);
    CInput::GetInst()->AddKeyCallback<CEditorScene>("EditorRightMove", KT_Push, this, &CEditorScene::RightMove);
    CInput::GetInst()->AddKeyCallback<CEditorScene>("EditorMouseLButton", KT_Push, this, &CEditorScene::MouseLButton);
	CInput::GetInst()->AddKeyCallback<CEditorScene>("EditorMouseRButton", KT_Push, this, &CEditorScene::MouseRButton);

	//CIMGUIManager::GetInst()->FindIMGUIWindow("TestWindow")->Open();
	CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectWindow")->Open();
	CIMGUIManager::GetInst()->FindIMGUIWindow("InspectorWindow")->Open();
	CIMGUIManager::GetInst()->FindIMGUIWindow("PrefabWindow")->Open();
	CIMGUIManager::GetInst()->FindIMGUIWindow("ComponentWindow")->Open();
	CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectWindow")->Open();
	CIMGUIManager::GetInst()->FindIMGUIWindow("ToolWindow")->Open();
	CIMGUIManager::GetInst()->FindIMGUIWindow("SaveLoadWindow")->Open();

	m_ObjectWindow = (CObjectWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectWindow");
	m_PrefabWindow = (CPrefabWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("PrefabWindow");

	CGameObject* EditorCamera = m_pScene->SpawnObject<CGameObject>("EditorCamera");
	CCamera* Camera = EditorCamera->CreateSceneComponent<CCamera>("EditorCameraComponent");
	EditorCamera->SetRootComponent(Camera);
	// 지형 ( 테스트 )
	{
		//CMainLandScape* LandScape = m_pScene->SpawnObject<CMainLandScape>("LandScape");
	}

    return true;
}

void CEditorScene::Update(float DeltaTime)
{
    CSceneMode::Update(DeltaTime);

	if (CGlobalValue::MouseState != Mouse_State::Prefab)
	{
		if (GetAsyncKeyState(0x31) & 0x8000) //1
		{
			CGlobalValue::MouseState = Mouse_State::World;
		}
		if (GetAsyncKeyState(0x32) & 0x8000)//2
		{
			CGlobalValue::MouseState = Mouse_State::UI;
		}
	}
}

void CEditorScene::PostUpdate(float DeltaTime)
{
    CSceneMode::PostUpdate(DeltaTime);
}

void CEditorScene::MoveFront(float DeltaTime)
{
	CCamera* Camera = m_pScene->GetCameraManager()->GetCurrentCamera();

	Camera->AddRelativePos(Camera->GetAxis(AXIS_Z) * 10.f * DeltaTime);
}

void CEditorScene::MoveBack(float DeltaTime)
{
	CCamera* Camera = m_pScene->GetCameraManager()->GetCurrentCamera();

	Camera->AddRelativePos(Camera->GetAxis(AXIS_Z) * 10.f * -DeltaTime);
}

void CEditorScene::LeftMove(float DeltaTime)
{
	CCamera* Camera = m_pScene->GetCameraManager()->GetCurrentCamera();

	Camera->AddRelativePos(Camera->GetAxis(AXIS_X) * 10.f * -DeltaTime);
}

void CEditorScene::RightMove(float DeltaTime)
{
	CCamera* Camera = m_pScene->GetCameraManager()->GetCurrentCamera();

	Camera->AddRelativePos(Camera->GetAxis(AXIS_X) * 10.f * DeltaTime);
}

void CEditorScene::MouseLButton(float DeltaTime)
{
	m_ObjectWindow->ClickWorldObject();
}

void CEditorScene::MouseRButton(float DeltaTime)
{
	CCamera* Camera = m_pScene->GetCameraManager()->GetCurrentCamera();
	Vector2 MovePos=CInput::GetInst()->GetMouseMove();

	Camera->AddRelativeRotationY(MovePos.x * DeltaTime * 20.f);
	Camera->AddRelativeRotationX(-MovePos.y* DeltaTime*20.f);
	
}

void CEditorScene::AddObjectMap()
{
}

void CEditorScene::CreateParticle()
{
	
}

void CEditorScene::CreateCollisionProfile()
{
	CCollisionManager::GetInst()->CreateChannel("Player", Collision_Interaction::Block);
	CCollisionManager::GetInst()->CreateChannel("Monster", Collision_Interaction::Block);
	CCollisionManager::GetInst()->CreateChannel("PlayerAttack", Collision_Interaction::Block);
	CCollisionManager::GetInst()->CreateChannel("MonsterAttack", Collision_Interaction::Block);
	CCollisionManager::GetInst()->CreateChannel("MapCollision", Collision_Interaction::Block);
	CCollisionManager::GetInst()->CreateChannel("SpawnZone", Collision_Interaction::Trigger);
	CCollisionManager::GetInst()->CreateChannel("MapItem", Collision_Interaction::Trigger);
	CCollisionManager::GetInst()->CreateChannel("PlayerEvade", Collision_Interaction::Block);
	CCollisionManager::GetInst()->CreateChannel("CollisionBlock", Collision_Interaction::Ignore);


	CCollisionManager::GetInst()->CreateProfile("Player", Collision_Channel::Player);
	CCollisionManager::GetInst()->CreateProfile("Monster", Collision_Channel::Monster);
	CCollisionManager::GetInst()->CreateProfile("PlayerAttack", Collision_Channel::PlayerAttack);
	CCollisionManager::GetInst()->CreateProfile("MonsterAttack", Collision_Channel::MonsterAttack);
	CCollisionManager::GetInst()->CreateProfile("MapCollision", Collision_Channel::MapCollision);
	CCollisionManager::GetInst()->CreateProfile("SpawnZone", Collision_Channel::SpawnZone);
	CCollisionManager::GetInst()->CreateProfile("MapItem", Collision_Channel::MapItem);
	CCollisionManager::GetInst()->CreateProfile("PlayerEvade", Collision_Channel::PlayerEvade);
	CCollisionManager::GetInst()->CreateProfile("CollisionBlock", Collision_Channel::CollisionBlock);

	CCollisionManager::GetInst()->SetProfileChannelState("Player", Collision_Channel::PlayerAttack, Collision_Interaction::Ignore);
	CCollisionManager::GetInst()->SetProfileChannelState("Player", Collision_Channel::Player, Collision_Interaction::Ignore);
	CCollisionManager::GetInst()->SetProfileChannelState("Player", Collision_Channel::PlayerEvade, Collision_Interaction::Ignore);
	CCollisionManager::GetInst()->SetProfileChannelState("PlayerEvade", Collision_Channel::PlayerEvade, Collision_Interaction::Ignore);

	CCollisionManager::GetInst()->SetProfileChannelState("PlayerAttack", Collision_Channel::PlayerAttack, Collision_Interaction::Ignore);
	CCollisionManager::GetInst()->SetProfileChannelState("MonsterAttack", Collision_Channel::PlayerAttack, Collision_Interaction::Ignore);
	CCollisionManager::GetInst()->SetProfileChannelState("SpawnZone", Collision_Channel::Monster, Collision_Interaction::Ignore);

	CCollisionManager::GetInst()->SetProfileChannelState("Monster", Collision_Channel::MonsterAttack, Collision_Interaction::Ignore);
	CCollisionManager::GetInst()->SetProfileChannelState("PlayerAttack", Collision_Channel::MonsterAttack, Collision_Interaction::Ignore);
	CCollisionManager::GetInst()->SetProfileChannelState("MonsterAttack", Collision_Channel::MonsterAttack, Collision_Interaction::Ignore);


	CCollisionManager::GetInst()->SetProfileChannelState("Player", Collision_Channel::MonsterAttack, Collision_Interaction::Trigger);
	CCollisionManager::GetInst()->SetProfileChannelState("MonsterAttack", Collision_Channel::Player, Collision_Interaction::Trigger);
	CCollisionManager::GetInst()->SetProfileChannelState("Player", Collision_Channel::MapItem,
		Collision_Interaction::Trigger);

	CCollisionManager::GetInst()->SetProfileChannelState("MapCollision", Collision_Channel::MapCollision, Collision_Interaction::Ignore);
	CCollisionManager::GetInst()->SetProfileChannelState("MapCollision", Collision_Channel::SpawnZone, Collision_Interaction::Ignore);
	CCollisionManager::GetInst()->SetProfileChannelState("MapCollision", Collision_Channel::MonsterAttack, Collision_Interaction::Ignore);
	CCollisionManager::GetInst()->SetProfileChannelState("MapCollision", Collision_Channel::Monster, Collision_Interaction::Ignore);

	CCollisionManager::GetInst()->SetProfileChannelState("CollisionBlock", Collision_Channel::CollisionBlock, Collision_Interaction::Block);


}
