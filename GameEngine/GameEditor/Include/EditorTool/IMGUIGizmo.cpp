#include "../pch.h"
#include "IMGUIGizmo.h"
#include "Gizmo/ImApp.h"

#include "Gizmo/ImGuizmo.h"
#include "Gizmo/ImSequencer.h"
#include "Gizmo/ImCurveEdit.h"
#include "Gizmo/GraphEditor.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "Component/Camera.h"
#include "Scene/CameraManager.h"
#include "Device.h"
#include "Engine.h"
#include "../EditorComponent/IMGUIGizmoComponent.h"
static ImGuizmo::OPERATION mCurrentGizmoOperation(ImGuizmo::TRANSLATE);
static const float identityMatrix[16] =
{ -1.f, 0.f, 0.f, 0.f,
	0.f, -1.f, 0.f, 0.f,
	0.f, 0.f, -1.f, 0.f,
	0.f, 0.f, 0.f, -1.f };

CIMGUIGizmo::CIMGUIGizmo():
	m_Scene(nullptr),
	m_GizmoComponent(nullptr)
{
}

CIMGUIGizmo::~CIMGUIGizmo()
{
}

bool CIMGUIGizmo::Init()
{


	return true;
}

void CIMGUIGizmo::Render()
{
	if (m_Scene == nullptr)
		return;
	CCamera* Camera = m_Scene->GetCameraManager()->GetCurrentCamera();
	if (nullptr == Camera)
		return;
	ImGuizmo::BeginFrame();

	Matrix ViewMatrix = Camera->GetViewMatrix();
	Matrix ViewProjection = Camera->GetProjMatrix();
	float* cameraView = &ViewMatrix[0][0];


	float* cameraProjection = &ViewProjection[0][0];

	ImGuizmo::SetOrthographic(false);

	ImGuiIO& io = ImGui::GetIO();
	ImGuizmo::SetID(0);


	EditTransform(cameraView, cameraProjection, true);


}

bool CIMGUIGizmo::IsUsing()
{
	return ImGuizmo::IsUsing();
}

void CIMGUIGizmo::GizmoStart(class CScene* Scene)
{
	m_Scene = Scene;

}

void CIMGUIGizmo::EditTransform(float* cameraView, float* cameraProjection, bool editTransformDecomposition)
{
	static ImGuizmo::MODE mCurrentGizmoMode(ImGuizmo::WORLD);
	static bool useSnap = false;
	static float snap[3] = { 1.f, 1.f, 1.f };
	static float bounds[] = { -0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f };
	static float boundsSnap[] = { 0.1f, 0.1f, 0.1f };
	static bool boundSizing = false;
	static bool boundSizingSnap = false;

	ImGuiIO& io = ImGui::GetIO();

	Resolution RS=CDevice::GetInst()->GetResolution();
	HWND hWnd=CEngine::GetInst()->GetHwnd();
	RECT Rect = {};
	::GetWindowRect(hWnd, &Rect);

	ImGuizmo::SetRect((float)Rect.left, (float)Rect.top, (float)Rect.right- (float)Rect.left, (float)Rect.bottom- (float)Rect.top);

	if (m_GizmoComponent != nullptr)
	{
		Vector3 Pos = m_GizmoComponent->GetPosition();
		Vector3 Rotation = m_GizmoComponent->GetRotation();
		Vector3 Scale = m_GizmoComponent->GetScale();
		Matrix matrix;
		ImGuizmo::RecomposeMatrixFromComponents(&Pos[0], &Rotation[0], &Scale[0], &matrix[0][0]);
		ImGuizmo::Manipulate(cameraView, cameraProjection, mCurrentGizmoOperation, mCurrentGizmoMode, &matrix[0][0], NULL, useSnap ? &snap[0] : NULL, boundSizing ? bounds : NULL, boundSizingSnap ? boundsSnap : NULL);

		if (ImGuizmo::IsUsing())
		{
			ImGuizmo::DecomposeMatrixToComponents(&matrix[0][0], &Pos[0], &Rotation[0], &Scale[0]);
			//이동은 Pos만 World적용되게 입력
			m_GizmoComponent->SetPosition(Pos);
			m_GizmoComponent->SetRotation(Rotation);
			m_GizmoComponent->SetScale(Scale);
		}
	}

}
void CIMGUIGizmo::SetCurrentGizmoOperation(int Option)
{
	switch (Option)
	{
	case 0:
	{
		mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
			break;
	}
	case 1:
	{
		mCurrentGizmoOperation = ImGuizmo::ROTATE;
		break;
	}
	case 2:
	{
		mCurrentGizmoOperation = ImGuizmo::SCALE;
		break;
	}
	case 3:
	{
		mCurrentGizmoOperation = ImGuizmo::UNIVERSAL;
		break;
	}
	}
}



