#pragma once

#include "UI/WidgetWindow.h"
#include "UI/Image.h"
#include "UI/Button.h"
#include "UI/Text.h"
#include "UI/ProgressBar.h"
#include "UI/NumberWidget.h"
#include "../DataTable/ItemDataTable.h"


class CLobbySupplyUI :
	public CWidgetWindow
{
	friend class CViewport;

protected:
	CLobbySupplyUI();
	CLobbySupplyUI(const CLobbySupplyUI& widget);
	virtual ~CLobbySupplyUI();

private:
	CSharedPtr<CButton>   m_BtnBack;
	CSharedPtr<CText>   m_GoldText;
	CSharedPtr<CText>   m_CrystalText;

	CSharedPtr<CButton>   m_BtnSupply1;
	CSharedPtr<CButton>   m_BtnSupply10;
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CLobbySupplyUI* Clone();

public:
	void BtnBackCallback();
	void BtnSupply1();
	void BtnSupply10();
};

