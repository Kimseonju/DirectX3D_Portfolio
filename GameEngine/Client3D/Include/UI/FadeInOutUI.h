#pragma once

#include "UI/WidgetWindow.h"
#include "UI/Image.h"

class CFadeInOutUI :
    public CWidgetWindow
{
    friend class CViewport;

private:

    CSharedPtr<CImage>    m_FadeImage;
    float m_Alpha;
    bool m_FadeOut;
    bool m_FadeIn;
protected:
    CFadeInOutUI();
    virtual ~CFadeInOutUI();
public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CFadeInOutUI* Clone();
public:
    void SetFadeIn();
	void SetFadeOut();
	bool IsFadeIn()
	{
		return m_FadeIn;
	}
	bool IsFadeOut()
	{
		return m_FadeOut;
	}
};

