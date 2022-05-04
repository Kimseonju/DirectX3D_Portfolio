#pragma once

#include "UI/WidgetWindow.h"
#include "UI/Image.h"
#include "UI/Text.h"
class CGameClearUI :
	public CWidgetWindow
{
	friend class CViewport;

private:
	CSharedPtr<CText>    m_Combo;
	CSharedPtr<CText>    m_ClearTime;

protected:
	CGameClearUI();
	virtual ~CGameClearUI();
public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CGameClearUI* Clone();

	void SetComboText(int Combo);
	void SetClearTimeText(int Time);
};

