
#include "CollisionRay.h"
#include "../CollisionManager.h"
#include "../Input.h"
DEFINITION_SINGLE(CCollisionRay);

CCollisionRay::CCollisionRay()
{
}

CCollisionRay::~CCollisionRay()
{
}

bool CCollisionRay::LineTraceSingleByChannel(CScene* Scene, HitResult& _HitResult,  Vector3 Start, Vector3 End, const std::string& Profile)
{
	HitResult CheckHitResult;
	float CheckLength = (Start - End).Length();
	//한번이라도 성공했는지 못했는지 체크
	bool Check = false;

	std::vector<int> vecSelectionIndex=Scene->GetCollisionManager()->GetCollisionSection3D(Start, End);
	CollisionProfile* pProfile=CCollisionManager::GetInst()->FindProfile(Profile);

	CollisionSectionInfo* Section3D = Scene->GetCollisionManager()->GetSection3D();
	for (size_t i = 0; i < vecSelectionIndex.size(); ++i)
	{
		//있다면 충돌체있음 즉 한번이라도 성공했다는것
		if (Section3D->vecSection[vecSelectionIndex[i]]->RayCheck(CheckHitResult, Start, End, pProfile))
		{
			float Length=(CheckHitResult.HitPoint - Start).Length();
			if (CheckLength > Length)
			{
				_HitResult = CheckHitResult;
				CheckLength = Length;
				Check = true;
			}
		}
	}

	return Check;
}
