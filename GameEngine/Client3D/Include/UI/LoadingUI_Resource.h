#pragma once

#include "UI/WidgetWindow.h"
#include "UI/ProgressBar.h"
#include "UI/Button.h"
class CLoadingUI_Resource :
	public CWidgetWindow
{
	friend class CViewport;

private:

	CSharedPtr<CProgressBar>    m_LoadingProgressBar;
	CSharedPtr<CButton>    m_LoadingEndButton;
	bool m_LoadingEnd;
protected:
	CLoadingUI_Resource();
	virtual ~CLoadingUI_Resource();
public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CLoadingUI_Resource* Clone();

public:
	void LoadingEndButtonCallback();
	void SetPercent(float Percent);
};

