
#include "Viewport.h"

CViewport::CViewport()	:
	m_Camera(nullptr),
	m_Scene(nullptr)
{
}

CViewport::~CViewport()
{

}

void CViewport::Start()
{
	auto	iter = m_vecWindow.begin();
	auto	iterEnd = m_vecWindow.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->Start();
	}
}

bool CViewport::Init()
{
	m_Camera = new CCamera;

	m_Camera->SetName("UICamera");
	m_Camera->m_pScene = m_Scene;

	m_Camera->Init();
	m_Camera->SetCameraType(Camera_Type::CamUI);

	m_Camera->Release();

	return true;
}

void CViewport::Update(float DeltaTime)
{
	auto iter = m_vecWindow.begin();
	auto iterEnd = m_vecWindow.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = m_vecWindow.erase(iter);
			iterEnd = m_vecWindow.end();
			continue;
		}
		(*iter)->Update(DeltaTime);
		++iter;
	}
}

void CViewport::PostUpdate(float DeltaTime)
{

	auto iter = m_vecWindow.begin();
	auto iterEnd = m_vecWindow.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = m_vecWindow.erase(iter);
			iterEnd = m_vecWindow.end();
			continue;
		}
		(*iter)->PostUpdate(DeltaTime);
		++iter;
	}
}

void CViewport::Render()
{


	auto	iter = m_vecWindow.begin();
	auto	iterEnd = m_vecWindow.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->Render();
	}
}
bool CViewport::SortZOrder(CSharedPtr<CWidgetWindow> Src, CSharedPtr<CWidgetWindow> Dest)
{
	int	SrcZ = Src->GetZOrder();
	int	DestZ = Dest->GetZOrder();

	return SrcZ < DestZ;
}
