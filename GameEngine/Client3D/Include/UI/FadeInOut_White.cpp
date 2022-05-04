
#include "FadeInOut_White.h"
#include "UIManager.h"
#include "Device.h"
CFadeInOut_White::CFadeInOut_White() :
	m_FadeOut(false),
	m_FadeIn(false),
	m_Alpha(0.f)
{
}

CFadeInOut_White::~CFadeInOut_White()
{
}

bool CFadeInOut_White::Init()
{
	CWidgetWindow::Init();
	Resolution RS = CDevice::GetInst()->GetResolution();
	
	m_FadeImage = CreateWidget<CImage>("FadeImage2");
	m_FadeImage->SetSize((float)RS.Width, (float)RS.Height);
	m_FadeImage->SetColorTint(1.f, 1.f, 1.f, 0.f);
	m_FadeImage->SetPos(0.f, 0.f);
	m_FadeImage->SetCollision(false);

	return true;
}

void CFadeInOut_White::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
	//m_FadeIn은  서서히 나타나게
	if (m_FadeOut)
	{
		m_Alpha -= DeltaTime;
		m_FadeImage->SetColorTint(1.f, 1.f, 1.f, m_Alpha);
		if (m_Alpha <= 0.f)
		{
			m_FadeOut = false;
			Enable(false);
		}
	}
	else if (m_FadeIn)
	{
		m_Alpha += DeltaTime;
		m_FadeImage->SetColorTint(1.f, 1.f, 1.f, m_Alpha);
		if (m_Alpha >= 1.f)
		{
			m_FadeIn = false;
		}
	}
}

void CFadeInOut_White::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CFadeInOut_White::Render()
{
	CWidgetWindow::Render();
}

CFadeInOut_White* CFadeInOut_White::Clone()
{
	return new CFadeInOut_White(*this);
}


void CFadeInOut_White::SetFadeIn()
{
	m_Alpha = 0.f;
	m_FadeIn = true;
	Enable(true);
}

void CFadeInOut_White::SetFadeOut()
{
	m_Alpha = 1.f;
	m_FadeOut = true;
	Enable(true);
}
