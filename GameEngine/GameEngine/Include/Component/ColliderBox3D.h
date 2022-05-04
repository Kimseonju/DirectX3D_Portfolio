#pragma once
#include "Collider.h"

// 선분을 이루는 양끝 두 점 
struct LinePoint
{
	Vector3 Point[2];

	// 3차원에서 높이값 제거
	std::vector<Vector2> GetPointVector3ToVector2()
	{
		std::vector<Vector2> result;
		Vector2 pointX = { Point[0].x, Point[0].z };
		Vector2 pointY = { Point[1].x, Point[1].z };

		result.push_back(pointX);
		result.push_back(pointY);

		return result;
	}
};

class CColliderBox3D :
	public CCollider
{
	friend class CGameObject;

protected:
	CColliderBox3D();
	CColliderBox3D(const CColliderBox3D& com);
	virtual ~CColliderBox3D();

protected:
	Box3DInfo	m_Info;
	Vector3 m_BottomPoint[4];

public:
	Box3DInfo GetInfo()	const
	{
		return m_Info;
	}

public:
	void SetExtent(float X, float Y, float Z)
	{
		m_Info.Length[0] = X;
		m_Info.Length[1] = Y;
		m_Info.Length[2] = Z;

		SetWorldScale(m_Info.Length[0] * 2.f, m_Info.Length[1] * 2.f, m_Info.Length[2] * 2.f);
	}

	void GetBottomPoint(std::vector<Vector3>& bottomPoint)
	{
		for (int i = 0; i < 4; ++i)
		{
			bottomPoint.push_back(m_BottomPoint[i]);
		}
	}

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void PrevRender(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CColliderBox3D* Clone();

public:
	virtual bool Collision(CCollider* Dest);
	virtual bool CollisionMouse(const Vector2& MousePos);
	virtual bool CollisionRay(HitResult& _HitResult, const Vector3& Start, const Vector3& Dir, float Length);

public:
	// 선분에 직교하는 두가지 노맓 벡터를 계산
	std::vector<Vector2> GetNormalVectorToLine(const Vector2& pointStart, const Vector2& pointEnd);
	// PostUpdate 연산 함수로 정리
	void CaculateVertexPos();		

public:
	virtual void Save(FILE* pFile);
	virtual void Load(FILE* pFile);
};

