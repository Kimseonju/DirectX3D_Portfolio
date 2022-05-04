#pragma once

#include "UI/WidgetWindow.h"
#include "UI/Image.h"
#include "UI/Button.h"
#include "UI/Text.h"
#include "UI/ProgressBar.h"
#include "UI/NumberWidget.h"
#include "ValkyrieImageButton.h"
struct ItemInfo
{
	CButton* Button;
	CImage* ItemImage;
	CText* Text;
	ItemData* Data;
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

class CLobbyLevelUpDialog :
	public CWidgetWindow
{
	friend class CViewport;

protected:
	CLobbyLevelUpDialog();
	CLobbyLevelUpDialog(const CLobbyLevelUpDialog& widget);
	virtual ~CLobbyLevelUpDialog();

private:
	int m_Count;
	int m_MaxCount;
	int m_SelectItem;
	int m_NowLevel;
	int m_NextLevel;
	int m_InputExp;
	int m_MaxExp;
	CSharedPtr<CText> m_ExpText;
	CSharedPtr<CText> m_NowLevelText;
	CSharedPtr<CText> m_NextLevelText;
	CSharedPtr<CText> m_CountText;
	std::vector<ItemInfo> m_vecPlayerUpgradeItemInfo;

	CSharedPtr<CButton>   m_BtnCannel;
	CSharedPtr<CButton>   m_BtnEnter;
	CSharedPtr<CButton> m_BtnBack;
	CSharedPtr<CButton> m_BtnCountAdd;
	CSharedPtr<CButton> m_BtnCountSub;
	CSharedPtr<CProgressBar> m_ProgressBarCount;
	PlayerStatus* m_Status;
public:
	virtual void Enable(bool bEnable);
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CLobbyLevelUpDialog* Clone();
public:
	void SetPlayerData(PlayerStatus* Status)
	{
		m_Status = Status;
	}
	void SetLevelUpDialog();
	int LevelUp(int Exp);
public:
	void BtnEnterCallback();
	void BtnCannelCallback();
	void BtnSelectUpgradeItemCallback();
	void BtnCountAddCallback();
	void BtnCountSubCallback();

public:
	
};

