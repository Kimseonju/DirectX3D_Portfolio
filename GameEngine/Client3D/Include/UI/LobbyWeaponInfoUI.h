#pragma once

#include "UI/WidgetWindow.h"
#include "UI/Image.h"
#include "UI/Button.h"
#include "UI/Text.h"
#include "UI/ProgressBar.h"
#include "UI/NumberWidget.h"
#include "ValkyrieImageButton.h"

class CLobbyWeaponInfoUI :
	public CWidgetWindow
{
	friend class CViewport;

protected:
	CLobbyWeaponInfoUI();
	CLobbyWeaponInfoUI(const CLobbyWeaponInfoUI& widget);
	virtual ~CLobbyWeaponInfoUI();

private:
	CSharedPtr<CButton>   m_BtnBack;
	CSharedPtr<CImage>   m_ItemImage;
	//가운데에 나타나는 텍스처

	CSharedPtr<CText> m_ItemNameText;
	CSharedPtr<CText> m_ItemInfoText;
	CSharedPtr<CText> m_ItemLevelText;
	CSharedPtr<CText> m_ItemExp;
	CSharedPtr<CProgressBar> m_ExpProgressBar;
	CSharedPtr<CText> m_DamageText;

	CSharedPtr<CButton> m_BtnUpgrade;


	CSharedPtr<CText>   m_GoldText;
	CSharedPtr<CText>   m_CrystalText;

	ItemData* m_ItemData;

	bool m_BackEquip;
	bool m_BackValkyrieSelect;
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CLobbyWeaponInfoUI* Clone();
public:
	void SetItemData(ItemData* Data)
	{
		m_ItemData = Data;
	}
	void SetEquip()
	{
		m_BackEquip = true;
		m_BackValkyrieSelect = false;
	}
	void SetValkyrieSelect()
	{
		m_BackEquip = false;
		m_BackValkyrieSelect = true;
	}
public:
	void BtnBackCallback();
	void BtnWeaponLevelUpCallback();
public:
	void WeaponInfoUpdate();
};

