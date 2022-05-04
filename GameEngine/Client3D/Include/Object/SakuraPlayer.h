#pragma once
#include "Player.h"
#include "Component/TrailComponent.h"
#include "Component/TornadoTrailComponent.h"
class CSakuraPlayer :
    public CPlayer
{
public:
	CSakuraPlayer();
	CSakuraPlayer(const CSakuraPlayer& obj);
	virtual ~CSakuraPlayer();

private:


	CSharedPtr<CTrailComponent> m_TrailComponent;
	CSharedPtr<CTrailComponent> m_TrailComponentCharge;
	bool m_PoseCopy;
	float m_PoseCopyTimer;
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CSakuraPlayer* Clone();
	
public:
	
	virtual void AnimationNotify(const std::string& Name);

	virtual void EvadeStay();
	virtual void EvadeEnd();
	virtual void UltraSkillAttack();
	virtual void UltraSkillEffect1();
	virtual void UltraSkillEffect2();
	virtual void UltraSkillEffect1End();
	virtual void UltraSkillEffect2End();

	virtual void AttackStart();
	virtual void MoveStart();
	virtual void Hit_LStart();
	virtual void Hit_HStart();
	virtual void CombatStart();
	virtual void UltraSkillStart();
	virtual void EvadeStart();
	virtual void SwitchInStart();
	virtual void SwitchOutStart();
	virtual void VictoryStart();
	virtual void VictoryIdleStart();
public:
};

