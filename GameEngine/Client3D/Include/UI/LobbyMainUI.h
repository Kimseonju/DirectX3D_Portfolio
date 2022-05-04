#pragma once

#include "UI/WidgetWindow.h"
#include "UI/Image.h"
#include "UI/Button.h"
#include "UI/Text.h"
#include "UI/ProgressBar.h"
#include "UI/NumberWidget.h"

class CLobbyMainUI :
	public CWidgetWindow
{
	friend class CViewport;

protected:
	CLobbyMainUI();
	CLobbyMainUI(const CLobbyMainUI& widget);
	virtual ~CLobbyMainUI();

private:
	CSharedPtr<CButton>   m_BtnAttack;
	CSharedPtr<CButton>   m_BtnValkyrja;
	CSharedPtr<CButton>   m_BtnEquip;
	CSharedPtr<CButton>   m_BtnShop;

	CSharedPtr<CText>   m_GoldText;
	CSharedPtr<CText>   m_CrystalText;


public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CLobbyMainUI* Clone();
public:
	void SetGoldText(int Gold);
	void SetCrystalText(int Crystal);
public:
	void BtnAttackCallback();
	void BtnValkyrjaCallback();
	void BtnEquipCallback();
	void BtnShopCallback();
};

