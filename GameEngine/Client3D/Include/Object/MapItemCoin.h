#pragma once
#include "MapItem.h"
class CMapItemCoin :
	public CMapItem
{
	friend class CScene;

protected:
	CMapItemCoin();
	CMapItemCoin(const CMapItemCoin& obj);
	virtual ~CMapItemCoin();
private:
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void PrevRender(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CMapItemCoin* Clone();

};

