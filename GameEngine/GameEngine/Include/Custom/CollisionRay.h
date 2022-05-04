#pragma once
//임의 레이저
//무조건 레이저쏴서 충돌체 가져온다.
//모든 충돌관련 접근함
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

