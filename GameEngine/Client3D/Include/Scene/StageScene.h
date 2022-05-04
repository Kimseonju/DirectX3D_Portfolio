#pragma once
#include "Scene/SceneMode.h"


//���� ���� �� SelectPlayers�� �Է����ִ°� �ʼ�
class CStageScene :
	public CSceneMode
{
	friend class CScene;

protected:
	CStageScene();
	virtual ~CStageScene();


public:
	virtual bool Init();
	virtual void Start();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void SelectPlayers(const std::string& Name1, const std::string& Name2 = "", const std::string& Name3 = "");
	virtual void SceneLoad();

protected:
	virtual void CreatePlayer(const std::string& Name, int Index);
};
