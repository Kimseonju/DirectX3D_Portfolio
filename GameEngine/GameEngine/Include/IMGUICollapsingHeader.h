#pragma once
#include "IMGUIWidget.h"
class CIMGUICollapsingHeader :
	public CIMGUIWidget
{
	friend class CIMGUIWindow;

protected:
	CIMGUICollapsingHeader();
	virtual ~CIMGUICollapsingHeader();
	std::vector<CIMGUIWidget*> m_vecWidget;
public:
	void WidgetPush(CIMGUIWidget* Widget);
	void WidgetPush(std::vector<CIMGUIWidget*>& Widget);
public:
	virtual bool Init();
	virtual void Render();
};
