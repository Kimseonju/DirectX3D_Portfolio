#include "UIDamageText.h"
#include "GameObject.h"
#include "Scene/scene.h"
CUIDamageText::CUIDamageText() :
	m_LifeTime(2.f),
	m_Alpha(1.f),
	m_Update(false)
{
}

CUIDamageText::CUIDamageText(const CUIDamageText& widget) :
	CWidgetWindow(widget)
{
	m_LifeTime= widget.m_LifeTime;
	m_Alpha = widget.m_Alpha;
	m_Update = widget.m_Update;
}

CUIDamageText::~CUIDamageText()
{
}


bool CUIDamageText::Init()
{
	CWidgetWindow::Init();
	m_Image100 = CreateWidget<CImage>("Image100");
	m_Image100->SetPos(-28.f, 0.f);
	m_Image100->SetSize(28.f, 42.f);
	m_Image100->SetCollision(false);
	m_Image100->SetZOrder(1);

	m_Image10 = CreateWidget<CImage>("Image10");
	m_Image10->SetPos(0.f, 0.f);
	m_Image10->SetSize(28.f, 42.f);
	m_Image10->SetCollision(false);
	m_Image10->SetZOrder(1);

	m_Image1 = CreateWidget<CImage>("Image11");
	m_Image1->SetPos(28.f, 0.f);
	m_Image1->SetSize(28.f, 42.f);
	m_Image1->SetCollision(false);
	m_Image1->SetZOrder(1);
	return true;
}

void CUIDamageText::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
	m_LifeTime -= DeltaTime;
	Vector2 Pos= GetPos();
	Pos.y += DeltaTime*40.f;
	SetPos(Pos);

	if (m_LifeTime < 0.f)
	{
		Active(false);
		m_Image100->Active(false);
		m_Image10->Active(false);
		m_Image1->Active(false);
		
		return;
	}
	m_Image100->SetColorTint(1.f, 1.f, 1.f, m_LifeTime);
	m_Image10->SetColorTint(1.f, 1.f, 1.f, m_LifeTime);
	m_Image1->SetColorTint(1.f, 1.f, 1.f, m_LifeTime);
}

void CUIDamageText::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CUIDamageText::Render()
{
	if (!m_Update)
	{
		m_Update = true;
		return;
	}
	CWidgetWindow::Render();
}

CUIDamageText* CUIDamageText::Clone()
{
	return new CUIDamageText(*this);
}


void CUIDamageText::SetDamage(int Damage)
{
	int hundred = Damage / 100;
	Damage = Damage % 100;
	int ten = Damage / 10;
	int num = Damage % 10;
	bool bhundred = false;
	bool bten = false;
	if (hundred != 0)
	{
		SetNumberImage(m_Image100, hundred);
		bhundred = true;
	}
	else
	{
		m_Image100->Enable(false);
	}
	if (bhundred || ten != 0)
	{
		SetNumberImage(m_Image10, ten);
		bten = true;
	}
	else
	{
		m_Image10->Enable(false);
	}
	if (bten || num != 0)
	{
		SetNumberImage(m_Image1, num);
	}
}

void CUIDamageText::SetNumberImage(CImage* Image, int Number)
{
	switch (Number)
	{
	case 0:
		Image->SetTexture("Blue0", TEXT("UI/In Game/Blue0.png"));
		break;
	case 1:
		Image->SetTexture("Blue1", TEXT("UI/In Game/Blue1.png"));
		break;
	case 2:
		Image->SetTexture("Blue2", TEXT("UI/In Game/Blue2.png"));
		break;
	case 3:
		Image->SetTexture("Blue3", TEXT("UI/In Game/Blue3.png"));
		break;
	case 4:
		Image->SetTexture("Blue4", TEXT("UI/In Game/Blue4.png"));
		break;
	case 5:
		Image->SetTexture("Blue5", TEXT("UI/In Game/Blue5.png"));
		break;
	case 6:
		Image->SetTexture("Blue6", TEXT("UI/In Game/Blue6.png"));
		break;
	case 7:
		Image->SetTexture("Blue7", TEXT("UI/In Game/Blue7.png"));
		break;
	case 8:
		Image->SetTexture("Blue8", TEXT("UI/In Game/Blue8.png"));
		break;
	case 9:
		Image->SetTexture("Blue9", TEXT("UI/In Game/Blue9.png"));
		break;
	}
}
