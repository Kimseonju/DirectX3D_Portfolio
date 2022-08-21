
#include "Camera.h"
#include "../Render/RenderManager.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Device.h"
#include "../Scene/LightManager.h"
#include "LightComponent.h"

CCamera::CCamera()
{
	m_SceneComponentType = SceneComponent_Type::Camera;
	m_CameraType = Camera_Type::Cam3D;

	m_ViewAngle = 90.f;
	m_Distance = 1000.f;
	m_CameraLeft = 0.f;
	m_CameraBottom = 0.f;

	SetTransformState(Transform_State::None);
}

CCamera::CCamera(const CCamera& com) :
	CSceneComponent(com)
{
	m_CameraType = com.m_CameraType;
	m_ViewAngle = com.m_ViewAngle;
	m_Distance = com.m_Distance;
	m_matView = com.m_matView;
	m_matProj = com.m_matProj;
	m_CameraLeft = com.m_CameraLeft;
	m_CameraBottom = com.m_CameraBottom;
	m_ShadowTargetLight = com.m_ShadowTargetLight;
}

CCamera::~CCamera()
{
}

void CCamera::SetShadowTargetLight(CLightComponent* Light)
{
	m_ShadowTargetLight = Light;
}

Vector2 CCamera::WorldToScreen(const Vector3& Pos)
{
	Vector3 toTarget = (GetWorldPos() - Pos);
	toTarget.Normalize();

	float Dot = toTarget.Dot(GetAxis(AXIS_Z));

	if (Dot > 0.f)
	{
		return Vector2::Infinity;
	}
	Matrix matVP = m_matView * m_matProj;

	Vector4 vPos = Vector4(Pos.x, Pos.y, Pos.z, 1.0f).TransformCoord(matVP.m);
	Vector3 vProjection(vPos.x / vPos.w, vPos.y / vPos.w, vPos.z / vPos.w);

	Resolution  RS = CDevice::GetInst()->GetResolution();
	if (vProjection.x > 1.0f)
		return Vector2::Infinity;
	if (vProjection.x < -1.0f)
		return Vector2::Infinity;
	if (vProjection.y > 1.0f)
		return Vector2::Infinity;
	if (vProjection.y < -1.0f)
		return Vector2::Infinity;
	if (vProjection.z < 0.0f)
		return Vector2::Infinity;

	Vector2 vView((vProjection.x * 0.5f) + 0.5f, (vProjection.y * 0.5f) + 0.5f);
	return Vector2(vView.x * (float)RS.Width, (vView.y) * (float)RS.Height);
}

void CCamera::CreateProjectionMatrix()
{
	Resolution  RS = CDevice::GetInst()->GetResolution();

	switch (m_CameraType)
	{
	case Camera_Type::Cam3D:
	{
		float	Angle = XMConvertToRadians(m_ViewAngle);

		m_matProj = XMMatrixPerspectiveFovLH(Angle,
			RS.Width / (float)RS.Height, 0.1f, m_Distance);

		// 그림자 맵 용 투영행렬
		m_matShadowProj = XMMatrixPerspectiveFovLH(PI / 2.f, 1.f, 0.1f, m_Distance);
	}
		break;
	case Camera_Type::Cam2D:
	case Camera_Type::CamUI:
	{
		m_matProj = XMMatrixOrthographicOffCenterLH(0.f, (float)RS.Width, 0.f, (float)RS.Height,
			0.f, m_Distance);
	}
		break;
	}
}

void CCamera::Start()
{
	CSceneComponent::Start();

	CreateProjectionMatrix();

	m_RS = CDevice::GetInst()->GetResolution();
}

bool CCamera::Init()
{
	if (!CSceneComponent::Init())
		return false;

	// 기본으로 글로벌라이트를 지정해둔다.

	return true;
}

void CCamera::Update(float DeltaTime)
{
	CSceneComponent::Update(DeltaTime);
	// 기본으로 글로벌라이트를 지정해둔다.
	m_ShadowTargetLight = m_pScene->GetLightManager()->GetGlobalLightComponent();

	Resolution  RS = CDevice::GetInst()->GetResolution();

	m_CameraBottom = GetWorldPos().y - RS.Height / 2.f;
	m_CameraLeft = GetWorldPos().x - RS.Width / 2.f;

	//if ((GetAsyncKeyState(VK_NUMPAD9) & 0x8000))
	//{
	//	StartShake(0.01f, 0.01f, 2.f);
	//}
}

void CCamera::PostUpdate(float DeltaTime)
{
	CSceneComponent::PostUpdate(DeltaTime);

	m_matView.Identity();

	for (int i = 0; i < AXIS_END; ++i)
	{
		Vector3	Axis = GetAxis((AXIS)i);
		memcpy(&m_matView[i][0], &Axis, sizeof(Vector3));
	}

	// 회전부분을 전치해서 최종 View의 회전으로 만들어준다.
	m_matView.Transpose();

	for (int i = 0; i < AXIS_END; ++i)
	{
		Vector3	Axis = GetAxis((AXIS)i);
		Vector3	Pos = GetWorldPos();

		Pos += UpdateShake(DeltaTime);
		Pos = Pos * -1.f;

		m_matView[3][i] = Axis.Dot(Pos);
	}

	if (m_ShadowTargetLight)
	{
		m_matShadowView.Identity();

		//Vector3	LightPos = (GetWorldPos() + m_ShadowTargetLight->GetWorldPos() ;
		Vector3	LightPos = (m_ShadowTargetLight->GetWorldPos() + m_ShadowTargetLight->GetAxis(AXIS_Z) * -10.f);
		Vector3	Axis[AXIS_END] = {};

		Axis[AXIS_Y] = Vector3(0.f, 1.f, 0.f);

		Axis[AXIS_X] = Axis[AXIS_Y].Cross(m_ShadowTargetLight->GetAxis(AXIS_Z));
		Axis[AXIS_X].Normalize();

		Axis[AXIS_Y] = m_ShadowTargetLight->GetAxis(AXIS_Z).Cross(Axis[AXIS_X]);
		Axis[AXIS_Y].Normalize();

		Axis[AXIS_Z] = m_ShadowTargetLight->GetAxis(AXIS_Z);

		for (int i = 0; i < AXIS_END; ++i)
		{
			memcpy(&m_matShadowView[i][0], &Axis[i], sizeof(Vector3));
		}

		// 회전부분을 전치해서 최종 View의 회전으로 만들어준다.
		m_matShadowView.Transpose();

		for (int i = 0; i < AXIS_END; ++i)
		{
			m_matShadowView[3][i] = Axis[i].Dot(LightPos * -1.f);
		}
	}

	/*
	1 0 0 0
	0 1 0 0 
	0 0 1 0
	-x -y -z 1

	Xx Yx Zx 0
	Xy Yy Zy 0
	Xz Yz Zz 0
	0  0  0  1

	Xx Yx Zx 0
	Xy Yy Zy 0
	Xz Yz Zz 0
	-P.X -P.Y -P.Z 1


	WorldCameraAxisX * ViewMatrix = 1, 0, 0
	WorldCameraAxisY * ViewMatrix = 0, 1, 0
	WorldCAmeraAxisZ * ViewMatrix = 0, 0, 1

	Xx Xy Xz   Xx Yx Zx    1 0 0
	Yx Yy Yz * Xy Yy Zy = 0 1 0
	Zx Zy Zz   Xz Yz Zz    0 0 1

	서로 정직교 하는 행렬을 직교행렬이라고 한다.
	직교행렬은 전치행렬과 역행렬이 같다.
	*/
}

void CCamera::Collision(float DeltaTime)
{
	CSceneComponent::Collision(DeltaTime);
}

void CCamera::PrevRender(float DeltaTime)
{
	CSceneComponent::PrevRender(DeltaTime);
}

void CCamera::Render(float DeltaTime)
{
	CSceneComponent::Render(DeltaTime);
}

CCamera* CCamera::Clone()
{
	return new CCamera(*this);
}


void CCamera::StartShake(float fAmplitude, float fFrequency, float fTime)
{
	m_Shake = true;
	m_ShakeAmplitude = fAmplitude;
	m_ShakeFrequency = fFrequency;
	m_ShakeTimeMax = fTime;
	m_ShakeTime = 0.0f;
}
void CCamera::EndShake()
{
	m_Shake = false;
	m_ShakeAmplitude = 0.0f;
	m_ShakeFrequency = 0.0f;
	m_ShakeTime = 0.0f;
}
Vector3 CCamera::UpdateShake(float DeltaTime)
{
	if (m_Shake)
	{
		m_ShakeTime += DeltaTime;
		float Progress = m_ShakeTime / m_ShakeTimeMax;
		float Magnitude = (sinf(m_ShakeTime * m_ShakeFrequency) * m_ShakeAmplitude) * 
			(1.0f - Progress);

		if (Progress >= 1.0f)
		{
			m_ShakeAmplitude = 0.0f;
			m_ShakeFrequency = 0.0f;
			m_ShakeTime = 0.0f;
			m_Shake = false;
		}
		return Vector3::GetRandomDir() * Magnitude;
	}
	else
		return Vector3::Zero;
}

