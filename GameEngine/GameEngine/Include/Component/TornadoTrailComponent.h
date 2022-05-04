#pragma once

#include "PrimitiveComponent.h"
#include "../Resource/StaticMesh.h"
#include "../Resource/Animation3D_Tex.h"
#include "../Resource/TrailShader.h"
class CTornadoTrailComponent :
	public CPrimitiveComponent
{
	friend class CGameObject;

protected:
	CTornadoTrailComponent();
	CTornadoTrailComponent(const CTornadoTrailComponent& com);
	virtual ~CTornadoTrailComponent();

protected:
	CSharedPtr<CMesh>     m_pMesh;
	class CShader* m_TrailShader;
	class CTrailCBuffer* m_TrailCBuffer;
	CSharedPtr<CShader>         m_RenderShader;
	class CRenderState* m_State;
	std::deque<Vector3>	m_vecPos;
	std::vector<Vector3>	m_vecRenderPos;
	std::vector<Matrix>	m_vecRenderMat;

	Vector3 m_LocalSwordLow;
	Vector3 m_LocalSwordHigh;
	float			m_Time;
	float			m_Size;
	int			m_VecSize;
	int			m_CallmullCount;
	bool			m_TrailUpdate;

public:
	bool IsTrailUpdate()
	{
		return m_TrailUpdate;
	}
	void SetTrailUpdate(bool Update);
	void SetSize(float Size)
	{
		m_Size = Size;
	}
	float GetSize()
	{
		return m_Size;
	}
	void SetPositionAllList();
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CTornadoTrailComponent* Clone();

};

