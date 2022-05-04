#pragma once
#include "StageScene.h"

//씬을 만든 후 SelectPlayers를 입력해주는게 필수
class CStageScene1 :
	public CStageScene
{
	friend class CScene;

protected:
	CStageScene1();
	virtual ~CStageScene1();


public:
	virtual bool Init();
	virtual void Start();
	virtual void SelectPlayers(const std::string& Name1, const std::string& Name2="", const std::string& Name3 = "");
	virtual void SceneLoad();

private:

	void CreatePlayer(const std::string& Name, int Index);
};
