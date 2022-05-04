#pragma once
#include "StageScene.h"

//씬을 만든 후 SelectPlayers를 입력해주는게 필수
class CLoadingScene :
	public CSceneMode
{
	friend class CScene;

protected:
	CLoadingScene();
	virtual ~CLoadingScene();
	bool m_LoadingEnd;
public:
	virtual bool Init();
	virtual void Start();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);

private:
	class CLoadingThread* m_Thread;
};
