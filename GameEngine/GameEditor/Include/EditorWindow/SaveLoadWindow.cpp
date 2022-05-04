#include "../pch.h"
#include "SaveLoadWindow.h"
#include "IMGUIButton.h"
#include "IMGUISameLine.h"
#include "ObjectWindow.h"
#include "IMGUIManager.h"


CSaveLoadWindow::CSaveLoadWindow():
	m_SaveButton(nullptr),
	m_LoadButton(nullptr)
{
}

CSaveLoadWindow::~CSaveLoadWindow()
{

}

bool CSaveLoadWindow::Init()
{
	m_SaveButton = AddWidget<CIMGUIButton>("SaveButton");
	m_SaveButton->SetText("Save");
	m_SaveButton->SetClickCallback<CSaveLoadWindow>(this, &CSaveLoadWindow::SaveButton);
	CIMGUISameLine* SameLine = AddWidget<CIMGUISameLine>("SameLine");

	m_LoadButton = AddWidget<CIMGUIButton>("LoadButton");
	m_LoadButton->SetText("Load");
	m_LoadButton->SetClickCallback<CSaveLoadWindow>(this, &CSaveLoadWindow::LoadButton);
	SameLine = AddWidget<CIMGUISameLine>("SameLine");

	return true;
}

void CSaveLoadWindow::Update(float DeltaTime)
{
	CIMGUIWindow::Update(DeltaTime);
}

void CSaveLoadWindow::SaveButton()
{

	static TCHAR Filter[] = TEXT("맵 파일(*.map)|*.map|모든파일(*.*)|*.*||");
	CFileDialog	dlg(FALSE, TEXT("*.map"), TEXT(""), OFN_OVERWRITEPROMPT,
		Filter);

	if (dlg.DoModal() == IDOK)
	{
		CString	Path = dlg.GetPathName();
		Save(Path);
	}
}
void CSaveLoadWindow::Save(const TCHAR* FullPath)
{
	char	FullPathMultibyte[MAX_PATH] = {};
#ifdef UNICODE

	int ConvertLength = WideCharToMultiByte(CP_ACP, 0, FullPath, -1, nullptr, 0, nullptr, nullptr);
	WideCharToMultiByte(CP_ACP, 0, FullPath, -1, FullPathMultibyte, ConvertLength, nullptr, nullptr);

#else

	strcpy_s(FullPathMultibyte, FullPath);

#endif // UNICODE

	FILE* pFile = nullptr;

	fopen_s(&pFile, FullPathMultibyte, "wb");

	if (!pFile)
		return;

	CObjectWindow* objWindow = (CObjectWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectWindow");
	objWindow->SaveAllObject(pFile);

	fclose(pFile);
}

void CSaveLoadWindow::LoadButton()
{
	static TCHAR Filter[] = TEXT("맵 파일(*.map)|*.map|모든파일(*.*)|*.*||");
	CFileDialog	dlg(TRUE, TEXT("*.map"), TEXT(""), OFN_HIDEREADONLY,
		Filter);

	if (dlg.DoModal() == IDOK)
	{
		CString	Path = dlg.GetPathName();
		Load(Path);
	}


}

void CSaveLoadWindow::Load(const TCHAR* FullPath)
{
	char	FullPathMultibyte[MAX_PATH] = {};

#ifdef UNICODE

	int ConvertLength = WideCharToMultiByte(CP_ACP, 0, FullPath, -1, nullptr, 0, nullptr, nullptr);
	WideCharToMultiByte(CP_ACP, 0, FullPath, -1, FullPathMultibyte, ConvertLength, nullptr, nullptr);

#else

	strcpy_s(FullPathMultibyte, FullPath);

#endif // UNICODE

	FILE* pFile = nullptr;

	fopen_s(&pFile, FullPathMultibyte, "rb");

	if (!pFile)
		return;


	CObjectWindow* objWindow = (CObjectWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectWindow");
	objWindow->LoadAllObject(pFile);


	fclose(pFile);
}