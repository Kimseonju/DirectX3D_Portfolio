#pragma once
#include "IMGUIWidget.h"
class CIMGUICheckBox :
	public CIMGUIWidget
{
	friend class CIMGUIWindow;

protected:
	CIMGUICheckBox();
	virtual ~CIMGUICheckBox();

protected:
	std::function<void(bool) >	m_ClickCallback;
	bool					m_Check;
	
	wchar_t	m_Text[1024];
	char	m_TextUTF8[1024];
	bool	m_Align;
public:
	void SetText(const char* Text)
	{
		// 변환할 문자열 수를 얻어온다.
		int	Length = MultiByteToWideChar(CP_ACP, 0, Text, -1, 0, 0);
		MultiByteToWideChar(CP_ACP, 0, Text, -1, m_Text, Length);

		// UTF8로 변환한다.
		Length = WideCharToMultiByte(CP_UTF8, 0, m_Text, -1, 0, 0, 0, 0);
		WideCharToMultiByte(CP_UTF8, 0, m_Text, -1, m_TextUTF8, Length, 0, 0);
	}

	void AddText(const char* Text)
	{
		// 변환할 문자열 수를 얻어온다.
		wchar_t	WideText[1024] = {};
		int	Length = MultiByteToWideChar(CP_ACP, 0, Text, -1, 0, 0);
		MultiByteToWideChar(CP_ACP, 0, Text, -1, WideText, Length);
		lstrcat(m_Text, WideText);

		// UTF8로 변환한다.
		Length = WideCharToMultiByte(CP_UTF8, 0, m_Text, -1, 0, 0, 0, 0);
		WideCharToMultiByte(CP_UTF8, 0, m_Text, -1, m_TextUTF8, Length, 0, 0);
	}

	void SetAlign(bool Align)
	{
		m_Align = Align;
	}
	void SetCheck(bool Check)
	{
		m_Check = Check;
	}
	bool GetCheck()
	{
		return m_Check;
	}
public:
	virtual bool Init();
	virtual void Render();


public:
	template <typename T>
	void SetCheckCallback(T* pObj, void(T::* pFunc)(bool))
	{
		m_ClickCallback = std::bind(pFunc, pObj , std::placeholders::_1);
	}
};
