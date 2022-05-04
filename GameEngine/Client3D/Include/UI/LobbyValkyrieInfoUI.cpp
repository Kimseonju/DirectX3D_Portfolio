
#include "LobbyValkyrieInfoUI.h"
#include "UI/Image.h"
#include "UI/Button.h"
#include <Device.h>
#include "../Object/Player.h"
#include "UIManager.h"
#include "Resource/Animation.h"
#include "../PublicData.h"
#include "Scene/SceneManager.h"
#include "../PublicData.h"
#include "../DataTable/PlayerDataTable.h"
#include "Device.h"
#include "../LobbyManager.h"
#include "Scene/Scene.h"
#include "Scene/CameraManager.h"
#include "../Object/LobbyValkyrieSelectZone.h"
#include "LobbyLevelUpDialog.h"
CLobbyValkyrieInfoUI::CLobbyValkyrieInfoUI() :
	m_CurStatus(nullptr)
{
}

CLobbyValkyrieInfoUI::CLobbyValkyrieInfoUI(const CLobbyValkyrieInfoUI& widget) :
	CWidgetWindow(widget)
{
	m_CurStatus = widget.m_CurStatus;
}

CLobbyValkyrieInfoUI::~CLobbyValkyrieInfoUI()
{
}

void CLobbyValkyrieInfoUI::Start()
{
	CWidgetWindow::Start();
}

bool CLobbyValkyrieInfoUI::Init()
{
	CWidgetWindow::Init();
	Resolution RS = CDevice::GetInst()->GetResolution();

	CImage* Image;


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
	m_BtnBack->SetClickCallback<CLobbyValkyrieInfoUI>(this, &CLobbyValkyrieInfoUI::BtnBackCallback);

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


	Image = CreateWidget<CImage>("ValkyrjaInfoBG");
	Image->SetPos(620.f, 400.f);
	Image->SetSize(620.f, 220.f);
	Image->SetCollision(false);
	Image->SetZOrder(2);
	Image->SetTexture("Energy_debris", TEXT("UI/Share/Energy_debris.png"));

	Text = CreateWidget<CText>("Text1");
	Text->SetPos(650.f, 560.f);
	Text->SetSize(150.f, 50.f);
	Text->SetFontSize(30.f);
	Text->SetCollision(false);
	Text->SetAlignH(TEXT_ALIGN_H::Left);
	Text->SetAlignV(TEXT_ALIGN_V::Bottom);
	Text->SetZOrder(3);
	Text->SetText(TEXT("기본 속성"));

	m_ImgValkyrjaStar = CreateWidget<CImage>("ImgValkyrjaStar");
	m_ImgValkyrjaStar->SetPos(1140.f, 540.f);
	m_ImgValkyrjaStar->SetSize(60.f, 60.f);
	m_ImgValkyrjaStar->SetCollision(false);
	m_ImgValkyrjaStar->SetZOrder(3);
	m_ImgValkyrjaStar->SetTexture("Star_Avatar_5M", TEXT("UI/Character Select/Star Avatar/Star_Avatar_5M.png"));


	Text = CreateWidget<CText>("Text1HP");
	Text->SetPos(650.f, 520.f);
	Text->SetSize(40.f, 30.f);
	Text->SetFontSize(20.f);
	Text->SetCollision(false);
	Text->SetAlignH(TEXT_ALIGN_H::Left);
	Text->SetAlignV(TEXT_ALIGN_V::Bottom);
	Text->SetZOrder(3);
	Text->SetText(TEXT("HP"));


	m_HPText = CreateWidget<CText>("Text1HP");
	m_HPText->SetPos(800.f, 520.f);
	m_HPText->SetSize(90.f, 40.f);
	m_HPText->SetFontSize(20.f);
	m_HPText->SetCollision(false);
	m_HPText->SetAlignH(TEXT_ALIGN_H::Right);
	m_HPText->SetAlignV(TEXT_ALIGN_V::Bottom);
	m_HPText->SetZOrder(3);
	m_HPText->SetText(TEXT("1234"));


	Text = CreateWidget<CText>("Text1Damage");
	Text->SetPos(650.f, 470.f);
	Text->SetSize(600.f, 30.f);
	Text->SetFontSize(20.f);
	Text->SetCollision(false);
	Text->SetAlignH(TEXT_ALIGN_H::Left);
	Text->SetAlignV(TEXT_ALIGN_V::Bottom);
	Text->SetZOrder(3);
	Text->SetText(TEXT("공격력"));

	m_DamageText = CreateWidget<CText>("DamageText");
	m_DamageText->SetPos(800.f, 470.f);
	m_DamageText->SetSize(90.f, 40.f);
	m_DamageText->SetFontSize(20.f);
	m_DamageText->SetCollision(false);
	m_DamageText->SetAlignH(TEXT_ALIGN_H::Right);
	m_DamageText->SetAlignV(TEXT_ALIGN_V::Bottom);
	m_DamageText->SetZOrder(3);
	m_DamageText->SetText(TEXT("1234"));


	Text = CreateWidget<CText>("Text1SP");
	Text->SetPos(960.f, 470.f);
	Text->SetSize(40.f, 30.f);
	Text->SetFontSize(20.f);
	Text->SetCollision(false);
	Text->SetAlignH(TEXT_ALIGN_H::Left);
	Text->SetAlignV(TEXT_ALIGN_V::Bottom);
	Text->SetZOrder(3);
	Text->SetText(TEXT("SP"));

	m_SPText = CreateWidget<CText>("Text1HP");
	m_SPText->SetPos(1125.f, 470.f);
	m_SPText->SetSize(90.f, 40.f);
	m_SPText->SetFontSize(20.f);
	m_SPText->SetCollision(false);
	m_SPText->SetAlignH(TEXT_ALIGN_H::Right);
	m_SPText->SetAlignV(TEXT_ALIGN_V::Bottom);
	m_SPText->SetZOrder(3);
	m_SPText->SetText(TEXT("1234"));


	Image = CreateWidget<CImage>("ValkyrjaInfoBG2");
	Image->SetPos(620.f, 330.f);
	Image->SetSize(620.f, 60.f);
	Image->SetCollision(false);
	Image->SetZOrder(2);
	Image->SetTexture("Energy_debris", TEXT("UI/Share/Energy_debris.png"));

	Text = CreateWidget<CText>("Text1EXP");
	Text->SetPos(650.f, 350.f);
	Text->SetSize(40.f, 30.f);
	Text->SetFontSize(20.f);
	Text->SetCollision(false);
	Text->SetAlignH(TEXT_ALIGN_H::Left);
	Text->SetAlignV(TEXT_ALIGN_V::Bottom);
	Text->SetZOrder(3);
	Text->SetText(TEXT("EXP"));


	m_ExpText = CreateWidget<CText>("ExpText");
	m_ExpText->SetPos(890.f, 355.f);
	m_ExpText->SetSize(90.f, 30.f);
	m_ExpText->SetFontSize(15.f);
	m_ExpText->SetCollision(false);
	m_ExpText->SetAlignH(TEXT_ALIGN_H::Right);
	m_ExpText->SetAlignV(TEXT_ALIGN_V::Bottom);
	m_ExpText->SetZOrder(3);
	m_ExpText->SetText(TEXT("1234"));

	m_ExpProgressBar = CreateWidget<CProgressBar>("ExpProgressBar");
	m_ExpProgressBar->SetPos(747.f, 335.f);
	m_ExpProgressBar->SetSize(470.f, 15.f);
	//m_ExpProgressBar->SetBackTint(0.5f, 0.5f, 1.f, 0.5f);

	m_BtnValkyrjaLevelUp = CreateWidget<CButton>("BtnValkyrjaLevelUp");
	m_BtnValkyrjaLevelUp->SetPos(1080.f, 270.f);
	m_BtnValkyrjaLevelUp->SetSize(140.f, 50.f);
	m_BtnValkyrjaLevelUp->SetCollision(true);
	m_BtnValkyrjaLevelUp->SetZOrder(3);
	m_BtnValkyrjaLevelUp->SetStateTexture(Button_State::Normal, "UI_2", TEXT("UI/Share/UI_2.png"));
	m_BtnValkyrjaLevelUp->SetStateTexture(Button_State::MouseOn, "UI_2", TEXT("UI/Share/UI_2.png"));
	m_BtnValkyrjaLevelUp->SetStateTexture(Button_State::Disabled, "UI_2", TEXT("UI/Share/UI_2.png"));
	m_BtnValkyrjaLevelUp->SetStateTexture(Button_State::Click, "UI_2", TEXT("UI/Share/UI_2.png"));
	m_BtnValkyrjaLevelUp->SetClickCallback<CLobbyValkyrieInfoUI>(this, &CLobbyValkyrieInfoUI::BtnValkyrjaLevelUpCallback);

	Text = CreateWidget<CText>("Text1LevelUp");
	Text->SetPos(1080.f, 270.f);
	Text->SetSize(140.f, 50.f);
	Text->SetFontSize(25.f);
	Text->SetCollision(false);
	Text->SetAlignH(TEXT_ALIGN_H::Center);
	Text->SetAlignV(TEXT_ALIGN_V::Middle);
	Text->SetZOrder(4);
	Text->SetColor(0.f, 0.f, 0.f);
	Text->SetColorTint(0.f, 0.f, 0.f, 1.f);
	Text->SetText(TEXT("레벨 업"));

#pragma endregion

#pragma region ValkyrieInfo_Name_Level

	Image = CreateWidget<CImage>("ValkyrjaInfoBG2");
	Image->SetPos(35.f, 20.f);
	Image->SetSize(500.f, 100.f);
	Image->SetCollision(false);
	Image->SetZOrder(2);
	Image->SetTexture("Energy_debris", TEXT("UI/Share/Energy_debris.png"));


	m_ImgValkyrjaParticularType = CreateWidget<CImage>("ImgValkyrjaParticularType");
	m_ImgValkyrjaParticularType->SetPos(50.f, 30.f);
	m_ImgValkyrjaParticularType->SetSize(77.f, 77.f);
	m_ImgValkyrjaParticularType->SetCollision(false);
	m_ImgValkyrjaParticularType->SetZOrder(2);
	m_ImgValkyrjaParticularType->SetTexture("AttributeTypeJixie", TEXT("UI/Character Select/Attribute Type/AttributeTypeJixie.png"));


	m_ValkyrjaNameText = CreateWidget<CText>("ValkyrjaNameText");
	m_ValkyrjaNameText->SetPos(140.f, 70.f);
	m_ValkyrjaNameText->SetSize(250.f, 40.f);
	m_ValkyrjaNameText->SetFontSize(20.f);
	m_ValkyrjaNameText->SetCollision(false);
	m_ValkyrjaNameText->SetAlignH(TEXT_ALIGN_H::Left);
	m_ValkyrjaNameText->SetAlignV(TEXT_ALIGN_V::Bottom);
	m_ValkyrjaNameText->SetZOrder(3);
	m_ValkyrjaNameText->SetText(TEXT("발키리이름"));

	m_ValkyrjaLevelText = CreateWidget<CText>("ValkyrjaLevelText");
	m_ValkyrjaLevelText->SetPos(465.f, 70.f);
	m_ValkyrjaLevelText->SetSize(65.f, 40.f);
	m_ValkyrjaLevelText->SetFontSize(20.f);
	m_ValkyrjaLevelText->SetCollision(false);
	m_ValkyrjaLevelText->SetAlignH(TEXT_ALIGN_H::Left);
	m_ValkyrjaLevelText->SetAlignV(TEXT_ALIGN_V::Bottom);
	m_ValkyrjaLevelText->SetZOrder(3);
	m_ValkyrjaLevelText->SetText(TEXT("Lv.1"));
#pragma endregion

#pragma region BtnLevelUP_Weapon
	//m_BtnLevelUp = CreateWidget<CButton>("BtnLevelUp");
	//m_BtnLevelUp->SetPos(630.f, 20.f);
	//m_BtnLevelUp->SetSize(300.f, 70.f);
	//m_BtnLevelUp->SetCollision(true);
	//m_BtnLevelUp->SetZOrder(3);
	//m_BtnLevelUp->SetStateTexture(Button_State::Normal, "UI_Box_White", TEXT("UI/Share/UI_Box_White.png"));
	//m_BtnLevelUp->SetStateTexture(Button_State::MouseOn, "UI_Box_White", TEXT("UI/Share/UI_Box_White.png"));
	//m_BtnLevelUp->SetStateTexture(Button_State::Disabled, "UI_Box_White", TEXT("UI/Share/UI_Box_White.png"));
	//m_BtnLevelUp->SetStateTexture(Button_State::Click, "UI_Box_White", TEXT("UI/Share/UI_Box_White.png"));
	//
	//Text = CreateWidget<CText>("Text");
	//Text->SetPos(630.f, 20.f);
	//Text->SetSize(300.f, 70.f);
	//Text->SetFontSize(40.f);
	//Text->SetCollision(false);
	//Text->SetAlignH(TEXT_ALIGN_H::Center);
	//Text->SetAlignV(TEXT_ALIGN_V::Middle);
	//Text->SetZOrder(4);
	//Text->SetColor(0.f, 0.f, 0.f);
	//Text->SetColorTint(0.f, 0.f, 0.f, 1.f);
	//Text->SetText(TEXT("레벨 업"));
	//
	//
	//m_BtnWeapon = CreateWidget<CButton>("BtnWeapon");
	//m_BtnWeapon->SetPos(940.f, 20.f);
	//m_BtnWeapon->SetSize(300.f, 70.f);
	//m_BtnWeapon->SetCollision(true);
	//m_BtnWeapon->SetZOrder(3);
	//m_BtnWeapon->SetStateTexture(Button_State::Normal, "UI_Btn_Blue", TEXT("UI/Share/UI_Btn_Blue.png"));
	//m_BtnWeapon->SetStateTexture(Button_State::MouseOn, "UI_Btn_Blue", TEXT("UI/Share/UI_Btn_Blue.png"));
	//m_BtnWeapon->SetStateTexture(Button_State::Disabled, "UI_Btn_Blue", TEXT("UI/Share/UI_Btn_Blue.png"));
	//m_BtnWeapon->SetStateTexture(Button_State::Click, "UI_Btn_Blue", TEXT("UI/Share/UI_Btn_Blue.png"));
	//m_BtnWeapon->SetClickCallback<CLobbyValkyrieInfoUI>(this, &CLobbyValkyrieInfoUI::BtnWeaponCallback);
	//
	//Text = CreateWidget<CText>("Text");
	//Text->SetPos(940.f, 20.f);
	//Text->SetSize(300.f, 70.f);
	//Text->SetFontSize(40.f);
	//Text->SetCollision(false);
	//Text->SetAlignH(TEXT_ALIGN_H::Center);
	//Text->SetAlignV(TEXT_ALIGN_V::Middle);
	//Text->SetZOrder(3);
	//Text->SetText(TEXT("무기"));
	//
	return true;
}

void CLobbyValkyrieInfoUI::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
	ValkyrieInfoUpdate();
	m_CrystalText->SetText(std::to_wstring(CPublicData::GetInst()->GetCrystal()).c_str());
}

void CLobbyValkyrieInfoUI::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CLobbyValkyrieInfoUI::Render()
{
	CWidgetWindow::Render();
}

CLobbyValkyrieInfoUI* CLobbyValkyrieInfoUI::Clone()
{
	return new CLobbyValkyrieInfoUI(*this);
}

void CLobbyValkyrieInfoUI::BtnBackCallback()
{
	CSound* Sound = m_Scene->GetResource()->FindSound2D("ButtonClick");
	Sound->Play();
	Enable(false);
	CUIManager::GetInst()->FindWidgetWindow("LobbyValkyrieSelectUI")->Enable(true);
	CLobbyManager::GetInst()->GetValkyrieSelectZone()->Valkyrie_Zone();
}

void CLobbyValkyrieInfoUI::BtnValkyrjaLevelUpCallback()
{
	if (m_CurStatus->Level == m_CurStatus->LevelMax)
	{
		return;
	}
	CLobbyLevelUpDialog* LobbyLevelUpDialog =(CLobbyLevelUpDialog *)CUIManager::GetInst()->FindWidgetWindow("LobbyLevelUpDialog");
	LobbyLevelUpDialog->SetPlayerData(m_CurStatus);
	LobbyLevelUpDialog->SetLevelUpDialog();
	LobbyLevelUpDialog->Enable(true);
}

void CLobbyValkyrieInfoUI::BtnWeaponCallback()
{
}


void CLobbyValkyrieInfoUI::ValkyrieInfoUpdate()
{
	if (m_CurStatus)
	{
		std::wstring str;
		str=std::to_wstring(m_CurStatus->HPMax);
		m_HPText->SetText(str.c_str());
		
		str = std::to_wstring(m_CurStatus->SPMax);
		m_SPText->SetText(str.c_str());

		str = std::to_wstring(m_CurStatus->DamageMax);
		m_DamageText->SetText(str.c_str());

		str = std::to_wstring(m_CurStatus->Exp) + TEXT("/") + std::to_wstring(m_CurStatus->ExpMax);
		m_ExpText->SetText(str.c_str());
		m_ExpProgressBar->SetPercent((float)m_CurStatus->Exp / (float)m_CurStatus->ExpMax);
		switch (m_CurStatus->starType)
		{
		case StarType::B:
			m_ImgValkyrjaStar->SetTexture("Star_Avatar_1M", TEXT("UI/Character Select/Star Avatar/Star_Avatar_1M.png"));
			break;
		case StarType::A:
			m_ImgValkyrjaStar->SetTexture("Star_Avatar_2M", TEXT("UI/Character Select/Star Avatar/Star_Avatar_2M.png"));
			break;
		case StarType::S:
			m_ImgValkyrjaStar->SetTexture("Star_Avatar_3M", TEXT("UI/Character Select/Star Avatar/Star_Avatar_3M.png"));
			break;
		case StarType::SS:
			m_ImgValkyrjaStar->SetTexture("Star_Avatar_4M", TEXT("UI/Character Select/Star Avatar/Star_Avatar_4M.png"));
			break;
		case StarType::SSS:
			m_ImgValkyrjaStar->SetTexture("Star_Avatar_5M", TEXT("UI/Character Select/Star Avatar/Star_Avatar_5M.png"));
			break;
		}
		switch (m_CurStatus->attributeType)
		{
		case AttributeType::Biologic:
			m_ImgValkyrjaParticularType->SetTexture("UI_Biologic", TEXT("UI/Equip/UI_Biologic.png"));
			break;
		case AttributeType::Psychic:
			m_ImgValkyrjaParticularType->SetTexture("UI_Psychic", TEXT("UI/Equip/UI_Psychic.png"));
			break;
		case AttributeType::Mecha:
			m_ImgValkyrjaParticularType->SetTexture("UI_Mecha", TEXT("UI/Equip/UI_Mecha.png"));
			break;
		}
		m_ValkyrjaNameText->SetText(m_CurStatus->PlayerName.c_str());

		str = TEXT("Lv.")+std::to_wstring(m_CurStatus->Level);
		m_ValkyrjaLevelText->SetText(str.c_str());
	}

}

