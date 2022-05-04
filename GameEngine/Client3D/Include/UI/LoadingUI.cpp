
#include "LoadingUI.h"
#include "UIManager.h"
#include "Device.h"
CLoadingUI::CLoadingUI():
	m_LoadTimer(0.f)
{
}

CLoadingUI::~CLoadingUI()
{
}

bool CLoadingUI::Init()
{
	CWidgetWindow::Init();
	Resolution RS = CDevice::GetInst()->GetResolution();

	m_LoadingImage = CreateWidget<CImage>("LoadingUIImage");
	m_LoadingImage->SetSize((float)RS.Width, (float)RS.Height);
	m_LoadingImage->SetPos(0.f, 0.f);
	m_LoadingImage->SetCollision(false);
	m_LoadingImage->SetTexture("LoadingUIImage", TEXT("UI/Loading/Loading.png"));
	return true;
}

void CLoadingUI::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
	m_LoadTimer += DeltaTime;

	if (m_LoadTimer > 1.f)
	{
		//이벤트 발생
		m_LoadTimer = 0.f;
		Enable(false);

	}
}

void CLoadingUI::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CLoadingUI::Render()
{
	CWidgetWindow::Render();
}

CLoadingUI* CLoadingUI::Clone()
{
	return new CLoadingUI(*this);
}
