#pragma once

#include "UI/WidgetWindow.h"
#include "UI/Image.h"
#include "UI/Button.h"
#include "UI/Text.h"
#include "UI/ProgressBar.h"
#include "UI/NumberWidget.h"

class CPlayerHitComboUI :
	public CWidgetWindow
{
	friend class CViewport;

protected:
	CPlayerHitComboUI();
	CPlayerHitComboUI(const CPlayerHitComboUI& widget);
	virtual ~CPlayerHitComboUI();

private:
	CSharedPtr<CImage> m_HitImage;
	CSharedPtr<CText> m_HitText;
public:
	
	virtual void Enable(bool bEnable);

	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CPlayerHitComboUI* Clone();

	void SetCombo(int Combo);
};

