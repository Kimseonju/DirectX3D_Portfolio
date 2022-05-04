#include "IMGUIDrag.h"
#include "imgui_internal.h"

CIMGUIDrag::CIMGUIDrag() :
	m_Align(true),
	m_ValueInt(0),
	m_ValueFloat(0.f),
	m_NumberInt(false),
	m_NumberFloat(false),
	m_Speed(0.05f)
{
}

CIMGUIDrag::~CIMGUIDrag()
{
}

bool CIMGUIDrag::Init()
{
	return true;
}

void CIMGUIDrag::Render()
{
	if (m_Font)
		ImGui::PushFont(m_Font);

	//if (m_Align)
	//	ImGui::AlignTextToFramePadding();

	bool	Input = false;

	ImGui::PushItemWidth(m_Size.x);

	//ImGui::TextColored(m_Color, m_TextUTF8);
	//ImGui::InputText

	if (m_NumberInt)
	{
		Input = ImGui::DragInt(m_Name, &m_ValueInt, m_Speed);
	}

	else if (m_NumberFloat)
	{
		Input = ImGui::DragFloat(m_Name, &m_ValueFloat, m_Speed);
	}

	if (Input)
	{
		if (m_InputCallback)
			m_InputCallback();
	}
	if (m_Font)
		ImGui::PopFont();
}
