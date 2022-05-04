#pragma once

#include "PrimitiveComponent.h"
#include "../Resource/StaticMesh.h"
#include "../Resource/Animation3D_Tex.h"
#include "../Resource/TrailShader.h"
class CTrailComponent :
	public CPrimitiveComponent
{
	friend class CGameObject;

protected:
	CTrailComponent();
	CTrailComponent(const CTrailComponent& com);
	virtual ~CTrailComponent();

protected:
	CSharedPtr<CMesh>     m_pMesh;
	class CShader* m_TrailShader;
	class CTrailCBuffer* m_TrailCBuffer;
	CSharedPtr<CShader>         m_RenderShader;
	class CRenderState* m_State;
	std::deque<Matrix>	m_vecMatrix;
	Matrix m_Prevmat;

	Vector3 m_LocalSwordLow;
	Vector3 m_LocalSwordHigh;
	VertexUV	m_Info[20];
	float			m_Time;
	float			m_Length;
	float			m_Size;
	int				m_VecSize;
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
	void SetPositionAllList(const Matrix& mat);
	void SetTrailLength(float Length)
	{m_Length = Length;}
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CTrailComponent* Clone();

};

