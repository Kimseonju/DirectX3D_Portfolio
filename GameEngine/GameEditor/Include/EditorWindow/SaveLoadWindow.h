#pragma once
#include "IMGUIWindow.h"
#include "GameObject.h"

//�׽�Ʈ�������Դϴ�.
//���� IMGUI�� ���̺�ε�� �ٲܿ���
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
