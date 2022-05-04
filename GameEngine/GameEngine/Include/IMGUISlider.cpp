#include "IMGUISlider.h"
#include "imgui_internal.h"

CIMGUISlider::CIMGUISlider() :
	m_Align(true),
	m_ValueInt(0),
	m_ValueFloat(0.f),
	m_NumberInt(false),
	m_NumberFloat(false),
	m_ValueIntMin(0),
	m_ValueIntMax(0),
	m_ValueFloatMin(0.f),
	m_ValueFloatMax(0.f)
{
}

CIMGUISlider::~CIMGUISlider()
{
}

bool CIMGUISlider::Init()
{
	return true;
}

void CIMGUISlider::Render()
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
		Input = ImGui::SliderInt(m_Name, &m_ValueInt, m_ValueIntMin, m_ValueIntMax);
	}

	else if (m_NumberFloat)
	{
		Input = ImGui::SliderFloat(m_Name, &m_ValueFloat, m_ValueFloatMin, m_ValueFloatMax, "%.3f");
	}

	if (Input)
	{
		if (m_InputCallback)
			m_InputCallback();
	}
	if (m_Font)
		ImGui::PopFont();
}
