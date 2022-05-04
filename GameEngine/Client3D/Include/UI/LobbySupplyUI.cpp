
#include "LobbySupplyUI.h"
#include <Device.h>
#include "../PublicData.h"
#include "UIManager.h"
#include "LobbySupplyResultUI.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "../StageManager.h"
CLobbySupplyUI::CLobbySupplyUI()
{
}

CLobbySupplyUI::CLobbySupplyUI(const CLobbySupplyUI& widget)
{
}

CLobbySupplyUI::~CLobbySupplyUI()
{
}

void CLobbySupplyUI::Start()
{
	CWidgetWindow::Start();
}

bool CLobbySupplyUI::Init()
{
	CWidgetWindow::Init();
	Resolution RS = CDevice::GetInst()->GetResolution();

	CImage* Image;
	Image = CreateWidget<CImage>("BG_2");
	Image->SetSize((float)RS.Width, (float)RS.Height);
	Image->SetPos(0.f, 0.f);
	Image->SetCollision(false);
	Image->SetZOrder(1);
	Image->SetTexture("UI_BG", TEXT("UI/Share/UI_BG.png"));
	Image->SetColorTint(1.f, 1.f, 1.f, 1.f);

	Image = CreateWidget<CImage>("BG_3");
	Image->SetPos(400.5f, 50.f);
	Image->SetSize(685.f, 620.25f);
	
	Image->SetCollision(false);
	Image->SetZOrder(3);
	Image->SetTexture("CharaSakura", TEXT("UI/Supply/CharaSakura.png"));
	Image->SetColorTint(1.f, 1.f, 1.f, 1.f);
	for (int y = 0; y < 6; ++y)
	{
		for (int x = 0; x < 6; ++x)
		{
			Image = CreateWidget<CImage>("HexagonalTexture");
			Image->SetSize(246.f, 142.f);
			Image->SetPos(246.f * x, 142.f * y);
			Image->SetCollision(false);
			Image->SetZOrder(2);
			Image->SetTexture("HexagonalTexture", TEXT("UI/Stage_Select/HexagonalTexture.png"));
			Image->SetColorTint(1.f, 1.f, 1.f, 0.3f);
		}
	}



	//금화
	Image = CreateWidget<CImage>("GoldBG");
	Image->SetPos(835.f, 670.f);
	Image->SetSize(160.f, 30.f);
	Image->SetCollision(false);
	Image->SetTexture("UI_Btn_Gray", TEXT("UI/Share/UI_Btn_Gray.png"));
	Image->SetZOrder(4);

	Image = CreateWidget<CImage>("Gold");
	Image->SetPos(835.f, 670.f);
	Image->SetSize(36.f, 36.f);
	Image->SetCollision(false);
	Image->SetTexture("Gold", TEXT("UI/MainPage/Gold.png"));
	Image->SetZOrder(5);

	m_GoldText = CreateWidget<CText>("GoldText");
	m_GoldText->SetPos(870.f, 670.f);
	m_GoldText->SetSize(100.f, 30);
	m_GoldText->SetFontSize(20.f);
	m_GoldText->SetCollision(false);
	m_GoldText->SetText(std::to_wstring(CPublicData::GetInst()->GetGold()).c_str());
	m_GoldText->SetZOrder(6);
	m_GoldText->SetAlignH(TEXT_ALIGN_H::Right);
	m_GoldText->SetAlignV(TEXT_ALIGN_V::Bottom);

	//크리스탈
	Image = CreateWidget<CImage>("CrystalBG");
	Image->SetPos(1050.f, 670.f);
	Image->SetSize(150.f, 30.f);
	Image->SetCollision(false);
	Image->SetTexture("UI_Btn_Gray", TEXT("UI/Share/UI_Btn_Gray.png"));
	Image->SetZOrder(4);

	Image = CreateWidget<CImage>("Crystal");
	Image->SetPos(1050.f, 670.f);
	Image->SetSize(36.f, 36.f);
	Image->SetCollision(false);
	Image->SetTexture("Crystal", TEXT("UI/MainPage/Crystal.png"));
	Image->SetZOrder(5);

	m_CrystalText = CreateWidget<CText>("CrystalText");
	m_CrystalText->SetPos(1095, 670.f);
	m_CrystalText->SetSize(80.f, 30.f);
	m_CrystalText->SetFontSize(20.f);
	m_CrystalText->SetCollision(false);
	m_CrystalText->SetText(std::to_wstring(CPublicData::GetInst()->GetCrystal()).c_str());
	m_CrystalText->SetZOrder(6);
	m_CrystalText->SetAlignH(TEXT_ALIGN_H::Right);
	m_CrystalText->SetAlignV(TEXT_ALIGN_V::Bottom);

#pragma region BtnBack
	m_BtnBack = CreateWidget<CButton>("BackButton");
	m_BtnBack->SetPos(0.f, 650.f);
	m_BtnBack->SetSize(130.f, 50.f);
	m_BtnBack->SetCollision(true);
	m_BtnBack->SetZOrder(4);
	m_BtnBack->SetStateTexture(Button_State::Normal, "UI_Btn_Yellow", TEXT("UI/Share/UI_Btn_Yellow.png"));
	m_BtnBack->SetStateTexture(Button_State::MouseOn, "UI_Btn_Yellow", TEXT("UI/Share/UI_Btn_Yellow.png"));
	m_BtnBack->SetStateTexture(Button_State::Disabled, "UI_Btn_Yellow", TEXT("UI/Share/UI_Btn_Yellow.png"));
	m_BtnBack->SetStateTexture(Button_State::Click, "UI_Btn_Yellow", TEXT("UI/Share/UI_Btn_Yellow.png"));
	m_BtnBack->SetClickCallback<CLobbySupplyUI>(this, &CLobbySupplyUI::BtnBackCallback);

	CText* Text = CreateWidget<CText>("BackText");
	Text->SetPos(10.f, 660.f);
	Text->SetSize(100.f, 50.f);
	Text->SetFontSize(30.f);
	Text->SetCollision(false);
	Text->SetAlignH(TEXT_ALIGN_H::Left);
	Text->SetAlignV(TEXT_ALIGN_V::Bottom);
	Text->SetZOrder(5);
	Text->SetColor(0.f, 0.f, 0.f);
	Text->SetText(TEXT("< 뒤로"));
#pragma endregion


	m_BtnSupply1 = CreateWidget<CButton>("BtnSupply1");
	m_BtnSupply1->SetPos(757.f, 30.f);
	m_BtnSupply1->SetSize(235.f, 95.f);
	m_BtnSupply1->SetCollision(true);
	m_BtnSupply1->SetZOrder(4);
	m_BtnSupply1->SetStateTexture(Button_State::Normal, "UI_Btn_Yellow", TEXT("UI/Share/UI_Btn_Yellow.png"));
	m_BtnSupply1->SetStateTexture(Button_State::MouseOn, "UI_Btn_Yellow", TEXT("UI/Share/UI_Btn_Yellow.png"));
	m_BtnSupply1->SetStateTexture(Button_State::Disabled, "UI_Btn_Yellow", TEXT("UI/Share/UI_Btn_Yellow.png"));
	m_BtnSupply1->SetStateTexture(Button_State::Click, "UI_Btn_Yellow", TEXT("UI/Share/UI_Btn_Yellow.png"));
	m_BtnSupply1->SetClickCallback<CLobbySupplyUI>(this, &CLobbySupplyUI::BtnSupply1);

	Text = CreateWidget<CText>("Supply1Text");
	Text->SetPos(757.f, 65.f);
	Text->SetSize(240.f, 55.f);
	Text->SetFontSize(25.f);
	Text->SetCollision(false);
	Text->SetAlignH(TEXT_ALIGN_H::Center);
	Text->SetAlignV(TEXT_ALIGN_V::Middle);
	Text->SetZOrder(5);
	Text->SetColor(0.f, 0.f, 0.f);
	Text->SetText(TEXT("보급 1회"));

	Image = CreateWidget<CImage>("Supply1CrystalBG");
	Image->SetPos(780.f, 35.f);
	Image->SetSize(180.f, 30.f);
	Image->SetCollision(false);
	Image->SetTexture("UI_Btn_Gray", TEXT("UI/Share/UI_Btn_Gray.png"));
	Image->SetZOrder(5);

	Image = CreateWidget<CImage>("Supply1Crystal");
	Image->SetPos(780.f, 35.f);
	Image->SetSize(28.f, 28.f);
	Image->SetCollision(false);
	Image->SetTexture("Crystal", TEXT("UI/MainPage/Crystal.png"));
	Image->SetZOrder(6);

	Text = CreateWidget<CText>("Supply1Text");
	Text->SetPos(825.f, 35.f);
	Text->SetSize(110.f, 30.f);
	Text->SetFontSize(20.f);
	Text->SetCollision(false);
	Text->SetText(TEXT("x200"));
	Text->SetZOrder(7);
	Text->SetAlignH(TEXT_ALIGN_H::Right);
	Text->SetAlignV(TEXT_ALIGN_V::Bottom);


	m_BtnSupply10 = CreateWidget<CButton>("BtnSupply10");
	m_BtnSupply10->SetPos(1020.f, 30.f);
	m_BtnSupply10->SetSize(235.f, 95.f);
	m_BtnSupply10->SetCollision(true);
	m_BtnSupply10->SetZOrder(4);
	m_BtnSupply10->SetStateTexture(Button_State::Normal, "UI_Btn_Yellow", TEXT("UI/Share/UI_Btn_Yellow.png"));
	m_BtnSupply10->SetStateTexture(Button_State::MouseOn, "UI_Btn_Yellow", TEXT("UI/Share/UI_Btn_Yellow.png"));
	m_BtnSupply10->SetStateTexture(Button_State::Disabled, "UI_Btn_Yellow", TEXT("UI/Share/UI_Btn_Yellow.png"));
	m_BtnSupply10->SetStateTexture(Button_State::Click, "UI_Btn_Yellow", TEXT("UI/Share/UI_Btn_Yellow.png"));
	m_BtnSupply10->SetClickCallback<CLobbySupplyUI>(this, &CLobbySupplyUI::BtnSupply10);

	Text = CreateWidget<CText>("BtnSupply10");
	Text->SetPos(1020.f, 65.f);
	Text->SetSize(240.f, 55.f);
	Text->SetFontSize(25.f);
	Text->SetCollision(false);
	Text->SetAlignH(TEXT_ALIGN_H::Center);
	Text->SetAlignV(TEXT_ALIGN_V::Middle);
	Text->SetZOrder(5);
	Text->SetColor(0.f, 0.f, 0.f);
	Text->SetText(TEXT("보급 10회"));

	Image = CreateWidget<CImage>("Supply1CrystalBG");
	Image->SetPos(1050.f, 35.f);
	Image->SetSize(172.f, 30.f);
	Image->SetCollision(false);
	Image->SetTexture("UI_Btn_Gray", TEXT("UI/Share/UI_Btn_Gray.png"));
	Image->SetZOrder(5);

	//1220
	Image = CreateWidget<CImage>("Supply1Crystal");
	Image->SetPos(1050.f, 35.f);
	Image->SetSize(28.f, 28.f);
	Image->SetCollision(false);
	Image->SetTexture("Crystal", TEXT("UI/MainPage/Crystal.png"));
	Image->SetZOrder(6);

	Text = CreateWidget<CText>("Supply1Text");
	Text->SetPos(1095.f, 35.f);
	Text->SetSize(102.f, 30.f);
	Text->SetFontSize(20.f);
	Text->SetCollision(false);
	Text->SetText(TEXT("x2000"));
	Text->SetZOrder(7);
	Text->SetAlignH(TEXT_ALIGN_H::Right);
	Text->SetAlignV(TEXT_ALIGN_V::Bottom);

	return true;
}

void CLobbySupplyUI::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
	m_CrystalText->SetText(std::to_wstring(CPublicData::GetInst()->GetCrystal()).c_str());


}

void CLobbySupplyUI::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CLobbySupplyUI::Render()
{
	CWidgetWindow::Render();
}

CLobbySupplyUI* CLobbySupplyUI::Clone()
{
	return new CLobbySupplyUI(*this);
}


void CLobbySupplyUI::BtnBackCallback()
{
	CStageManager::GetInst()->BGMPlay("LobbyBG");
	CSound* Sound = m_Scene->GetResource()->FindSound2D("ButtonClick");
	Sound->Play();
	CUIManager::GetInst()->FindWidgetWindow("LobbyMainUI")->Enable(true);
	Enable(false);
}

void CLobbySupplyUI::BtnSupply1()
{
	CSound* Sound = m_Scene->GetResource()->FindSound2D("ButtonClick");
	Sound->Play();
	CStageManager::GetInst()->BGMStop();
	int Crystal = CPublicData::GetInst()->GetCrystal();
	if (Crystal < 200)
	{
		return;
	}
	CPublicData::GetInst()->SetCrystal(Crystal - 200);
	CLobbySupplyResultUI* LobbySupplyResultUI = (CLobbySupplyResultUI*)CUIManager::GetInst()->FindWidgetWindow("LobbySupplyResultUI");
	
	LobbySupplyResultUI->SetSupply(1);
	Enable(false);
	LobbySupplyResultUI->Enable(true);
}

void CLobbySupplyUI::BtnSupply10()
{
	CSound* Sound = m_Scene->GetResource()->FindSound2D("ButtonClick");
	Sound->Play();
	CStageManager::GetInst()->BGMStop();
	int Crystal = CPublicData::GetInst()->GetCrystal();
	if (Crystal < 2000)
	{
		return;
	}
	CPublicData::GetInst()->SetCrystal(Crystal - 2000);
	CLobbySupplyResultUI* LobbySupplyResultUI = (CLobbySupplyResultUI *)CUIManager::GetInst()->FindWidgetWindow("LobbySupplyResultUI");
	LobbySupplyResultUI->SetSupply(10);
	Enable(false);
	LobbySupplyResultUI->Enable(true);
}
