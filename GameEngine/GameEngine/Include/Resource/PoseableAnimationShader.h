#pragma once
#include "GraphicShader.h"
class CPoseableAnimationShader :
	public CGraphicShader
{
	friend class CShaderManager;

protected:
	CPoseableAnimationShader();
	virtual ~CPoseableAnimationShader();

public:
	virtual bool Init();
};

