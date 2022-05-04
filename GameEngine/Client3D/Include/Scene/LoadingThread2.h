#pragma once

#include "Thread.h"

class CLoadingThread2 :
	public CThread
{
public:
	CLoadingThread2();
	~CLoadingThread2();

	class CScene* m_pScene;
public:
	virtual void Run();
};

