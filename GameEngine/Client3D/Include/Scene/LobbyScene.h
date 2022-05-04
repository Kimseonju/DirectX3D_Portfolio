#pragma once
#include "StageScene.h"

//���� ���� �� SelectPlayers�� �Է����ִ°� �ʼ�
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
