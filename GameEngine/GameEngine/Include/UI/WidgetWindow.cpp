
#include "WidgetWindow.h"
#include "../Scene/Viewport.h"

CWidgetWindow::CWidgetWindow()	:
	m_OwnerComponent(nullptr)
{
}

CWidgetWindow::CWidgetWindow(const CWidgetWindow& widget)	:
	CWidget(widget)
{
	m_OwnerComponent = widget.m_OwnerComponent;
}

CWidgetWindow::~CWidgetWindow()
{
}

void CWidgetWindow::SetZOrder(int ZOrder)
{
	CWidget::SetZOrder(ZOrder);

	auto	iter = m_vecWidget.begin();
	auto	iterEnd = m_vecWidget.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->SetZOrder(ZOrder);
	}
}

void CWidgetWindow::Start()
{
	CWidget::Start();

	auto	iter = m_vecWidget.begin();
	auto	iterEnd = m_vecWidget.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->Start();
	}
}

bool CWidgetWindow::Init()
{
	return true;
}

void CWidgetWindow::Update(float DeltaTime)
{
	CWidget::Update(DeltaTime);
	if (!m_Start)
		Start();

	auto	iter = m_vecWidget.begin();
	auto	iterEnd = m_vecWidget.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->IsStart())
			(*iter)->Start();
		if (!(*iter)->IsActive())
		{
			iter=m_vecWidget.erase(iter);
			iterEnd = m_vecWidget.end();
			continue;
		}
		(*iter)->Update(DeltaTime);
		iter++;
	}
}

void CWidgetWindow::PostUpdate(float DeltaTime)
{
	auto	iter = m_vecWidget.begin();
	auto	iterEnd = m_vecWidget.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = m_vecWidget.erase(iter);
			iterEnd = m_vecWidget.end();
			continue;
		}
		(*iter)->PostUpdate(DeltaTime);
		iter++;

	}
}

void CWidgetWindow::Render()
{
	// 정렬한다.

	if (!IsEnable())
		return;
	if (m_vecWidget.size() > 1)
	{
		//qsort(&m_vecWidget[0], m_vecWidget.size(), (size_t)sizeof(CSharedPtr<CWidget>),
		//	CWidgetWindow::SortZOrder);
		std::sort(m_vecWidget.begin(), m_vecWidget.end(),
			CWidgetWindow::SortZOrder);
	}

	auto	iter = m_vecWidget.begin();
	auto	iterEnd = m_vecWidget.end();

	for (; iter != iterEnd; ++iter)
	{

		if(!(*iter)->IsEnable())
			continue;
		(*iter)->Render();
	}
}

CWidgetWindow* CWidgetWindow::Clone()
{
	return new CWidgetWindow(*this);
}

void CWidgetWindow::CallAnimNotify(const std::string& Name)
{
}

//int CWidgetWindow::SortZOrder(const void* Src, const void* Dest)
//{
//	CWidget* SrcUI = *((CSharedPtr<CWidget>*)Src);
//	CWidget* DestUI = *((CSharedPtr<CWidget>*)Dest);
//
//	int	SrcZ = SrcUI->GetZOrder();
//	int	DestZ = DestUI->GetZOrder();
//
//	if (SrcZ < DestZ)
//		return -1;
//
//	else if (SrcZ > DestZ)
//		return 1;
//
//	return 0;
//}

bool CWidgetWindow::SortZOrder(CSharedPtr<CWidget> Src, 
	CSharedPtr<CWidget> Dest)
{
	int	SrcZ = Src->GetZOrder();
	int	DestZ = Dest->GetZOrder();

	return SrcZ < DestZ;
}
