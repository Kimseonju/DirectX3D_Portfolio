#include "Collision.h"
#include "Component/ColliderBox2D.h"
#include "Component/ColliderBox3D.h"
#include "Component/ColliderCircle.h"
#include "Component/ColliderPixel.h"
#include "Component/ColliderSphere.h"
#include "Component/ColliderBox3D.h"
#include "GameObject.h"
#include "Input.h"

float CCollision::fDeltaTime = 0.f;

bool CCollision::CollisionBox2DToBox2D(HitResult& SrcResult, HitResult& DestResult,
	CColliderBox2D* Src, CColliderBox2D* Dest)
{
	if (CollisionBox2DToBox2D(SrcResult, DestResult, Src->GetInfo(), Dest->GetInfo()))
	{
		SrcResult.DestCollider = Dest;
		SrcResult.DestObject = Dest->GetOwner();

		DestResult.DestCollider = Src;
		DestResult.DestObject = Src->GetOwner();
		return true;
	}

	SrcResult.DestCollider = Dest;
	SrcResult.DestObject = Dest->GetOwner();

	DestResult.DestCollider = Src;
	DestResult.DestObject = Src->GetOwner();

	return false;
}

bool CCollision::CollisionCircleToCircle(HitResult& SrcResult, HitResult& DestResult,
	CColliderCircle* Src, CColliderCircle* Dest)
{
	if (CollisionCircleToCircle(SrcResult, DestResult, Src->GetInfo(), Dest->GetInfo()))
	{
		SrcResult.DestCollider = Dest;
		SrcResult.DestObject = Dest->GetOwner();

		DestResult.DestCollider = Src;
		DestResult.DestObject = Src->GetOwner();
		return true;
	}

	SrcResult.DestCollider = Dest;
	SrcResult.DestObject = Dest->GetOwner();

	DestResult.DestCollider = Src;
	DestResult.DestObject = Src->GetOwner();

	return false;
}

bool CCollision::CollisionBox2DToCircle(HitResult& SrcResult, HitResult& DestResult,
	CColliderBox2D* Src, CColliderCircle* Dest)
{
	if (CollisionBox2DToCircle(SrcResult, DestResult, Src->GetInfo(), Dest->GetInfo()))
	{
		SrcResult.DestCollider = Dest;
		SrcResult.DestObject = Dest->GetOwner();

		DestResult.DestCollider = Src;
		DestResult.DestObject = Src->GetOwner();
		return true;
	}

	SrcResult.DestCollider = Dest;
	SrcResult.DestObject = Dest->GetOwner();

	DestResult.DestCollider = Src;
	DestResult.DestObject = Src->GetOwner();

	return false;
}

bool CCollision::CollisionBox2DToPixel(HitResult& SrcResult, HitResult& DestResult,
	CColliderBox2D* Src, CColliderPixel* Dest)
{
	if (CollisionBox2DToPixel(SrcResult, DestResult, Src->GetInfo(), Dest->GetInfo()))
	{
		SrcResult.DestCollider = Dest;
		SrcResult.DestObject = Dest->GetOwner();

		DestResult.DestCollider = Src;
		DestResult.DestObject = Src->GetOwner();
		return true;
	}

	SrcResult.DestCollider = Dest;
	SrcResult.DestObject = Dest->GetOwner();

	DestResult.DestCollider = Src;
	DestResult.DestObject = Src->GetOwner();

	return false;
}

bool CCollision::CollisionCircleToPixel(HitResult& SrcResult, HitResult& DestResult,
	CColliderCircle* Src, CColliderPixel* Dest)
{
	if (CollisionCircleToPixel(SrcResult, DestResult, Src->GetInfo(), Dest->GetInfo()))
	{
		SrcResult.DestCollider = Dest;
		SrcResult.DestObject = Dest->GetOwner();

		DestResult.DestCollider = Src;
		DestResult.DestObject = Src->GetOwner();
		return true;
	}

	SrcResult.DestCollider = Dest;
	SrcResult.DestObject = Dest->GetOwner();

	DestResult.DestCollider = Src;
	DestResult.DestObject = Src->GetOwner();

	return false;
}

bool CCollision::CollisionSpherePicking(HitResult& SrcResult,
	CColliderSphere* Sphere, const Ray& ray)
{
	SphereInfo	Info = Sphere->GetInfo();

	Vector3	M = ray.Pos - Info.Center;
	float	b = 2.f * M.Dot(ray.Dir);
	float	c = M.Dot(M) - Info.Radius * Info.Radius;

	// 루트 b^2 - 4c
	float	Det = b * b - 4.f * c;

	if (Det < 0.f)
		return false;

	Det = sqrtf(Det);

	float t1, t2;

	t1 = (-b + Det) / 2.f;
	t2 = (-b - Det) / 2.f;

	if (t1 < 0.f && t2 < 0.f)
		return false;

	float	Dist = t1 < t2 ? t1 : t2;

	SrcResult.HitPoint = ray.Pos + ray.Dir * Dist;

	return true;
}

bool CCollision::CollisionBox3DPicking(HitResult& SrcResult, CColliderBox3D* Box3D, const Ray& ray)
{
	Box3DInfo Info = Box3D->GetInfo();
	
	Vector3 RayOrigin = ray.Pos;
	Vector3 RayDir = ray.Dir;

	float Min = -99999.f, Max = 99999.f, tMin, tMax, s, IsP;

	Vector3 Axis = Info.Axis[AXIS_X];
	Axis.Normalize();

	s = Axis.Dot(Info.Center - RayOrigin);
	IsP = Axis.Dot(RayDir);

	//Ray와 평면이 평행한지 검사
	if (IsP == 0.f)
	{
		float Temp1 = -s - Info.Length[0];
		float Temp2 = -s + Info.Length[0];

		if (Temp1 > 0.f || Temp2 < 0.f)
			return false;
	}

	tMin = (s - Info.Length[0]) / IsP;
	tMax = (s + Info.Length[0]) / IsP;

	//최솟값이 최댓값보다 더 크다면 순서가 잘못된 것이다. -> Swap 처리 해준다.
	if (tMin > tMax)
	{
		float Temp = 0.f;

		Temp = tMin;
		tMin = tMax;
		tMax = Temp;

	}

	//최솟값 중에서 최댓값을 찾기 위해 갱신
	if (Min < tMin)
		Min = tMin;

	//최댓값 중에서 최솟값을 찾기 위해 갱신
	if (Max > tMax)
		Max = tMax;

	//축을 바꿔 반복
	Axis = Info.Axis[AXIS_Y];
	Axis.Normalize();

	s = Axis.Dot(Info.Center - RayOrigin);
	IsP = Axis.Dot(RayDir);

	if (IsP == 0.f)
	{
		float Temp1 = -s - Info.Length[1];
		float Temp2 = -s + Info.Length[1];

		if (Temp1 > 0.f || Temp2 < 0.f)
			return false;
	}

	tMin = (s - Info.Length[1]) / IsP;
	tMax = (s + Info.Length[1]) / IsP;

	if (tMin > tMax)
	{
		float Temp = 0.f;

		Temp = tMin;
		tMin = tMax;
		tMax = Temp;

	}

	if (Min < tMin)
		Min = tMin;

	if (Max > tMax)
		Max = tMax;

	Axis = Info.Axis[AXIS_Z];
	Axis.Normalize();

	s = Axis.Dot(Info.Center - RayOrigin);
	IsP = Axis.Dot(RayDir);

	if (IsP == 0.f)
	{
		float Temp1 = -s - Info.Length[2];
		float Temp2 = -s + Info.Length[2];

		if (Temp1 > 0.f || Temp2 < 0.f)
			return false;
	}

	tMin = (s - Info.Length[2]) / IsP;
	tMax = (s + Info.Length[2]) / IsP;

	if (tMin > tMax)
	{
		float Temp = 0.f;

		Temp = tMin;
		tMin = tMax;
		tMax = Temp;

	}

	if (Min < tMin)
		Min = tMin;

	if (Max > tMax)
		Max = tMax;

	//최솟값중에서 가장 큰 값이 최댓값중에서 가장 작은 값보다 작을 경우 충돌 처리
	if (Min < Max)
	{
		Vector3 Pos = Info.Center - Vector3(Info.Length[0], Info.Length[1], Info.Length[2]);

		SrcResult.HitPoint = RayOrigin + RayDir * Max;

		return true;

	}

	SrcResult = {};

	return false;
}

bool CCollision::CollisionBox3DRay(HitResult& SrcResult, CColliderBox3D* Box3D, const Vector3& Start, const Vector3& Dir, float Length)
{
	//Box3DInfo	Info = Box3D->GetInfo();
	//
	//Ray ray;
	//ray.Pos = Start;
	//ray.Dir = Dir;
	//
	//
	//Vector3 T_1, T_2; // vectors to hold the T-values for every direction
	//double t_near = -DBL_MAX; // maximums defined in float.h
	//double t_far = DBL_MAX;
	//
	//for (int i = 0; i < 3; i++) { //we test slabs in every direction
	//	if (ray.Dir[i] == 0) { // ray parallel to planes in this direction
	//		if ((ray.Dir[i] < Info.Min[i]) || (ray.Pos[i] > Info.Max[i])) {
	//			return false; // parallel AND outside box : no intersection possible
	//		}
	//	}
	//	else { // ray not parallel to planes in this direction
	//			T_1[i] = (Info.Min[i] - ray.Pos[i]) * ray.Dir[i];
	//		T_2[i] = (Info.Max[i] - ray.Pos[i]) * ray.Dir[i];
	//
	//		if (T_1[i] > T_2[i]) { // we want T_1 to hold values for intersection with near plane
	//			std::swap(T_1, T_2);
	//		}
	//		if (T_1[i] > t_near) {
	//			t_near = T_1[i];
	//		}
	//		if (T_2[i] < t_far) {
	//			t_far = T_2[i];
	//		}
	//		if ((t_near > t_far) || (t_far < 0)) {
	//			return false;
	//		}
	//	}
	//}
	//if (Length > t_far)
	//{
	//	SrcResult.HitPoint = Start + Dir * t_far;
	//	return true;
	//}
	//return false;
	//Box Slap Method
	Box3DInfo Info = Box3D->GetInfo();

	Vector3 RayOrigin = Start;
	Vector3 RayDir = Dir;

	float Min = -99999.f, Max = 99999.f, tMin, tMax, s, IsP;

	Vector3 Axis = Info.Axis[AXIS_X];
	Axis.Normalize();

	s = Axis.Dot(Info.Center - RayOrigin);
	IsP = Axis.Dot(RayDir);

	//Ray와 평면이 평행한지 검사
	if (IsP == 0.f)
	{
		float Temp1 = -s - Info.Length[0];
		float Temp2 = -s + Info.Length[0];

		if (Temp1 > 0.f || Temp2 < 0.f)
			return false;
	}

	tMin = (s - Info.Length[0]) / IsP;
	tMax = (s + Info.Length[0]) / IsP;

	//최솟값이 최댓값보다 더 크다면 순서가 잘못된 것이다. -> Swap 처리 해준다.
	if (tMin > tMax)
	{
		float Temp = 0.f;

		Temp = tMin;
		tMin = tMax;
		tMax = Temp;

	}

	//최솟값 중에서 최댓값을 찾기 위해 갱신
	if (Min < tMin)
		Min = tMin;

	//최댓값 중에서 최솟값을 찾기 위해 갱신
	if (Max > tMax)
		Max = tMax;

	//축을 바꿔 반복
	Axis = Info.Axis[AXIS_Y];
	Axis.Normalize();

	s = Axis.Dot(Info.Center - RayOrigin);
	IsP = Axis.Dot(RayDir);

	if (IsP == 0.f)
	{
		float Temp1 = -s - Info.Length[1];
		float Temp2 = -s + Info.Length[1];

		if (Temp1 > 0.f || Temp2 < 0.f)
			return false;
	}

	tMin = (s - Info.Length[1]) / IsP;
	tMax = (s + Info.Length[1]) / IsP;

	if (tMin > tMax)
	{
		float Temp = 0.f;

		Temp = tMin;
		tMin = tMax;
		tMax = Temp;

	}

	if (Min < tMin)
		Min = tMin;

	if (Max > tMax)
		Max = tMax;

	Axis = Info.Axis[AXIS_Z];
	Axis.Normalize();

	s = Axis.Dot(Info.Center - RayOrigin);
	IsP = Axis.Dot(RayDir);

	if (IsP == 0.f)
	{
		float Temp1 = -s - Info.Length[2];
		float Temp2 = -s + Info.Length[2];

		if (Temp1 > 0.f || Temp2 < 0.f)
			return false;
	}

	tMin = (s - Info.Length[2]) / IsP;
	tMax = (s + Info.Length[2]) / IsP;

	if (tMin > tMax)
	{
		float Temp = 0.f;

		Temp = tMin;
		tMin = tMax;
		tMax = Temp;

	}

	if (Min < tMin)
		Min = tMin;

	if (Max > tMax)
		Max = tMax;

	//최솟값중에서 가장 큰 값이 최댓값중에서 가장 작은 값보다 작을 경우 충돌 처리
	if (Min < Max)
	{
		Vector3 Pos = Info.Center - Vector3(Info.Length[0], Info.Length[1], Info.Length[2]);

		SrcResult.HitPoint = RayOrigin + RayDir * Max;

		return true;

	}

	SrcResult = {};

	return false;
}

bool CCollision::CollisionSphereRay(HitResult& SrcResult, CColliderSphere* Sphere, const Vector3& Start, const Vector3& Dir, float Length)
{
	SphereInfo	Info = Sphere->GetInfo();

	Ray ray;
	ray.Pos = Start;
	ray.Dir = Dir;

	Vector3	M = ray.Pos - Info.Center;
	float	b = 2.f * M.Dot(ray.Dir);
	float	c = M.Dot(M) - Info.Radius * Info.Radius;

	// 루트 b^2 - 4c
	float	Det = b * b - 4.f * c;

	if (Det < 0.f)
		return false;

	Det = sqrtf(Det);

	float t1, t2;

	t1 = (-b + Det) / 2.f;
	t2 = (-b - Det) / 2.f;

	if (t1 < 0.f && t2 < 0.f)
		return false;

	float	Dist = t1 < t2 ? t1 : t2;

	SrcResult.HitPoint = ray.Pos + ray.Dir * Dist;

	return true;
}

bool CCollision::CollisionSphereToSphere(HitResult& SrcResult, HitResult& DestResult,
	CColliderSphere* Src, CColliderSphere* Dest)
{
	if (CollisionSphereToSphere(SrcResult, DestResult, Src->GetInfo(), Dest->GetInfo()))
	{
		SrcResult.DestCollider = Dest;
		SrcResult.DestObject = Dest->GetOwner();

		DestResult.DestCollider = Src;
		DestResult.DestObject = Src->GetOwner();
		return true;
	}

	SrcResult.DestCollider = Dest;
	SrcResult.DestObject = Dest->GetOwner();

	DestResult.DestCollider = Src;
	DestResult.DestObject = Src->GetOwner();

	return false;
}

bool CCollision::CollisionBox3DToSphere(HitResult& SrcResult, HitResult& DestResult, CColliderBox3D* Src, CColliderSphere* Dest)
{
	if (CollisionBox3DToSphere(SrcResult, DestResult, Src->GetInfo(), Dest->GetInfo()))
	{
		SrcResult.DestCollider = Dest;
		SrcResult.DestObject = Dest->GetOwner();

		DestResult.DestCollider = Src;
		DestResult.DestObject = Src->GetOwner();
		return true;
	}

	SrcResult.DestCollider = Dest;
	SrcResult.DestObject = Dest->GetOwner();

	DestResult.DestCollider = Src;
	DestResult.DestObject = Src->GetOwner();

	return false;
}

bool CCollision::CollisionBox3DToBox3D(HitResult& SrcResult, HitResult& DestResult, CColliderBox3D* Src, CColliderBox3D* Dest)
{
	if (CollisionBox3DToBox3D(SrcResult, DestResult, Src->GetInfo(), Dest->GetInfo()))
	{
		SrcResult.DestCollider = Dest;
		SrcResult.DestObject = Dest->GetOwner();

		DestResult.DestCollider = Src;
		DestResult.DestObject = Src->GetOwner();

		// Block (후에 블락을 사용할지 말지에 대한 기능 추가 예정)
#pragma region Block

		// Player만 Block함
		//if (SrcResult.DestCollider->GetProfile()->Name == "Player" || 
		//	Dest->GetOwner()->GetPrevWorldPos() != Dest->GetOwner()->GetWorldPos())
		//{
		//	CollisionProfile* SrcProfile = Src->GetProfile();
		//	CollisionProfile* DestProfile = Dest->GetProfile();
		//
		//	if (Dest->GetProfile()->Name == "MapCollision")
		//	{
		//		BlockBox3D(Src, Dest);
		//	}
		//	// 서로 Block 인 경우에만 블락을 실시한다.
		//}
#pragma endregion



		return true;
	}

	SrcResult.DestCollider = Dest;
	SrcResult.DestObject = Dest->GetOwner();

	DestResult.DestCollider = Src;
	DestResult.DestObject = Src->GetOwner();

	return false;
}
bool CCollision::CollisionBox2DToBox2D(HitResult& SrcResult, HitResult& DestResult,
	const Box2DInfo& Src, const Box2DInfo& Dest)
{
	Vector2 CenterDir = Src.Center - Dest.Center;

	// Src의 X축으로 투영
	Vector2 Axis = Src.Axis[AXIS_X];

	float	CenterDot = abs(CenterDir.Dot(Axis));

	float   r1, r2;

	r1 = Src.Length[0];
	r2 = abs(Dest.Axis[AXIS_X].Dot(Axis)) * Dest.Length[0] +
		abs(Dest.Axis[AXIS_Y].Dot(Axis)) * Dest.Length[1];

	if (CenterDot > r1 + r2)
		return false;

	Axis = Src.Axis[AXIS_Y];

	CenterDot = abs(CenterDir.Dot(Axis));

	r1 = Src.Length[1];
	r2 = abs(Dest.Axis[AXIS_X].Dot(Axis)) * Dest.Length[0] +
		abs(Dest.Axis[AXIS_Y].Dot(Axis)) * Dest.Length[1];

	if (CenterDot > r1 + r2)
		return false;

	Axis = Dest.Axis[AXIS_X];

	CenterDot = abs(CenterDir.Dot(Axis));

	r1 = Dest.Length[0];
	r2 = abs(Src.Axis[AXIS_X].Dot(Axis)) * Src.Length[0] +
		abs(Src.Axis[AXIS_Y].Dot(Axis)) * Src.Length[1];

	if (CenterDot > r1 + r2)
		return false;

	Axis = Dest.Axis[AXIS_Y];

	CenterDot = abs(CenterDir.Dot(Axis));

	r1 = Dest.Length[1];
	r2 = abs(Src.Axis[AXIS_X].Dot(Axis)) * Src.Length[0] +
		abs(Src.Axis[AXIS_Y].Dot(Axis)) * Src.Length[1];

	if (CenterDot > r1 + r2)
		return false;

	return true;
}

bool CCollision::CollisionCircleToCircle(HitResult& SrcResult, HitResult& DestResult,
	const CircleInfo& Src, const CircleInfo& Dest)
{
	float	Distance = Src.Center.Distance(Dest.Center);

	bool	Result = Distance <= Src.Radius + Dest.Radius;

	if (Result)
	{
		Vector2	Center = (Src.Center + Dest.Center) / 2.f;
		SrcResult.HitPoint = Vector3(Center.x, Center.y, 0.f);
		DestResult.HitPoint = Vector3(Center.x, Center.y, 0.f);
	}

	return Result;
}

bool CCollision::CollisionBox2DToCircle(HitResult& SrcResult, HitResult& DestResult,
	const Box2DInfo& Src, const CircleInfo& Dest)
{
	Vector2 CenterDir = Src.Center - Dest.Center;

	// Src의 X축으로 투영
	Vector2 Axis = Src.Axis[AXIS_X];
	Axis.Normalize();

	float	CenterDot = abs(CenterDir.Dot(Axis));

	float   r1, r2;

	r1 = Src.Length[0];
	r2 = Dest.Radius;

	if (CenterDot > r1 + r2)
		return false;

	Axis = Src.Axis[AXIS_Y];
	Axis.Normalize();

	CenterDot = abs(CenterDir.Dot(Axis));

	r1 = Src.Length[1];
	r2 = Dest.Radius;

	if (CenterDot > r1 + r2)
		return false;


	Axis = CenterDir;
	Axis.Normalize();

	CenterDot = abs(CenterDir.Dot(Axis));

	r1 = abs(Src.Axis[AXIS_X].Dot(Axis)) * Src.Length[0] +
		abs(Src.Axis[AXIS_Y].Dot(Axis)) * Src.Length[1];
	r2 = Dest.Radius;

	if (CenterDot > r1 + r2)
		return false;

	return true;
}

bool CCollision::CollisionBox2DToPixel(HitResult& SrcResult, HitResult& DestResult,
	const Box2DInfo& Src, const PixelInfo& Dest)
{
	if (!CollisionBox2DToBox2D(SrcResult, DestResult, Src, Dest.Box))
		return false;

	// 교집합 사각형을 구한다.
	float	Left = Src.Min.x < Dest.Min.x ? Dest.Min.x : Src.Min.x;
	float	Right = Src.Max.x > Dest.Max.x ? Dest.Max.x : Src.Max.x;
	float	Top = Src.Max.y > Dest.Max.y ? Dest.Max.y : Src.Max.y;
	float	Bottom = Src.Min.y < Dest.Min.y ? Dest.Min.y : Src.Min.y;

	// 픽셀 충돌체의 좌 하단 좌표를 구한다.
	Vector2	LeftBottom = Dest.Box.Center - Vector2(Dest.Box.Length[0], Dest.Box.Length[1]);

	Left -= LeftBottom.x;
	Right -= LeftBottom.x;

	Top -= LeftBottom.y;
	Bottom -= LeftBottom.y;

	Left = Left < 0.f ? 0.f : Left;
	Right = Right >= (float)Dest.Width ? (float)Dest.Width - 1 : Right;

	Bottom = Bottom < 0.f ? 0.f : Bottom;
	Top = Top >= (float)Dest.Height ? (float)Dest.Height - 1 : Top;

	Top = Dest.Height - Top;
	Bottom = Dest.Height - Bottom;

	for (int y = (int)Top; y < (int)Bottom; ++y)
	{
		for (int x = (int)Left; x <= (int)Right; ++x)
		{
			int	Index = y * (int)Dest.Width * 4 + x * 4;

			switch (Dest.Type)
			{
			case PixelCollision_Type::Color_Ignore:
			{
				if (Dest.Pixel[Index] == Dest.Color[0] &&
					Dest.Pixel[Index + 1] == Dest.Color[1] &&
					Dest.Pixel[Index + 2] == Dest.Color[2])
					continue;

				// 무시할 색상이 아니라면 이 픽셀의 점이 Box2D 안에 들어가는지 판단한다.
				// 픽셀의 월드상에서의 위치를 만들어낸다.
				Vector2	PixelPos = LeftBottom + Vector2((float)x, (float)Dest.Height - y);

				if (CollisionBox2DToPoint(SrcResult, DestResult, Src, PixelPos))
				{
					SrcResult.HitPoint = Vector3(PixelPos.x, PixelPos.y, 0.f);
					DestResult.HitPoint = Vector3(PixelPos.x, PixelPos.y, 0.f);
					return true;
				}
			}
			break;
			case PixelCollision_Type::Color_Confirm:
			{
				if (Dest.Pixel[Index] != Dest.Color[0] ||
					Dest.Pixel[Index + 1] != Dest.Color[1] ||
					Dest.Pixel[Index + 2] != Dest.Color[2])
					continue;

				// 무시할 색상이 아니라면 이 픽셀의 점이 Box2D 안에 들어가는지 판단한다.
				// 픽셀의 월드상에서의 위치를 만들어낸다.
				Vector2	PixelPos = LeftBottom + Vector2((float)x, (float)Dest.Height - y);

				if (CollisionBox2DToPoint(SrcResult, DestResult, Src, PixelPos))
				{
					SrcResult.HitPoint = Vector3(PixelPos.x, PixelPos.y, 0.f);
					DestResult.HitPoint = Vector3(PixelPos.x, PixelPos.y, 0.f);
					return true;
				}
			}
			break;
			case PixelCollision_Type::Alpha_Ignore:
			{
				if (Dest.Pixel[Index + 3] == Dest.Color[3])
					continue;

				// 무시할 색상이 아니라면 이 픽셀의 점이 Box2D 안에 들어가는지 판단한다.
				// 픽셀의 월드상에서의 위치를 만들어낸다.
				Vector2	PixelPos = LeftBottom + Vector2((float)x, (float)Dest.Height - y);

				if (CollisionBox2DToPoint(SrcResult, DestResult, Src, PixelPos))
				{
					SrcResult.HitPoint = Vector3(PixelPos.x, PixelPos.y, 0.f);
					DestResult.HitPoint = Vector3(PixelPos.x, PixelPos.y, 0.f);
					return true;
				}
			}
			break;
			case PixelCollision_Type::Alpha_Confirm:
			{
				if (Dest.Pixel[Index + 3] != Dest.Color[3])
					continue;

				// 무시할 색상이 아니라면 이 픽셀의 점이 Box2D 안에 들어가는지 판단한다.
				// 픽셀의 월드상에서의 위치를 만들어낸다.
				Vector2	PixelPos = LeftBottom + Vector2((float)x, (float)Dest.Height - y);

				if (CollisionBox2DToPoint(SrcResult, DestResult, Src, PixelPos))
				{
					SrcResult.HitPoint = Vector3(PixelPos.x, PixelPos.y, 0.f);
					DestResult.HitPoint = Vector3(PixelPos.x, PixelPos.y, 0.f);
					return true;
				}
			}
			break;
			}
		}
	}

	return false;
}

bool CCollision::CollisionCircleToPixel(HitResult& SrcResult, HitResult& DestResult,
	const CircleInfo& Src, const PixelInfo& Dest)
{
	if (!CollisionBox2DToCircle(DestResult, SrcResult, Dest.Box, Src))
		return false;

	// 교집합 사각형을 구한다.
	float	Left = Src.Min.x < Dest.Min.x ? Dest.Min.x : Src.Min.x;
	float	Right = Src.Max.x > Dest.Max.x ? Dest.Max.x : Src.Max.x;
	float	Top = Src.Max.y > Dest.Max.y ? Dest.Max.y : Src.Max.y;
	float	Bottom = Src.Min.y < Dest.Min.y ? Dest.Min.y : Src.Min.y;

	// 픽셀 충돌체의 좌 하단 좌표를 구한다.
	Vector2	LeftBottom = Dest.Box.Center - Vector2(Dest.Box.Length[0], Dest.Box.Length[1]);

	Left -= LeftBottom.x;
	Right -= LeftBottom.x;

	Top -= LeftBottom.y;
	Bottom -= LeftBottom.y;

	Left = Left < 0.f ? 0.f : Left;
	Right = Right >= (float)Dest.Width ? (float)Dest.Width - 1 : Right;

	Bottom = Bottom < 0.f ? 0.f : Bottom;
	Top = Top >= (float)Dest.Height ? (float)Dest.Height - 1 : Top;

	Top = Dest.Height - Top;
	Bottom = Dest.Height - Bottom;

	for (int y = (int)Top; y < (int)Bottom; ++y)
	{
		for (int x = (int)Left; x <= (int)Right; ++x)
		{
			int	Index = y * (int)Dest.Width * 4 + x * 4;

			switch (Dest.Type)
			{
			case PixelCollision_Type::Color_Ignore:
			{
				if (Dest.Pixel[Index] == Dest.Color[0] &&
					Dest.Pixel[Index + 1] == Dest.Color[1] &&
					Dest.Pixel[Index + 2] == Dest.Color[2])
					continue;

				// 무시할 색상이 아니라면 이 픽셀의 점이 Box2D 안에 들어가는지 판단한다.
				// 픽셀의 월드상에서의 위치를 만들어낸다.
				Vector2	PixelPos = LeftBottom + Vector2((float)x, (float)Dest.Height - y);

				if (CollisionCircleToPoint(SrcResult, DestResult, Src, PixelPos))
				{
					SrcResult.HitPoint = Vector3(PixelPos.x, PixelPos.y, 0.f);
					DestResult.HitPoint = Vector3(PixelPos.x, PixelPos.y, 0.f);
					return true;
				}
			}
			break;
			case PixelCollision_Type::Color_Confirm:
			{
				if (Dest.Pixel[Index] != Dest.Color[0] ||
					Dest.Pixel[Index + 1] != Dest.Color[1] ||
					Dest.Pixel[Index + 2] != Dest.Color[2])
					continue;

				// 무시할 색상이 아니라면 이 픽셀의 점이 Box2D 안에 들어가는지 판단한다.
				// 픽셀의 월드상에서의 위치를 만들어낸다.
				Vector2	PixelPos = LeftBottom + Vector2((float)x, (float)Dest.Height - y);

				if (CollisionCircleToPoint(SrcResult, DestResult, Src, PixelPos))
				{
					SrcResult.HitPoint = Vector3(PixelPos.x, PixelPos.y, 0.f);
					DestResult.HitPoint = Vector3(PixelPos.x, PixelPos.y, 0.f);
					return true;
				}
			}
			break;
			case PixelCollision_Type::Alpha_Ignore:
			{
				if (Dest.Pixel[Index + 3] == Dest.Color[3])
					continue;

				// 무시할 색상이 아니라면 이 픽셀의 점이 Box2D 안에 들어가는지 판단한다.
				// 픽셀의 월드상에서의 위치를 만들어낸다.
				Vector2	PixelPos = LeftBottom + Vector2((float)x, (float)Dest.Height - y);

				if (CollisionCircleToPoint(SrcResult, DestResult, Src, PixelPos))
				{
					SrcResult.HitPoint = Vector3(PixelPos.x, PixelPos.y, 0.f);
					DestResult.HitPoint = Vector3(PixelPos.x, PixelPos.y, 0.f);
					return true;
				}
			}
			break;
			case PixelCollision_Type::Alpha_Confirm:
			{
				if (Dest.Pixel[Index + 3] != Dest.Color[3])
					continue;

				// 무시할 색상이 아니라면 이 픽셀의 점이 Box2D 안에 들어가는지 판단한다.
				// 픽셀의 월드상에서의 위치를 만들어낸다.
				Vector2	PixelPos = LeftBottom + Vector2((float)x, (float)Dest.Height - y);

				if (CollisionCircleToPoint(SrcResult, DestResult, Src, PixelPos))
				{
					SrcResult.HitPoint = Vector3(PixelPos.x, PixelPos.y, 0.f);
					DestResult.HitPoint = Vector3(PixelPos.x, PixelPos.y, 0.f);
					return true;
				}
			}
			break;
			}
		}
	}

	return false;
}

bool CCollision::CollisionBox2DToPoint(HitResult& SrcResult, HitResult& DestResult,
	const Box2DInfo& Src, const Vector2& Dest)
{
	Vector2 CenterDir = Src.Center - Dest;

	// Src의 X축으로 투영
	Vector2 Axis = Src.Axis[AXIS_X];

	float	CenterDot = abs(CenterDir.Dot(Axis));

	if (CenterDot > Src.Length[0])
		return false;

	Axis = Src.Axis[AXIS_Y];

	CenterDot = abs(CenterDir.Dot(Axis));

	if (CenterDot > Src.Length[1])
		return false;

	return true;
}

bool CCollision::CollisionCircleToPoint(HitResult& SrcResult, HitResult& DestResult,
	const CircleInfo& Src, const Vector2& Dest)
{
	float	Dist = Src.Center.Distance(Dest);

	return Dist <= Src.Radius;
}

bool CCollision::CollisionPixelToPoint(HitResult& SrcResult,
	HitResult& DestResult, const PixelInfo& Src, const Vector2& Dest)
{
	if (Src.Min.x <= Dest.x && Dest.x <= Src.Max.x &&
		Src.Min.y <= Dest.y && Dest.y <= Src.Max.y)
	{
		int	x = (int)(Dest.x - Src.Min.x);
		int	y = (int)(Dest.y - Src.Min.y);

		int	Index = y * (int)Src.Width * 4 + x * 4;

		switch (Src.Type)
		{
		case PixelCollision_Type::Color_Ignore:
		{
			if (Src.Pixel[Index] == Src.Color[0] &&
				Src.Pixel[Index + 1] == Src.Color[1] &&
				Src.Pixel[Index + 2] == Src.Color[2])
				return false;

			SrcResult.HitPoint = Vector3(Dest.x, Dest.y, 0.f);
			DestResult.HitPoint = Vector3(Dest.x, Dest.y, 0.f);
		}
		break;
		case PixelCollision_Type::Color_Confirm:
		{
			if (Src.Pixel[Index] != Src.Color[0] ||
				Src.Pixel[Index + 1] != Src.Color[1] ||
				Src.Pixel[Index + 2] != Src.Color[2])
				return false;

			SrcResult.HitPoint = Vector3(Dest.x, Dest.y, 0.f);
			DestResult.HitPoint = Vector3(Dest.x, Dest.y, 0.f);
		}
		break;
		case PixelCollision_Type::Alpha_Ignore:
		{
			if (Src.Pixel[Index + 3] == Src.Color[3])
				return false;

			SrcResult.HitPoint = Vector3(Dest.x, Dest.y, 0.f);
			DestResult.HitPoint = Vector3(Dest.x, Dest.y, 0.f);
		}
		break;
		case PixelCollision_Type::Alpha_Confirm:
		{
			if (Src.Pixel[Index + 3] != Src.Color[3])
				return false;

			SrcResult.HitPoint = Vector3(Dest.x, Dest.y, 0.f);
			DestResult.HitPoint = Vector3(Dest.x, Dest.y, 0.f);
		}
		break;
		}

		return true;
	}

	return false;
}

bool CCollision::CollisionBox3DToSphere(HitResult& SrcResult, HitResult& DestResult, const Box3DInfo& Src, const SphereInfo& Dest)
{
	Vector3 LocalPos = Src.Center - Dest.Center;
	Vector3 local = Vector3(
		LocalPos.Dot(Src.Axis[AXIS::AXIS_X]),
		LocalPos.Dot(Src.Axis[AXIS::AXIS_Y]),
		LocalPos.Dot(Src.Axis[AXIS::AXIS_Z]));

	//Dot(Ai, D)
	float d[3];

	float r0, r1, r2;

	//local = d;
	d[0] = local.x;
	r0 = abs(d[0]);

	r1 = Src.Length[0];
	r2 = Dest.Radius;

	if (r0 > r1 + r2)
		return false;

	d[1] = local.y;
	r0 = abs(d[1]);

	r1 = Src.Length[1];
	r2 = Dest.Radius;

	if (r0 > r1 + r2)
		return false;
	//A2

	d[2] = local.z;
	r0 = abs(d[2]);

	r1 = Src.Length[2];
	r2 = Dest.Radius;

	if (r0 > r1 + r2)
		return false;

	return true;
}

bool CCollision::CollisionBox3DToBox3D(HitResult& SrcResult, HitResult& DestResult, const Box3DInfo& Src, const Box3DInfo& Dest)
{
	Vector3 CenterDir = Src.Center - Dest.Center;

	//Dot (A   B)
	float c[3][3];
	float absC[3][3];

	//Dot(Ai, D)
	float d[3];

	float r0, r1, r2;


	//A0
	for (int i = 0; i < 3; ++i)
	{
		//각도에따른 변퍼센트비율 구하기
		c[0][i] = Src.Axis[AXIS_X].Dot(Dest.Axis[i]);
		absC[0][i] = abs(c[0][i]);
	}
	d[0] = CenterDir.Dot(Src.Axis[AXIS_X]);
	r0 = abs(d[0]);

	r1 = Src.Length[0];
	r2 = absC[0][0] * Dest.Length[0] + absC[0][1] * Dest.Length[1] + absC[0][2] * Dest.Length[2];

	if (r0 > r1 + r2)
		return false;

	//A1
	for (int i = 0; i < 3; ++i)
	{
		//각도에따른 변퍼센트비율 구하기
		c[1][i] = Src.Axis[AXIS_Y].Dot(Dest.Axis[i]);
		absC[1][i] = abs(c[1][i]);
	}
	d[1] = CenterDir.Dot(Src.Axis[AXIS_Y]);
	r0 = abs(d[1]);

	r1 = Src.Length[1];
	r2 = absC[1][0] * Dest.Length[0] + absC[1][1] * Dest.Length[1] + absC[1][2] * Dest.Length[2];

	if (r0 > r1 + r2)
		return false;
	//A2

	for (int i = 0; i < 3; ++i)
	{
		//각도에따른 변퍼센트비율 구하기
		c[2][i] = Src.Axis[AXIS_Z].Dot(Dest.Axis[i]);
		absC[2][i] = abs(c[2][i]);
	}
	d[2] = CenterDir.Dot(Src.Axis[AXIS_Z]);
	r0 = abs(d[2]);

	r1 = Src.Length[2];
	r2 = absC[2][0] * Dest.Length[0] + absC[2][1] * Dest.Length[1] + absC[2][2] * Dest.Length[2];

	if (r0 > r1 + r2)
		return false;


	//B0
	r0 = abs(CenterDir.Dot(Dest.Axis[AXIS_X]));
	r1 = Dest.Length[0];
	r2 = absC[0][0] * Src.Length[0] + absC[1][0] * Src.Length[1] + absC[2][0] * Src.Length[2];

	if (r0 > r1 + r2)
		return false;

	//B1
	r0 = abs(CenterDir.Dot(Dest.Axis[AXIS_Y]));
	r1 = Dest.Length[1];
	r2 = absC[0][1] * Src.Length[0] + absC[1][1] * Src.Length[1] + absC[2][1] * Src.Length[2];

	if (r0 > r1 + r2)
		return false;
	//B2
	r0 = abs(CenterDir.Dot(Dest.Axis[AXIS_Z]));
	r1 = Dest.Length[2];
	r2 = absC[0][2] * Src.Length[0] + absC[1][2] * Src.Length[1] + absC[2][2] * Src.Length[2];

	if (r0 > r1 + r2)
		return false;


	//A0B0
	r0 = abs(d[2] * c[1][0] - d[1] * c[2][0]);
	r1 = Src.Length[1] * absC[2][0] + Src.Length[2] * absC[1][0];
	r2 = Dest.Length[1] * absC[0][2] + Dest.Length[2] * absC[0][1];

	if (r0 > r1 + r2)
		return false;

	//A0B1
	r0 = abs(d[2] * c[1][1] - d[1] * c[2][1]);
	r1 = Src.Length[1] * absC[2][1] + Src.Length[2] * absC[1][1];
	r2 = Dest.Length[0] * absC[0][2] + Dest.Length[2] * absC[0][0];

	if (r0 > r1 + r2)
		return false;

	//A0B2
	r0 = abs(d[2] * c[1][2] - d[1] * c[2][2]);
	r1 = Src.Length[1] * absC[2][2] + Src.Length[2] * absC[1][2];
	r2 = Dest.Length[0] * absC[0][1] + Dest.Length[1] * absC[0][0];

	if (r0 > r1 + r2)
		return false;


	//A1B0
	r0 = abs(d[0] * c[2][0] - d[2] * c[0][0]);
	r1 = Src.Length[0] * absC[2][0] + Src.Length[2] * absC[0][0];
	r2 = Dest.Length[1] * absC[1][2] + Dest.Length[2] * absC[1][1];

	if (r0 > r1 + r2)
		return false;

	//A1B1
	r0 = abs(d[0] * c[2][1] - d[2] * c[0][1]);
	r1 = Src.Length[0] * absC[2][1] + Src.Length[2] * absC[0][1];
	r2 = Dest.Length[0] * absC[1][2] + Dest.Length[2] * absC[1][0];

	if (r0 > r1 + r2)
		return false;

	//A1B2
	r0 = abs(d[0] * c[2][2] - d[2] * c[0][2]);
	r1 = Src.Length[0] * absC[2][2] + Src.Length[2] * absC[0][2];
	r2 = Dest.Length[0] * absC[1][1] + Dest.Length[1] * absC[1][0];

	if (r0 > r1 + r2)
		return false;


	//A2B0
	r0 = abs(d[1] * c[0][0] - d[0] * c[1][0]);
	r1 = Src.Length[0] * absC[1][0] + Src.Length[1] * absC[0][0];
	r2 = Dest.Length[1] * absC[2][2] + Dest.Length[2] * absC[2][1];

	if (r0 > r1 + r2)
		return false;

	//A2B1
	r0 = abs(d[1] * c[0][1] - d[0] * c[1][1]);
	r1 = Src.Length[0] * absC[1][1] + Src.Length[1] * absC[0][1];
	r2 = Dest.Length[0] * absC[2][2] + Dest.Length[2] * absC[2][0];

	if (r0 > r1 + r2)
		return false;

	//A2B2
	r0 = abs(d[1] * c[0][2] - d[0] * c[1][2]);
	r1 = Src.Length[0] * absC[1][2] + Src.Length[1] * absC[0][2];
	r2 = Dest.Length[0] * absC[2][1] + Dest.Length[1] * absC[2][0];

	if (r0 > r1 + r2)
		return false;
	return true;


	// 분리축 구하기
	/*return !(GetSeparatingAxis(CenterDir, Src.Axis[AXIS_X], Src, Dest) ||
		GetSeparatingAxis(CenterDir, Src.Axis[AXIS_Y], Src, Dest) ||
		GetSeparatingAxis(CenterDir, Src.Axis[AXIS_Z], Src, Dest) ||
		GetSeparatingAxis(CenterDir, Dest.Axis[AXIS_X], Src, Dest) ||
		GetSeparatingAxis(CenterDir, Dest.Axis[AXIS_Y], Src, Dest) ||
		GetSeparatingAxis(CenterDir, Dest.Axis[AXIS_Z], Src, Dest) ||
		GetSeparatingAxis(CenterDir, Src.Axis[AXIS_X].Cross(Dest.Axis[AXIS_X]), Src, Dest) ||
		GetSeparatingAxis(CenterDir, Src.Axis[AXIS_X].Cross(Dest.Axis[AXIS_Y]), Src, Dest) ||
		GetSeparatingAxis(CenterDir, Src.Axis[AXIS_X].Cross(Dest.Axis[AXIS_Z]), Src, Dest) ||
		GetSeparatingAxis(CenterDir, Src.Axis[AXIS_Y].Cross(Dest.Axis[AXIS_X]), Src, Dest) ||
		GetSeparatingAxis(CenterDir, Src.Axis[AXIS_Y].Cross(Dest.Axis[AXIS_Y]), Src, Dest) ||
		GetSeparatingAxis(CenterDir, Src.Axis[AXIS_Y].Cross(Dest.Axis[AXIS_Z]), Src, Dest) ||
		GetSeparatingAxis(CenterDir, Src.Axis[AXIS_Z].Cross(Dest.Axis[AXIS_X]), Src, Dest) ||
		GetSeparatingAxis(CenterDir, Src.Axis[AXIS_Z].Cross(Dest.Axis[AXIS_Y]), Src, Dest) ||
		GetSeparatingAxis(CenterDir, Src.Axis[AXIS_Z].Cross(Dest.Axis[AXIS_Z]), Src, Dest));*/
}

bool CCollision::CollisionSphereToSphere(HitResult& SrcResult, HitResult& DestResult,
	const SphereInfo& Src, const SphereInfo& Dest)
{
	float	Distance = Src.Center.Distance(Dest.Center);

	bool	Result = Distance <= Src.Radius + Dest.Radius;

	if (Result)
	{
		Vector3	Center = (Src.Center + Dest.Center) / 2.f;
		SrcResult.HitPoint = Center;
		DestResult.HitPoint = Center;
	}

	return Result;
}

bool CCollision::EqualAbs(float a, float b, float epsilon)
{
	return abs(a - b) < epsilon;
}

void CCollision::BlockBox3D(CColliderBox3D* Src, CColliderBox3D* Dest)
{
	// 각각의 밑변 네개의 점을 가져옴
	std::vector<Vector3> srcBottomPoint, destBottomPoint;

	Src->GetBottomPoint(srcBottomPoint);
	Dest->GetBottomPoint(destBottomPoint);

	// 각각의 사각형의 점을 기반으로 네 변을 구성
	LinePoint srcLinePoint[4];
	srcLinePoint[0].Point[0] = srcBottomPoint[0];
	srcLinePoint[0].Point[1] = srcBottomPoint[1];

	srcLinePoint[1].Point[0] = srcBottomPoint[1];
	srcLinePoint[1].Point[1] = srcBottomPoint[2];

	srcLinePoint[2].Point[0] = srcBottomPoint[2];
	srcLinePoint[2].Point[1] = srcBottomPoint[3];

	srcLinePoint[3].Point[0] = srcBottomPoint[3];
	srcLinePoint[3].Point[1] = srcBottomPoint[0];

	LinePoint destLinePoint[4];
	destLinePoint[0].Point[0] = destBottomPoint[0];
	destLinePoint[0].Point[1] = destBottomPoint[1];

	destLinePoint[1].Point[0] = destBottomPoint[1];
	destLinePoint[1].Point[1] = destBottomPoint[2];

	destLinePoint[2].Point[0] = destBottomPoint[2];
	destLinePoint[2].Point[1] = destBottomPoint[3];

	destLinePoint[3].Point[0] = destBottomPoint[3];
	destLinePoint[3].Point[1] = destBottomPoint[0];

	std::vector<Vector2> vecIntersectPoint;
	std::vector<LinePoint> vecSrcHitline;
	std::vector<LinePoint> vecDestHitline;

	// Src와 Dest의 선분들 중 교차점을 판단 (얘 나중에 시선 벡터에 수직인 선분으로 바꾸기)
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			Vector2 IntersectPoint;

			// Vector3 -> Vector2 로 변경
			Vector2 PointSrc1 = srcLinePoint[i].GetPointVector3ToVector2()[0];
			Vector2 PointSrc2 = srcLinePoint[i].GetPointVector3ToVector2()[1];
			Vector2 PointDest1 = destLinePoint[j].GetPointVector3ToVector2()[0];
			Vector2 PointDest2 = destLinePoint[j].GetPointVector3ToVector2()[1];

			if (Vector2::GetIntersectPoint(PointSrc1, PointSrc2, PointDest1, PointDest2, IntersectPoint))
			{
				// 히트 포인트 저장
				vecIntersectPoint.push_back(IntersectPoint);

				bool srcLineSave = true;
				bool destLineSave = true;

				// 부딪친 선분의 정보를 저장
				if (vecSrcHitline.size() > 0)
				{
					for (size_t index = 0; index < vecSrcHitline.size(); ++index)
					{
						// 벡터 안에 이미 정보가 저장되어 있을 경우 해당 성분은 중첩 (저장할 필요 x)
						if (vecSrcHitline[index].Point[0] == srcLinePoint[i].Point[0] &&
							vecSrcHitline[index].Point[1] == srcLinePoint[i].Point[1])
						{
							srcLineSave = false;
							break;
						}
					}
				}

				if (vecDestHitline.size() > 0)
				{
					for (size_t index = 0; index < vecDestHitline.size(); ++index)
					{
						if (vecDestHitline[index].Point[0] == destLinePoint[j].Point[0] &&
							vecDestHitline[index].Point[1] == destLinePoint[j].Point[1])
						{
							// 하나라도 겹치는 경우 
							destLineSave = false;
							break;
						}
					}
				}

				if (srcLineSave)
					vecSrcHitline.push_back(srcLinePoint[i]);

				if (destLineSave)
					vecDestHitline.push_back(destLinePoint[j]);
			}
		}
	}

	std::vector<Vector3> vecPlaneNormal;
	std::vector<LinePoint> vecDetectedLine;

	for (int i = 0; i < vecSrcHitline.size(); ++i)
	{
		// 부딪친 선분이 바라보는 방향을 구함.
		// 바닥 면의 네 변을 기준으로 면이 바라보는 방향을 구해서 저장
		Vector3 TopHorizontalLine = vecSrcHitline[i].Point[1] - vecSrcHitline[i].Point[0];
		Vector3 TopStartPoint = vecSrcHitline[i].Point[0];
		TopStartPoint.y += Src->GetInfo().Length[AXIS_Y] * 2;			// Y축 올려줌

		// 수직 방향 벡터 (상단 시작점에서 수직 방향으로 가는 선분)
		Vector3 VerticalLine = vecSrcHitline[i].Point[0] - TopStartPoint;
		Vector3 PlaneNormal = TopHorizontalLine.Cross(VerticalLine);
		PlaneNormal.Normalize();

		vecPlaneNormal.push_back(PlaneNormal);
	}
	
	// 여러 충돌체가 닿을 경우 블락의 진행 방향을 바꿔야함 (오히려 이상할것같음. 그냥 튕겨내기) 
	size_t CollisionCount = Dest->GetPrevCollisionList().size();
	if (CollisionCount > 1)
	{
		Dest->GetOwner()->SetWorldPos(Dest->GetPrevWorldPos());
		return;
	}


	if (vecPlaneNormal.size() > 0 )
	{

		// 플레이어의 정면 벡터 (입사 벡터)
		Vector3 DestFowardVector = (Dest->GetOwner()->GetAxis(AXIS_Z));
		Vector3 PlaneNormal = vecPlaneNormal[0];

		// 현재 플레이어의 z축이 뒤집혀 있음
		// 축이 뒤집혀있는게 아닌 방향이 뒤집혀있었음
		// 
		//DestFowardVector.z *= -1.f;
		//PlaneNormal.z *= -1.f;
		DestFowardVector *= -1.f;
		//PlaneNormal.z *= -1.f;

		//DestFowardVector.x *= -1.f;
		//PlaneNormal.x *= -1.f;

		Vector3 ProjVector = PlaneNormal * (DestFowardVector.Dot(PlaneNormal));
		Vector3 SlidingVector = DestFowardVector + PlaneNormal * (-DestFowardVector.Dot(PlaneNormal));

		// 입력이 없을 경우 완전 밀어내버림
		if (!CInput::GetInst()->IsAnyInput())
		{
			SlidingVector = DestFowardVector + PlaneNormal * 2.f * (-DestFowardVector.Dot(PlaneNormal));
		}

		Vector3 SlidingPos = Dest->GetPrevWorldPos() + (SlidingVector * 5.f * fDeltaTime);
		Dest->GetOwner()->SetWorldPos(SlidingPos);

	
	}
}

bool CCollision::GetSeparatingAxis(const Vector3& CenterDir, const Vector3 Plane, const Box3DInfo& Src, const Box3DInfo& Dest)
{
	float CenterDot = abs(CenterDir.Dot(Plane));

	return (CenterDot >
		(abs((Src.Axis[AXIS_X].Dot(Plane)) * Src.Length[AXIS_X]) +
			abs((Src.Axis[AXIS_Y].Dot(Plane)) * Src.Length[AXIS_Y]) +
			abs((Src.Axis[AXIS_Z].Dot(Plane)) * Src.Length[AXIS_Z]) +
			abs((Dest.Axis[AXIS_X].Dot(Plane)) * Dest.Length[AXIS_X]) +
			abs((Dest.Axis[AXIS_Y].Dot(Plane)) * Dest.Length[AXIS_Y]) +
			abs((Dest.Axis[AXIS_Z].Dot(Plane)) * Dest.Length[AXIS_Z])));
}
