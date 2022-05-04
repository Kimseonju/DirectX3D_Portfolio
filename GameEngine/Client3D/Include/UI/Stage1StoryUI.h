#pragma once

#include "UI/WidgetWindow.h"
#include "UI/Image.h"
#include "UI/Text.h"
class CStage1StoryUI :
	public CWidgetWindow
{
	friend class CViewport;

private:

protected:
	CStage1StoryUI();
	virtual ~CStage1StoryUI();
public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CStage1StoryUI* Clone();
};

