#include "IMGUICheckBox.h"

CIMGUICheckBox::CIMGUICheckBox() :
	m_Check(false)
{
}

CIMGUICheckBox::~CIMGUICheckBox()
{
}

bool CIMGUICheckBox::Init()
{
	return true;
}

void CIMGUICheckBox::Render()
{
	if (m_Font)
		ImGui::PushFont(m_Font);
	bool Input = false;
	Input= ImGui::Checkbox(m_Name, &m_Check);
	if (Input)
	{
		m_ClickCallback(m_Check);
	}
	if (m_Font)
		ImGui::PopFont();

}
