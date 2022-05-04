
#include "LobbyMainUI.h"
#include "UI/Image.h"
#include "UI/Button.h"
#include <Device.h>
#include "../Object/Player.h"
#include "UIManager.h"
#include "Resource/Animation.h"
#include "../PublicData.h"
#include "../StageManager.h"
#include "../LobbyManager.h"
#include "Scene/Scene.h"
#include "Scene/CameraManager.h"
CLobbyMainUI::CLobbyMainUI()
{
}

CLobbyMainUI::CLobbyMainUI(const CLobbyMainUI& widget)
{
}

CLobbyMainUI::~CLobbyMainUI()
{
}

bool CLobbyMainUI::Init()
{
	CWidgetWindow::Init();

	CText* Text = CreateWidget<CText>("Lv");
	Text->SetPos(20.f, 680.f);
	Text->SetSize(100.f, 50.f);
	Text->SetFontSize(30.f);
	Text->SetCollision(false);
	Text->SetText(TEXT("Lv.22"));
	Text->SetZOrder(2);
	Text->SetAlignH(TEXT_ALIGN_H::Left);
	Text->SetAlignV(TEXT_ALIGN_V::Bottom);

	Text = CreateWidget<CText>("CharacterName");
	Text->SetPos(125.f, 680.f);
	Text->SetSize(200.f, 50.f);
	Text->SetFontSize(30.f);
	Text->SetCollision(false);
	Text->SetText(TEXT("함장"));
	Text->SetZOrder(2);
	Text->SetAlignH(TEXT_ALIGN_H::Left);
	Text->SetAlignV(TEXT_ALIGN_V::Bottom);

	//왼쪽위EXP
	CImage* Image;

	//위쪽버튼
	m_BtnAttack = CreateWidget<CButton>("LobbyBtnAttack");
	m_BtnAttack->SetPos(1030.f, 480.f);
	m_BtnAttack->SetSize(140.f, 140.f);
	m_BtnAttack->SetCollision(true);
	m_BtnAttack->SetZOrder(2);
	m_BtnAttack->SetStateTexture(Button_State::Normal, "UI_BtnAttack", TEXT("UI/MainPage/UI_BtnAttack.png"));
	m_BtnAttack->SetStateTexture(Button_State::MouseOn, "UI_BtnAttack", TEXT("UI/MainPage/UI_BtnAttack.png"));
	m_BtnAttack->SetStateTexture(Button_State::Disabled, "UI_BtnAttack", TEXT("UI/MainPage/UI_BtnAttack.png"));
	m_BtnAttack->SetStateTexture(Button_State::Click, "UI_BtnAttackClick", TEXT("UI/MainPage/UI_BtnAttack_Click.png"));
	m_BtnAttack->SetClickCallback<CLobbyMainUI>(this, &CLobbyMainUI::BtnAttackCallback);


	//가운데 왼쪽
	m_BtnValkyrja = CreateWidget<CButton>("LobbyBtnValkyrja");
	m_BtnValkyrja->SetPos(950.f, 340.f);
	m_BtnValkyrja->SetSize(140.f, 140.f);
	m_BtnValkyrja->SetCollision(true);
	m_BtnValkyrja->SetZOrder(2);
	m_BtnValkyrja->SetStateTexture(Button_State::Normal, "UI_BtnValkyrja", TEXT("UI/MainPage/UI_BtnValkyrja.png"));
	m_BtnValkyrja->SetStateTexture(Button_State::MouseOn, "UI_BtnValkyrja", TEXT("UI/MainPage/UI_BtnValkyrja.png"));
	m_BtnValkyrja->SetStateTexture(Button_State::Disabled, "UI_BtnValkyrja", TEXT("UI/MainPage/UI_BtnValkyrja.png"));
	m_BtnValkyrja->SetStateTexture(Button_State::Click, "UI_BtnValkyrjaClick", TEXT("UI/MainPage/UI_BtnValkyrja_Click.png"));
	m_BtnValkyrja->SetClickCallback<CLobbyMainUI>(this, &CLobbyMainUI::BtnValkyrjaCallback);

	//가운데오른쪽
	m_BtnEquip = CreateWidget<CButton>("LobbyBtnEquip");
	m_BtnEquip->SetPos(1100.f, 340.f);
	m_BtnEquip->SetSize(140.f, 140.f);
	m_BtnEquip->SetCollision(true);
	m_BtnEquip->SetZOrder(2);
	m_BtnEquip->SetStateTexture(Button_State::Normal, "UI_BtnEquip", TEXT("UI/MainPage/UI_BtnEquip.png"));
	m_BtnEquip->SetStateTexture(Button_State::MouseOn, "UI_BtnEquip", TEXT("UI/MainPage/UI_BtnEquip.png"));
	m_BtnEquip->SetStateTexture(Button_State::Disabled, "UI_BtnEquip", TEXT("UI/MainPage/UI_BtnEquip.png"));
	m_BtnEquip->SetStateTexture(Button_State::Click, "UI_BtnEquipClick", TEXT("UI/MainPage/UI_BtnEquip_Click.png"));
	m_BtnEquip->SetClickCallback<CLobbyMainUI>(this, &CLobbyMainUI::BtnEquipCallback);

	//아래버튼
	m_BtnShop = CreateWidget<CButton>("LobbyBtnShop");
	m_BtnShop->SetPos(1030.f, 200.f);
	m_BtnShop->SetSize(140.f, 140.f);
	m_BtnShop->SetCollision(true);
	m_BtnShop->SetZOrder(2);
	m_BtnShop->SetStateTexture(Button_State::Normal, "UI_BtnShop", TEXT("UI/MainPage/UI_BtnShop.png"));
	m_BtnShop->SetStateTexture(Button_State::MouseOn, "UI_BtnShop", TEXT("UI/MainPage/UI_BtnShop.png"));
	m_BtnShop->SetStateTexture(Button_State::Disabled, "UI_BtnShop", TEXT("UI/MainPage/UI_BtnShop.png"));
	m_BtnShop->SetStateTexture(Button_State::Click, "UI_BtnShopClick", TEXT("UI/MainPage/UI_BtnShop_Click.png"));
	m_BtnShop->SetClickCallback<CLobbyMainUI>(this, &CLobbyMainUI::BtnShopCallback);

	//본부
	//Image = CreateWidget<CImage>("Center");
	//Image->SetPos(980.f, 50.f);
	//Image->SetSize(150.f, 50.f);
	//Image->SetCollision(false);
	//Image->SetZOrder(2);
	//Image->SetTexture("UI_Btn_Gray", TEXT("UI/Share/UI_Btn_Gray.png"));



	//금화
	Image = CreateWidget<CImage>("GoldBG");
	Image->SetPos(835.f, 670.f);
	Image->SetSize(160.f, 30.f);
	Image->SetCollision(false);
	Image->SetTexture("UI_Btn_Gray", TEXT("UI/Share/UI_Btn_Gray.png"));
	Image->SetZOrder(2);

	Image = CreateWidget<CImage>("Gold");
	Image->SetPos(835.f, 670.f);
	Image->SetSize(36.f, 36.f);
	Image->SetCollision(false);
	Image->SetTexture("Gold", TEXT("UI/MainPage/Gold.png"));
	Image->SetZOrder(3);

	m_GoldText = CreateWidget<CText>("GoldText");
	m_GoldText->SetPos(870.f, 670.f);
	m_GoldText->SetSize(100.f, 30);
	m_GoldText->SetFontSize(20.f);
	m_GoldText->SetCollision(false);
	m_GoldText->SetText(std::to_wstring(CPublicData::GetInst()->GetGold()).c_str());
	m_GoldText->SetZOrder(4);
	m_GoldText->SetAlignH(TEXT_ALIGN_H::Right);
	m_GoldText->SetAlignV(TEXT_ALIGN_V::Bottom);

	//크리스탈
	Image = CreateWidget<CImage>("CrystalBG");
	Image->SetPos(1050.f, 670.f);
	Image->SetSize(150.f, 30.f);
	Image->SetCollision(false);
	Image->SetTexture("UI_Btn_Gray", TEXT("UI/Share/UI_Btn_Gray.png"));
	Image->SetZOrder(2);

	Image = CreateWidget<CImage>("Crystal");
	Image->SetPos(1050.f, 670.f);
	Image->SetSize(36.f, 36.f);
	Image->SetCollision(false);
	Image->SetTexture("Crystal", TEXT("UI/MainPage/Crystal.png"));
	Image->SetZOrder(3);

	m_CrystalText = CreateWidget<CText>("CrystalText");
	m_CrystalText->SetPos(1095, 670.f);
	m_CrystalText->SetSize(80.f, 30.f);
	m_CrystalText->SetFontSize(20.f);
	m_CrystalText->SetCollision(false);
	m_CrystalText->SetText(std::to_wstring(CPublicData::GetInst()->GetCrystal()).c_str());
	m_CrystalText->SetZOrder(4);
	m_CrystalText->SetAlignH(TEXT_ALIGN_H::Right);
	m_CrystalText->SetAlignV(TEXT_ALIGN_V::Bottom);

	return true;
}

void CLobbyMainUI::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
	m_CrystalText->SetText(std::to_wstring(CPublicData::GetInst()->GetCrystal()).c_str());
}

void CLobbyMainUI::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CLobbyMainUI::Render()
{
	CWidgetWindow::Render();
}

CLobbyMainUI* CLobbyMainUI::Clone()
{
	return new CLobbyMainUI(*this);
}

void CLobbyMainUI::SetGoldText(int Gold)
{
	std::wstring str;
	str = std::to_wstring(Gold);
	m_GoldText->SetText(str.c_str());
}

void CLobbyMainUI::SetCrystalText(int Crystal)
{
	std::wstring str;
	str = std::to_wstring(Crystal);
	m_CrystalText->SetText(str.c_str());
}

void CLobbyMainUI::BtnAttackCallback()
{
	CSound* Sound = m_Scene->GetResource()->FindSound2D("ButtonClick");
	Sound->Play();
	Enable(false);
	CUIManager::GetInst()->FindWidgetWindow("LobbyStageSelectUI")->Enable(true);
	CStageManager::GetInst()->BGMPlay("StageSelectBG");
}

void CLobbyMainUI::BtnValkyrjaCallback()
{
	CSound* Sound = m_Scene->GetResource()->FindSound2D("ButtonClick");
	Sound->Play();
	Enable(false);
	CUIManager::GetInst()->FindWidgetWindow("LobbyValkyrieSelectUI")->Enable(true);
	Vector3 Pos = CLobbyManager::GetInst()->GetSelectCameraPos();
	m_Scene->GetCameraManager()->GetCurrentCamera()->SetWorldPos(Pos);
	
}

void CLobbyMainUI::BtnEquipCallback()
{
	CSound* Sound = m_Scene->GetResource()->FindSound2D("ButtonClick");
	Sound->Play();
	Enable(false);
	CUIManager::GetInst()->FindWidgetWindow("LobbyEquipmemtUI")->Enable(true);
}

void CLobbyMainUI::BtnShopCallback()
{
	CStageManager::GetInst()->BGMPlay("ShopBG");
	CSound* Sound = m_Scene->GetResource()->FindSound2D("ButtonClick");
	Sound->Play();
	Enable(false);
	CUIManager::GetInst()->FindWidgetWindow("LobbySupplyUI")->Enable(true);
	
}