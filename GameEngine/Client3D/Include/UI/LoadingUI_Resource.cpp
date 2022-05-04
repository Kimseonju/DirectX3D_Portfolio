
#include "LoadingUI_Resource.h"
#include "UIManager.h"
#include "Device.h"
#include "../LobbyManager.h"
#include "../Object/LoadingStartObject.h"
CLoadingUI_Resource::CLoadingUI_Resource():
	m_LoadingEnd(false)
{
}

CLoadingUI_Resource::~CLoadingUI_Resource()
{
}

bool CLoadingUI_Resource::Init()
{
	CWidgetWindow::Init();
	Resolution RS = CDevice::GetInst()->GetResolution();
	m_LoadingProgressBar = CreateWidget<CProgressBar>("LoadingProgressBar");
	m_LoadingProgressBar->SetPos(460.f, 150.f);
	m_LoadingProgressBar->SetSize(320.f, 40.f);
	m_LoadingProgressBar->SetBackTint(255.f / 255.f, 145.f / 255.f, 65.f / 255.f, 1.f);
	m_LoadingProgressBar->SetTexture("UI_HPBar", TEXT("UI/In Game/UI_HPBar.png"));
	m_LoadingProgressBar->SetBackTexture("UI_HPBar", TEXT("UI/In Game/UI_HPBar.png"));
	m_LoadingProgressBar->SetTint(1.f, 0.f, 1.f, 1.f);
	m_LoadingProgressBar->SetBackTint(0.1f, 0.1f, 0.1f, 0.5f);
	m_LoadingProgressBar->SetCollision(false);
	m_LoadingProgressBar->SetZOrder(1);

	m_LoadingEndButton = CreateWidget<CButton>("LoadingEndButton");
	m_LoadingEndButton->SetPos(460.f, 150.f);
	m_LoadingEndButton->SetSize(320.f, 40.f);
	m_LoadingEndButton->SetCollision(true);
	m_LoadingEndButton->SetZOrder(2);
	m_LoadingEndButton->SetStateTexture(Button_State::Normal, "StatButton", TEXT("UI/Loading/StatButton.png"));
	m_LoadingEndButton->SetStateTexture(Button_State::MouseOn, "StatButton", TEXT("UI/Loading/StatButton.png"));
	m_LoadingEndButton->SetStateTexture(Button_State::Disabled, "StatButton", TEXT("UI/Loading/StatButton.png"));
	m_LoadingEndButton->SetStateTexture(Button_State::Click, "StatButton", TEXT("UI/Loading/StatButton.png"));
	m_LoadingEndButton->SetClickCallback<CLoadingUI_Resource>(this, &CLoadingUI_Resource::LoadingEndButtonCallback);
	m_LoadingEndButton->Enable(false);
	return true;
}

void CLoadingUI_Resource::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);

}

void CLoadingUI_Resource::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CLoadingUI_Resource::Render()
{
	CWidgetWindow::Render();
}

CLoadingUI_Resource* CLoadingUI_Resource::Clone()
{
	return new CLoadingUI_Resource(*this);
}

void CLoadingUI_Resource::LoadingEndButtonCallback()
{
	if (!m_LoadingEnd)
		return;
	Enable(false);

	CLobbyManager::GetInst()->GetLoadingStartObject()->GoShipStart();
}

void CLoadingUI_Resource::SetPercent(float Percent)
{
	if (Percent == 1.f)
	{
		m_LoadingEnd = true;
		m_LoadingEndButton->Enable(true);
		m_LoadingProgressBar->Enable(false);
	}
	m_LoadingProgressBar->SetPercent(Percent);
}
