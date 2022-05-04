#pragma once
#include "UI\WidgetWindow.h"
#include <UI/Text.h>
#include <UI/Image.h>
class CTargetImageWidget :
	public CWidgetWindow
{

public:
	CTargetImageWidget();
	CTargetImageWidget(const CTargetImageWidget& widget);
	~CTargetImageWidget();

private:
	CSharedPtr<CImage> m_TargetImage;
	CSharedPtr<CImage> m_MarkerImage;
	
	float m_Angle;
public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CTargetImageWidget* Clone();

	void SetSizePercent(float Percent);
};

