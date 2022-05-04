
#include "LobbyStageSelectUI.h"
#include "UIManager.h"
#include "Device.h"
#include "Scene/SceneManager.h"
#include "../Scene/StageScene1.h"
#include "../Scene/StageScene2.h"
#include "../StageManager.h"
CLobbyStageSelectUI::CLobbyStageSelectUI()
{
}

CLobbyStageSelectUI::~CLobbyStageSelectUI()
{
}

bool CLobbyStageSelectUI::Init()
{
	CWidgetWindow::Init();
	Resolution RS = CDevice::GetInst()->GetResolution();
	CImage* Image = CreateWidget<CImage>("BG_2");
	Image->SetSize((float)RS.Width, (float)RS.Height);
	Image->SetPos(0.f, 0.f);
	Image->SetCollision(false);
	Image->SetZOrder(1);
	Image->SetTexture("BG_23", TEXT("UI/Stage_Select/BG_23.png"));
	Image->SetColorTint(1.f, 1.f, 1.f, 1.f);

	for (int y = 0; y < 2; ++y)
	{
		for (int x = 0; x < 6; ++x)
		{
			Image = CreateWidget<CImage>("HexagonalTexture");
			Image->SetSize(492.f, 284.f);
			Image->SetPos(492.f * x, 284.f * y);
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

	m_Stage1Btn = CreateWidget<CButton>("Stage1Btn");
	m_Stage1Btn->SetPos(130.f, 126.f);
	m_Stage1Btn->SetSize(254.f, 398.f);
	m_Stage1Btn->SetCollision(true);
	m_Stage1Btn->SetZOrder(3);
	m_Stage1Btn->SetStateTexture(Button_State::Normal, "BookTimesOut", TEXT("UI/Stage_Select/BookTimesOut.tga"));
	m_Stage1Btn->SetStateTexture(Button_State::MouseOn, "BookTimesOut", TEXT("UI/Stage_Select/Stage1.pngBookTimesOut.tga"));
	m_Stage1Btn->SetStateTexture(Button_State::Disabled, "BookTimesOut", TEXT("UI/Stage_Select/BookTimesOut.tga"));
	m_Stage1Btn->SetStateTexture(Button_State::Click, "BookTimesOut", TEXT("UI/Stage_Select/BookTimesOut.tga"));
	m_Stage1Btn->SetClickCallback<CLobbyStageSelectUI>(this, &CLobbyStageSelectUI::BtnStage1Callback);

	m_Stage2Btn = CreateWidget<CButton>("Stage2Btn");
	m_Stage2Btn->SetPos(420.f, 126.f);
	m_Stage2Btn->SetSize(254.f, 398.f);
	m_Stage2Btn->SetCollision(true);
	m_Stage2Btn->SetZOrder(3);
	m_Stage2Btn->SetStateTexture(Button_State::Normal, "BookEventBoss2", TEXT("UI/Stage_Select/BookEventBoss2.tga"));
	m_Stage2Btn->SetStateTexture(Button_State::MouseOn, "BookEventBoss2", TEXT("UI/Stage_Select/BookEventBoss2.tga"));
	m_Stage2Btn->SetStateTexture(Button_State::Disabled, "BookEventBoss2", TEXT("UI/Stage_Select/BookEventBoss2.tga"));
	m_Stage2Btn->SetStateTexture(Button_State::Click, "BookEventBoss2", TEXT("UI/Stage_Select/BookEventBoss2.tga"));
	m_Stage2Btn->SetClickCallback<CLobbyStageSelectUI>(this, &CLobbyStageSelectUI::BtnStage2Callback);

	CButton* BtnBack = CreateWidget<CButton>("BackButton");
	BtnBack->SetPos(0.f, 650.f);
	BtnBack->SetSize(130.f, 50.f);
	BtnBack->SetCollision(true);
	BtnBack->SetZOrder(3);
	BtnBack->SetStateTexture(Button_State::Normal, "UI_Btn_Yellow", TEXT("UI/Share/UI_Btn_Yellow.png"));
	BtnBack->SetStateTexture(Button_State::MouseOn, "UI_Btn_Yellow", TEXT("UI/Share/UI_Btn_Yellow.png"));
	BtnBack->SetStateTexture(Button_State::Disabled, "UI_Btn_Yellow", TEXT("UI/Share/UI_Btn_Yellow.png"));
	BtnBack->SetStateTexture(Button_State::Click, "UI_Btn_Yellow", TEXT("UI/Share/UI_Btn_Yellow.png"));
	BtnBack->SetClickCallback<CLobbyStageSelectUI>(this, &CLobbyStageSelectUI::BtnBackCallback);

	CText* Text = CreateWidget<CText>("BackText");
	Text->SetPos(10.f, 660.f);
	Text->SetSize(100.f, 50.f);
	Text->SetFontSize(30.f);
	Text->SetCollision(false);
	Text->SetAlignH(TEXT_ALIGN_H::Left);
	Text->SetAlignV(TEXT_ALIGN_V::Bottom);
	Text->SetZOrder(3);
	Text->SetText(TEXT("< 뒤로"));
	Text->SetColor(0.f, 0.f, 0.f);
	return true;
}

void CLobbyStageSelectUI::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
	m_CrystalText->SetText(std::to_wstring(CPublicData::GetInst()->GetCrystal()).c_str());
}

void CLobbyStageSelectUI::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CLobbyStageSelectUI::Render()
{
	CWidgetWindow::Render();
}

CLobbyStageSelectUI* CLobbyStageSelectUI::Clone()
{
	return new CLobbyStageSelectUI(*this);
}

void CLobbyStageSelectUI::BtnStage1Callback()
{
	CSound* Sound = m_Scene->GetResource()->FindSound2D("ButtonClick");
	Sound->Play();
	Enable(false);
	CSceneManager::GetInst()->SetSceneMode<CStageScene1>();
}

void CLobbyStageSelectUI::BtnStage2Callback()
{
	CSound* Sound = m_Scene->GetResource()->FindSound2D("ButtonClick");
	Sound->Play();
	Enable(false);
	CSceneManager::GetInst()->SetSceneMode<CStageScene2>();
}

void CLobbyStageSelectUI::BtnBackCallback()
{
	CSound* Sound = m_Scene->GetResource()->FindSound2D("ButtonClick");
	Sound->Play();
	CUIManager::GetInst()->FindWidgetWindow("LobbyMainUI")->Enable(true);
	CStageManager::GetInst()->BGMPlay("LobbyBG");
	Enable(false);
}
