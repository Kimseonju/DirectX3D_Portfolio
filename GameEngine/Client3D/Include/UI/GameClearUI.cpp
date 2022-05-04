
#include "GameClearUI.h"
#include "UIManager.h"
#include "Device.h"
CGameClearUI::CGameClearUI()
{
}

CGameClearUI::~CGameClearUI()
{
}

bool CGameClearUI::Init()
{
	CWidgetWindow::Init();
	Resolution RS = CDevice::GetInst()->GetResolution();

	CText* Text = CreateWidget<CText>("ComboText");
	Text->SetPos(794.f, 515.f);
	Text->SetSize(200.f, 50.f);
	Text->SetFontSize(30.f);
	Text->SetCollision(false);
	Text->SetAlignH(TEXT_ALIGN_H::Left);
	Text->SetAlignV(TEXT_ALIGN_V::Bottom);
	Text->SetZOrder(3);
	Text->SetText(TEXT("최대 콤보 수"));
	CImage* Image = CreateWidget<CImage>("ComboTextBackGround");
	Image->SetPos(765.f, 490.f);
	Image->SetSize(340.f, 75.f);
	Image->SetCollision(false);
	Image->SetZOrder(2);
	Image->SetTexture("Energy_debris", TEXT("UI/Share/Energy_debris.png"));



	m_Combo = CreateWidget <CText>("Combo");
	m_Combo->SetPos(1140.f, 495.f);
	m_Combo->SetSize(120.f, 75.f);
	m_Combo->SetFontSize(30.f);
	m_Combo->SetCollision(false);
	m_Combo->SetAlignH(TEXT_ALIGN_H::Center);
	m_Combo->SetAlignV(TEXT_ALIGN_V::Middle);
	m_Combo->SetZOrder(3);
	m_Combo->SetText(TEXT("콤보"));

	Image = CreateWidget<CImage>("ComboBackGround");
	Image->SetPos(1130.f, 490.f);
	Image->SetSize(120.f, 75.f);
	Image->SetCollision(false);
	Image->SetZOrder(2);
	Image->SetTexture("Energy_debris", TEXT("UI/Share/Energy_debris.png"));


	Text = CreateWidget<CText>("TimeText");
	Text->SetPos(795.f, 430.f);
	Text->SetSize(200.f, 50.f);
	Text->SetFontSize(30.f);
	Text->SetCollision(false);
	Text->SetAlignH(TEXT_ALIGN_H::Left);
	Text->SetAlignV(TEXT_ALIGN_V::Bottom);
	Text->SetZOrder(3);
	Text->SetText(TEXT("전투 시간"));

	Image = CreateWidget<CImage>("TimeTextBackGround");
	Image->SetPos(765.f, 410.f);
	Image->SetSize(340.f, 75.f);
	Image->SetCollision(false);
	Image->SetZOrder(2);
	Image->SetTexture("Energy_debris", TEXT("UI/Share/Energy_debris.png"));


	m_ClearTime = CreateWidget <CText>("ClearTime");
	m_ClearTime->SetPos(1140.f, 410.f);
	m_ClearTime->SetSize(120.f, 75.f);
	m_ClearTime->SetFontSize(30.f);
	m_ClearTime->SetCollision(false);
	m_ClearTime->SetAlignH(TEXT_ALIGN_H::Center);
	m_ClearTime->SetAlignV(TEXT_ALIGN_V::Middle);
	m_ClearTime->SetZOrder(3);
	m_ClearTime->SetText(TEXT("55:55"));

	Image = CreateWidget<CImage>("TimeTextBackGround");
	Image->SetPos(1130.f, 410.f);
	Image->SetSize(120.f, 75.f);
	Image->SetCollision(false);
	Image->SetZOrder(2);
	Image->SetTexture("Energy_debris", TEXT("UI/Share/Energy_debris.png"));
	return true;
}

void CGameClearUI::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
}

void CGameClearUI::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CGameClearUI::Render()
{
	CWidgetWindow::Render();
}

CGameClearUI* CGameClearUI::Clone()
{
	return new CGameClearUI(*this);
}

void CGameClearUI::SetComboText(int Combo)
{

	std::wstring str;
	str = std::to_wstring(Combo);
	m_Combo->SetText(str.c_str());
}

void CGameClearUI::SetClearTimeText(int Time)
{
	Time++;
	int Minute = Time / 60;
	std::wstring str;
	if (Minute < 10)
	{
		str=TEXT("0");
	}
	str += std::to_wstring(Minute)+TEXT(":");

	int Second = Time % 60;
	if (Second < 10)
	{
		str += TEXT("0");
	}
	str += std::to_wstring(Second);

	m_ClearTime->SetText(str.c_str());
}
