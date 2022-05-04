#pragma once
#include "IMGUIWidgetComponent.h"



class CIMGUICameraComponent :
	public CIMGUIWidgetComponent
{
public:
	CIMGUICameraComponent();
	virtual ~CIMGUICameraComponent();

private:
	class CIMGUIText* m_CameraType;

	class CCamera* m_Camera;
public:
	void UpdateInfo(CCamera* CCamera);

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

public:
};
