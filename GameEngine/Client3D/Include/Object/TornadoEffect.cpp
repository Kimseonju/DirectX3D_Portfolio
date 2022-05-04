#include "TornadoEffect.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Resource/Material.h"

CTornadoEffect::CTornadoEffect()
{
}

CTornadoEffect::CTornadoEffect(const CTornadoEffect& obj) : CClientObject(obj)
{
}

CTornadoEffect::~CTornadoEffect()
{
	m_TornadoTrail->Active(false);
	m_Dust->Active(false);
}

void CTornadoEffect::Start()
{
	CClientObject::Start();
}

bool CTornadoEffect::Init()
{
	CClientObject::Init();
	
	m_TornadoTrail = m_pScene->SpawnObject<CTornadoTrailObject>("TornadoTrail");
	m_TornadoTrail->SetWorldPos(GetWorldPos());
	m_TornadoTrail->AddWorldPos(0.f, -0.7f, 0.f);
	m_Dust = m_pScene->SpawnObject<CTestParticle>("obj");
	{
		m_Effect1 = CreateSceneComponent<CBillboardComponent>("Billboard");
		SetRootComponent(m_Effect1);
		m_Effect1->SetBillboardEnable(false);
		CMaterial* Mtrl = m_pScene->GetResource()->FindMaterial("Tornado_01");
		Mtrl->SetShader("BillboardShader");
		m_Effect1->AddMaterial(Mtrl);
		m_Effect1->SetWorldScale(4.f, 4.f, 4.f);
		m_Effect1->SetWorldRotationX(90.f);
		m_Effect1->AddWorldPos(0.f, 0.f, 0.f);
	}
	{
		m_Bill = CreateSceneComponent<CBillboardComponent>("Billboard");
		m_Effect1->AddChild(m_Bill);
		m_Bill->SetBillboardEnable(false);
		CMaterial* Mtrl = m_pScene->GetResource()->FindMaterial("AirHole_Wind_Black");
		Mtrl->SetShader("BillboardShader");
		m_Bill->AddMaterial(Mtrl);
		m_Bill->SetWorldScale(4.f, 4.f, 4.f);
		m_Bill->AddWorldPos(0.f, 0.f, 0.f);
		m_Bill->SetWorldRotationX(90.f);
	}
	{
		m_Effect2 = CreateSceneComponent<CBillboardComponent>("Billboard");
		m_Effect1->AddChild(m_Effect2);
		m_Effect2->SetBillboardEnable(false);
		CMaterial* Mtrl = m_pScene->GetResource()->FindMaterial("Tornado_02");
		Mtrl->SetShader("BillboardShader");
		Mtrl->SetOpacity(0.5f);
		Mtrl->SetBaseColor(0.8f, 0.8f, 0.8f, 0.8f);
		m_Effect2->AddMaterial(Mtrl);
		m_Effect2->SetWorldScale(5.f, 5.f, 5.f);
		m_Effect2->AddWorldPos(0.f, 0.2f, 0.f);
		m_Effect2->SetWorldRotationX(90.f);
	}

	//{
	//	m_Effect3 = CreateSceneComponent<CBillboardComponent>("Billboard");
	//	SetRootComponent(m_Effect3);
	//	m_Effect3->SetBillboardEnable(false);
	//	CMaterial* Mtrl = m_pScene->GetResource()->FindMaterial("Tornado_02");
	//	Mtrl->SetShader("BillboardShader");
	//	m_Effect3->AddMaterial(Mtrl);
	//	m_Effect3->SetWorldScale(1.f, 1.f, 1.f);
	//}
	return true;
}

void CTornadoEffect::Update(float DeltaTime)
{
	CClientObject::Update(DeltaTime);

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
	}
	m_Dust->SetWorldPos(GetWorldPos());
	m_TornadoTrail->SetWorldPos(GetWorldPos());
	m_Effect1->AddWorldRotation(m_Effect1->GetAxis(AXIS_Z) * -1000.f * DeltaTime);
	m_Effect2->AddWorldRotation(m_Effect2->GetAxis(AXIS_Z) * -100.f * DeltaTime);
	m_Bill->AddWorldRotation(m_Bill->GetAxis(AXIS_Z) * -1000.f * DeltaTime);
}

void CTornadoEffect::PostUpdate(float DeltaTime)
{
	CClientObject::PostUpdate(DeltaTime);
}

void CTornadoEffect::Collision(float DeltaTime)
{
	CClientObject::Collision(DeltaTime);
}

void CTornadoEffect::Render(float DeltaTime)
{
	CClientObject::Render(DeltaTime);
}

CTornadoEffect* CTornadoEffect::Clone()
{
	return new CTornadoEffect(*this);
}
