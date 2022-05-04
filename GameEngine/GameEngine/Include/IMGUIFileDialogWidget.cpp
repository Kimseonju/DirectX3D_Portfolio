#include "IMGUIFileDialogWidget.h"
#include "ImGuiFileDialog.h"
CIMGUIFileDialogWidget::CIMGUIFileDialogWidget()
{
}

CIMGUIFileDialogWidget::~CIMGUIFileDialogWidget()
{
	ImGuiFileDialog::Instance()->Close();
}

bool CIMGUIFileDialogWidget::Init()
{
	return true;
}

void CIMGUIFileDialogWidget::FileDialogSetting(const std::string& KeyName, const std::string& Title, 
	const std::string& vFilter, const std::string& vFilePathName, Vector2 Size)
{
	m_KeyName = KeyName;
	m_Title = Title;
	m_vFilter = vFilter;
	m_vFilePathName = vFilePathName;
	m_Size = Size;
	ImGui::SetNextWindowSize(ImVec2(200.f, 100.f));
	ImGuiFileDialog::Instance()->OpenDialog(m_KeyName, m_Title, m_vFilter.c_str(), m_vFilePathName);
}

void CIMGUIFileDialogWidget::Render()
{
	if (m_Font)
		ImGui::PushFont(m_Font);
	if (m_Click || m_KeyName == "" ||
		m_Title == "" || m_vFilter == "" ||
		m_vFilePathName == "")
	{
		return;
	}
		

	if (m_Font)
		ImGui::PopFont();

	if (ImGuiFileDialog::Instance()->Display(m_KeyName, 32, ImVec2(m_Size.x, m_Size.y)))
	{

		if (ImGuiFileDialog::Instance()->IsOk() && m_ClickCallback)
		{
			m_Click = true;
			m_FilePathName = ImGuiFileDialog::Instance()->GetFilePathName();
			m_FilePath = ImGuiFileDialog::Instance()->GetCurrentPath();

			std::string fileName = ImGuiFileDialog::Instance()->GetCurrentFileName();
			auto iter = fileName.end();
			std::string _Filter=ImGuiFileDialog::Instance()->GetCurrentFilter();
			iter -= _Filter.size();
			fileName.erase(iter, fileName.end());
			m_ClickCallback(fileName);
		}
	}
}
