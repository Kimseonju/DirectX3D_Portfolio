#include "PlayerMainCamera.h"
#include "Player.h"
#include "../UI/UIManager.h"
#include "Custom/CollisionRay.h"
#include "../PublicData.h"
#include "Input.h"
#include "../StageManager.h"
#include "../UI/TargetImageWidget.h"
#include "../UI/UIManager.h"
CPlayerMainCamera::CPlayerMainCamera() :
	m_PrevTargetPos(-INT_MAX, -INT_MAX, -INT_MAX),
	m_Bool(false),
	m_MouseClick(false),
	m_Camera(nullptr),
	m_Target(nullptr)
{
	SetLength(2.f);
	SetOffset(0.f, 2.f, 0.f);

}

CPlayerMainCamera::CPlayerMainCamera(const CPlayerMainCamera& com)
	: CClientObject(com)
{
	m_Bool = com.m_Bool;
	m_PrevTargetPos = com.m_PrevTargetPos;
	m_MouseClick = com.m_MouseClick;
	m_Camera = com.m_Camera;
	m_Target = com.m_Target;
	m_Length = com.m_Length;
	m_Offset = com.m_Offset;
}

CPlayerMainCamera::~CPlayerMainCamera()
{
}

void CPlayerMainCamera::SetTarget(CPlayer* Target)
{
	m_Target = Target;

	SetWorldRotation(m_Target->GetWorldRotation());
	Vector3	TargetPos = m_Target->GetWorldPos();
	Vector3	Pos = TargetPos + m_Offset + m_Target->GetAxis(AXIS_Z) * m_Length;
	SetWorldPos(Pos);


	Vector3	Dir = TargetPos - GetWorldPos() - m_Offset;
	Dir.y = 0.f;
	Dir.Normalize();


	Vector3 v1 = Dir;
	Vector3 v2 = Vector3(0, 0, -1);

	v1.Normalize();
	v2.Normalize();

	float   Dot = v1.Dot(v2);

	float Angle = RadianToDegree(acosf(Dot));

	if (m_Target->GetWorldPos().x > GetWorldPos().x)
		Angle = 360.f - Angle;
	Vector3 Rot = GetWorldRotation();
	Vector3 NextRot = Rot;
	//카메라는 반대방향으로해야됨
	NextRot.y = Angle - 180.f;
	SetWorldRotation(NextRot);

}

void CPlayerMainCamera::Start()
{
	CClientObject::Start();
	SetTarget(CPublicData::GetInst()->GetCurPlayer());
}

bool CPlayerMainCamera::Init()
{
	if (!CClientObject::Init())
		return false;
	m_Camera = CreateSceneComponent<CCamera>("Player");
	SetRootComponent(m_Camera);
	m_Camera->SetTransformState(Transform_State::None);
	CInput::GetInst()->AddKeyCallback("ClientMouseRButton", Key_Type::KT_Push, this, &CPlayerMainCamera::MouseClick);
	CInput::GetInst()->AddKeyCallback("ClientMouseRButton", Key_Type::KT_Up, this, &CPlayerMainCamera::MouseRelease);
	CInput::GetInst()->AddKeyCallback("ClientMouseWHEEL", Key_Type::KT_Down, this, &CPlayerMainCamera::CameraWheel);
	return true;
}

void CPlayerMainCamera::Update(float DeltaTime)
{
	CClientObject::Update(DeltaTime);
	
	if (!m_Bool)
	{
		m_Bool = true;
		return;
	}
	m_Target = CPublicData::GetInst()->GetCurPlayer();
	m_MonsterTarget = m_Target->GetMonsterTarget();
	float Length = m_Length;
	if (m_MonsterTarget)
	{
		CTargetImageWidget* TargetImageWidget =(CTargetImageWidget*)CUIManager::GetInst()->FindWidgetWindow("TargetImageWidget");
		if (TargetImageWidget)
		{
			Vector3 Dir = GetWorldPos() - m_MonsterTarget->GetWorldPos();
			Vector3 Axis = GetAxis(AXIS_Y);
			float Length = (Dir).Length(); 
			Dir.Normalize();
			Vector3 MosnterTarget = m_MonsterTarget->GetWorldPos();
			MosnterTarget.y += 1.0f;


			Vector2 Pos=m_Camera->WorldToScreen(MosnterTarget);
			if (Pos != Vector2::Infinity)
			{
				TargetImageWidget->SetPos(Pos);
				TargetImageWidget->SetSizePercent(1.f / Length);
				TargetImageWidget->Enable(true);
			}
			else
			{
				TargetImageWidget->Enable(false);
			}
		}
	}
	else
	{
		CTargetImageWidget* TargetImageWidget = (CTargetImageWidget*)CUIManager::GetInst()->FindWidgetWindow("TargetImageWidget");
		if (TargetImageWidget)
		{
			TargetImageWidget->Enable(false);
		}

	}
	if (m_Target)
	{
		Vector3	TargetPos;
		Vector3	Dir;
		TargetPos = m_Target->GetWorldPos();

		if (m_MonsterTarget && m_MonsterTarget->IsEnable() && m_MonsterTarget->IsActive())
		{
		
			Length = (m_Target->GetWorldPos() - m_MonsterTarget->GetWorldPos()).Length()/2.f + 2.5f;
		}
		//Dir = TargetPos - GetWorldPos() - m_Offset;
		//Dir.y = 0.f;
		//Dir.Normalize();
		//
		//Vector3 v1 = Dir;
		//Vector3 v2 = Vector3(0, 0, -1);
		//
		//v1.Normalize();
		//v2.Normalize();
		//
		//float   Dot = v1.Dot(v2);
		//
		//float Angle = RadianToDegree(acosf(Dot));
		//
		//if (TargetPos.x > GetWorldPos().x)
		//{
		//	Angle = 360.f - Angle;
		//}
		//
		//Vector3 Velocity = m_Target->GetVelocity();
		//
		//if (!m_MouseClick)
		//{
		//	Vector3 Rot = GetWorldRotation();
		//	Vector3 NextRot = Rot;
		//	Vector3 RotLerp;
		//	NextRot.y = Angle - 180.f;
		//
		//	while (NextRot.y > 360.f)
		//	{
		//		NextRot.y -= 360.f;
		//	}
		//	while (NextRot.y < 0.f)
		//	{
		//		NextRot.y += 360.f;
		//	}
		//	SetWorldRotation(NextRot);
		//}
		
		

		Vector3 Pos = GetWorldPos();
		HitResult Result;
		if (CCollisionRay::GetInst()->LineTraceSingleByChannel(m_pScene, Result, GetWorldPos(), TargetPos + m_Offset + GetAxis(AXIS_Z) * -Length, "MapCollision"))
		{
			Length = (Result.HitPoint - GetWorldPos()).Length();
		}

		Vector3 NextPos = TargetPos + m_Offset + GetAxis(AXIS_Z) * -Length;
		if (!m_MouseClick)
		{
			NextPos = Vector3::Lerp3D(Pos, NextPos, DeltaTime * 7.f);
		}
		SetWorldPos(NextPos);

		m_PrevTargetPos = TargetPos;
	}
	//Vector2 MovePos = CInput::GetInst()->GetMouseMove();
	//
	//char	FPSLog[256] = {};
	//sprintf_s(FPSLog, "X : %.5f\n", MovePos.x);
	//OutputDebugStringA(FPSLog);
	//
	//sprintf_s(FPSLog, "Y : %.5f\n", MovePos.y);
	//OutputDebugStringA(FPSLog);
}

void CPlayerMainCamera::PostUpdate(float DeltaTime)
{
	CClientObject::PostUpdate(DeltaTime);
}

void CPlayerMainCamera::Collision(float DeltaTime)
{
	CClientObject::Collision(DeltaTime);
}

void CPlayerMainCamera::PrevRender(float DeltaTime)
{
	CClientObject::PrevRender(DeltaTime);
}

void CPlayerMainCamera::Render(float DeltaTime)
{
	CClientObject::Render(DeltaTime);
}

CPlayerMainCamera* CPlayerMainCamera::Clone()
{
	return new CPlayerMainCamera(*this);
}


void CPlayerMainCamera::CameraWheel(float Time)
{
	float Wheel=CInput::GetInst()->GetMouseWheel()*Time;
	m_Length += Wheel;
	if (m_Length < 1.f)
	{
		m_Length = 1.f;
	}
	if (m_Length > 4.f)
	{
		m_Length = 3.f;
	}
}

void CPlayerMainCamera::MouseClick(float Time)
{
	m_MouseClick = true;
	Vector2 MovePos = CInput::GetInst()->GetMouseMove();

	m_Camera->AddWorldRotationY(MovePos.x * Time * 20.f);
}

void CPlayerMainCamera::MouseRelease(float Time)
{
	m_MouseClick = false;
}