#include "IMGUITabBar.h"
#include "IMGUITabBarEnd.h"
CIMGUITabBar::CIMGUITabBar()
{
}

CIMGUITabBar::~CIMGUITabBar()
{
}

void CIMGUITabBar::WidgetPush(CIMGUIWidget* Widget)
{
	m_vecWidget.push_back(Widget);
}

void CIMGUITabBar::WidgetPush(std::vector<CIMGUIWidget*>& Widget)
{
	m_vecWidget = Widget;
}

bool CIMGUITabBar::Init()
{
	return true;
}

void CIMGUITabBar::Render()
{
	if (ImGui::BeginTabBar(m_Name))
	{
		for (size_t i = 0; i < m_vecWidget.size(); i++)
		{
			m_vecWidget[i]->Enable(true);
		}
		m_BarEnd->Enable(true);
	}
	else
	{
		for (size_t i = 0; i < m_vecWidget.size(); i++)
		{
			m_vecWidget[i]->Enable(false);
		}
		m_BarEnd->Enable(false);
	}
}

