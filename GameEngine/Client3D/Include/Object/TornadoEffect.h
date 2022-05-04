#pragma once
#include "GameObject.h"
#include "ClientObject.h"
#include "Component/BillboardComponent.h"
#include "Resource/Animation3D_Tex.h"
#include "TornadoTrailObject.h"
#include "TestParticle.h"
class CTornadoEffect : public CClientObject
{
	friend class CScene;

protected:
	CTornadoEffect();
	CTornadoEffect(const CTornadoEffect& obj);
	virtual ~CTornadoEffect();


public:
protected:
	CSharedPtr<CBillboardComponent> m_Bill;
	CSharedPtr<CTestParticle>		m_Dust;
	CSharedPtr<CTornadoTrailObject> m_TornadoTrail;


	CSharedPtr<CBillboardComponent> m_Effect1;
	CSharedPtr<CBillboardComponent> m_Effect2;
	CSharedPtr<CBillboardComponent> m_Effect3;


public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CTornadoEffect* Clone();
};