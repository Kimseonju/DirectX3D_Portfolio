
#include "LobbyItemInfoDialog.h"
#include "Device.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
CLobbyItemInfoDialog::CLobbyItemInfoDialog()
{
}

CLobbyItemInfoDialog::CLobbyItemInfoDialog(const CLobbyItemInfoDialog& widget)
{
}

CLobbyItemInfoDialog::~CLobbyItemInfoDialog()
{
}

void CLobbyItemInfoDialog::Enable(bool bEnable)
{
	CWidgetWindow::Enable(bEnable);
	if (bEnable)
	{
		CSound* Sound = m_Scene->GetResource()->FindSound2D("PopUpIn");
		Sound->Play();
	}
}

void CLobbyItemInfoDialog::Start()
{
	CWidgetWindow::Start();
}

bool CLobbyItemInfoDialog::Init()
{
	CWidgetWindow::Init();
	SetZOrder(Widget_ZOrder_Dialog);
	Resolution RS = CDevice::GetInst()->GetResolution();

	CImage* Image;
	Image = CreateWidget<CImage>("BG_2");
	Image->SetSize((float)RS.Width, (float)RS.Height);
	Image->SetPos(0.f, 0.f);
	Image->SetCollision(false);
	Image->SetZOrder(0);
	Image->SetColorTint(0.f, 0.f, 0.f, 0.5f);

	Image = CreateWidget<CImage>("BG_");
	Image->SetPos(200.f, 100.f);
	Image->SetSize(920.f, 480.f);
	Image->SetCollision(false);
	Image->SetZOrder(1);
	Image->SetTexture("UI_Btn_Blue", TEXT("UI/Share/UI_Btn_Blue.png"));

	CText* Text = CreateWidget<CText>("Text");
	Text->SetPos(200.f, 500.f);
	Text->SetSize(920.f, 70.f);
	Text->SetFontSize(30.f);
	Text->SetCollision(false);
	Text->SetAlignH(TEXT_ALIGN_H::Center);
	Text->SetAlignV(TEXT_ALIGN_V::Middle);
	Text->SetZOrder(3);
	Text->SetText(TEXT("아이템 설명"));

	m_BtnBack = CreateWidget<CButton>("BtnBack");
	m_BtnBack->SetPos(1030.f, 530.f);
	m_BtnBack->SetSize(80.f, 50.f);
	m_BtnBack->SetCollision(true);
	m_BtnBack->SetZOrder(2);
	m_BtnBack->SetColorTint(0.f, 0.f, 0.f, 0.f);
	m_BtnBack->SetStateTexture(Button_State::Normal, "UI_Opacity0", TEXT("UI/Share/UI_Opacity0.png"));
	m_BtnBack->SetStateTexture(Button_State::MouseOn, "UI_Opacity0", TEXT("UI/Share/UI_Opacity0.png"));
	m_BtnBack->SetStateTexture(Button_State::Disabled, "UI_Opacity0", TEXT("UI/Share/UI_Opacity0.png"));
	m_BtnBack->SetStateTexture(Button_State::Click, "UI_Opacity0", TEXT("UI/Share/UI_Opacity0.png"));
	m_BtnBack->SetClickCallback<CLobbyItemInfoDialog>(this, &CLobbyItemInfoDialog::BtnBackCallback);
	
	Text = CreateWidget<CText>("XX");
	Text->SetPos(1030.f, 530.f);
	Text->SetSize(80.f, 50.f);
	Text->SetFontSize(30.f);
	Text->SetCollision(false);
	Text->SetAlignH(TEXT_ALIGN_H::Center);
	Text->SetAlignV(TEXT_ALIGN_V::Middle);
	Text->SetZOrder(3);
	Text->SetText(TEXT("X"));


	m_ItemImage = CreateWidget<CImage>("ItemImage");
	m_ItemImage->SetPos(260.f, 240.f);
	m_ItemImage->SetSize(248.f, 248.f);
	m_ItemImage->SetCollision(false);
	m_ItemImage->SetZOrder(1);
	m_ItemImage->SetColorTint(1.f, 1.f, 1.f, 1.f);

	m_ItemText = CreateWidget<CText>("ItemText");
	m_ItemText->SetPos(580.f, 450.f);
	m_ItemText->SetSize(370.f, 50.f);
	m_ItemText->SetFontSize(30.f);
	m_ItemText->SetCollision(false);
	m_ItemText->SetAlignH(TEXT_ALIGN_H::Left);
	m_ItemText->SetAlignV(TEXT_ALIGN_V::Bottom);
	m_ItemText->SetZOrder(3);
	m_ItemText->SetText(TEXT("아이템이름"));

	m_ItemInfo = CreateWidget<CText>("ItemInfo");
	m_ItemInfo->SetPos(580.f, 400.f);
	m_ItemInfo->SetSize(270.f, 30.f);
	m_ItemInfo->SetFontSize(25.f);
	m_ItemInfo->SetCollision(false);
	m_ItemInfo->SetAlignH(TEXT_ALIGN_H::Left);
	m_ItemInfo->SetAlignV(TEXT_ALIGN_V::Bottom);
	m_ItemInfo->SetZOrder(3);
	m_ItemInfo->SetText(TEXT("아이템 기능"));

	Text = CreateWidget<CText>("Text");
	Text->SetPos(900.f, 140.f);
	Text->SetSize(130.f, 35.f);
	Text->SetFontSize(25.f);
	Text->SetCollision(false);
	Text->SetAlignH(TEXT_ALIGN_H::Left);
	Text->SetAlignV(TEXT_ALIGN_V::Bottom);
	Text->SetZOrder(3);
	Text->SetText(TEXT("보유 수량"));

	m_ItemCount = CreateWidget<CText>("ItemCount");
	m_ItemCount->SetPos(1050.f, 140.f);
	m_ItemCount->SetSize(80.f, 50.f);
	m_ItemCount->SetFontSize(30.f);
	m_ItemCount->SetCollision(false);
	m_ItemCount->SetAlignH(TEXT_ALIGN_H::Left);
	m_ItemCount->SetAlignV(TEXT_ALIGN_V::Bottom);
	m_ItemCount->SetZOrder(3);
	m_ItemCount->SetText(TEXT("갯수"));

	return true;
}

void CLobbyItemInfoDialog::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
}

void CLobbyItemInfoDialog::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CLobbyItemInfoDialog::Render()
{
	CWidgetWindow::Render();
}

CLobbyItemInfoDialog* CLobbyItemInfoDialog::Clone()
{
	return new CLobbyItemInfoDialog(*this);
}

void CLobbyItemInfoDialog::SetItemInfoDialog(const TCHAR* ItemText, CTexture* ItemImage, const TCHAR* ItemInfo, int ItemCount)
{
	m_ItemText->SetText(ItemText);
	m_ItemImage->SetTexture(ItemImage);
	m_ItemInfo->SetText(ItemInfo);
	m_ItemCount->SetText(std::to_wstring(ItemCount).c_str());
}

void CLobbyItemInfoDialog::BtnBackCallback()
{
	Enable(false);

	CSound* Sound = m_Scene->GetResource()->FindSound2D("PopUpOut");
	Sound->Play();
}

void CLobbyItemInfoDialog::BtnEnterCallback()
{

}

void CLobbyItemInfoDialog::BtnCannelCallback()
{

}
