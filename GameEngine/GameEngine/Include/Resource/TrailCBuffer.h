#pragma once
#include "ConstantBufferData.h"
class CTrailCBuffer :
	public CConstantBufferData
{
public:
	CTrailCBuffer();
	CTrailCBuffer(const CTrailCBuffer& buffer);
	virtual ~CTrailCBuffer();

protected:
	TrailCBuffer    m_BufferData;

public:
	virtual bool Init();
	virtual void UpdateCBuffer();
	virtual CTrailCBuffer* Clone();

public:
	void SetPos(float x, float y, float z)
	{
		m_BufferData.TrailCurrentPos = Vector3(x, y, z);
	}

	void SetPos(const Vector3& Pos)
	{
		m_BufferData.TrailCurrentPos = Pos;
	}

	void SetScale(float Scale)
	{
		m_BufferData.TrailScale = Scale;
	}

	void SetVelocity(int Index, const Vector3& Velocity, const Vector3& Velocity2)
	{
		m_BufferData.TrailVelocity[Index] = Vector4(Velocity.x, Velocity.y, Velocity.z,0.f);
		m_BufferData.TrailVelocity2[Index] = Vector4(Velocity2.x, Velocity2.y, Velocity2.z, 0.f);
	}
	Vector3 GetVelocityLow(int Index)
	{
		Vector4 vec = m_BufferData.TrailVelocity[Index];
		return Vector3(vec.x, vec.y, vec.z);
	}

	Vector3 GetVelocityHigh(int Index)
	{
		Vector4 vec = m_BufferData.TrailVelocity2[Index];
		return Vector3(vec.x, vec.y, vec.z);
	}
};

