#pragma once
#include "ClientObject.h"
#include "Component/TornadoTrailComponent.h"
class CTornadoTrailObject :
	public CClientObject
{
public:
	CTornadoTrailObject();
	CTornadoTrailObject(const CTornadoTrailObject& obj);
	virtual ~CTornadoTrailObject();

private:
	CSharedPtr<CSceneComponent> m_SceneComponent;

	CSharedPtr<CTornadoTrailComponent> m_TornadoTrailComponent;
	CSharedPtr<CTornadoTrailComponent> m_TornadoTrailComponent2;
	CSharedPtr<CTornadoTrailComponent> m_TornadoTrailComponent3;
	CSharedPtr<CTornadoTrailComponent> m_TornadoTrailComponent4;
public:
	CSceneComponent* GetSceneComponent()
	{return m_SceneComponent;}
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CTornadoTrailObject* Clone();

};

