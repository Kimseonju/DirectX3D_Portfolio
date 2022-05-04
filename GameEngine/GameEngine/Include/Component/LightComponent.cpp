
#include "LightComponent.h"
#include "../Scene/Scene.h"
#include "../Scene/LightManager.h"
#include "../Scene/CameraManager.h"
#include "Camera.h"

CLightComponent::CLightComponent()
{
	m_SceneComponentType = SceneComponent_Type::Light;
	m_CBuffer = nullptr;
	m_ClassType = Component_Class_Type::Light;
	SetTransformState(Transform_State::None);
}

CLightComponent::CLightComponent(const CLightComponent& com) :
	CSceneComponent(com)
{
	m_CBuffer = com.m_CBuffer->Clone();
}

CLightComponent::~CLightComponent()
{
	SAFE_DELETE(m_CBuffer);
}

void CLightComponent::Start()
{
	CSceneComponent::Start();


}

bool CLightComponent::Init()
{
	if (!CSceneComponent::Init())
		return false;

	// 상수버퍼 생성
	m_CBuffer = new CLightConstantBuffer;

	m_CBuffer->Init();

	m_pScene->GetLightManager()->AddLight(this);
	return true;
}

void CLightComponent::Update(float DeltaTime)
{
	CSceneComponent::Update(DeltaTime);

	if (GetOwner()->GetName() == "GlobalLight")
	{
		m_pScene->GetLightManager()->SetGlobalLightComponent(this);
		m_pScene->GetLightManager()->SetGlobalLight(GetOwner());
	}
}

void CLightComponent::PostUpdate(float DeltaTime)
{
	CSceneComponent::PostUpdate(DeltaTime);

	CCamera* Camera = m_pScene->GetCameraManager()->GetCurrentCamera();

	if (m_CBuffer->GetLightType() != Light_Type::Dir)
	{
		// 현재 이 조명의 위치는 월드공간에서의 위치이다. 이를 뷰 공간으로 바꿔서
		// 넘겨준다.
		Vector3	Pos = GetWorldPos();

		Pos = Pos.TransformCoord(Camera->GetViewMatrix());

		m_CBuffer->SetPos(Pos);

		if (m_CBuffer->GetLightType() == Light_Type::Point)
			SetRelativeScale(m_CBuffer->GetLightDistance(), m_CBuffer->GetLightDistance(), m_CBuffer->GetLightDistance());
	}

	if (m_CBuffer->GetLightType() != Light_Type::Point)
	{
		Vector3	Dir = GetAxis(AXIS_Z);

		Dir = Dir.TransformNormal(Camera->GetViewMatrix());
		Dir.Normalize();

		m_CBuffer->SetDir(Dir);
	}
}

void CLightComponent::Collision(float DeltaTime)
{
	CSceneComponent::Collision(DeltaTime);
}

void CLightComponent::PrevRender(float DeltaTime)
{
	CSceneComponent::PrevRender(DeltaTime);
}

void CLightComponent::Render(float DeltaTime)
{
	CSceneComponent::Render(DeltaTime);
}

CLightComponent* CLightComponent::Clone()
{
	return new CLightComponent(*this);
}

void CLightComponent::SetShader()
{
	m_CBuffer->UpdateCBuffer();
}

void CLightComponent::Save(FILE* pFile)
{
	CSceneComponent::Save(pFile);
	Light_Type Type = m_CBuffer->GetLightType();
	fwrite(&Type, sizeof(Light_Type), 1, pFile);
	Vector4 Diffuse = m_CBuffer->GetDiffuse();
	fwrite(&Diffuse, sizeof(Vector4), 1, pFile);
	Vector4 Ambient = m_CBuffer->GetAmbient();
	fwrite(&Ambient, sizeof(Vector4), 1, pFile);
	Vector4 Specular = m_CBuffer->GetSpecular();
	fwrite(&Specular, sizeof(Vector4), 1, pFile);

	Vector3 Dir = m_CBuffer->GetDir();
	fwrite(&Dir, sizeof(Vector3), 1, pFile);

	float Distance = m_CBuffer->GetDistance();
	fwrite(&Distance, sizeof(float), 1, pFile);

	float AngleIn = m_CBuffer->GetAngleIn();
	fwrite(&AngleIn, sizeof(float), 1, pFile);
	float AngleOut = m_CBuffer->GetAngleOut();
	fwrite(&AngleOut, sizeof(float), 1, pFile);
}

void CLightComponent::Load(FILE* pFile)
{
	CSceneComponent::Load(pFile);

	Light_Type Type = Light_Type::Dir;
	fread(&Type, sizeof(Light_Type), 1, pFile);
	m_CBuffer->SetLightType(Type);

	Vector4 Diffuse;
	fread(&Diffuse, sizeof(Vector4), 1, pFile);
	m_CBuffer->SetDiffuse(Diffuse);

	Vector4 Ambient;
	fread(&Ambient, sizeof(Vector4), 1, pFile);
	m_CBuffer->SetDiffuse(Diffuse);
	Vector4 Specular;
	fread(&Specular, sizeof(Vector4), 1, pFile);
	m_CBuffer->SetSpecular(Specular);

	Vector3 Dir;
	fread(&Dir, sizeof(Vector3), 1, pFile);
	m_CBuffer->SetDir(Dir);

	float Distance = 0.f;
	fread(&Distance, sizeof(float), 1, pFile);
	m_CBuffer->SetDistance(Distance);

	float AngleIn = 0.f;
	fread(&AngleIn, sizeof(float), 1, pFile);
	m_CBuffer->SetAngleIn(AngleIn);

	float AngleOut = 0.f;
	fread(&AngleOut, sizeof(float), 1, pFile);
	m_CBuffer->SetAngleOut(AngleOut);
}
