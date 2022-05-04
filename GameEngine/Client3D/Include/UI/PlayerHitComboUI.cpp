
#include "PlayerHitComboUI.h"
#include "UI/Image.h"
#include "UI/Button.h"
#include <Device.h>
#include "../Object/Player.h"
#include "UIManager.h"
#include "Resource/Animation.h"
#include "../PublicData.h"
CPlayerHitComboUI::CPlayerHitComboUI()
{
}

CPlayerHitComboUI::CPlayerHitComboUI(const CPlayerHitComboUI& widget)
{
}

CPlayerHitComboUI::~CPlayerHitComboUI()
{
}

void CPlayerHitComboUI::Enable(bool bEnable)
{
	CWidgetWindow::Enable(bEnable);
}

bool CPlayerHitComboUI::Init()
{
	CWidgetWindow::Init();
	m_HitImage = CreateWidget<CImage>("HitCount");
	m_HitImage->SetPos(160.f, 530.f);
	m_HitImage->SetSize(75.f, 36.f);
	m_HitImage->SetCollision(false);
	m_HitImage->SetZOrder(3);
	m_HitImage->SetTexture("Hits", TEXT("UI/Icon/Hits.png"));

	m_HitText = CreateWidget<CText>("HitCount");
	m_HitText->SetPos(60.f, 515.f);
	m_HitText->SetSize(100.f, 60.f);
	m_HitText->SetFontSize(50.f);
	m_HitText->SetCollision(false);
	m_HitText->SetText(TEXT("11"));
	m_HitText->SetZOrder(3);
	m_HitText->SetAlignH(TEXT_ALIGN_H::Left);
	m_HitText->SetAlignV(TEXT_ALIGN_V::Bottom);

	return true;
}

void CPlayerHitComboUI::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
}

void CPlayerHitComboUI::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CPlayerHitComboUI::Render()
{
	CWidgetWindow::Render();
}

CPlayerHitComboUI* CPlayerHitComboUI::Clone()
{
	return new CPlayerHitComboUI(*this);
}

void CPlayerHitComboUI::SetCombo(int Combo)
{
	m_HitText->SetText(std::to_wstring(Combo).c_str());
}
