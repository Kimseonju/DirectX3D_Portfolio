#pragma once
#include "IMGUIWidget.h"
class CIMGUITreePopNode :
	public CIMGUIWidget
{
	friend class CIMGUIWindow;

protected:
	CIMGUITreePopNode();
	virtual ~CIMGUITreePopNode();

public:
	virtual bool Init();
	virtual void Render();
};
