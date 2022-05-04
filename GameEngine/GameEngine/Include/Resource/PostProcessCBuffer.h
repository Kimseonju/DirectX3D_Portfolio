#pragma once
#include "ConstantBufferData.h"
class CPostProcessCBuffer :
    public CConstantBufferData
{
public:
	CPostProcessCBuffer();
	CPostProcessCBuffer(const CPostProcessCBuffer& buffer);
	virtual ~CPostProcessCBuffer();

protected:
	PostProcessCBuffer    m_BufferData;

public:
	virtual bool Init();
	virtual void UpdateCBuffer();
	virtual CPostProcessCBuffer* Clone();

public:
	void SetBloom(bool Enable)
	{
		m_BufferData.Bloom = Enable ? 1 : 0;
	}

	void SetBlur(bool Enable)
	{
		m_BufferData.Blur = Enable ? 1 : 0;
	}

	void SetDistortion(bool Enable)
	{
		m_BufferData.Distortion = Enable ? 1 : 0;
	}

	void SetOutLine(bool Enable)
	{
		m_BufferData.OutLine = Enable ? 1 : 0;
	}

	void SetCelShader(bool Enable)
	{
		m_BufferData.CelShader = Enable ? 1 : 0;
	}

	void SetToonShader(bool Enable)
	{
		m_BufferData.ToonShader = Enable ? 1 : 0;
	}
	void SetTexSize(const Vector2& Size)
	{
		m_BufferData.TexelSize = Size;
	}
	void SetFXAA(bool Enable)
	{
		m_BufferData.FXAA = Enable ? 1 : 0;
	}
};

