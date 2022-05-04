#include "pch.h"
#include "BasicMouse.h"
#include <Input.h>
CBasicMouse::CBasicMouse() :
	m_State(Mouse_State::World),
	m_Down(false),
	m_Push(false),
	m_Up(false)
{
}


CBasicMouse::~CBasicMouse()
{
}

bool CBasicMouse::Init()
{
	CMouseWidget::Init();
	return true;
}

void CBasicMouse::Update(float DeltaTime)
{
	CMouseWidget::Update(DeltaTime);
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (!m_Down && !m_Push)
			m_Down = true;

		else if (!m_Push)
		{
			m_Down = false;
			m_Push = true;
		}
	}

	else if (m_Push || m_Down)
	{
		m_Up = true;
		m_Push = false;
		m_Down = false;
	}

	else if (m_Up)
	{
		m_Up = false;

	}

}

void CBasicMouse::PostUpdate(float DeltaTime)
{
	CMouseWidget::PostUpdate(DeltaTime);
}

void CBasicMouse::Render()
{
	CMouseWidget::Render();
	
}

CMouseWidget* CBasicMouse::Clone()
{
	return new CBasicMouse(*this);
}
