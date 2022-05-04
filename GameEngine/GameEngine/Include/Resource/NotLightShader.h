#pragma once
#include "GraphicShader.h"
class CNotLightShader :
	public CGraphicShader
{
	friend class CShaderManager;

protected:
	CNotLightShader();
	virtual ~CNotLightShader();

public:
	virtual bool Init();
};

