#pragma once
#include "IMGUIWidget.h"
class CIMGUITabItem :
	public CIMGUIWidget
{
	friend class CIMGUIWindow;

protected:
	CIMGUITabItem();
	virtual ~CIMGUITabItem();
	std::vector<CIMGUIWidget*> m_vecWidget;
	class CIMGUITabItemEnd* m_BarEnd;
public:
	void WidgetPush(CIMGUIWidget* Widget);
	void WidgetPush(std::vector<CIMGUIWidget*>& Widget);
	void SetTabBarEnd(CIMGUITabItemEnd* BarEnd)
	{
		m_BarEnd = BarEnd;
	}
public:
	virtual bool Init();
	virtual void Render();
};
