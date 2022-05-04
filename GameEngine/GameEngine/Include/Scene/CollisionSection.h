#pragma once

#include "../GameEngine.h"

class CCollisionSection
{
	friend class CSceneCollision;

private:
	CCollisionSection();
	~CCollisionSection();

private:
	std::vector<CSharedPtr<class CCollider>>	m_vecCollider;
	std::vector<CSharedPtr<class CGameObject>>	m_vecPrevObject;
	std::vector<CSharedPtr<class CCollider>>	m_vecPrevCollider;
	Vector3			m_SectionSize;
	Vector3			m_SectionTotalSize;
	Vector3			m_Min;
	Vector3			m_Max;
	int				m_IndexX;
	int				m_IndexY;
	int				m_IndexZ;
	int				m_Index;
	static Matrix	m_matView;

public:
	bool Init(int IndexX, int IndexY, int IndexZ, int Index,
		const Vector3& SectionSize, const Vector3& SectionTotalSize);
	void SetSectionMin(const Vector3& Min);
	void SetSectionMax(const Vector3& Max);
	void AddCollider(class CCollider* Collider);
	void Clear();
	void Collision(float DeltaTime);
	class CCollider* CollisionMouse(bool Is2D, float DeltaTime);
public:
	bool RayCheck(HitResult& _HitResult, const Vector3& Start, const Vector3& End, CollisionProfile* Profile);
private:
	static int SortY(const void* Src, const void* Dest);
	static int SortZ(const void* Src, const void* Dest);
};

