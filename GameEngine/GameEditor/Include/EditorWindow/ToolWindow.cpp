
#include "../pch.h"
#include "ToolWindow.h"
#include "../EditorComponent/IMGUIGizmoComponent.h"
#include "../EditorComponent/IMGUICurCameraComponent.h"
#include "../EditorComponent/IMGUIRenderOptionComponent.h"


CToolWindow::CToolWindow():
	m_GizmoComponent(nullptr),
	m_CurCameraComponent(nullptr),
	m_RenderOptionComponent(nullptr)
{
}

CToolWindow::~CToolWindow()
{
	SAFE_DELETE(m_GizmoComponent);
	SAFE_DELETE(m_CurCameraComponent);
	SAFE_DELETE(m_RenderOptionComponent);
}

bool CToolWindow::Init()
{
	CreateGizmoComponent();
	CreateCameraComponent();
	CreateRenderOptionComponent();
	m_GizmoComponent->Enable(true);
	m_CurCameraComponent->Enable(true);
	m_RenderOptionComponent->Enable(true);
	return true;
}

void CToolWindow::Update(float DeltaTime)
{
	CIMGUIWindow::Update(DeltaTime);
	m_CurCameraComponent->Update(DeltaTime);
}

void CToolWindow::GizmoComponentUpdate(CSceneComponent* Component)
{
	m_GizmoComponent->SetComponent(Component);
	m_GizmoComponent->Enable(true);
}
void CToolWindow::CreateGizmoComponent()
{
	if (m_GizmoComponent)
		return;
	m_GizmoComponent = new CIMGUIGizmoComponent;
	m_GizmoComponent->SetOwner(this);
	m_GizmoComponent->Init();
}

void CToolWindow::CreateCameraComponent()
{
	if (m_CurCameraComponent)
		return;
	m_CurCameraComponent = new CIMGUICurCameraComponent;
	m_CurCameraComponent->SetOwner(this);
	m_CurCameraComponent->Init();
}

void CToolWindow::CreateRenderOptionComponent()
{
	if (m_RenderOptionComponent)
		return;
	m_RenderOptionComponent = new CIMGUIRenderOptionComponent;
	m_RenderOptionComponent->SetOwner(this);
	m_RenderOptionComponent->Init();
}


void CToolWindow::AllComponentClose()
{
	m_GizmoComponent->Enable(false);
}

