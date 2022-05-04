#include "IMGUIText.h"

CIMGUIText::CIMGUIText()	:
	m_Text{},
	m_TextUTF8{},
	m_Align(true),
	m_SizeText(true)
{
	m_ButtonColor.Value.x = 0.f;
	m_ButtonColor.Value.y = 0.f;
	m_ButtonColor.Value.z = 0.f;
	m_ButtonColor.Value.w = 0.f;
}

CIMGUIText::~CIMGUIText()
{
}

bool CIMGUIText::Init()
{
	if (m_Size.x == 100.f && m_Size.y == 100.f)
	{
		m_Size.x = 70.f;
		m_Size.y = 20.f;
	}
	return true;
}

void CIMGUIText::Render()
{
	if (m_Font)
		ImGui::PushFont(m_Font);

	if (m_Align)
		ImGui::AlignTextToFramePadding();

	if (m_SizeText)
	{
		ImVec2 vec = ImVec2(0.f, 0.f);
		ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, vec);
		ImGui::PushStyleColor(ImGuiCol_Text, m_Color.Value);
		ImGui::PushStyleColor(ImGuiCol_Button, m_ButtonColor.Value);
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, m_ButtonColor.Value);
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, m_ButtonColor.Value);
		ImGui::Button(m_TextUTF8, m_Size);
		ImGui::PopStyleColor(4);
		ImGui::PopStyleVar();
	}
	else
		ImGui::TextColored(m_Color, m_TextUTF8);


	if (m_Font)
		ImGui::PopFont();
}


