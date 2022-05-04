#pragma once

#include "UI/WidgetWindow.h"
#include "UI/Image.h"
#include "UI/Button.h"
#include "UI/Text.h"
#include "UI/ProgressBar.h"
#include "UI/NumberWidget.h"
#include "UI/MultiProgressBar.h"

class CPlayerUI :
    public CWidgetWindow
{
    friend class CViewport;

protected:
    CPlayerUI();
    CPlayerUI(const CPlayerUI& widget);
    virtual ~CPlayerUI();

private:
    CSharedPtr<CMultiProgressBar> m_MonsterHP;
    CSharedPtr<CText>   m_MonsterName;

    CSharedPtr<CText> m_Timer;

	CSharedPtr<CImage> m_Stick;
	CSharedPtr<CText>   m_HP;
	//CSharedPtr<CText>   m_HPSlash;
    //CSharedPtr<CText>   m_HPMax;
    CSharedPtr<CMultiProgressBar> m_HPBar;

	CSharedPtr<CText>   m_SP;
	//CSharedPtr<CText>   m_SPMax;
    CSharedPtr<CProgressBar> m_SPBar;

	CSharedPtr<CImage> m_EvadeImage;
	CSharedPtr<CButton> m_EvadeButton;

    CSharedPtr<CImage> m_AttackImage;
	CSharedPtr<CButton> m_AttackButton;


	CSharedPtr<CImage> m_UltraSkillImage;
    CSharedPtr<CButton> m_UltraSkillButton;

	CSharedPtr<CImage>  m_SkillImage;
    CSharedPtr<CButton> m_SkillButton;

	CSharedPtr<CButton> m_BtnChangeValkyrie;
	CSharedPtr<CImage> m_ImgChangeValkyrie;
public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
	virtual CPlayerUI* Clone();
public:
    void SetTimer(int Time);
public:
    void EvadeBtnCallback();
    void AttackBtnCallback();
    void UltraSkillBtnCallback();
    void SkillBtnCallback();

	void BtnChangeValkyrieCallback();
    
};

