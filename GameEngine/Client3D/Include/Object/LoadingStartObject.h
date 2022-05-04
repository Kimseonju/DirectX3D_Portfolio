#pragma once
#include "ClientObject.h"
#include "../Global.h"
#include "Component/AnimationMeshComponent.h"
#include "Component/StaticMeshComponent.h"
#include "Component/LightComponent.h"
#include "Component/SpringArm3D.h"
class CLoadingStartObject :
	public CClientObject
{
	friend class CScene;

protected:
	CLoadingStartObject();
	CLoadingStartObject(const CLoadingStartObject& obj);
	virtual ~CLoadingStartObject();


protected:
	class CSound* m_Sound;
	CSharedPtr<CSceneComponent> m_Root;
	CSharedPtr<CStaticMeshComponent> m_Pillar;
	CSharedPtr<CStaticMeshComponent> m_DoorDownMove;
	CSharedPtr<CStaticMeshComponent> m_DoorUp;
	CSharedPtr<CStaticMeshComponent> m_DoorDown;
	CSharedPtr<CStaticMeshComponent> m_Elevator;
	CSharedPtr<CStaticMeshComponent> m_GroundIn;
	CSharedPtr<CStaticMeshComponent> m_DoorMain;
	CSharedPtr<CStaticMeshComponent> m_LoadingMark;
	CSharedPtr<CLightComponent> m_LightComponent;
	CSharedPtr<CSceneComponent> m_CameraPos;
	LoadingStartObjectState m_State;
	float m_OpenDoorPause;
	bool m_SoundChange;
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void PrevRender(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CLoadingStartObject* Clone();
public:
	void LoadingEndMark();
	void GoShipStart();
public:
	Vector3 GetCameraPos();
	void LoadingStartSound();
	void LobbyStartSound();
};

