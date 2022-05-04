
#include "MultiProgressBar.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Resource/ShaderManager.h"
#include "../Resource/Shader.h"
#include "../Input.h"
#include "../Resource/UITransformConstantBuffer.h"
#include "WidgetWindow.h"
#include "../Component/WidgetComponent.h"

CMultiProgressBar::CMultiProgressBar() 
{
}

CMultiProgressBar::CMultiProgressBar(const CMultiProgressBar& widget)
{
}

CMultiProgressBar::~CMultiProgressBar()
{
}

void CMultiProgressBar::SetBarCount(int Count)
{
	size_t Size = m_vecProgressBar.size();
	for (size_t i = 0; i < Size; ++i)
	{
		m_vecProgressBar[i]->Active(false);
	}
	m_vecProgressBar.clear();

	for (int i = 0; i < Count; ++i)
	{
		CProgressBar* Bar = CreateWidget<CProgressBar>("ProgressBar" + std::to_string(i));
		m_vecProgressBar.push_back(Bar);
	}
	

}

void CMultiProgressBar::SetPos(const Vector2& Pos)
{
	if (m_vecProgressBar.empty())
	{
		return;
	}
	Vector2 Size = m_vecProgressBar[0]->GetSize();
	size_t BarCount = m_vecProgressBar.size();
	for (size_t i = 0; i < BarCount; ++i)
	{
		Vector2 BarPos = Pos;
		BarPos.x += Size.x * (float)i;
		m_vecProgressBar[i]->SetPos(BarPos);

	}
	
}

void CMultiProgressBar::SetPos(float x, float y)
{
	SetPos(Vector2(x, y));
}

void CMultiProgressBar::SetSize(float x, float y)
{
	SetSize(Vector2(x, y));
}

void CMultiProgressBar::SetSize(const Vector2& Size)
{
	if (m_vecProgressBar.empty())
	{
		return;
	}
	Vector2 Pos = m_vecProgressBar[0]->GetPos();
	size_t BarCount = m_vecProgressBar.size();
	for (size_t i = 0; i < BarCount; ++i)
	{
		Vector2 BarPos = Pos;
		BarPos.x += Size.x * (float)i;
		m_vecProgressBar[i]->SetPos(BarPos);
		m_vecProgressBar[i]->SetSize(Size);

	}

}



bool CMultiProgressBar::Init()
{
	CWidgetWindow::Init();

	return true;
}

void CMultiProgressBar::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
}

void CMultiProgressBar::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CMultiProgressBar::Render()
{
	CWidgetWindow::Render();
}

CMultiProgressBar* CMultiProgressBar::Clone()
{
	return new CMultiProgressBar(*this);
}

void CMultiProgressBar::SetPercent(float Percent)
{
	if (m_vecProgressBar.empty())
	{
		return;
	}
	size_t BarCount = m_vecProgressBar.size();
	Percent =Percent* BarCount;

	for (size_t i = 0; i < BarCount; ++i)
	{
		float BarPercent = 0.f;
		if (Percent > 1.f)
		{
			Percent -= 1.f;
			BarPercent = 1.f;
		}
		else
		{
			BarPercent = Percent;
			Percent = 0.f;
		}
		m_vecProgressBar[i]->SetPercent(BarPercent);
	}
}

bool CMultiProgressBar::SetTexture(const std::string& Name, const TCHAR* FileName, const std::string& PathName)
{
	size_t BarCount = m_vecProgressBar.size();
	for (size_t i = 0; i < BarCount; ++i)
	{
		m_vecProgressBar[i]->SetTexture(Name, FileName, PathName);
	}

	return true;
}

bool CMultiProgressBar::SetBackTexture(const std::string& Name, const TCHAR* FileName, const std::string& PathName)
{
	size_t BarCount = m_vecProgressBar.size();
	for (size_t i = 0; i < BarCount; ++i)
	{
		m_vecProgressBar[i]->SetBackTexture(Name, FileName, PathName);
	}

	return true;
}

void CMultiProgressBar::SetTint(float r, float g, float b, float a)
{
	size_t BarCount = m_vecProgressBar.size();
	for (size_t i = 0; i < BarCount; ++i)
	{
		m_vecProgressBar[i]->SetTint(r, g, b, a);
		
	}
}

void CMultiProgressBar::SetBackTint(float r, float g, float b, float a)
{
	size_t BarCount = m_vecProgressBar.size();
	for (size_t i = 0; i < BarCount; ++i)
	{
		m_vecProgressBar[i]->SetBackTint(r, g, b, a);
	}
}
