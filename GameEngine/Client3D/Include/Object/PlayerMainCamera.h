#pragma once
#include "Component\Camera.h"
#include "ClientObject.h"
class CPlayerMainCamera :
	public CClientObject
{
public:
	CPlayerMainCamera();
	CPlayerMainCamera(const CPlayerMainCamera& com);
	virtual ~CPlayerMainCamera();

protected:
	CCamera* m_Camera;
	class CPlayer* m_Target;
	CSharedPtr<CClientObject> m_MonsterTarget;
	Vector3 m_PrevTargetPos;
	Vector3 m_Offset;
	float m_Length;


	bool m_Bool;
	bool m_MouseClick;
public:
	CPlayer* GetTarget()	const
	{
		return m_Target;
	}
	CCamera* GetCamera()
	{
		return m_Camera;
	}
	void SetTarget(CPlayer* Target);
	void SetLength(float Length)
	{
		m_Length = Length;
	}

	void SetOffset(float x, float y, float z)
	{
		m_Offset = Vector3(x, y, z);
	}

	void SetOffset(const Vector3& Offset)
	{
		m_Offset = Offset;
	}
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void PrevRender(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CPlayerMainCamera* Clone();

public:
	void CameraWheel(float Time);

	void MouseClick(float Time);
	void MouseRelease(float Time);

private:
	float Lerp(float percent, float max);

	float Lerp(float percent, float min, float max);
};

