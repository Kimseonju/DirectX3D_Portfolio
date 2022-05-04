#pragma once
#include "IMGUIWidget.h"
class CIMGUIRadioButton :
	public CIMGUIWidget
{
	friend class CIMGUIWindow;

protected:
	CIMGUIRadioButton();
	virtual ~CIMGUIRadioButton();

protected:
	std::vector<std::string>	m_vecItem;
	bool	m_Select;
	int		m_SelectIndex;
	int		m_PageItemCount;
	std::function<void(int, const char*)>	m_SelectCallback;

public:
	const std::string& GetItem(int Index)
	{
		return m_vecItem[Index];
	}

public:
	void AddItem(const char* Item)
	{
		m_vecItem.push_back(Item);
	}

	void SetPageItemCount(int Count)
	{
		m_PageItemCount = Count;
	}

	void DeleteItem(int Index)
	{
		auto	iter = m_vecItem.begin() + Index;

		m_vecItem.erase(iter);
	}

	void Clear()
	{
		m_vecItem.clear();
		m_SelectIndex = -1;
	}

public:
	virtual bool Init();
	virtual void Render();

public:
	template <typename T>
	void SetSelectCallback(T* Obj, void(T::* Func)(int, const char*))
	{
		m_SelectCallback = std::bind(Func, Obj, std::placeholders::_1, std::placeholders::_2);
	}
};
