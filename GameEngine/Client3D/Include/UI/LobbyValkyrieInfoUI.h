#pragma once

#include "UI/WidgetWindow.h"
#include "UI/Image.h"
#include "UI/Button.h"
#include "UI/Text.h"
#include "UI/ProgressBar.h"
#include "UI/NumberWidget.h"
#include "ValkyrieImageButton.h"

class CLobbyValkyrieInfoUI :
	public CWidgetWindow
{
	friend class CViewport;

protected:
	CLobbyValkyrieInfoUI();
	CLobbyValkyrieInfoUI(const CLobbyValkyrieInfoUI& widget);
	virtual ~CLobbyValkyrieInfoUI();

private:
	CSharedPtr<CButton>   m_BtnBack;
	//가운데에 나타나는 텍스처
	CSharedPtr<CText> m_HPText;
	CSharedPtr<CText> m_SPText;
	CSharedPtr<CText> m_DamageText;

	CSharedPtr<CText> m_ExpText;
	CSharedPtr<CProgressBar> m_ExpProgressBar;
	CSharedPtr<CButton>   m_BtnValkyrjaLevelUp;


	CSharedPtr<CImage> m_ImgValkyrjaStar;

	CSharedPtr<CImage> m_ImgValkyrjaParticularType;
	CSharedPtr<CText> m_ValkyrjaNameText;
	CSharedPtr<CText> m_ValkyrjaLevelText;

	CSharedPtr<CButton>   m_BtnLevelUp;
	CSharedPtr<CButton>   m_BtnWeapon;

	CSharedPtr<CText>   m_GoldText;
	CSharedPtr<CText>   m_CrystalText;

	PlayerStatus* m_CurStatus;
public:
	void SetCurStatus(PlayerStatus* Status)
	{
		m_CurStatus = Status;
	}
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CLobbyValkyrieInfoUI* Clone();


public:
	void BtnBackCallback();
	void BtnValkyrjaLevelUpCallback();
	void BtnWeaponCallback();
public:
	void ValkyrieInfoUpdate();
};

