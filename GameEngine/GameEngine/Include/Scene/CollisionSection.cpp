
#include "CollisionSection.h"
#include "../Component/Collider.h"
#include "../Input.h"
#include "../Component/Camera.h"
#include "CameraManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "../Collision.h"

Matrix CCollisionSection::m_matView;

CCollisionSection::CCollisionSection()
{
	m_vecCollider.reserve(300);
}

CCollisionSection::~CCollisionSection()
{
}

bool CCollisionSection::Init(int IndexX, int IndexY, int IndexZ, int Index, 
	const Vector3& SectionSize, const Vector3& SectionTotalSize)
{
	m_IndexX = IndexX;
	m_IndexY = IndexY;
	m_IndexZ = IndexZ;
	m_Index = Index;
	m_SectionSize = SectionSize;
	m_SectionTotalSize = SectionTotalSize;

	return true;
}

void CCollisionSection::SetSectionMin(const Vector3& Min)
{
	m_Min = Min;
}

void CCollisionSection::SetSectionMax(const Vector3& Max)
{
	m_Max = Max;
}

void CCollisionSection::AddCollider(CCollider* Collider)
{
	m_vecCollider.push_back(Collider);

	Collider->AddSectionIndex(m_Index);
}

void CCollisionSection::Clear()
{
	m_vecPrevObject.clear();
	m_vecPrevCollider.clear();
	m_vecPrevCollider = m_vecCollider;
	size_t Size = m_vecPrevCollider.size();
	//ref추가
	for (size_t i = 0; i < Size; ++i)
	{
		m_vecPrevObject.push_back(m_vecPrevCollider[i]->GetOwner());
	}
	m_vecCollider.clear();
}

void CCollisionSection::Collision(float DeltaTime)
{
	size_t	Size = m_vecCollider.size();
	CCollision::fDeltaTime = DeltaTime;

	//for (size_t i = 0; i < Size; ++i)
	//{
	//	CCollider* Collider = m_vecCollider[i];

	//	if (Collider->GetCurrentSectionCheck())
	//		continue;

	//	Collider->CurrentSectionCheck();

	//	// 이전 프레임에 충돌되었던 충돌체들을 체크해본다.
	//	Collider->CheckPrevColliderSection();
	//}


	if (Size < 2)
		return;

	for (size_t i = 0; i < Size - 1; ++i)
	{
		CCollider* Src = m_vecCollider[i];

		if (!Src->IsEnable())
			continue;

		if (!Src->GetOwner()->IsEnable())
			continue;
		for (size_t j = i + 1; j < Size; ++j)
		{
			CCollider* Dest = m_vecCollider[j];

			if (!Dest->IsEnable())
				continue;
			if (!Dest->GetOwner()->IsEnable())
				continue;

			if (Src == Dest)
				continue;
			// 현재 프레임에 다른 섹션에서 둘이 충돌처리를 해본적이 있을 경우
			if (Src->CheckCurrentFrameCollision(Dest))
				continue;

			CollisionProfile* SrcProfile = Src->GetProfile();
			CollisionProfile* DestProfile = Dest->GetProfile();

			if (SrcProfile->vecChannel[(int)DestProfile->Channel].Interaction ==
				Collision_Interaction::Ignore ||
				DestProfile->vecChannel[(int)SrcProfile->Channel].Interaction ==
				Collision_Interaction::Ignore)
				continue;

			if (Src->Collision(Dest))
			{
				// 이전에 이 충돌체와 충돌했는지를 판단한다.
				// 이전충돌체에 없다면 지금 막 충돌을 시작한다는 의미이다.
				if (!Src->CheckPrevCollision(Dest))
				{
					Src->AddPrevCollider(Dest);
					Dest->AddPrevCollider(Src);

					// Callback 함수 호출
					Src->CallCollisionCallback(Collision_State::Begin);
					Dest->CallCollisionCallback(Collision_State::Begin);
				}

				//현재 충돌중이라는 뜻 
				else
				{
					Src->CallCollisionCallback(Collision_State::Middle);
					Dest->CallCollisionCallback(Collision_State::Middle);
				}
			}

			// 충돌이 아니라면 이전에 충돌되었던 물체인지를 판단한다.
			// 이전에 충돌되었던 물체라면 부딪힌 물체가 지금 떨어진다는 의미이다.
			else if (Src->CheckPrevCollision(Dest))
			{
				Src->DeletePrevCollider(Dest);
				Dest->DeletePrevCollider(Src);

				// Callback 함수 호출
				Src->CallCollisionCallback(Collision_State::End);
				Dest->CallCollisionCallback(Collision_State::End);
			}
		}
	}
}

CCollider* CCollisionSection::CollisionMouse(bool Is2D, float DeltaTime)
{
	if (Is2D)
	{
		Vector2	MousePos = CInput::GetInst()->GetMouse2DWorldPos();

		size_t	Size = m_vecCollider.size();

		if (Size > 1)
		{
			std::sort(m_vecCollider.begin(), m_vecCollider.end(), CCollisionSection::SortY);

		}
		//if (Size > 1)
		{
		//	qsort(&m_vecCollider[0], Size, (size_t)sizeof(CCollider*),
		//		CCollisionSection::SortY);
		}

		for (size_t i = 0; i < Size; ++i)
		{
			if (m_vecCollider[i]->CollisionMouse(MousePos))
				return m_vecCollider[i];
		}
	}

	else
	{
		size_t	Size = m_vecCollider.size();

		if (Size > 1)
		{
			m_matView = CSceneManager::GetInst()->GetScene()->GetCameraManager()->GetCurrentCamera()->GetViewMatrix();

			qsort(&m_vecCollider[0], Size, (size_t)sizeof(CCollider*),
				CCollisionSection::SortZ);
		}

		for (size_t i = 0; i < Size; ++i)
		{
			if (m_vecCollider[i]->CollisionMouse(Vector2()))
				return m_vecCollider[i];
		}
	}

	return nullptr;
}

bool CCollisionSection::RayCheck(HitResult& _HitResult, const Vector3& Start, const Vector3& End, CollisionProfile* Profile)
{
	bool Check = false;
	std::vector<int> vecCollider;
	size_t	Size = m_vecPrevCollider.size();

	Vector3 Min = Vector3(min(Start.x, End.x), min(Start.y, End.y), min(Start.z, End.z));
	Vector3 Max = Vector3(max(Start.x, End.x), max(Start.y, End.y), max(Start.z, End.z));
	HitResult CheckHitResult;
	CCollider* CheckCollider=nullptr;
	float CheckLength = (Start - End).Length();

	if (Size == 0)
		return Check;
	for (size_t i = 0; i < Size - 1; ++i)
	{
		CCollider* Src = m_vecPrevCollider[i];

		if (Src->GetProfile() != Profile)
			continue;
		if (!Src->IsActive())
			continue;
		Vector3 Dir = End - Start;
		float Length=Dir.Length();
		Dir.Normalize();
		if (Src->CollisionRay(CheckHitResult, Start, Dir, Length))
		{
			float Length = (CheckHitResult.HitPoint - Start).Length();
			if (CheckLength > Length)
			{
				CheckLength = Length;
				CheckCollider = Src;
				_HitResult = CheckHitResult;
				_HitResult.DestCollider = Src;
				_HitResult.DestObject = Src->GetOwner();
				Check = true;
			}

		}

	}

	return Check;
}



int CCollisionSection::SortY(const void* Src, const void* Dest)
{
	CCollider* SrcCollider = *((CCollider**)Src);
	CCollider* DestCollider = *((CCollider**)Dest);

	float	SrcY = SrcCollider->GetWorldPos().y;
	float	DestY = SrcCollider->GetWorldPos().y;

	if (SrcY < DestY)
		return -1;

	else if (SrcY > DestY)
		return 1;

	return 0;
}

int CCollisionSection::SortZ(const void* Src, const void* Dest)
{
	CCollider* SrcCollider = *((CCollider**)Src);
	CCollider* DestCollider = *((CCollider**)Dest);

	float	SrcZ = SrcCollider->GetWorldPos().TransformCoord(m_matView).z;
	float	DestZ = SrcCollider->GetWorldPos().TransformCoord(m_matView).z;

	if (SrcZ < DestZ)
		return -1;

	else if (SrcZ > DestZ)
		return 1;

	return 0;
}
