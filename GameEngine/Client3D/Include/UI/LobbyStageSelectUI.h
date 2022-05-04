#pragma once

#include "UI/WidgetWindow.h"
#include "UI/Image.h"
#include "UI/Text.h"
#include "UI/Button.h"
class CLobbyStageSelectUI :
	public CWidgetWindow
{
	friend class CViewport;

private:
	CSharedPtr<CButton> m_Stage1Btn;
	CSharedPtr<CButton> m_Stage2Btn;
	CSharedPtr<CText> m_CrystalText;
	CSharedPtr<CText> m_GoldText;
protected:
	CLobbyStageSelectUI();
	virtual ~CLobbyStageSelectUI();
public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CLobbyStageSelectUI* Clone();
public:
	void BtnStage1Callback();
	void BtnStage2Callback();
	void BtnBackCallback();
};

