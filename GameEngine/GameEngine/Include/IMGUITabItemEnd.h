#pragma once
#include "IMGUIWidget.h"
class CIMGUITabItemEnd :
	public CIMGUIWidget
{
	friend class CIMGUIWindow;

protected:
	CIMGUITabItemEnd();
	virtual ~CIMGUITabItemEnd();
public:
	virtual bool Init();
	virtual void Render();
};
