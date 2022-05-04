#pragma once
#include "StageScene.h"

//���� ���� �� SelectPlayers�� �Է����ִ°� �ʼ�
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
