#pragma once
//���� ������
//������ ���������� �浹ü �����´�.
//��� �浹���� ������
#include "../Scene/CollisionSection.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneManager.h"
#include "../CollisionManager.h"
#include "../GameEngine.h"
#include "../GameObject.h"
class CCollisionRay
{
public:
	bool LineTraceSingleByChannel(CScene* Scene, HitResult& _HitResult, Vector3 Start, Vector3 End, const std::string& Profile);

	DECLARE_SINGLE(CCollisionRay);
};

