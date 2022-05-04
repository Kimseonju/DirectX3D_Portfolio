#pragma once
#include "GameObject.h"
#include "../Global.h"
class CClientObject :
    public CGameObject
{
	friend class CScene;

protected:
	CClientObject();
	CClientObject(const CClientObject& obj);
	virtual ~CClientObject();

protected:
	ClientClassType m_ClientClassType;
public:

	ClientClassType GetClientClassType()
	{
		return m_ClientClassType;
	}

	void SetClientClassType(ClientClassType _Type)
	{
		m_ClientClassType = _Type;
	}
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void PrevRender(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CClientObject* Clone();
	virtual void CameraAction();
public:
	virtual void Save(FILE* pFile);
	virtual void Load(FILE* pFile);
};

