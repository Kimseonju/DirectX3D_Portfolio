#pragma once
#include "GameObject.h"
#include "ClientObject.h"
#include "Component/BillboardComponent.h"
#include "Resource/Animation3D_Tex.h"
class CWendyAirHitEffect : public CClientObject
{
	friend class CScene;

protected:
	CWendyAirHitEffect();
	CWendyAirHitEffect(const CWendyAirHitEffect& obj);
	virtual ~CWendyAirHitEffect();

protected:
	CSharedPtr<CBillboardComponent> m_Billboard;
	CAnimation3D_Tex* m_Animation;

	CSharedPtr<CBillboardComponent> m_Billboard2;
	CAnimation3D_Tex* m_Animation2;

	bool m_HitAniOn;
	CSharedPtr<CBillboardComponent> m_Billboard3;
	CAnimation3D_Tex* m_Animation3;


	CMaterial* m_Mtrl;
	float m_Timer;
	float m_Scale;
	bool m_PowerX2;
public:
	void HitOn()
	{m_HitAniOn = true;}
	void Power2()
	{m_PowerX2 = true;}
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CWendyAirHitEffect* Clone();
};