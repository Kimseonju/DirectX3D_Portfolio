#include "TargetImageWidget.h"

CTargetImageWidget::CTargetImageWidget():
	m_Angle(0.f)
{
}

CTargetImageWidget::CTargetImageWidget(const CTargetImageWidget& widget) :
	CWidgetWindow(widget)
{
	m_Angle = widget.m_Angle;
}

CTargetImageWidget::~CTargetImageWidget()
{
}


bool CTargetImageWidget::Init()
{
	CWidgetWindow::Init();
	SetCollision(false);
	
	m_TargetImage = CreateWidget<CImage>("TargetImage");
	m_TargetImage->SetPos(0.f, 0.f);
	m_TargetImage->SetSize(128.f, 128.f);
	m_TargetImage->SetCenter();
	m_TargetImage->SetTexture("B2785713", TEXT("UI/Player/B2785713.png"));
	m_TargetImage->SetCollision(false);
	m_TargetImage->SetZOrder(2);

	m_MarkerImage = CreateWidget<CImage>("MarkerImage");
	m_MarkerImage->SetPos(0.f, 0.f);
	m_MarkerImage->SetSize(128.f, 128.f);
	m_MarkerImage->SetCenter();
	m_MarkerImage->SetTexture("CurrentMark", TEXT("UI/Player/CurrentMark.png"));
	m_MarkerImage->SetCollision(false);
	m_MarkerImage->SetZOrder(3);

	return true;
}

void CTargetImageWidget::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
	m_Angle += 90.f * DeltaTime;;
	if (m_Angle >= 360.f)
	{
		m_Angle -= 360.f;
	}
	m_MarkerImage->SetRotation(m_Angle);
}

void CTargetImageWidget::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CTargetImageWidget::Render()
{
	CWidgetWindow::Render();
}

CTargetImageWidget* CTargetImageWidget::Clone()
{
	return new CTargetImageWidget(*this);
}

void CTargetImageWidget::SetSizePercent(float Percent)
{
	float Size = 256.f * Percent;

	m_TargetImage->SetSize(Size, Size);
	m_MarkerImage->SetSize(Size, Size);
}
