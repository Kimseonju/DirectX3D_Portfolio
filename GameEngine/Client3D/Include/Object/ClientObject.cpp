#include "ClientObject.h"

CClientObject::CClientObject()
{
	m_ObjectType = Object_Type::Client;
	m_ClientClassType = ClientClassType::Default;
}

CClientObject::CClientObject(const CClientObject& obj):
	CGameObject(obj)
{
	m_ObjectType = obj.m_ObjectType;
	m_ClientClassType = obj.m_ClientClassType;
}

CClientObject::~CClientObject()
{
}

void CClientObject::Start()
{
	CGameObject::Start();
}

bool CClientObject::Init()
{
	if (!CGameObject::Init())
		return false;
	return true;
}

void CClientObject::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CClientObject::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CClientObject::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CClientObject::PrevRender(float DeltaTime)
{
	CGameObject::PrevRender(DeltaTime);
}

void CClientObject::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CClientObject* CClientObject::Clone()
{
	return new CClientObject(*this);
}

void CClientObject::CameraAction()
{
}

void CClientObject::Save(FILE* pFile)
{
	CGameObject::Save(pFile);
}

void CClientObject::Load(FILE* pFile)
{
	CGameObject::Load(pFile);
}
