#pragma once
#include "ClientObject.h"
#include "../Global.h"
#include "Component/AnimationMeshComponent.h"
#include "Component/StaticMeshComponent.h"
#include "Component/BillboardComponent.h"
#include "Component/LightComponent.h"
class CLobbyValkyrieSelectZone :
	public CClientObject
{
	friend class CScene;

protected:
	CLobbyValkyrieSelectZone();
	CLobbyValkyrieSelectZone(const CLobbyValkyrieSelectZone& obj);
	virtual ~CLobbyValkyrieSelectZone();

protected:

	CSharedPtr<CSceneComponent> m_Root;

	//보여줄것 캐릭터가 늘어날까..
	std::unordered_map<std::string, CSharedPtr<CAnimationMeshComponent>> m_mapSelectMesh;
	CSharedPtr<CAnimationMeshComponent> m_SelectMesh;
	CSharedPtr<CBillboardComponent> m_Background;
	CSharedPtr<CSceneComponent> m_CameraPos;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void PrevRender(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CLobbyValkyrieSelectZone* Clone();
public:
	void ChangeValkrie(const std::string& Name);

	Vector3 GetCameraPos()
	{
		return m_CameraPos->GetWorldPos();
	}
	void Valkyrie_Info();
	void Valkyrie_Zone();
};

