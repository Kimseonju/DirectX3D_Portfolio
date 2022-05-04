#pragma once
#include "IMGUIWidget.h"

//팝업란에 실행되어야하는 클래스입니다.
class CIMGUIFileDialogWidget :
	public CIMGUIWidget
{
	friend class CIMGUIWindow;

protected:
	CIMGUIFileDialogWidget();
	virtual ~CIMGUIFileDialogWidget();

protected:
	std::string m_KeyName;
	std::string  m_Title;
	std::string m_vFilter;
	std::string m_vFilePathName;

	std::string m_FilePathName;
	std::string m_FilePath;

	Vector2 m_Size;
	bool m_Click;
	std::function<void(std::string)>	m_ClickCallback;

public:

	const std::string& GetFilePathName()
	{
		return m_FilePathName;
	}
	const std::string& GetFilePath()
	{
		return m_FilePath;
	}

public:
	virtual bool Init();
	void FileDialogSetting(const std::string& KeyName, const std::string& Title, const std::string& vFilter, 
		const std::string& vFilePathName, Vector2 Size= Vector2(300.f,200.f));
	virtual void Render();
public:
	template <typename T>
	void SetClickCallback(T* pObj, void(T::* pFunc)(std::string))
	{
		m_ClickCallback = std::bind(pFunc, pObj, std::placeholders::_1);
	}
};
