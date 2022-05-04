#pragma once
#include "MapItem.h"
class CMapItemHeal :
	public CMapItem
{
	friend class CScene;

protected:
	CMapItemHeal();
	CMapItemHeal(const CMapItemHeal& obj);
	virtual ~CMapItemHeal();
private:
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void PrevRender(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CMapItemHeal* Clone();

};

