#pragma once

#include "Thread.h"

class CLoadingThread1 :
	public CThread
{
public:
	CLoadingThread1();
	~CLoadingThread1();

	class CScene* m_pScene;
public:
	virtual void Run();
};

