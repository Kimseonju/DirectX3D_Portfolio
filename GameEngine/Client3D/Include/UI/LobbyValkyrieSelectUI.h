#pragma once

#include "UI/WidgetWindow.h"
#include "UI/Image.h"
#include "UI/Button.h"
#include "UI/Text.h"
#include "UI/ProgressBar.h"
#include "UI/NumberWidget.h"
#include "ValkyrieImageButton.h"

struct ValkyrieInfo
{
	CValkyrieImageButton* ValkyrieButton;
	CImage* Star;
	CImage* ValkyrieImage;
	CText* Level;
	PlayerStatus* Status;
	void Enable(bool bEnable)
	{
		ValkyrieButton->Enable(bEnable);
		Star->Enable(bEnable);
		Level->Enable(bEnable);
		ValkyrieImage->Enable(bEnable);

	}
	void Active(bool bActive)
	{
		ValkyrieButton->Active(bActive);
		Star->Active(bActive);
		Level->Active(bActive);
		ValkyrieImage->Active(bActive);
	}
};

class CLobbyValkyrieSelectUI :
	public CWidgetWindow
{
	friend class CViewport;

protected:
	CLobbyValkyrieSelectUI();
	CLobbyValkyrieSelectUI(const CLobbyValkyrieSelectUI& widget);
	virtual ~CLobbyValkyrieSelectUI();

private:
	CSharedPtr<CButton>   m_BtnBack;
	//가운데에 나타나는 텍스처
	CSharedPtr<CText> m_ValkyrjaNameText;
	CSharedPtr<CButton>   m_BtnValkyrjaLevel;
	CSharedPtr<CText> m_ValkyrjaLevelText;

	CSharedPtr<CImage> m_ImgValkyrjaStar;
	CSharedPtr<CButton>   m_BtnWeapon;
	CSharedPtr<CText>   m_WeaponNameText;

	CSharedPtr<CText>   m_GoldText;
	CSharedPtr<CText>   m_CrystalText;


	//발키리의 모든 정보
	std::vector<ValkyrieInfo> m_vecValkyrieInfo;
	//선택된 발키리
	int m_CurValkyrja;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CLobbyValkyrieSelectUI* Clone();

public:
	void BtnValkyrjaCallback();
	void BtnBackCallback();
	void BtnValkyrjaLevelCallback();
	void BtnWeaponCallback();
public:
	void ValkyrieInfoUpdate();
};

