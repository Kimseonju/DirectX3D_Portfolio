#include "TornadoTrailObject.h"
#include "Resource/BoneSocket.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "../PublicData.h"
#include "PlayerAttCol.h"
CTornadoTrailObject::CTornadoTrailObject()
{

}

CTornadoTrailObject::CTornadoTrailObject(const CTornadoTrailObject& obj) :
	CClientObject(obj)
{
}

CTornadoTrailObject::~CTornadoTrailObject()
{
}

void CTornadoTrailObject::Start()
{
	CClientObject::Start();
}

bool CTornadoTrailObject::Init()
{
	if (!CClientObject::Init())
		return false;
	m_SceneComponent = CreateSceneComponent<CSceneComponent>("SceneComponent");
	m_TornadoTrailComponent = CreateSceneComponent<CTornadoTrailComponent>("TornadoTrailComponent");
	m_TornadoTrailComponent2 = CreateSceneComponent<CTornadoTrailComponent>("TornadoTrailComponent2");
	m_TornadoTrailComponent3 = CreateSceneComponent<CTornadoTrailComponent>("TornadoTrailComponent3");
	m_TornadoTrailComponent4 = CreateSceneComponent<CTornadoTrailComponent>("TornadoTrailComponent4");


	SetRootComponent(m_SceneComponent);
	m_RootComponent->AddChild(m_TornadoTrailComponent);
	CMaterial* Mtrl = m_pScene->GetResource()->FindMaterial("TornadoTrail");
	m_TornadoTrailComponent->AddMaterial(Mtrl);
	m_TornadoTrailComponent->SetSize(0.3f);
	m_TornadoTrailComponent->Enable(true);
	m_TornadoTrailComponent->SetInheritRotY(true);
	m_TornadoTrailComponent->SetInheritRotX(true);
	m_TornadoTrailComponent->SetInheritRotZ(true);


	m_RootComponent->AddChild(m_TornadoTrailComponent2);
	Mtrl = m_pScene->GetResource()->FindMaterial("TornadoTrail");
	m_TornadoTrailComponent2->AddMaterial(Mtrl);
	m_TornadoTrailComponent2->SetSize(0.5f);
	m_TornadoTrailComponent2->Enable(true);
	m_TornadoTrailComponent2->SetInheritRotY(true);
	m_TornadoTrailComponent2->SetInheritRotX(true);
	m_TornadoTrailComponent2->SetInheritRotZ(true);
	m_TornadoTrailComponent2->SetRelativeRotationY(90.f);
	m_TornadoTrailComponent2->Enable(true);
	//
	m_RootComponent->AddChild(m_TornadoTrailComponent3);
	Mtrl = m_pScene->GetResource()->FindMaterial("TornadoTrail");
	m_TornadoTrailComponent3->AddMaterial(Mtrl);
	m_TornadoTrailComponent3->SetSize(0.5f);
	m_TornadoTrailComponent3->Enable(true);
	m_TornadoTrailComponent3->SetInheritRotY(true);
	m_TornadoTrailComponent3->SetInheritRotX(true);
	m_TornadoTrailComponent3->SetInheritRotZ(true);
	m_TornadoTrailComponent3->SetRelativeRotationY(180.f);
	m_TornadoTrailComponent3->Enable(true);
	//
	m_RootComponent->AddChild(m_TornadoTrailComponent4);
	Mtrl = m_pScene->GetResource()->FindMaterial("TornadoTrail");
	m_TornadoTrailComponent4->AddMaterial(Mtrl);
	m_TornadoTrailComponent4->SetSize(0.5f);
	m_TornadoTrailComponent4->Enable(true);
	m_TornadoTrailComponent4->SetInheritRotY(true);
	m_TornadoTrailComponent4->SetInheritRotX(true);
	m_TornadoTrailComponent4->SetInheritRotZ(true);
	m_TornadoTrailComponent4->SetRelativeRotationY(270.f);
	m_TornadoTrailComponent4->Enable(true);
	return true;
}

void CTornadoTrailObject::Update(float DeltaTime)
{
	CClientObject::Update(DeltaTime);
	AddWorldRotationY(DeltaTime * 720.f);
}

void CTornadoTrailObject::PostUpdate(float DeltaTime)
{
	CClientObject::PostUpdate(DeltaTime);
}

void CTornadoTrailObject::Collision(float DeltaTime)
{
	CClientObject::Collision(DeltaTime);
}

void CTornadoTrailObject::Render(float DeltaTime)
{
	CClientObject::Render(DeltaTime);
}

CTornadoTrailObject* CTornadoTrailObject::Clone()
{
	return new CTornadoTrailObject(*this);
}

