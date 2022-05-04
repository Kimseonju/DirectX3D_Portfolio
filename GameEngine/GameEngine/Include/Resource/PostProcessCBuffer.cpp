
#include "PostProcessCBuffer.h"
#include "ConstantBuffer.h"
#include "../Device.h"
CPostProcessCBuffer::CPostProcessCBuffer() :
    m_BufferData{}
{
}

CPostProcessCBuffer::CPostProcessCBuffer(const CPostProcessCBuffer& buffer) :
    CConstantBufferData(buffer)
{
    m_BufferData = buffer.m_BufferData;
}

CPostProcessCBuffer::~CPostProcessCBuffer()
{
}

bool CPostProcessCBuffer::Init()
{
    SetConstantBuffer("PostProcessCBuffer");
    Resolution RS = CDevice::GetInst()->GetResolution();

    SetTexSize(Vector2(1.f/float(RS.Width), 1.f / float(RS.Height))*0.5f);
    return true;
}

void CPostProcessCBuffer::UpdateCBuffer()
{
    m_pBuffer->UpdateBuffer(&m_BufferData);
}

CPostProcessCBuffer* CPostProcessCBuffer::Clone()
{
    return new CPostProcessCBuffer(*this);
}
