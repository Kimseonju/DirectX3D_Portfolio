#pragma once

#include "Thread.h"

class CLoadingThread :
	public CThread
{
public:
	CLoadingThread();
	~CLoadingThread();

private:
	int m_LoadingCount;
	int m_LoadingMaxCount;
public:
	virtual void Run();
	class CScene* nextScene;
public:

	void SetLoadingMaxCount(int Value) { m_LoadingMaxCount = Value; }
	int GetLoadingMaxCount() const { return m_LoadingMaxCount; }
	void SetLoadingCount(int num);
	int GetLoadingCount() const;

	float GetPersent() const;
	void NextScene();
};

