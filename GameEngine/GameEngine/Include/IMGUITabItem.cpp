#include "IMGUITabItem.h"
#include "IMGUITabItemEnd.h"
CIMGUITabItem::CIMGUITabItem()
{
}

CIMGUITabItem::~CIMGUITabItem()
{
}

void CIMGUITabItem::WidgetPush(CIMGUIWidget* Widget)
{
	m_vecWidget.push_back(Widget);
}

void CIMGUITabItem::WidgetPush(std::vector<CIMGUIWidget*>& Widget)
{
	m_vecWidget = Widget;
}

bool CIMGUITabItem::Init()
{
	return true;
}

void CIMGUITabItem::Render()
{
	if (ImGui::BeginTabItem(m_Name))
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

