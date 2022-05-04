
#include "FadeInOutUI.h"
#include "UIManager.h"
#include "Device.h"
CFadeInOutUI::CFadeInOutUI():
	m_FadeOut(false),
	m_FadeIn(false),
	m_Alpha(0.f)
{
}

CFadeInOutUI::~CFadeInOutUI()
{
}

bool CFadeInOutUI::Init()
{
	CWidgetWindow::Init();
	Resolution RS = CDevice::GetInst()->GetResolution();

	m_FadeImage = CreateWidget<CImage>("FadeImage");
	m_FadeImage->SetSize((float)RS.Width, (float)RS.Height);
	m_FadeImage->SetColorTint(0.f, 0.f, 0.f, 0.f);
	m_FadeImage->SetPos(0.f,0.f);
	m_FadeImage->SetCollision(false);

	return true;
}

void CFadeInOutUI::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
	if (m_FadeOut)
	{
		m_Alpha -= DeltaTime;
		m_FadeImage->SetColorTint(0.f, 0.f, 0.f, m_Alpha);
		if (m_Alpha <= 0.f)
		{
			m_FadeOut = false;
			Enable(false);
		}
	}

	else if (m_FadeIn)
	{
		m_Alpha += DeltaTime;
		m_FadeImage->SetColorTint(0.f, 0.f, 0.f, m_Alpha);
		if (m_Alpha >=1.f)
		{
			m_FadeIn = false;
			
		}
	}
}

void CFadeInOutUI::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CFadeInOutUI::Render()
{
	CWidgetWindow::Render();
}

CFadeInOutUI* CFadeInOutUI::Clone()
{
	return new CFadeInOutUI(*this);
}

void CFadeInOutUI::SetFadeIn()
{
	m_Alpha = 0.f;
	m_FadeIn = true;
	Enable(true);
}

void CFadeInOutUI::SetFadeOut()
{
	m_Alpha = 1.f;
	m_FadeOut = true;
	Enable(true);
}
