
#include "LobbyWeaponInfoUI.h"
#include <Device.h>
#include "../PublicData.h"
#include "UIManager.h"
#include "LobbyWeaponLevelUpDialog.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
CLobbyWeaponInfoUI::CLobbyWeaponInfoUI():
	m_BackEquip(false),
	m_BackValkyrieSelect(false),
	m_ItemData(nullptr)

{
}

CLobbyWeaponInfoUI::CLobbyWeaponInfoUI(const CLobbyWeaponInfoUI& widget):
	CWidgetWindow(widget)
{
	m_BackEquip = widget.m_BackEquip;
	m_BackValkyrieSelect = widget.m_BackValkyrieSelect;
	m_ItemData = widget.m_ItemData;
}

CLobbyWeaponInfoUI::~CLobbyWeaponInfoUI()
{
}

void CLobbyWeaponInfoUI::Start()
{
	CWidgetWindow::Start();
}

bool CLobbyWeaponInfoUI::Init()
{
	CWidgetWindow::Init();
	Resolution RS = CDevice::GetInst()->GetResolution();

	CImage* Image;
	Image = CreateWidget<CImage>("BG_2");
	Image->SetSize((float)RS.Width, (float)RS.Height);
	Image->SetPos(0.f, 0.f);
	Image->SetCollision(false);
	Image->SetZOrder(1);
	Image->SetTexture("SpaceShipBridge_City", TEXT("UI/Share/SpaceShipBridge_City_.png"));
	Image->SetColorTint(1.f, 1.f, 1.f, 1.f);


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
#pragma region BtnBack
	m_BtnBack = CreateWidget<CButton>("BackButton");
	m_BtnBack->SetPos(0.f, 650.f);
	m_BtnBack->SetSize(130.f, 50.f);
	m_BtnBack->SetCollision(true);
	m_BtnBack->SetZOrder(2);
	m_BtnBack->SetStateTexture(Button_State::Normal, "UI_Btn_Yellow", TEXT("UI/Share/UI_Btn_Yellow.png"));
	m_BtnBack->SetStateTexture(Button_State::MouseOn, "UI_Btn_Yellow", TEXT("UI/Share/UI_Btn_Yellow.png"));
	m_BtnBack->SetStateTexture(Button_State::Disabled, "UI_Btn_Yellow", TEXT("UI/Share/UI_Btn_Yellow.png"));
	m_BtnBack->SetStateTexture(Button_State::Click, "UI_Btn_Yellow", TEXT("UI/Share/UI_Btn_Yellow.png"));
	m_BtnBack->SetClickCallback<CLobbyWeaponInfoUI>(this, &CLobbyWeaponInfoUI::BtnBackCallback);

	CText* Text = CreateWidget<CText>("BackText");
	Text->SetPos(10.f, 660.f);
	Text->SetSize(100.f, 50.f);
	Text->SetFontSize(30.f);
	Text->SetCollision(false);
	Text->SetAlignH(TEXT_ALIGN_H::Left);
	Text->SetAlignV(TEXT_ALIGN_V::Bottom);
	Text->SetZOrder(3);
	Text->SetColor(0.f, 0.f, 0.f);
	Text->SetText(TEXT("< 뒤로"));
#pragma endregion

#pragma region ValkyrjaInfo

	Image = CreateWidget<CImage>("WeaponImageBG");
	Image->SetPos(33.f, 267.f);
	Image->SetSize(620.f, 360.f);
	Image->SetCollision(false);
	Image->SetZOrder(2);
	Image->SetTexture("Energy_debris", TEXT("UI/Share/Energy_debris.png"));

	m_ItemNameText = CreateWidget<CText>("ItemNameText");
	m_ItemNameText->SetPos(105.f, 550.f);
	m_ItemNameText->SetSize(300.f, 50.f);
	m_ItemNameText->SetFontSize(30.f);
	m_ItemNameText->SetCollision(false);
	m_ItemNameText->SetAlignH(TEXT_ALIGN_H::Left);
	m_ItemNameText->SetAlignV(TEXT_ALIGN_V::Bottom);
	m_ItemNameText->SetZOrder(3);
	m_ItemNameText->SetText(TEXT("아이템이름적기"));

	m_ItemImage = CreateWidget<CImage>("ItemImage");
	m_ItemImage->SetPos(240.f, 370.f);
	m_ItemImage->SetSize(200.f, 200.f);
	m_ItemImage->SetCollision(false);
	m_ItemImage->SetZOrder(3);



	Image = CreateWidget<CImage>("WeaponInfoBG");
	Image->SetPos(33.f, 100.f);
	Image->SetSize(620.f, 140.f);
	Image->SetCollision(false);
	Image->SetZOrder(2);
	Image->SetTexture("Energy_debris", TEXT("UI/Share/Energy_debris.png"));

	m_ItemInfoText = CreateWidget<CText>("ItemInfoText");
	m_ItemInfoText->SetPos(70.f, 80.f);
	m_ItemInfoText->SetSize(573.f, 115.f);
	m_ItemInfoText->SetFontSize(30.f);
	m_ItemInfoText->SetCollision(false);
	m_ItemInfoText->SetAlignH(TEXT_ALIGN_H::Left);
	m_ItemInfoText->SetAlignV(TEXT_ALIGN_V::Top);
	m_ItemInfoText->SetZOrder(3);
	m_ItemInfoText->SetText(TEXT("아이템설명아이템설명아이템설명아이템설명아이템설명아이템설명아이템설명아이템설명아이템설명아이템설명아이템설명"));

	m_ItemNameText->SetPos(105.f, 550.f);
	m_ItemNameText->SetSize(300.f, 50.f);

	Image = CreateWidget<CImage>("WeaponInfoBG");
	Image->SetPos(33.f, 20.f);
	Image->SetSize(620.f, 62.f);
	Image->SetCollision(false);
	Image->SetZOrder(2);
	Image->SetTexture("Energy_debris", TEXT("UI/Share/Energy_debris.png"));


	m_ItemLevelText = CreateWidget<CText>("ItemInfoText");
	m_ItemLevelText->SetPos(55.f, 30.f);
	m_ItemLevelText->SetSize(250.f, 40.f);
	m_ItemLevelText->SetFontSize(30.f);
	m_ItemLevelText->SetCollision(false);
	m_ItemLevelText->SetAlignH(TEXT_ALIGN_H::Left);
	m_ItemLevelText->SetAlignV(TEXT_ALIGN_V::Top);
	m_ItemLevelText->SetZOrder(3);
	m_ItemLevelText->SetText(TEXT("Lv. 1 / 5"));
	


	m_ExpProgressBar = CreateWidget<CProgressBar>("ProgressBarCount");
	m_ExpProgressBar->SetPos(237.f, 24.f);
	m_ExpProgressBar->SetSize(400.f, 10.f);
	m_ExpProgressBar->SetCollision(false);
	m_ExpProgressBar->SetZOrder(2);
	m_ExpProgressBar->SetTexture("UI_HPBar", TEXT("UI/In Game/UI_HPBar.png"));
	m_ExpProgressBar->SetBackTexture("UI_HPBar", TEXT("UI/In Game/UI_HPBar.png"));
	m_ExpProgressBar->SetTint(1.f, 0.f, 1.f, 1.f);
	m_ExpProgressBar->SetBackTint(0.1f, 0.1f, 0.1f, 0.5f);


	Image = CreateWidget<CImage>("WeaponInfoBG");
	Image->SetPos(680.f, 500.f);
	Image->SetSize(570.f, 120.f);
	Image->SetCollision(false);
	Image->SetZOrder(2);
	Image->SetTexture("Energy_debris", TEXT("UI/Share/Energy_debris.png"));


	Text = CreateWidget<CText>("Text1Damage");
	Text->SetPos(730.f, 550.f);
	Text->SetSize(100.f, 30.f);
	Text->SetFontSize(20.f);
	Text->SetCollision(false);
	Text->SetAlignH(TEXT_ALIGN_H::Left);
	Text->SetAlignV(TEXT_ALIGN_V::Bottom);
	Text->SetZOrder(3);
	Text->SetText(TEXT("공격력"));


	m_DamageText = CreateWidget<CText>("DamageText");
	m_DamageText->SetPos(840.f, 550.f);
	m_DamageText->SetSize(100.f, 30.f);
	m_DamageText->SetFontSize(20.f);
	m_DamageText->SetCollision(false);
	m_DamageText->SetAlignH(TEXT_ALIGN_H::Right);
	m_DamageText->SetAlignV(TEXT_ALIGN_V::Bottom);
	m_DamageText->SetZOrder(3);
	m_DamageText->SetText(TEXT("3333"));


	m_BtnUpgrade = CreateWidget<CButton>("BtnUpgrade");
	m_BtnUpgrade->SetPos(700.f, 20.f);
	m_BtnUpgrade->SetSize(280.f, 60.f);
	m_BtnUpgrade->SetCollision(true);
	m_BtnUpgrade->SetZOrder(3);
	m_BtnUpgrade->SetStateTexture(Button_State::Normal, "UI_2", TEXT("UI/Share/UI_2.png"));
	m_BtnUpgrade->SetStateTexture(Button_State::MouseOn, "UI_2", TEXT("UI/Share/UI_2.png"));
	m_BtnUpgrade->SetStateTexture(Button_State::Disabled, "UI_2", TEXT("UI/Share/UI_2.png"));
	m_BtnUpgrade->SetStateTexture(Button_State::Click, "UI_2", TEXT("UI/Share/UI_2.png"));
	m_BtnUpgrade->SetClickCallback<CLobbyWeaponInfoUI>(this, &CLobbyWeaponInfoUI::BtnWeaponLevelUpCallback);

	Text = CreateWidget<CText>("Text1LevelUp");
	Text->SetPos(700.f, 20.f);
	Text->SetSize(280.f, 60.f);
	Text->SetFontSize(25.f);
	Text->SetCollision(false);
	Text->SetAlignH(TEXT_ALIGN_H::Center);
	Text->SetAlignV(TEXT_ALIGN_V::Middle);
	Text->SetZOrder(4);
	Text->SetColor(0.f, 0.f, 0.f);
	Text->SetColorTint(0.f, 0.f, 0.f, 1.f);
	Text->SetText(TEXT("강화"));
	return true;
}

void CLobbyWeaponInfoUI::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
	WeaponInfoUpdate();
	m_CrystalText->SetText(std::to_wstring(CPublicData::GetInst()->GetCrystal()).c_str());
}

void CLobbyWeaponInfoUI::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CLobbyWeaponInfoUI::Render()
{
	CWidgetWindow::Render();
}

CLobbyWeaponInfoUI* CLobbyWeaponInfoUI::Clone()
{
	return new CLobbyWeaponInfoUI(*this);
}

void CLobbyWeaponInfoUI::BtnBackCallback()
{
	CSound* Sound = m_Scene->GetResource()->FindSound2D("ButtonClick");
	Sound->Play();
	if (m_BackEquip)
	{
		CUIManager::GetInst()->FindWidgetWindow("LobbyEquipmemtUI")->Enable(true);
	}
	if (m_BackValkyrieSelect)
	{
		CUIManager::GetInst()->FindWidgetWindow("LobbyValkyrieSelectUI")->Enable(true);
	}
	Enable(false);
}

void CLobbyWeaponInfoUI::BtnWeaponLevelUpCallback()
{
	if (m_ItemData->Level == m_ItemData->LevelMax)
	{
		return;
	}
	CLobbyWeaponLevelUpDialog* LobbyWeaponLevelUpDialog = (CLobbyWeaponLevelUpDialog*)CUIManager::GetInst()->FindWidgetWindow("LobbyWeaponLevelUpDialog");
	LobbyWeaponLevelUpDialog->SetItemData(m_ItemData);
	LobbyWeaponLevelUpDialog->SetLevelUpDialog();
	LobbyWeaponLevelUpDialog->Enable(true);
}

void CLobbyWeaponInfoUI::WeaponInfoUpdate()
{
	if (m_ItemData)
	{
		std::wstring str = stringToWstring(m_ItemData->Name);
		m_ItemNameText->SetText(str.c_str());
		str = stringToWstring(m_ItemData->Info);
		m_ItemInfoText->SetText(str.c_str());

		str = TEXT("Lv. ") + std::to_wstring(m_ItemData->Level) + TEXT(" / ") + std::to_wstring(m_ItemData->LevelMax);
		m_ItemLevelText->SetText(str.c_str());

		str = std::to_wstring(m_ItemData->Exp) + TEXT("/") + std::to_wstring(m_ItemData->ExpMax);
		m_ExpProgressBar->SetPercent((float)m_ItemData->Exp / float(m_ItemData->ExpMax));

		str = std::to_wstring(m_ItemData->Damage);
		m_DamageText->SetText(str.c_str());
		m_ItemImage->SetTexture(m_ItemData->FileName.c_str(), m_ItemData->FilePath.c_str());
	}

}

