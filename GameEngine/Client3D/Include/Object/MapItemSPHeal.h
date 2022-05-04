#pragma once
#include "MapItem.h"
class CMapItemSPHeal :
	public CMapItem
{
	friend class CScene;

protected:
	CMapItemSPHeal();
	CMapItemSPHeal(const CMapItemSPHeal& obj);
	virtual ~CMapItemSPHeal();
private:
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void PrevRender(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CMapItemSPHeal* Clone();

};

