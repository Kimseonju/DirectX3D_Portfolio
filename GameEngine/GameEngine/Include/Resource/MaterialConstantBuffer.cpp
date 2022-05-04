
#include "MaterialConstantBuffer.h"
#include "ConstantBuffer.h"

CMaterialConstantBuffer::CMaterialConstantBuffer()  :
    m_BufferData{}
{
    m_BufferData.ReceiveDecal = 1;
    m_BufferData.bFlow = false;
    m_BufferData.FlowDirection = false;     // Set X
    m_BufferData.FlowSpeedX = 0.2f;
    m_BufferData.FlowSpeedY = 0.2f;
    m_BufferData.ShadowEnable = 1;
}

CMaterialConstantBuffer::CMaterialConstantBuffer(const CMaterialConstantBuffer& buffer) :
    CConstantBufferData(buffer)
{
    m_BufferData = buffer.m_BufferData;
}

CMaterialConstantBuffer::~CMaterialConstantBuffer()
{
}

bool CMaterialConstantBuffer::Init()
{
    SetConstantBuffer("MaterialCBuffer");

    return true;
}

void CMaterialConstantBuffer::UpdateCBuffer()
{
    m_pBuffer->UpdateBuffer(&m_BufferData);
}

CMaterialConstantBuffer* CMaterialConstantBuffer::Clone()
{
    return new CMaterialConstantBuffer(*this);
}
