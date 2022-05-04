#include "ClientManager.h"
#include "Scene/SceneManager.h"
#include "Input.h"
#include "CollisionManager.h"
#include "IMGUIManager.h"
#include "Engine.h"
#include "UI/MouseWidget.h"
#include "Resource/ResourceManager.h"
#include "Scene/MainScene.h"
#include "Scene/LoadingScene.h"
#include "PublicData.h"
#include "Custom/CollisionRay.h"
#include "Scene/StageScene1.h"
#include "Scene/LobbyScene.h"
#include "StageManager.h"
#include "UI/UIManager.h"
#include "LobbyManager.h"
#include "Scene/EffectTestScene.h"
//#include "SceneMode/StartScene.h"

DEFINITION_SINGLE(CClientManager)

CClientManager::CClientManager()
{
}

CClientManager::~CClientManager()
{
	CUIManager::GetInst()->DestroyInst();
    CPublicData::DestroyInst();
	CCollisionRay::DestroyInst();
	CStageManager::DestroyInst();
    CLobbyManager::DestroyInst();
}

bool CClientManager::Init()
{
    //CEngine::GetInst()->OnDebugLog();
	//CEngine::GetInst()->OnLogFPS(true);
	CCollisionRay::GetInst();

    // 키 등록
    CInput::GetInst()->CreateKey("ClientMoveFront", 'W');
    CInput::GetInst()->CreateKey("ClientMoveBack", 'S');
    CInput::GetInst()->CreateKey("ClientLeftMove", 'A');
	CInput::GetInst()->CreateKey("ClientRightMove", 'D');
	CInput::GetInst()->CreateKey("ClientCameraLeft", 'Q');
	CInput::GetInst()->CreateKey("ClientCameraRight", 'E');
    CInput::GetInst()->CreateKey("ClientFire", VK_SPACE);
    CInput::GetInst()->CreateKey("ClientChange1", '1');
	CInput::GetInst()->CreateKey("ClientChange2", '2');
	CInput::GetInst()->CreateKey("ClientUltraSkill", 'I');
	CInput::GetInst()->CreateKey("ClientEvade", 'Z');
    CInput::GetInst()->SetControlKey("ClientSkill2", true);
    CInput::GetInst()->CreateKey("ClientMouseLButton", VK_LBUTTON);
	CInput::GetInst()->CreateKey("ClientMouseRButton", VK_RBUTTON);
	CInput::GetInst()->CreateKey("ClientMouseWHEEL", DIK_MOUSEWHEEL);

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

    CCollisionManager::GetInst()->SetProfileChannelState("Player", Collision_Channel::PlayerAttack,Collision_Interaction::Ignore);
	CCollisionManager::GetInst()->SetProfileChannelState("Player", Collision_Channel::Player, Collision_Interaction::Ignore);
	CCollisionManager::GetInst()->SetProfileChannelState("Player", Collision_Channel::PlayerEvade, Collision_Interaction::Ignore);
	CCollisionManager::GetInst()->SetProfileChannelState("PlayerEvade", Collision_Channel::PlayerEvade, Collision_Interaction::Ignore);

	CCollisionManager::GetInst()->SetProfileChannelState("Player", Collision_Channel::SpawnZone, Collision_Interaction::Block);
	CCollisionManager::GetInst()->SetProfileChannelState("SpawnZone", Collision_Channel::Player, Collision_Interaction::Block);


    CCollisionManager::GetInst()->SetProfileChannelState("PlayerAttack", Collision_Channel::PlayerAttack,Collision_Interaction::Ignore);
	CCollisionManager::GetInst()->SetProfileChannelState("MonsterAttack", Collision_Channel::PlayerAttack, Collision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetProfileChannelState("SpawnZone", Collision_Channel::Monster, Collision_Interaction::Ignore);

    CCollisionManager::GetInst()->SetProfileChannelState("Monster", Collision_Channel::MonsterAttack,Collision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetProfileChannelState("PlayerAttack", Collision_Channel::MonsterAttack,Collision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetProfileChannelState("MonsterAttack", Collision_Channel::MonsterAttack,Collision_Interaction::Ignore);


	CCollisionManager::GetInst()->SetProfileChannelState("Player", Collision_Channel::MonsterAttack, Collision_Interaction::Trigger);
	CCollisionManager::GetInst()->SetProfileChannelState("MonsterAttack", Collision_Channel::Player, Collision_Interaction::Trigger);
	CCollisionManager::GetInst()->SetProfileChannelState("Player", Collision_Channel::MapItem,
		Collision_Interaction::Trigger);

	CCollisionManager::GetInst()->SetProfileChannelState("MapCollision", Collision_Channel::MapCollision, Collision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetProfileChannelState("MapCollision", Collision_Channel::SpawnZone, Collision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetProfileChannelState("MapCollision", Collision_Channel::MonsterAttack, Collision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetProfileChannelState("MapCollision", Collision_Channel::Monster, Collision_Interaction::Ignore);
	
	CCollisionManager::GetInst()->SetProfileChannelState("CollisionBlock", Collision_Channel::Player, Collision_Interaction::Block);
	CCollisionManager::GetInst()->SetProfileChannelState("Player", Collision_Channel::CollisionBlock, Collision_Interaction::Block);
	CCollisionManager::GetInst()->SetProfileChannelState("CollisionBlock", Collision_Channel::Monster, Collision_Interaction::Block);
	CCollisionManager::GetInst()->SetProfileChannelState("Monster", Collision_Channel::CollisionBlock, Collision_Interaction::Block);


	//CSceneManager::GetInst()->SetSceneMode<CMainScene>();
    //CSceneManager::GetInst()->SetSceneMode<CEffectTestScene>();
	CSceneManager::GetInst()->SetSceneMode<CLoadingScene>();
	//CSceneManager::GetInst()->SetSceneMode<CLoadingScene>();
    //CSceneManager::GetInst()->SetSceneMode<CStageScene1>();
    
    CreateMouse();

    return true;
}

void CClientManager::CreateMouse()
{
    // 마우스 애니메이션 시퀀스 생성
    CResourceManager::GetInst()->CreateAnimationSequence2D("MouseDefault");

    std::vector<const TCHAR*> vecFileName;

    vecFileName.push_back(TEXT("UI/Share/MousePoint.png"));

    CResourceManager::GetInst()->SetAnimationSequence2DTexture("MouseDefault", "MouseDefault", vecFileName);

    CResourceManager::GetInst()->AddAnimationSequence2DFrame("MouseDefault", Vector2(0.f, 0.f), Vector2(25.f, 29.f), 1);

    CMouseWidget* Mouse = CEngine::GetInst()->CreateMouseWidget<CMouseWidget>("Mouse");

    Mouse->SetSize(25.f, 29.f);

    Mouse->CreateAnimation2D<CAnimation2D>();

    CAnimation2D* MouseAnim = Mouse->GetAnimation2D();

    MouseAnim->AddAnimationSequence2D("MouseDefault");
}
