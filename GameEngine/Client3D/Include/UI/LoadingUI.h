#pragma once

#include "UI/WidgetWindow.h"
#include "UI/Image.h"
#include "UI/Text.h"
class CLoadingUI :
	public CWidgetWindow
{
	friend class CViewport;

private:

	CSharedPtr<CImage>    m_LoadingImage;
	float m_LoadTimer;
protected:
	CLoadingUI();
	virtual ~CLoadingUI();
public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CLoadingUI* Clone();
};

