#pragma once
#include "IMGUIWidgetComponent.h"
#include "GameObject.h"
class CIMGUIParticleComponent :
	public CIMGUIWidgetComponent
{
public:
	CIMGUIParticleComponent();
	virtual ~CIMGUIParticleComponent();

private:

public:
	void UpdateInfo(CGameObject* Object);
public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
public:

};
