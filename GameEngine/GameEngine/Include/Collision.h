#pragma once

#include "GameEngine.h"

class CCollision
{
public:
	static float fDeltaTime;

public:
	static bool CollisionBox2DToBox2D(HitResult& SrcResult, HitResult& DestResult,
		class CColliderBox2D* Src, class CColliderBox2D* Dest);
	static bool CollisionCircleToCircle(HitResult& SrcResult, HitResult& DestResult,
		class CColliderCircle* Src, class CColliderCircle* Dest);
	static bool CollisionBox2DToCircle(HitResult& SrcResult, HitResult& DestResult,
		class CColliderBox2D* Src, class CColliderCircle* Dest);
	static bool CollisionBox2DToPixel(HitResult& SrcResult, HitResult& DestResult,
		class CColliderBox2D* Src, class CColliderPixel* Dest);
	static bool CollisionCircleToPixel(HitResult& SrcResult, HitResult& DestResult,
		class CColliderCircle* Src, class CColliderPixel* Dest);
	static bool CollisionSpherePicking(HitResult& SrcResult,
		class CColliderSphere* Sphere, const Ray& ray);

	static bool CollisionBox3DPicking(HitResult& SrcResult,
		class CColliderBox3D* Box3D, const Ray& ray);

	static bool CollisionBox3DRay(HitResult& SrcResult,
		class CColliderBox3D* Box3D, const Vector3& Start, const Vector3& Dir, float Length);
	static bool CollisionSphereRay(HitResult& SrcResult,
		class CColliderSphere* Sphere, const Vector3& Start, const Vector3& Dir, float Length);

	static bool CollisionSphereToSphere(HitResult& SrcResult, HitResult& DestResult,
		class CColliderSphere* Src, class CColliderSphere* Dest);
	static bool CollisionBox3DToSphere(HitResult& SrcResult, HitResult& DestResult,
		class CColliderBox3D* Src, class CColliderSphere* Dest);
	static bool CollisionBox3DToBox3D(HitResult& SrcResult, HitResult& DestResult,
		class CColliderBox3D* Src, class CColliderBox3D* Dest);


public:
	static bool CollisionBox2DToBox2D(HitResult& SrcResult, HitResult& DestResult, 
		const Box2DInfo& Src, const Box2DInfo& Dest);
	static bool CollisionCircleToCircle(HitResult& SrcResult, HitResult& DestResult,
		const CircleInfo& Src, const CircleInfo& Dest);
	static bool CollisionBox2DToCircle(HitResult& SrcResult, HitResult& DestResult,
		const Box2DInfo& Src, const CircleInfo& Dest);
	static bool CollisionBox2DToPixel(HitResult& SrcResult, HitResult& DestResult,
		const Box2DInfo& Src, const PixelInfo& Dest);
	static bool CollisionCircleToPixel(HitResult& SrcResult, HitResult& DestResult,
		const CircleInfo& Src, const PixelInfo& Dest);
	static bool CollisionBox2DToPoint(HitResult& SrcResult, HitResult& DestResult,
		const Box2DInfo& Src, const Vector2& Dest);
	static bool CollisionCircleToPoint(HitResult& SrcResult, HitResult& DestResult,
		const CircleInfo& Src, const Vector2& Dest);
	static bool CollisionPixelToPoint(HitResult& SrcResult, HitResult& DestResult,
		const PixelInfo& Src, const Vector2& Dest);

	static bool CollisionBox3DToSphere(HitResult& SrcResult, HitResult& DestResult,
		const Box3DInfo& Src, const SphereInfo& Dest);

	static bool CollisionBox3DToBox3D(HitResult& SrcResult, HitResult& DestResult,
		const Box3DInfo& Src, const Box3DInfo& Dest);
	static bool CollisionSphereToSphere(HitResult& SrcResult, HitResult& DestResult,
		const SphereInfo& Src, const SphereInfo& Dest);


	bool EqualAbs(float a, float b, float epsilon = 1e-4f);

private:
	static bool GetSeparatingAxis(const Vector3& CenterDir, const Vector3 Plane, const Box3DInfo& Src, const Box3DInfo& Dest);
	static void BlockBox3D(class CColliderBox3D* Src, class CColliderBox3D* Dest);


};

