
#include "TrailCBuffer.h"
#include "ConstantBuffer.h"

CTrailCBuffer::CTrailCBuffer() :
	m_BufferData{}
{
}

CTrailCBuffer::CTrailCBuffer(const CTrailCBuffer& buffer) :
	CConstantBufferData(buffer)
{
	m_BufferData = buffer.m_BufferData;
}

CTrailCBuffer::~CTrailCBuffer()
{
}

bool CTrailCBuffer::Init()
{
	SetConstantBuffer("TrailCBuffer");

	return true;
}

void CTrailCBuffer::UpdateCBuffer()
{
	m_pBuffer->UpdateBuffer(&m_BufferData);
}

CTrailCBuffer* CTrailCBuffer::Clone()
{
	return new CTrailCBuffer(*this);
}
