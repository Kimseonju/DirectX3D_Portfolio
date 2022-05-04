#pragma once
#include "IMGUIWidget.h"
class CIMGUITreeNode :
	public CIMGUIWidget
{
	friend class CIMGUIWindow;

protected:
	CIMGUITreeNode();
	virtual ~CIMGUITreeNode();

public:
	virtual bool Init();
	virtual void Render();
};
