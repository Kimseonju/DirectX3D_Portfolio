#include "IMGUIRadioButton.h"

CIMGUIRadioButton::CIMGUIRadioButton() :
	m_SelectIndex(0),
	m_Select(false),
	m_PageItemCount(3)
{
}

CIMGUIRadioButton::~CIMGUIRadioButton()
{
}

bool CIMGUIRadioButton::Init()
{
	return true;
}

void CIMGUIRadioButton::Render()
{
	if (m_Font)
		ImGui::PushFont(m_Font);


	int	Size = (int)m_vecItem.size();

	for (int i = 0; i < Size; ++i)
	{
		m_Select = m_SelectIndex == i;
		
		if (ImGui::RadioButton(m_vecItem[i].c_str(), &m_SelectIndex, i))
		{
			if (m_SelectCallback)
				m_SelectCallback((int)i, m_vecItem[i].c_str());

			m_SelectIndex = (int)i;
		}
		if(i!=Size-1)
			ImGui::SameLine();

		if (m_Select)
			ImGui::SetItemDefaultFocus();
	}

	if (m_Font)
		ImGui::PopFont();
}
