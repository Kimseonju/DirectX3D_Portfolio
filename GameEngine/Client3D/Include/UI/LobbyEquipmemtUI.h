#pragma once

#include "UI/WidgetWindow.h"
#include "UI/Image.h"
#include "UI/Button.h"
#include "UI/Text.h"
#include "UI/ProgressBar.h"
#include "UI/NumberWidget.h"
#include "../DataTable/ItemDataTable.h"



struct EquipItemInfo
{
	CButton* Button;
	CImage* ItemImage;
	CText* Text;
	ItemData* Status;
	void Enable(bool bEnable)
	{
		Button->Enable(bEnable);
		ItemImage->Enable(bEnable);
		Text->Enable(bEnable);
	}
	void SetCollision(bool bCollision)
	{
		Button->SetCollision(bCollision);
	}
	void Active(bool bActive)
	{
		Button->Active(bActive);
		ItemImage->Active(bActive);
		Text->Active(bActive);
	}
};

class CLobbyEquipmemtUI :
	public CWidgetWindow
{
	friend class CViewport;

protected:
	CLobbyEquipmemtUI();
	CLobbyEquipmemtUI(const CLobbyEquipmemtUI& widget);
	virtual ~CLobbyEquipmemtUI();

private:
	CSharedPtr<CButton>   m_BtnBack;
	CSharedPtr<CButton>   m_BtnWeaponInventory;
	CSharedPtr<CButton>   m_BtnUpgradeItemInventory;
	
	CSharedPtr<CText>   m_GoldText;
	CSharedPtr<CText>   m_CrystalText;


	std::vector<EquipItemInfo> m_vecWeaponItemInfo;
	std::vector<EquipItemInfo> m_vecUpgradeItemInfo;
	
	bool m_UpgradeItem;
	bool m_Weapon;
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CLobbyEquipmemtUI* Clone();

public:
	void BtnBackCallback();
	void BtnWeaponInventoryCallback();
	void BtnUpgradeItemInventoryCallback();

	void BtnWeaponCallback();
	void BtnUpgradeItemCallback();
};

