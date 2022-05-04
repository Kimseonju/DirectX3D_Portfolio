#pragma once
#include "StageScene.h"

//씬을 만든 후 SelectPlayers를 입력해주는게 필수
class CLobbyScene :
	public CStageScene
{
	friend class CScene;

protected:
	CLobbyScene();
	virtual ~CLobbyScene();
	CGameObject* m_CameraObject;
public:
	virtual bool Init();
	virtual void Start();
	virtual void Update(float DeltaTime);
	virtual void SceneLoad();

};
