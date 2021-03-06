
#include "Component.h"

CComponent::CComponent()
{
    m_ClassType = Component_Class_Type::Default;
}

CComponent::CComponent(const CComponent& com)
{
}

CComponent::~CComponent()
{
}

void CComponent::Active(bool bActive)
{
    CRef::Active(bActive);
}

void CComponent::Start()
{
}

bool CComponent::Init()
{
    return true;
}

void CComponent::Update(float DeltaTime)
{
}

void CComponent::PostUpdate(float DeltaTime)
{
}

void CComponent::Collision(float DeltaTime)
{
}

void CComponent::PrevRender(float DeltaTime)
{
}

void CComponent::Render(float DeltaTime)
{
}

void CComponent::RenderDebug(float DeltaTime)
{
}

void CComponent::Save(FILE* pFile)
{
	fwrite(&m_ClassType, sizeof(Component_Class_Type), 1, pFile);
}

void CComponent::Load(FILE* pFile)
{
}
