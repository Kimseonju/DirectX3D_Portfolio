#pragma once
#include "IMGUIWidget.h"
class CIMGUITabBarEnd :
	public CIMGUIWidget
{
	friend class CIMGUIWindow;

protected:
	CIMGUITabBarEnd();
	virtual ~CIMGUITabBarEnd();
public:
	virtual bool Init();
	virtual void Render();
};
