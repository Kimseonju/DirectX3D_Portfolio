#pragma once

#include "UI/WidgetWindow.h"
#include "UI/Image.h"
#include "UI/Button.h"
#include "UI/Text.h"
#include "UI/ProgressBar.h"
#include "UI/NumberWidget.h"
#include "ValkyrieImageButton.h"

class CLobbyItemInfoDialog :
	public CWidgetWindow
{
	friend class CViewport;

protected:
	CLobbyItemInfoDialog();
	CLobbyItemInfoDialog(const CLobbyItemInfoDialog& widget);
	virtual ~CLobbyItemInfoDialog();

private:
	CSharedPtr<CText> m_ItemText;
	CSharedPtr<CImage> m_ItemImage;
	CSharedPtr<CText> m_ItemInfo;
	CSharedPtr<CText> m_ItemCount;
	CSharedPtr<CButton> m_BtnBack;
public:
	virtual void Enable(bool bEnable);
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CLobbyItemInfoDialog* Clone();
public:
	void SetItemInfoDialog(const TCHAR* ItemText, CTexture* ItemImage, const TCHAR* ItemInfo,int ItemCount);
public:
	void BtnBackCallback();
	void BtnEnterCallback();
	void BtnCannelCallback();

	
};

