#include "UIManager.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Scene/Viewport.h"
#include "PlayerUI.h"
#include "LobbyMainUI.h"
#include "LobbyValkyrieSelectUI.h"
#include "FadeInOut_White.h"
#include "FadeInOutUI.h"
#include "LobbyStageSelectUI.h"
#include "GameClearUI.h"
#include "LoadingUI.h"
#include "LobbyValkyrieInfoUI.h"
#include "PlayerHitComboUI.h"
#include "TargetImageWidget.h"
#include "LobbyEquipmemtUI.h"
#include "LobbyLevelUpDialog.h"
#include "LobbyItemInfoDialog.h"
#include "LobbyWeaponInfoUI.h"
#include "LobbyWeaponLevelUpDialog.h"
#include "LobbySupplyUI.h"
#include "LobbySupplyResultUI.h"
#include "LoadingUI_Resource.h"
DEFINITION_SINGLE(CUIManager)

CUIManager::CUIManager() :
	m_pScene(nullptr)
{
}

CUIManager::~CUIManager()
{
	m_vecWidgetWindow.clear();
}


bool CUIManager::Init(CScene* Scene)
{
	if (!Scene)
		return false;
	//이미있음
	if (m_vecWidgetWindow.size() != 0)
	{
		return true;
	}
	m_pScene = Scene;
	CWidgetWindow* PlayerUI = m_pScene->GetViewport()->AddWindow<CPlayerUI>("PlayerUI");
	PlayerUI->Enable(false);
	m_vecWidgetWindow.insert(std::make_pair("PlayerUI", PlayerUI));
	CWidgetWindow* LobbyMainUI = m_pScene->GetViewport()->AddWindow<CLobbyMainUI>("LobbyMainUI");
	LobbyMainUI->Enable(false);
	m_vecWidgetWindow.insert(std::make_pair("LobbyMainUI", LobbyMainUI));

	CWidgetWindow* LobbyValkyrieSelectUI = m_pScene->GetViewport()->AddWindow<CLobbyValkyrieSelectUI>("LobbyValkyrieSelectUI");
	LobbyValkyrieSelectUI->Enable(false);
	m_vecWidgetWindow.insert(std::make_pair("LobbyValkyrieSelectUI", LobbyValkyrieSelectUI));

	CWidgetWindow* LobbyStageSelectUI = m_pScene->GetViewport()->AddWindow<CLobbyStageSelectUI>("LobbyStageSelectUI");
	LobbyStageSelectUI->Enable(false);
	m_vecWidgetWindow.insert(std::make_pair("LobbyStageSelectUI", LobbyStageSelectUI));

	CWidgetWindow* GameClearUI = m_pScene->GetViewport()->AddWindow<CGameClearUI>("GameClearUI");
	GameClearUI->Enable(false);
	m_vecWidgetWindow.insert(std::make_pair("GameClearUI", GameClearUI));

	CWidgetWindow* LoadingUI = m_pScene->GetViewport()->AddWindow<CLoadingUI>("LoadingUI");
	LoadingUI->Enable(false);
	m_vecWidgetWindow.insert(std::make_pair("LoadingUI", LoadingUI));

	CWidgetWindow* FadeInOut_White = m_pScene->GetViewport()->AddWindow<CFadeInOut_White>("FadeInOut_WhiteUI");
	FadeInOut_White->Enable(false);
	m_vecWidgetWindow.insert(std::make_pair("FadeInOut_WhiteUI", FadeInOut_White));


	CWidgetWindow* FadeInOutUI = m_pScene->GetViewport()->AddWindow<CFadeInOutUI>("FadeInOutUI");
	FadeInOutUI->Enable(false);
	m_vecWidgetWindow.insert(std::make_pair("FadeInOutUI", FadeInOutUI));

	CWidgetWindow* LobbyValkyrieInfoUI = m_pScene->GetViewport()->AddWindow<CLobbyValkyrieInfoUI>("LobbyValkyrieInfoUI");
	LobbyValkyrieInfoUI->Enable(false);
	m_vecWidgetWindow.insert(std::make_pair("LobbyValkyrieInfoUI", LobbyValkyrieInfoUI));

	CWidgetWindow* PlayerHitComboUI = m_pScene->GetViewport()->AddWindow<CPlayerHitComboUI>("PlayerHitComboUI");
	PlayerHitComboUI->Enable(false);
	m_vecWidgetWindow.insert(std::make_pair("PlayerHitComboUI", PlayerHitComboUI));

	CTargetImageWidget* TargetImageWidget = m_pScene->GetViewport()->AddWindow<CTargetImageWidget>("TargetImageWidget");
	TargetImageWidget->Enable(false);
	m_vecWidgetWindow.insert(std::make_pair("TargetImageWidget", TargetImageWidget));

	CLobbyEquipmemtUI* LobbyEquipmemtUI = m_pScene->GetViewport()->AddWindow<CLobbyEquipmemtUI>("LobbyEquipmemtUI");
	LobbyEquipmemtUI->Enable(false);
	m_vecWidgetWindow.insert(std::make_pair("LobbyEquipmemtUI", LobbyEquipmemtUI));

	CLobbyLevelUpDialog* LobbyLevelUpDialog = m_pScene->GetViewport()->AddWindow<CLobbyLevelUpDialog>("LobbyLevelUpDialog");
	LobbyLevelUpDialog->Enable(false);
	m_vecWidgetWindow.insert(std::make_pair("LobbyLevelUpDialog", LobbyLevelUpDialog));

	CLobbyItemInfoDialog* LobbyItemInfoDialog = m_pScene->GetViewport()->AddWindow<CLobbyItemInfoDialog>("LobbyItemInfoDialog");
	LobbyItemInfoDialog->Enable(false);
	m_vecWidgetWindow.insert(std::make_pair("LobbyItemInfoDialog", LobbyItemInfoDialog));

	CLobbyWeaponInfoUI* LobbyWeaponInfoUI = m_pScene->GetViewport()->AddWindow<CLobbyWeaponInfoUI>("LobbyWeaponInfoUI");
	LobbyWeaponInfoUI->Enable(false);
	m_vecWidgetWindow.insert(std::make_pair("LobbyWeaponInfoUI", LobbyWeaponInfoUI));

	CLobbyWeaponLevelUpDialog* LobbyWeaponLevelUpDialog = m_pScene->GetViewport()->AddWindow<CLobbyWeaponLevelUpDialog>("LobbyWeaponLevelUpDialog");
	LobbyWeaponLevelUpDialog->Enable(false);
	m_vecWidgetWindow.insert(std::make_pair("LobbyWeaponLevelUpDialog", LobbyWeaponLevelUpDialog));

	CLobbySupplyUI* LobbySupplyUI = m_pScene->GetViewport()->AddWindow<CLobbySupplyUI>("LobbySupplyUI");
	LobbySupplyUI->Enable(false);
	m_vecWidgetWindow.insert(std::make_pair("LobbySupplyUI", LobbySupplyUI));

	CLobbySupplyResultUI* LobbySupplyResultUI = m_pScene->GetViewport()->AddWindow<CLobbySupplyResultUI>("LobbySupplyResultUI");
	LobbySupplyResultUI->Enable(false);
	m_vecWidgetWindow.insert(std::make_pair("LobbySupplyResultUI", LobbySupplyResultUI));

	CLoadingUI_Resource* LoadingUI_Resource = m_pScene->GetViewport()->AddWindow<CLoadingUI_Resource>("LoadingUI_Resource");
	LoadingUI_Resource->Enable(false);
	m_vecWidgetWindow.insert(std::make_pair("LoadingUI_Resource", LoadingUI_Resource));
	return true;
}

CWidgetWindow* CUIManager::FindWidgetWindow(const std::string& Name)
{
	auto iter = m_vecWidgetWindow.find(Name);
	if (iter == m_vecWidgetWindow.end())
	{
		return nullptr;
	}
	return iter->second;
}

void CUIManager::AllWidgetClose()
{
	auto iter = m_vecWidgetWindow.begin();
	auto iterEnd = m_vecWidgetWindow.end();

	for (; iter != iterEnd; ++iter)
	{
		iter->second->Enable(false);
	}
}
