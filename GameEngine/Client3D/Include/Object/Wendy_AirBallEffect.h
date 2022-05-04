#pragma once
#include "GameObject.h"
#include "ClientObject.h"
#include "Component/BillboardComponent.h"
#include "Resource/Animation3D_Tex.h"
class CWendyAirBallEffect : public CClientObject
{
	friend class CScene;

protected:
	CWendyAirBallEffect();
	CWendyAirBallEffect(const CWendyAirBallEffect& obj);
	virtual ~CWendyAirBallEffect();

	CGameObject*	m_Owner;
	std::vector<CGameObject*> m_Child;
	Vector3			m_OffSet;

public:
	void IsDeath()
	{
		auto iter = m_Child.begin();
		auto iterEnd = m_Child.end();

		for (; iter != iterEnd;)
		{
			(*iter)->Active(false);
		}
		this->Active(false);
	}
	void SetOwner(CGameObject* Obj)
	{m_Owner = Obj;}
	void SetOffSet(Vector3 OffSet)
	{m_OffSet = OffSet;}
	void SetAnimationRate(float Rate)
	{m_Animation->SetSequencePlayRate("Wendy_AirBall",Rate);}
	void AddChild(CWendyAirBallEffect* Child)
	{m_Child.push_back(Child);}
protected:
	CSharedPtr<CBillboardComponent> m_Billboard;
	CAnimation3D_Tex* m_Animation;
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CWendyAirBallEffect* Clone();
};