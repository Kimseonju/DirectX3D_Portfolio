#include "IMGUICollapsingHeader.h"

CIMGUICollapsingHeader::CIMGUICollapsingHeader()
{
}

CIMGUICollapsingHeader::~CIMGUICollapsingHeader()
{
}

void CIMGUICollapsingHeader::WidgetPush(CIMGUIWidget* Widget)
{
	m_vecWidget.push_back(Widget);
}

void CIMGUICollapsingHeader::WidgetPush(std::vector<CIMGUIWidget*>& Widget)
{
	m_vecWidget = Widget;
}

bool CIMGUICollapsingHeader::Init()
{
	return true;
}

void CIMGUICollapsingHeader::Render()
{
	if (ImGui::CollapsingHeader(m_Name))
	{
		for (size_t i = 0; i < m_vecWidget.size(); i++)
		{
			m_vecWidget[i]->Enable(true);
		}
	}
	else
	{
		for (size_t i = 0; i < m_vecWidget.size(); i++)
		{
			m_vecWidget[i]->Enable(false);
		}
	}
}

