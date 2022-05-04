#pragma once

#include "UI/WidgetWindow.h"
#include "UI/Image.h"
#include "UI/Button.h"
#include "UI/Text.h"
#include "UI/ProgressBar.h"
#include "UI/NumberWidget.h"
#include "../DataTable/ItemDataTable.h"

struct SupplyResultUI
{
	CImage* BG;
	CImage* ItemImage;
	ItemData* Data;

	void Enable(bool Enable)
	{
		BG->Enable(Enable);
		ItemImage->Enable(Enable);
	}
	void Active(bool Active)
	{
		BG->Active(Active);
		ItemImage->Active(Active);
	}
};
class CLobbySupplyResultUI :
	public CWidgetWindow
{
	friend class CViewport;

protected:
	CLobbySupplyResultUI();
	CLobbySupplyResultUI(const CLobbySupplyResultUI& widget);
	virtual ~CLobbySupplyResultUI();

private:
	CSharedPtr<CButton>   m_BtnBack;
	CSharedPtr<CText>   m_GoldText;
	CSharedPtr<CText>   m_CrystalText;

	std::vector<SupplyResultUI> m_SupplyResult;
	int m_SupplyShowCount;
	float m_Timer;
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CLobbySupplyResultUI* Clone();
public:
	void SetSupply(int SupplyCount);

public:
	void BtnBackCallback();

	void LobbySupplyResultUpdate(float DeltaTime);
};

