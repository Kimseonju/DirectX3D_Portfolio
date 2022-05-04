
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
	//�ѹ��̶� �����ߴ��� ���ߴ��� üũ
	bool Check = false;

	std::vector<int> vecSelectionIndex=Scene->GetCollisionManager()->GetCollisionSection3D(Start, End);
	CollisionProfile* pProfile=CCollisionManager::GetInst()->FindProfile(Profile);

	CollisionSectionInfo* Section3D = Scene->GetCollisionManager()->GetSection3D();
	for (size_t i = 0; i < vecSelectionIndex.size(); ++i)
	{
		//�ִٸ� �浹ü���� �� �ѹ��̶� �����ߴٴ°�
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
