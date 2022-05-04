#pragma once

#include "GraphicShader.h"

class CTrailShader :
	public CGraphicShader
{
	friend class CShaderManager;

protected:
	CTrailShader();
	virtual ~CTrailShader();

public:
	virtual bool Init();
};

