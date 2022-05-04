#pragma once
#include "IMGUIWindow.h"
#include "GameObject.h"

//테스트윈도우입니다.
//이후 IMGUI로 세이브로드로 바꿀예정
class CSaveLoadWindow :
	public CIMGUIWindow
{
public:
	CSaveLoadWindow();
	virtual ~CSaveLoadWindow();

private:

	class CIMGUIButton* m_SaveButton;
	class CIMGUIButton* m_LoadButton;
public:
public:

	virtual bool Init();
	virtual void Update(float DeltaTime);

public:


	void SaveButton();
	void Save(const TCHAR* FullPath);
	void LoadButton();
	void Load(const TCHAR* FullPath);
};
