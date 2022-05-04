#pragma once
#include "IMGUIWidget.h"
class CIMGUITabBar :
	public CIMGUIWidget
{
	friend class CIMGUIWindow;

protected:
	CIMGUITabBar();
	virtual ~CIMGUITabBar();
	std::vector<CIMGUIWidget*> m_vecWidget;
	class CIMGUITabBarEnd* m_BarEnd;
public:
	void WidgetPush(CIMGUIWidget* Widget);
	void WidgetPush(std::vector<CIMGUIWidget*>& Widget);
	void SetTabBar(CIMGUITabBarEnd* BarEnd)
	{
		m_BarEnd = BarEnd;
	}
public:
	virtual bool Init();
	virtual void Render();
};
