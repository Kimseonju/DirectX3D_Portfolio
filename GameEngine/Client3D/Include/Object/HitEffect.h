#pragma once
#include "GameObject.h"
#include "ClientObject.h"
#include "Component/BillboardComponent.h"
#include "Resource/Animation3D_Tex.h"
class CHitEffect :
	public CClientObject
{
	friend class CScene;

protected:
	CHitEffect();
	CHitEffect(const CHitEffect& obj);
	virtual ~CHitEffect();

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
	virtual CHitEffect* Clone();
public:
	void AnimationEnd(const std::string& Name);
};