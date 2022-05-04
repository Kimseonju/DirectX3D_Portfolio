#pragma once
#include "IMGUIWidget.h"
class CIMGUISeparator :
	public CIMGUIWidget
{
	friend class CIMGUIWindow;

protected:
	CIMGUISeparator();
	virtual ~CIMGUISeparator();

public:
	virtual bool Init();
	virtual void Render();
};
