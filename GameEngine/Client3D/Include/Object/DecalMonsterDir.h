#pragma once

#include "GameObject.h"
#include "Component/DecalComponent.h"

class CDecalMonsterDir :
	public CGameObject
{
	friend class CScene;

protected:
	CDecalMonsterDir();
	CDecalMonsterDir(const CDecalMonsterDir& obj);
	virtual ~CDecalMonsterDir();

protected:
	CSharedPtr<CDecalComponent> m_Decal;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CDecalMonsterDir* Clone();
};

