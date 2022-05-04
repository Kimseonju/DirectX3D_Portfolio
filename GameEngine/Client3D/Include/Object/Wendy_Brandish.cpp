
#include "Wendy_Brandish.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Resource/Material.h"
#include "../PublicData.h"
#include "Resource/BoneSocket.h"
#include "Player.h"
#include "KnifeEffect.h"
CWendyBrandish::CWendyBrandish() :
	m_Setting(false),
	m_Coll(false),
	m_Wendy(nullptr),
	m_Timer(2.8f),
	m_DeltaTime(0.f),
	m_FirstAttack(false),
	m_Out(false)
{ 
}
 
CWendyBrandish::CWendyBrandish(const CWendyBrandish& obj) : CAttackObject(obj)
{
}

CWendyBrandish::~CWendyBrandish()
{
}

void CWendyBrandish::CollisionBegin(const HitResult& result, CCollider* Collider)
{
}

void CWendyBrandish::CollisionMiddle(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Name == "Player")
	{
		{
			CKnifeEffect* HitEffect = m_pScene->SpawnObject<CKnifeEffect>("HitEffect");
			Vector3	Dir = (result.DestObject->GetWorldPos() + (result.DestObject->GetWorldScale() * 0.5f));
			HitEffect->SetWorldPos(Dir);
			HitEffect->SetWendyAtt();
		}
		m_pScene->GetResource()->FindSound3D("Wendy_Brandish_Hit")->Play3D(GetWorldPos());
		m_Box->Enable(false);
	}
}

void CWendyBrandish::CollisionEnd(const HitResult& result, CCollider* Collider)
{
}

void CWendyBrandish::Start()
{
	CAttackObject::Start();
}

bool CWendyBrandish::Init()
{
	CAttackObject::Init();

	m_Box->Enable(true);
	m_Sphere->Enable(false);
	m_Box->SetWorldPos(Vector3::Zero);
	m_Box->SetExtent(1.f, 0.2f, 0.8f);
	m_Box->SetCollisionProfile("MonsterAttack");

	{
		m_Texture = CreateSceneComponent<CBillboardComponent>("BillboardComponent");
		m_Root->AddChild(m_Texture);
		m_Texture->SetInheritRotX(true);
		m_Texture->SetInheritRotY(true);
		m_Texture->SetInheritRotZ(true);
		m_Texture->AddMaterial("Wendy_Brandish");
		m_Texture->AddWorldRotationX(90.f);
		//m_Texture->AddWorldRotationX(90.f);
		m_Texture->SetBillboardEnable(false);
		m_Texture->SetWorldScale(Vector3::One * 2.f);
		m_Texture->GetMaterial(0)->SetTransparency(true);
	}
	{
		m_TextureBack = CreateSceneComponent<CBillboardComponent>("BillboardComponent");
		m_Texture->AddChild(m_TextureBack);
		m_TextureBack->SetInheritRotX(true);
		m_TextureBack->SetInheritRotY(true);
		m_TextureBack->SetInheritRotZ(true);
		m_TextureBack->AddMaterial("Wendy_Brandish");
		m_TextureBack->SetWorldRotation(m_Texture->GetWorldRotation());
		m_TextureBack->AddWorldRotationX(180.f);
		//m_TextureBack->AddWorldRotationY(180.f);
		m_TextureBack->SetBillboardEnable(false);
		m_TextureBack->SetWorldScale(Vector3::One * 2.f);
		m_TextureBack->GetMaterial(0)->SetTransparency(true);
	}


	m_TextureBack->GetMaterial(0)->SetOpacity(1.f);
	m_Texture->GetMaterial(0)->SetOpacity(1.f);

	SetDamage(30);
	SetDamageMax(50);

	return true;
}

void CWendyBrandish::Update(float DeltaTime)
{
	CAttackObject::Update(DeltaTime);
	m_DeltaTime = DeltaTime;

	if (!m_Setting)
	{
		SetWorldPos(m_Wendy->GetWorldPos());
		SetWorldRotation(m_Wendy->GetWorldRotation());

		if (m_FirstAttack)
			AddWorldRotationX(-45.f);
		else
			AddWorldRotationX(45.f);

		AddWorldRotationY(90.f);
		AddWorldPos(0.f, 1.f, 0.f);
		m_Setting = true;
	}

	//if (1.f <= m_Texture->GetMaterial(0)->GetOpacity() && !m_Out)
	//{
	//	m_Out = true;	
	//	m_TextureBack->GetMaterial(0)->SetOpacity(1.f);
	//	m_Texture->GetMaterial(0)->SetOpacity(1.f);
	//}
	//if (!m_Out)
	//{
	//	m_TextureBack->GetMaterial(0)->AddOpacity(DeltaTime * 5.f);
	//	m_Texture->GetMaterial(0)->AddOpacity(DeltaTime * 5.f);
	//}
	//else

	AddWorldPos(GetAxis(AXIS_X) * 10.f * DeltaTime);
	{
		m_TextureBack->GetMaterial(0)->AddOpacity(-DeltaTime * 2.f);
		m_Texture->GetMaterial(0)->AddOpacity(-DeltaTime * 2.f);
	}
	if (0.f >= m_Texture->GetMaterial(0)->GetOpacity())
	{
		this->Active(false);
	}
}

void CWendyBrandish::PostUpdate(float DeltaTime)
{
	CAttackObject::PostUpdate(DeltaTime);
}

void CWendyBrandish::Collision(float DeltaTime)
{
	CAttackObject::Collision(DeltaTime);
}

void CWendyBrandish::Render(float DeltaTime)
{
	CAttackObject::Render(DeltaTime);
}

CWendyBrandish* CWendyBrandish::Clone()
{
	return new CWendyBrandish(*this);
}
